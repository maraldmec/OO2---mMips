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
 
#ifndef HAZARD_H_INCLUDED
#define HAZARD_H_INCLUDED

#include "mips.h"

SC_MODULE(HAZARD) {
	sc_in<  sc_bv<1> > 				    enable;

	sc_in< 	sc_bv<W_REGWRITE> >			MEMWBRegWrite;
	sc_in< 	sc_bv<W_REGWRITE> >			EXMEMRegWrite;
	sc_in< 	sc_bv<W_REGWRITE> >			IDEXRegWrite;
	sc_in< 	sc_bv<W_REGDST> >			IDEXRegDst;
	sc_in< 	sc_bv<AWORDREG> >			IDEXWriteRegisterRt;
	sc_in< 	sc_bv<AWORDREG> >			IDEXWriteRegisterRd;
	sc_in< 	sc_bv<AWORDREG> >			EXMEMWriteRegister;
	sc_in< 	sc_bv<AWORDREG> >			MEMWBWriteRegister;
	sc_in< 	sc_bv<DWORD> >				Instr;
	sc_in<	sc_bv<W_BRANCHOP> >			BranchOp;
	sc_in< sc_bv<W_MEMREAD>		> MEM_EX_READ;
	sc_in< sc_bv<W_MEMREAD>		> MEM_ID_READ;

	sc_in< bool >                       dmem_wait, imem_wait;

	sc_out<	sc_bv<W_PCWRITEFLAG> >		PCWrite;
	sc_out<	sc_bv<W_IFIDWRITEFLAG> >	IFIDWrite;
	sc_out< sc_bv<W_HAZARDFLAG> >		Hazard;
	sc_out< sc_bv<2> >					Ex_fw1;
	sc_out< sc_bv<2> >					Ex_fw2;
	sc_out< sc_bv<1> >                  pipe_en, imem_en;
	
	void hazard();
	
	// Constructor
	SC_CTOR(HAZARD) {
		SC_METHOD(hazard);
		sensitive << MEMWBRegWrite << EXMEMRegWrite << IDEXRegWrite << IDEXRegDst;
		sensitive << IDEXWriteRegisterRt << IDEXWriteRegisterRd << BranchOp;
		sensitive << EXMEMWriteRegister << MEMWBWriteRegister << Instr 
				  << enable << dmem_wait << imem_wait;
	}
};

SC_MODULE(HAZARD_CTRL) {
	sc_in< sc_bv<W_HAZARDFLAG> >	Hazard;

	// CTRL inputs
	sc_in< sc_bv<W_REGDST> >		CtrlRegDst;
	sc_in< sc_bv<W_REGVAL> >		CtrlRegValue;
	sc_in< sc_bv<W_TARGET> >		CtrlTarget;
	sc_in< sc_bv<W_BRANCHOP> >		CtrlBranch;
	sc_in< sc_bv<W_MEMREAD> >		CtrlMemRead;
	sc_in< sc_bv<W_MEMTOREG> >		CtrlMemtoReg;
	sc_in< sc_bv<W_ALUOP> >			CtrlALUop;
	sc_in< sc_bv<W_MEMWRITE> >		CtrlMemWrite;
	sc_in< sc_bv<W_ALUSRC> >		CtrlALUSrc;
	sc_in< sc_bv<W_REGWRITE> >		CtrlRegWrite;
    sc_in< sc_bv<W_HILO_W> >        CtrlHiLoWrite;
    sc_in< sc_bv<W_HILOALU_S> >     CtrlHiLoAluSel;

	// CTRL outputs after hazard handling
	sc_out< sc_bv<W_REGDST> >		RegDst;
	sc_out< sc_bv<W_REGVAL> >		RegValue;
	sc_out< sc_bv<W_TARGET> >		Target;
	sc_out< sc_bv<W_BRANCHOP> >		Branch;
	sc_out< sc_bv<W_MEMREAD> >		MemRead;
	sc_out< sc_bv<W_MEMTOREG> >		MemtoReg;
	sc_out< sc_bv<W_ALUOP> >		ALUop;
	sc_out< sc_bv<W_MEMWRITE> >		MemWrite;
	sc_out< sc_bv<W_ALUSRC> >		ALUSrc;
	sc_out< sc_bv<W_REGWRITE> >		RegWrite;
    sc_out< sc_bv<W_HILO_W> >       HiLoWrite;
    sc_out< sc_bv<W_HILOALU_S> >    HiLoAluSel;
	
	void hazard_ctrl();
	
	// Constructor
	SC_CTOR(HAZARD_CTRL) {
		SC_METHOD(hazard_ctrl);
		sensitive << Hazard;
		sensitive << CtrlRegDst << CtrlBranch << CtrlMemRead << CtrlMemtoReg;
		sensitive << CtrlALUop << CtrlMemWrite;
		sensitive << CtrlALUSrc << CtrlRegWrite;
		sensitive << CtrlRegValue << CtrlTarget;
        sensitive << CtrlHiLoWrite << CtrlHiLoAluSel;
	}
};

#endif
