/*
 *  TU Eindhoven
 *  Eindhoven, The Netherlands
 *
 *  Name            :   hazard.h
 *
 *  Author          :   Sander Stuijk (sander@ics.ele.tue.nl)
 *
 *  Date            :   July 23, 2002
 *
 *  Function        :   Hazard detection unit
 *
 *  History         :
 *      23-07-02    :   Initial version.
 *      13-12-02    :   Synthesizable version A.S.Slusarczyk@tue.nl
 *
 */
 
#include "hazard.h"

void HAZARD::hazard()
{
	sc_uint<W_HAZARDFLAG> 	hazard;
	sc_uint<2> 	ex_fw1;
	sc_uint<2> 	ex_fw2;
	sc_uint<W_BRANCHOP> 	branchop;
	sc_uint<W_REGDST> 	idexregdst_t;
	sc_uint<W_REGWRITE>	memwbregwrite_t, exmemregwrite_t, idexregwrite_t;
	sc_uint<AWORDREG> 	idexwriteregisterrt_t, idexwriteregisterrd_t,
				exmemwriteregister_t,memwbwriteregister_t;
	sc_uint<DWORD> 		instr_t;
	sc_uint<AWORDREG> 	ifidreadregister1_t, ifidreadregister2_t;
	sc_uint<W_MEMREAD>	bus_ex_ctrl_mem_memread; 
	sc_uint<W_MEMREAD>	bus_id_ctrl_mem_memread; 
	sc_uint<1>			divide_hazard; 
	#ifdef VERBOSE
		clog << "HAZARD DETECTION UNIT" << endl;
	#endif
	
	// Read input
	memwbregwrite_t = MEMWBRegWrite.read();
	exmemregwrite_t = EXMEMRegWrite.read();
	idexregwrite_t = IDEXRegWrite.read();
	idexregdst_t = IDEXRegDst.read();
	idexwriteregisterrt_t = IDEXWriteRegisterRt.read();
	idexwriteregisterrd_t = IDEXWriteRegisterRd.read();
	exmemwriteregister_t = EXMEMWriteRegister.read();
	memwbwriteregister_t = MEMWBWriteRegister.read();
	bus_ex_ctrl_mem_memread=MEM_EX_READ.read();
	bus_id_ctrl_mem_memread=MEM_ID_READ.read();
	instr_t = Instr.read();
	branchop = BranchOp.read();
	divide_hazard=HAZARD_DIV.read();
	
	// Read registers
	ifidreadregister1_t = instr_t.range(25,21);
	ifidreadregister2_t = instr_t.range(20,16);
			
	// Enable the pipeline and instruction memory
    imem_en.write(1);
    pipe_en.write(1);
	pipe_en_and.write(1);

	//set default values
	ex_fw1 = 0;
	ex_fw2 = 0;
	hazard = 0;

	if (branchop != 0||divide_hazard==0) {
		// (Control) branch hazard
		// Don't fetch a new instruction, insert a 'nop'
		hazard = 1;
	}
	else
	{
		// No hazard
		if (exmemregwrite_t == 1 && bus_ex_ctrl_mem_memread!=0 &&
				(exmemwriteregister_t == ifidreadregister1_t))
			{
				hazard=1;
			}
		else if (exmemregwrite_t == 1 && bus_ex_ctrl_mem_memread!=0 &&
				(exmemwriteregister_t == ifidreadregister2_t))
			{
				hazard=1;
			}
		else if (idexregwrite_t == 1 &&  bus_id_ctrl_mem_memread!=0 &&
				((idexregdst_t == 0 && idexwriteregisterrt_t == ifidreadregister1_t) || 
				(idexregdst_t == 1 && idexwriteregisterrd_t == ifidreadregister1_t)))
			{
				hazard=1;
			} 
		else if (idexregwrite_t == 1 &&  bus_id_ctrl_mem_memread!=0 &&
				((idexregdst_t == 0 && idexwriteregisterrt_t == ifidreadregister2_t) || 
				(idexregdst_t == 1 && idexwriteregisterrd_t == ifidreadregister2_t)))
			{
				hazard=1;
			}
		else
		{

			if (memwbregwrite_t == 1 &&(memwbwriteregister_t == ifidreadregister1_t) )
				{
					ex_fw1=3;
				}
			if (memwbregwrite_t == 1 && (memwbwriteregister_t == ifidreadregister2_t))
				{
					ex_fw2=3;
				}
			if (exmemregwrite_t == 1 &&
					(exmemwriteregister_t == ifidreadregister1_t))
				{
					ex_fw1=2;
				}
			if (exmemregwrite_t == 1 &&
					(exmemwriteregister_t == ifidreadregister2_t))
				{
					ex_fw2=2;
				}
			if (idexregwrite_t == 1 &&
					((idexregdst_t == 0 && idexwriteregisterrt_t == ifidreadregister1_t) || 
					(idexregdst_t == 1 && idexwriteregisterrd_t == ifidreadregister1_t)))
				{
					ex_fw1 = 1;
				} 
			if (idexregwrite_t == 1 &&
					((idexregdst_t == 0 && idexwriteregisterrt_t == ifidreadregister2_t) || 
					(idexregdst_t == 1 && idexwriteregisterrd_t == ifidreadregister2_t)))
				{
					ex_fw2 = 1;
				}
		}
	}


	// Write output
	if( enable.read()[0] == 0 )
    {
		// block writing if not enabled
		PCWrite.write( 0 );
		IFIDWrite.write(0);
		Hazard.write( hazard );
		Ex_fw1.write(ex_fw1);
		Ex_fw2.write(ex_fw2);
        imem_en.write(0);
        pipe_en.write(0);
		pipe_en_and.write(0);
    }
    else if( dmem_wait.read() || imem_wait.read() )
    {
		PCWrite.write( 0 );
		IFIDWrite.write(0);
		Hazard.write( hazard );
		Ex_fw1.write(ex_fw1);
		Ex_fw2.write(ex_fw2);
        if( dmem_wait.read() )
			imem_en.write(0);
        pipe_en.write(0);
		pipe_en_and.write(0);
    }
	else if (hazard)
	{
        // pre-fetch next instruction if it's branch hazard
		PCWrite.write( branchop ? 1 : 0 );
		imem_en.write( branchop ? 1 : 0 );
		IFIDWrite.write(0);
		Hazard.write(1);
		Ex_fw1.write(ex_fw1);
		Ex_fw2.write(ex_fw2);
    }
	else
	{
        // In case this instruction is a branch, fetch the next instruction,
        // but don't change the program counter. The next instruction will
        // namely not be decoded duuring the next cycle. (we will insert a 'nop')
        if (instr_t.range(31,26) == 4 || instr_t.range(31,26) == 5)
        {
            PCWrite.write( 0 );
            imem_en.write( 0 );
        }
        else
        {
            PCWrite.write( 1 );
            imem_en.write( 1 );
        }

        IFIDWrite.write( 1 );
        Hazard.write(0);
		Ex_fw1.write(ex_fw1);
		Ex_fw2.write(ex_fw2);
	}

	if(divide_hazard==0)
	{
		pipe_en_and.write(0);
		//PCWrite.write(0);
		//IFIDWrite.write(0);
	}
		
}

void HAZARD_CTRL::hazard_ctrl()
{
	sc_bv<W_ALUOP> 		aluop;
	sc_bv<W_ALUSRC> 	alusrc;
	sc_bv<W_BRANCHOP> 	branch;
	sc_bv<W_HAZARDFLAG> hazard;
	sc_bv<W_MEMREAD> 	memread;
	sc_bv<W_MEMTOREG> 	memtoreg;
	sc_bv<W_MEMWRITE> 	memwrite;
	sc_bv<W_REGDST> 	regdst;
	sc_bv<W_REGVAL> 	regvalue;
	sc_bv<W_REGWRITE> 	regwrite;
	sc_bv<W_TARGET> 	target;
    sc_bv<W_HILO_W>     hilowrite;
    sc_bv<W_HILOALU_S>  hiloalusel;

	#ifdef VERBOSE
		clog << "HAZARD HANDLING UNIT" << endl;
	#endif

	// Read input
	hazard = Hazard.read();
	regdst = CtrlRegDst.read();
	regvalue = CtrlRegValue.read();
	target = CtrlTarget.read();
	branch = CtrlBranch.read();
	memread = CtrlMemRead.read();
	memtoreg = CtrlMemtoReg.read();
	aluop = CtrlALUop.read();
	memwrite = CtrlMemWrite.read();
	alusrc = CtrlALUSrc.read();
	regwrite = CtrlRegWrite.read();
    hilowrite = CtrlHiLoWrite.read();
    hiloalusel = CtrlHiLoAluSel.read();

	// Write output
	if (sc_uint<W_HAZARDFLAG>(hazard) == 0)
	{
		RegDst.write(regdst);
		RegValue.write(regvalue);
		Target.write(target);
		Branch.write(branch);
		MemRead.write(memread);
		MemtoReg.write(memtoreg);
		ALUop.write(aluop);
		MemWrite.write(memwrite);
		ALUSrc.write(alusrc);
		RegWrite.write(regwrite);
        HiLoWrite.write(hilowrite);
        HiLoAluSel.write(hiloalusel);
	}
	else
	{
		RegDst.write(0);
		RegValue.write(0);
		Target.write(0);
		Branch.write(0);
		MemRead.write(0);
		MemtoReg.write(0);
		ALUop.write(0);
		MemWrite.write(0);
		ALUSrc.write(0);
		RegWrite.write(0);
        HiLoWrite.write(0);
        HiLoAluSel.write(0);
	}
}
