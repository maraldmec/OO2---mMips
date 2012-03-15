/*
*  TU Eindhoven
*  Eindhoven, The Netherlands
*
*  Name            :   mmips.h
*
*  Author          :   A.S.Slusarczyk@tue.nl
*
*  Date            :   
*
*  Function        :   Top-level mMIPS module
*/


#ifndef MMIPS_H_INCLUDED
#define MMIPS_H_INCLUDED

#include "add.h"
#include "aluctrl.h"
#include "alu.h"
#include "branch.h"
#include "ctrl.h"
#include "decoder.h"
#include "hazard.h"
#include "imm2word.h"
#include "mux.h"
#include "register.h"
#include "shift.h"
#include "signextend.h"

#include "bregisterfile16.h"
#include "memdev.h"

SC_MODULE(mMIPS)
{
	sc_in<bool> clk;
	sc_in<bool> enable;
	sc_in<bool> rst;

	// Instruction memory
	sc_in< sc_bv<DWORD> >            rom_dout;
	sc_in< bool >                    rom_wait;
	sc_out< sc_bv<DWORD> >           rom_addr;
	sc_out< sc_bv<1> >               rom_r;

	// Data memory
	sc_in< sc_bv<DWORD> >            ram_dout;
	sc_in< bool >                    ram_wait;
	sc_out< sc_bv<DWORD> >           ram_din;
	sc_out< sc_bv<DWORD> >           ram_addr;
	sc_out< sc_bv<W_MEMREAD> >       ram_r;
	sc_out< sc_bv<W_MEMWRITE> >      ram_w;

	// memory-mapped-device infrostructure
	sc_out< sc_bv<DWORD> > dev_dout;
	sc_in< sc_bv<DWORD> > dev_din;
	sc_out< bool > dev_r, dev_w;
	sc_in< bool > dev_rdyr, dev_rdyw;
	sc_out< bool > dev_wdata, dev_waddr;
	sc_out<bool> dev_send_eop;
	sc_in<bool> dev_rcv_eop;

	/*
	*	SIGNALS
	*/

	// constants
	sc_signal< sc_bv<1> >		     GND, VCC;

	// Wait signals from instruction and data memory
	sc_signal< bool >                 bus_dmem_wait;
	sc_signal< sc_bv<DWORD>			> bus_pc;

	// Data signals
	sc_signal< sc_bv<DWORD> 		> bus_mux2;
	sc_signal< sc_bv<DWORD> 		> bus_mux3;
	sc_signal< sc_bv<AWORDREG>		> bus_mux4;
	sc_signal< sc_bv<DWORD> 		> bus_mux5;
	sc_signal< sc_bv<DWORD> 		> bus_mux6;
	sc_signal< sc_bv<DWORD> 		> bus_mux8;
	sc_signal< sc_bv<DWORD> 		> bus_mux9;
	sc_signal< sc_bv<DWORD> 		> bus_mux10;

	sc_signal< sc_bv<6> 			> bus_decoder_instr_31_26;
	sc_signal< sc_bv<DWORD> 		> bus_decoder_instr_25_0;
	sc_signal< sc_bv<AWORDREG> 		> bus_decoder_instr_20_16;
	sc_signal< sc_bv<AWORDREG> 		> bus_decoder_instr_15_11;
	sc_signal< sc_bv<16> 			> bus_decoder_instr_15_0;
	sc_signal< sc_bv<5> 			> bus_decoder_instr_10_6;
	sc_signal< sc_bv<6> 			> bus_decoder_instr_5_0;

	sc_signal< sc_bv<DWORD> 		> bus_add1;
	sc_signal< sc_bv<DWORD> 		> bus_add2;

	sc_signal< sc_bv<DWORD> 		> bus_shiftleft;
	sc_signal< sc_bv<DWORD> 		> bus_shiftleft_jmp;

	sc_signal< sc_bv<DWORD> 		> bus_imm2word;
	sc_signal< sc_bv<DWORD> 		> bus_signextendbyte;

	sc_signal< sc_bv<DWORD> 		> bus_dmem_1;

	sc_signal< sc_bv<DWORD> 		> bus_alu_result;
	sc_signal< sc_bv<DWORD> 		> bus_alu_result_2;
	sc_signal< sc_bv<1> 			> bus_alu_zero;

	sc_signal< sc_bv<DWORD>			> bus_register_hi;
	sc_signal< sc_bv<DWORD>			> bus_register_lo;

	sc_signal< sc_bv<DWORD> 		> bus_d_div;
	sc_signal< sc_bv<1> 		> bus_hazard_div;
	sc_signal< sc_bv<1> 		> bus_test2;
	sc_signal< sc_bv<1> 		> bus_test;
	sc_signal< sc_bv<DWORD> 		> bus_a_out;
	sc_signal< sc_bv<DWORD> 		> bus_b_out;
	sc_signal< sc_bv<DWORD> 		> bus_a_in;
	sc_signal< sc_bv<DWORD> 		> bus_b_in;
	sc_signal< sc_bv<6> 		> bus_iti_div;
	sc_signal< sc_bv<6> 		> bus_ito_div;

	sc_signal< sc_bv<DWORD> 		> bus_registers_1;
	sc_signal< sc_bv<DWORD> 		> bus_registers_2;

	// Control signals
	sc_signal< sc_bv<W_REGDST>		> bus_ctrl_regdst;
	sc_signal< sc_bv<W_REGVAL>		> bus_ctrl_regvalue;
	sc_signal< sc_bv<W_TARGET>		> bus_ctrl_target;
	sc_signal< sc_bv<W_BRANCHOP>	> bus_ctrl_branch;
	sc_signal< sc_bv<W_MEMREAD>		> bus_ctrl_memread;
	sc_signal< sc_bv<W_MEMTOREG>	> bus_ctrl_memtoreg;
	sc_signal< sc_bv<W_ALUOP>		> bus_ctrl_aluop;
	sc_signal< sc_bv<W_MEMWRITE>	> bus_ctrl_memwrite;
	sc_signal< sc_bv<W_ALUSRC>		> bus_ctrl_alusrc;
	sc_signal< sc_bv<W_REGWRITE>	> bus_ctrl_regwrite;
	sc_signal< sc_bv<W_SIGNEXTEND>  > bus_ctrl_signextend;   
	sc_signal< sc_bv<DWORD>			> bus_ctrl_c4;
	sc_signal< sc_bv<1>				> bus_ctrl_c1;
	sc_signal< sc_bv<AWORDREG>		> bus_ctrl_c31;
	sc_signal< sc_bv<1>				> bus_ctrl_enable;
	sc_signal< sc_bv<W_HILO_W>      > bus_ctrl_hilo_write;
	sc_signal< sc_bv<W_HILOALU_S>   > bus_ctrl_hiloalu_sel;
	
	//
	sc_signal< sc_bv<2>				> bus_ex_fw1_select;
	sc_signal< sc_bv<2>				> bus_ex_fw2_select;

	sc_signal< sc_bv<1>				> bus_pipe_en;
	sc_signal< sc_bv<1>				> bus_pipe_en_and;

	sc_signal< sc_bv<W_ALUCTRL>		> bus_aluctrl;
	sc_signal< sc_bv<W_ALUCTRL>		> bus_reg_aluctrl;

	sc_signal< sc_bv<W_BRANCHFLAG>	> bus_branch_ctrl;

	sc_signal< sc_bv<AWORDREG>		> bus_decoder_nb_instr_25_21;
	sc_signal< sc_bv<AWORDREG>		> bus_decoder_nb_instr_20_16;
	sc_signal< sc_bv<DWORD>			> bus_mux7;

	// Signals needed for pipelining
	// Instruction fecth -> Instruction decode
	sc_signal< sc_bv<DWORD>			> bus_if_pc; 
	sc_signal< sc_bv<DWORD>			> bus_if_instr; 

	// Instruction decode -> Execution
	sc_signal< sc_bv<DWORD>			> bus_id_pc; 
	sc_signal< sc_bv<DWORD> 		> bus_id_data_reg1; 
	sc_signal< sc_bv<DWORD> 		> bus_reg_mux2; 
	sc_signal< sc_bv<DWORD>			> bus_id_data_reg2; 
	sc_signal< sc_bv<DWORD>			> bus_id_immediate; 
	sc_signal< sc_bv<DWORD> 		> bus_id_instr_25_0; 
	sc_signal< sc_bv<AWORDREG> 		> bus_id_instr_20_16; 
	sc_signal< sc_bv<AWORDREG> 		> bus_id_instr_15_11;  
	//sc_signal< sc_bv<W_ALUOP> 		> bus_id_ctrl_ex_aluop; 
	sc_signal< sc_bv<W_REGDST>		> bus_id_ctrl_ex_regdst; 
	sc_signal< sc_bv<W_REGVAL>		> bus_id_ctrl_ex_regvalue; 
	sc_signal< sc_bv<W_TARGET>		> bus_id_ctrl_ex_target; 
	sc_signal< sc_bv<W_BRANCHOP> 	> bus_id_ctrl_mem_branch; 
	sc_signal< sc_bv<W_MEMWRITE> 	> bus_id_ctrl_mem_memwrite; 
	sc_signal< sc_bv<W_MEMREAD>		> bus_id_ctrl_mem_memread; 
	sc_signal< sc_bv<W_MEMREAD>		> bus_ex_ctrl_mem_memread; 
	sc_signal< sc_bv<W_REGWRITE> 	> bus_id_ctrl_wb_regwrite; 
	sc_signal< sc_bv<W_MEMTOREG> 	> bus_id_ctrl_wb_memtoreg; 
	sc_signal< sc_bv<W_HILO_W>      > bus_id_ctrl_ex_hilo_write;
	sc_signal< sc_bv<W_HILOALU_S>   > bus_id_ctrl_ex_hiloalu_sel;


	// Execution -> Memory stage
	sc_signal< sc_bv<AWORDREG>		> bus_ex_regdst_addr;
	sc_signal< sc_bv<DWORD>			> bus_ex_alu_result;
	sc_signal< sc_bv<W_REGWRITE>	> bus_ex_ctrl_wb_regwrite;
	sc_signal< sc_bv<W_MEMTOREG>	> bus_ex_ctrl_wb_memtoreg;

	// Memory stage -> Write back stage
	sc_signal< sc_bv<DWORD>			> bus_mem_dmem_data;
	sc_signal< sc_bv<DWORD>			> bus_mem_alu_result;
	sc_signal< sc_bv<AWORDREG>		> bus_mem_regdst_addr;
	sc_signal< sc_bv<W_REGWRITE> 	> bus_mem_ctrl_wb_regwrite;
	sc_signal< sc_bv<W_MEMTOREG> 	> bus_mem_ctrl_wb_memtoreg;

	// Hazard detection unit
	sc_signal< sc_bv<W_PCWRITEFLAG> > bus_hazard_pcwrite;
	sc_signal< sc_bv<W_IFIDWRITEFLAG> > bus_hazard_ifidwrite;
	sc_signal< sc_bv<W_HAZARDFLAG>	> bus_hazard_hazard;

	sc_signal< sc_bv<W_REGDST>		> bus_ctrl2hazard_regdst;
	sc_signal< sc_bv<W_REGVAL>		> bus_ctrl2hazard_regvalue;
	sc_signal< sc_bv<W_TARGET>		> bus_ctrl2hazard_target;
	sc_signal< sc_bv<W_BRANCHOP> 	> bus_ctrl2hazard_branch;
	sc_signal< sc_bv<W_MEMREAD>		> bus_ctrl2hazard_memread;
	sc_signal< sc_bv<W_MEMTOREG>	> bus_ctrl2hazard_memtoreg;
	sc_signal< sc_bv<W_ALUOP>		> bus_ctrl2hazard_aluop;
	sc_signal< sc_bv<W_MEMWRITE>	> bus_ctrl2hazard_memwrite;
	sc_signal< sc_bv<W_ALUSRC>		> bus_ctrl2hazard_alusrc;
	sc_signal< sc_bv<W_REGWRITE>	> bus_ctrl2hazard_regwrite;

	sc_signal< sc_bv<W_HILO_W>		> bus_ctrl2hazard_hilo_write;
	sc_signal< sc_bv<W_HILOALU_S>	> bus_ctrl2hazard_hiloalu_sel;

	/*
	*	MODULES
	*/
	// Pipeline registers
	// Instruction fecth - Instruction decode
	REGISTER_DWORD		        *if_pc;
	REGISTER_DWORD		        *if_instr;

	// Instruction decode - Execution
	REGISTER_DWORD		        *id_pc;
	REGISTER_DWORD		        *id_data_reg1;

	REGISTER_DWORD		        *reg_mux2;
	REGISTER_6			        *reg_aluctrl;

	REGISTER_DWORD		        *id_data_reg2;
	REGISTER_DWORD		        *id_immediate;
	REGISTER_DWORD		        *id_instr_25_0;
	REGISTER_AWORDREG	        *id_instr_20_16;
	REGISTER_AWORDREG	        *id_instr_15_11;
	REGISTER_W_REGDST	        *id_ctrl_ex_regdst;
	REGISTER_W_REGVAL	        *id_ctrl_ex_regvalue;
	REGISTER_W_TARGET	        *id_ctrl_ex_target;
	REGISTER_W_BRANCHOP         *id_ctrl_mem_branch;
	REGISTER_W_MEMWRITE         *id_ctrl_mem_memwrite;
	REGISTER_W_MEMREAD	        *id_ctrl_mem_memread;
	REGISTER_W_REGWRITE         *id_ctrl_wb_regwrite;
	REGISTER_W_MEMTOREG         *id_ctrl_wb_memtoreg;
	REGISTER_W_HILO_W           *id_ctrl_ex_hilo_write;
	REGISTER_W_HILOALU_S        *id_ctrl_ex_hiloalu_sel;

	// Execution - Memory stage
	REGISTER_AWORDREG	        *ex_regdst_addr;
	REGISTER_DWORD		        *ex_alu_result;
	REGISTER_W_REGWRITE         *ex_ctrl_wb_regwrite;
	REGISTER_W_MEMTOREG         *ex_ctrl_wb_memtoreg;
	REGISTER_W_MEMREAD	        *ex_ctrl_memread;

	// Memory stage - Write back stage
	REGISTER_DWORD		        *mem_dmem_data;
	REGISTER_DWORD		        *mem_alu_result;
	REGISTER_AWORDREG	        *mem_regdst_addr;
	REGISTER_W_REGWRITE         *mem_ctrl_wb_regwrite;
	REGISTER_W_MEMTOREG         *mem_ctrl_wb_memtoreg;


	// program counter
	REGISTER_DWORD	            *pc;

	// Hi/lo registers
	REGISTER_DWORD              *hi;
	REGISTER_DWORD              *lo;
	REGISTER_DWORD              *d_div;
	REGISTER_6             *it_div;

	// Hazard handling
	HAZARD						*hazard;
	HAZARD_CTRL			        *hazard_ctrl;

	// Branch handling
	BRANCH_CTRL		            *branch_ctrl;

	// Modules used for computation
	ADD							*add1;
	ADD							*add2;

	REGFILE16			        *registers;

	ALU							*alu;
	ALUCTRL						*aluctrl;

	IMM2WORD		            *imm2word;

	SIGNEXTEND_BYTE	            *signextendbyte;

	SHIFTLEFT		            *shiftleft;
	SHIFTLEFT		            *shiftleft_jmp;

	CTRL			            *ctrl;

	DECODER						*decoder;

	DECODER_NBUF                *decoder_nb;

	MUX2						*mux1;
	MUX2						*mux2;
	MUX3						*mux3;
	MUX3_AWORDREG				*mux4;
	MUX3						*mux5;
	MUX2						*mux6;
	MUX2                        *mux7;
	MUX3						*mux8;
	MUX4                        *mux9;
	MUX4						*mux10;

	// memory-mapped-device infrostructure
	MEMDEV *memdev;

	SC_CTOR(mMIPS){
		GND = 0;
		VCC = 1;

		if_pc = new REGISTER_DWORD("IF_pc");
		if_instr = new REGISTER_DWORD("IF_instr"); 
		id_pc = new REGISTER_DWORD("ID_pc"); 
		id_data_reg1 = new REGISTER_DWORD("ID_data_reg1"); 
		reg_mux2 = new REGISTER_DWORD("bus_reg_mux2");
		reg_aluctrl = new REGISTER_6("bus_reg_aluctrl");
		id_data_reg2 = new REGISTER_DWORD("ID_data_reg2"); 
		id_immediate = new REGISTER_DWORD("ID_immediate"); 
		id_instr_25_0 = new REGISTER_DWORD("ID_instr_25_0"); 
		id_instr_20_16 = new REGISTER_AWORDREG("ID_instr_20_16"); 
		id_instr_15_11 = new REGISTER_AWORDREG("ID_instr_15_11");  
		id_ctrl_ex_regdst = new REGISTER_W_REGDST("ID_ctrl_ex_regdst"); 
		id_ctrl_ex_regvalue = new REGISTER_W_REGVAL("ID_ctrl_ex_regvalue"); 
		id_ctrl_ex_target = new REGISTER_W_TARGET("ID_ctrl_ex_target"); 
		id_ctrl_ex_hilo_write = new REGISTER_W_HILO_W("ID_ctrl_ex_hilo_write");
		id_ctrl_ex_hiloalu_sel = new REGISTER_W_HILOALU_S("ID_ctrl_ex_hiloalu_sel");
		id_ctrl_mem_branch = new REGISTER_W_BRANCHOP("ID_ctrl_mem_branch"); 
		id_ctrl_mem_memwrite = new REGISTER_W_MEMWRITE("ID_ctrl_mem_memwrite"); 
		id_ctrl_mem_memread = new REGISTER_W_MEMREAD("ID_ctrl_mem_memread"); 
		id_ctrl_wb_regwrite = new REGISTER_W_REGWRITE("ID_ctrl_wb_regwrite"); 
		id_ctrl_wb_memtoreg = new REGISTER_W_MEMTOREG("ID_ctrl_wb_memtoreg"); 
		ex_regdst_addr = new REGISTER_AWORDREG("EX_regdst_addr"); 
		ex_alu_result = new REGISTER_DWORD("EX_alu_result"); 
		ex_ctrl_memread = new REGISTER_W_MEMREAD("EX_ctrl_memread");
		ex_ctrl_wb_regwrite = new REGISTER_W_REGWRITE("EX_ctrl_wb_regwrite"); 
		ex_ctrl_wb_memtoreg = new REGISTER_W_MEMTOREG("EX_ctrl_wb_memtoreg"); 
		mem_dmem_data = new REGISTER_DWORD("MEM_dmem_data"); 
		mem_alu_result = new REGISTER_DWORD("MEM_alu_result"); 
		mem_regdst_addr = new REGISTER_AWORDREG("MEM_regdst_addr"); 
		mem_ctrl_wb_regwrite = new REGISTER_W_REGWRITE("MEM_ctrl_wb_regwrite"); 
		mem_ctrl_wb_memtoreg = new REGISTER_W_MEMTOREG("MEM_ctrl_wb_memtoreg"); 

		pc = new REGISTER_DWORD("pc");						

		hi = new REGISTER_DWORD("hi");
		lo = new REGISTER_DWORD("lo");
		d_div = new REGISTER_DWORD("d_div");
		it_div = new REGISTER_6("it_div");

		hazard = new HAZARD("hazard"); 			
		hazard_ctrl = new HAZARD_CTRL("hazard_ctrl"); 
		branch_ctrl = new BRANCH_CTRL("branch_ctrl");

		add1 = new ADD("add1");
		add2 = new ADD("add2");	

		registers = new REGFILE16("registers");	
		alu = new ALU("alu");
		aluctrl = new ALUCTRL("aluctrl");	
		imm2word = new IMM2WORD("imm2word");
		signextendbyte = new SIGNEXTEND_BYTE("signextendbyte");
		shiftleft = new SHIFTLEFT("shiftleft");
		shiftleft_jmp = new SHIFTLEFT("shiftleft_jmp");
		ctrl = new CTRL("ctrl");
		decoder = new DECODER("decoder");

		mux7 = new MUX2("mux7");
		decoder_nb = new DECODER_NBUF("decoder_nb");

		mux1 = new MUX2("mux1");
		mux2 = new MUX2("mux2");
		mux3 = new MUX3("mux3");
		mux4 = new MUX3_AWORDREG("mux4");
		mux5 = new MUX3("mux5");
		mux6 = new MUX2("mux6");
		mux8 = new MUX3("mux8");
		mux9 = new MUX4("mux9");
		mux10 = new MUX4("mux10");

		/*
		*	Connections
		*/
		// Hazard detection unit
		hazard->MEMWBRegWrite(bus_mem_ctrl_wb_regwrite);
		hazard->EXMEMRegWrite(bus_ex_ctrl_wb_regwrite);
		hazard->IDEXRegWrite(bus_id_ctrl_wb_regwrite);
		hazard->IDEXRegDst(bus_id_ctrl_ex_regdst);
		hazard->IDEXWriteRegisterRt(bus_id_instr_20_16);
		hazard->IDEXWriteRegisterRd(bus_id_instr_15_11);
		hazard->EXMEMWriteRegister(bus_ex_regdst_addr);
		hazard->MEMWBWriteRegister(bus_mem_regdst_addr);
		hazard->Instr(bus_if_instr);
		hazard->BranchOp(bus_id_ctrl_mem_branch);
		hazard->PCWrite(bus_hazard_pcwrite);
		hazard->IFIDWrite(bus_hazard_ifidwrite);
		hazard->Hazard(bus_hazard_hazard);
		hazard->enable(bus_ctrl_enable);
		hazard->dmem_wait(bus_dmem_wait);
		hazard->imem_wait(rom_wait);
		hazard->imem_en(rom_r);
		hazard->pipe_en(bus_pipe_en);
		hazard->pipe_en_and(bus_pipe_en_and);
		hazard->Ex_fw1(bus_ex_fw1_select);
		hazard->Ex_fw2(bus_ex_fw2_select);
		hazard->MEM_EX_READ(bus_ex_ctrl_mem_memread);
		hazard->MEM_ID_READ(bus_id_ctrl_mem_memread);
		hazard->HAZARD_DIV(bus_hazard_div);


		// Hazard handling unit
		hazard_ctrl->Hazard(bus_hazard_hazard);
		hazard_ctrl->CtrlRegDst(bus_ctrl2hazard_regdst);
		hazard_ctrl->CtrlRegValue(bus_ctrl2hazard_regvalue);
		hazard_ctrl->CtrlTarget(bus_ctrl2hazard_target);
		hazard_ctrl->CtrlBranch(bus_ctrl2hazard_branch);
		hazard_ctrl->CtrlMemRead(bus_ctrl2hazard_memread);
		hazard_ctrl->CtrlMemtoReg(bus_ctrl2hazard_memtoreg);
		hazard_ctrl->CtrlALUop(bus_ctrl2hazard_aluop);
		hazard_ctrl->CtrlMemWrite(bus_ctrl2hazard_memwrite);
		hazard_ctrl->CtrlALUSrc(bus_ctrl2hazard_alusrc);
		hazard_ctrl->CtrlRegWrite(bus_ctrl2hazard_regwrite);
		hazard_ctrl->CtrlHiLoWrite(bus_ctrl2hazard_hilo_write);
		hazard_ctrl->CtrlHiLoAluSel(bus_ctrl2hazard_hiloalu_sel);
		hazard_ctrl->RegDst(bus_ctrl_regdst);
		hazard_ctrl->RegValue(bus_ctrl_regvalue);
		hazard_ctrl->Target(bus_ctrl_target);
		hazard_ctrl->Branch(bus_ctrl_branch);
		hazard_ctrl->MemRead(bus_ctrl_memread);
		hazard_ctrl->MemtoReg(bus_ctrl_memtoreg);
		hazard_ctrl->ALUop(bus_ctrl_aluop);
		hazard_ctrl->MemWrite(bus_ctrl_memwrite);
		hazard_ctrl->ALUSrc(bus_ctrl_alusrc);
		hazard_ctrl->RegWrite(bus_ctrl_regwrite);
		hazard_ctrl->HiLoWrite(bus_ctrl_hilo_write);
		hazard_ctrl->HiLoAluSel(bus_ctrl_hiloalu_sel);

		// Pipeline registers
		// Instruction fecth -> Instruction decode
		if_pc->in(bus_add1);
		if_pc->out(bus_if_pc);
		if_pc->w(bus_hazard_ifidwrite);
		if_pc->clk(clk);
		if_pc->rst(rst);

		if_instr->in(rom_dout);
		if_instr->out(bus_if_instr);
		if_instr->w(bus_hazard_ifidwrite);
		if_instr->clk(clk);
		if_instr->rst(rst);

		// Instruction decode -> Execution
		id_pc->in(bus_if_pc);
		id_pc->out(bus_id_pc);
		id_pc->w(bus_pipe_en_and);
		id_pc->clk(clk);
		id_pc->rst(rst);

		id_data_reg1->in(bus_mux9); 
		id_data_reg1->out(bus_id_data_reg1);
		id_data_reg1->w(bus_pipe_en_and);
		id_data_reg1->clk(clk);
		id_data_reg1->rst(rst);

		reg_mux2->in(bus_mux2); 
		reg_mux2->out(bus_reg_mux2);
		reg_mux2->w(bus_pipe_en_and);
		reg_mux2->clk(clk);
		reg_mux2->rst(rst);

		reg_aluctrl->in(bus_aluctrl); 
		reg_aluctrl->out(bus_reg_aluctrl);
		reg_aluctrl->w(bus_pipe_en_and);
		reg_aluctrl->clk(clk);
		reg_aluctrl->rst(rst);

		id_data_reg2->in(bus_mux10); 
		id_data_reg2->out(bus_id_data_reg2);
		id_data_reg2->w(bus_pipe_en_and);
		id_data_reg2->clk(clk);
		id_data_reg2->rst(rst);

		id_immediate->in(bus_imm2word);
		id_immediate->out(bus_id_immediate);
		id_immediate->w(bus_pipe_en_and);
		id_immediate->clk(clk);
		id_immediate->rst(rst);

		id_instr_25_0->in(bus_decoder_instr_25_0);
		id_instr_25_0->out(bus_id_instr_25_0);
		id_instr_25_0->w(bus_pipe_en_and);
		id_instr_25_0->clk(clk);
		id_instr_25_0->rst(rst);

		id_instr_20_16->in(bus_decoder_instr_20_16);
		id_instr_20_16->out(bus_id_instr_20_16);
		id_instr_20_16->w(bus_pipe_en_and);
		id_instr_20_16->clk(clk);
		id_instr_20_16->rst(rst);

		id_instr_15_11->in(bus_decoder_instr_15_11);
		id_instr_15_11->out(bus_id_instr_15_11);
		id_instr_15_11->w(bus_pipe_en_and);
		id_instr_15_11->clk(clk);
		id_instr_15_11->rst(rst);

		id_ctrl_ex_hilo_write->in(bus_ctrl_hilo_write);
		id_ctrl_ex_hilo_write->out(bus_id_ctrl_ex_hilo_write);
		id_ctrl_ex_hilo_write->w(bus_pipe_en_and);
		id_ctrl_ex_hilo_write->clk(clk);
		id_ctrl_ex_hilo_write->rst(rst);

		id_ctrl_ex_hiloalu_sel->in(bus_ctrl_hiloalu_sel);
		id_ctrl_ex_hiloalu_sel->out(bus_id_ctrl_ex_hiloalu_sel);
		id_ctrl_ex_hiloalu_sel->w(bus_pipe_en_and);
		id_ctrl_ex_hiloalu_sel->clk(clk);
		id_ctrl_ex_hiloalu_sel->rst(rst);

		id_ctrl_ex_regdst->in(bus_ctrl_regdst);
		id_ctrl_ex_regdst->out(bus_id_ctrl_ex_regdst);
		id_ctrl_ex_regdst->w(bus_pipe_en_and);
		id_ctrl_ex_regdst->clk(clk);
		id_ctrl_ex_regdst->rst(rst);

		id_ctrl_ex_regvalue->in(bus_ctrl_regvalue);
		id_ctrl_ex_regvalue->out(bus_id_ctrl_ex_regvalue);
		id_ctrl_ex_regvalue->w(bus_pipe_en_and);
		id_ctrl_ex_regvalue->clk(clk);
		id_ctrl_ex_regvalue->rst(rst);

		id_ctrl_ex_target->in(bus_ctrl_target);
		id_ctrl_ex_target->out(bus_id_ctrl_ex_target);
		id_ctrl_ex_target->w(bus_pipe_en_and);
		id_ctrl_ex_target->clk(clk);
		id_ctrl_ex_target->rst(rst);

		id_ctrl_mem_branch->in(bus_ctrl_branch);
		id_ctrl_mem_branch->out(bus_id_ctrl_mem_branch);
		id_ctrl_mem_branch->w(bus_pipe_en_and);
		id_ctrl_mem_branch->clk(clk);
		id_ctrl_mem_branch->rst(rst);

		id_ctrl_mem_memwrite->in(bus_ctrl_memwrite);
		id_ctrl_mem_memwrite->out(bus_id_ctrl_mem_memwrite);
		id_ctrl_mem_memwrite->w(bus_pipe_en_and);
		id_ctrl_mem_memwrite->clk(clk);
		id_ctrl_mem_memwrite->rst(rst);

		id_ctrl_mem_memread->in(bus_ctrl_memread);
		id_ctrl_mem_memread->out(bus_id_ctrl_mem_memread);
		id_ctrl_mem_memread->w(bus_pipe_en_and);
		id_ctrl_mem_memread->clk(clk);
		id_ctrl_mem_memread->rst(rst);

		id_ctrl_wb_regwrite->in(bus_ctrl_regwrite);
		id_ctrl_wb_regwrite->out(bus_id_ctrl_wb_regwrite);
		id_ctrl_wb_regwrite->w(bus_pipe_en_and);
		id_ctrl_wb_regwrite->clk(clk);
		id_ctrl_wb_regwrite->rst(rst);

		id_ctrl_wb_memtoreg->in(bus_ctrl_memtoreg);
		id_ctrl_wb_memtoreg->out(bus_id_ctrl_wb_memtoreg);
		id_ctrl_wb_memtoreg->w(bus_pipe_en_and);
		id_ctrl_wb_memtoreg->clk(clk);
		id_ctrl_wb_memtoreg->rst(rst);

		// Execution -> Memory stage
		ex_regdst_addr->in(bus_mux4);
		ex_regdst_addr->out(bus_ex_regdst_addr);
		ex_regdst_addr->w(bus_pipe_en);
		ex_regdst_addr->clk(clk);
		ex_regdst_addr->rst(rst);

		ex_alu_result->in(bus_mux6);
		ex_alu_result->out(bus_ex_alu_result);
		ex_alu_result->w(bus_pipe_en);
		ex_alu_result->clk(clk);
		ex_alu_result->rst(rst);

		ex_ctrl_wb_regwrite->in(bus_id_ctrl_wb_regwrite);
		ex_ctrl_wb_regwrite->out(bus_ex_ctrl_wb_regwrite);
		ex_ctrl_wb_regwrite->w(bus_pipe_en);
		ex_ctrl_wb_regwrite->clk(clk);
		ex_ctrl_wb_regwrite->rst(rst);

		ex_ctrl_wb_memtoreg->in(bus_id_ctrl_wb_memtoreg);
		ex_ctrl_wb_memtoreg->out(bus_ex_ctrl_wb_memtoreg);
		ex_ctrl_wb_memtoreg->w(bus_pipe_en);
		ex_ctrl_wb_memtoreg->clk(clk);
		ex_ctrl_wb_memtoreg->rst(rst);

		ex_ctrl_memread->in(bus_id_ctrl_mem_memread);
		ex_ctrl_memread->out(bus_ex_ctrl_mem_memread);
		ex_ctrl_memread->w(bus_pipe_en);
		ex_ctrl_memread->clk(clk);
		ex_ctrl_memread->rst(rst);

		// Memory stage -> Write back stage
		mem_dmem_data->in(bus_dmem_1);
		mem_dmem_data->out(bus_mem_dmem_data);
		mem_dmem_data->w(bus_pipe_en);
		mem_dmem_data->clk(clk);
		mem_dmem_data->rst(rst);

		mem_alu_result->in(bus_ex_alu_result);
		mem_alu_result->out(bus_mem_alu_result);
		mem_alu_result->w(bus_pipe_en);
		mem_alu_result->clk(clk);
		mem_alu_result->rst(rst);

		mem_regdst_addr->in(bus_ex_regdst_addr);
		mem_regdst_addr->out(bus_mem_regdst_addr);
		mem_regdst_addr->w(bus_pipe_en);
		mem_regdst_addr->clk(clk);
		mem_regdst_addr->rst(rst);

		mem_ctrl_wb_regwrite->in(bus_ex_ctrl_wb_regwrite);
		mem_ctrl_wb_regwrite->out(bus_mem_ctrl_wb_regwrite);
		mem_ctrl_wb_regwrite->w(bus_pipe_en);
		mem_ctrl_wb_regwrite->clk(clk);
		mem_ctrl_wb_regwrite->rst(rst);

		mem_ctrl_wb_memtoreg->in(bus_ex_ctrl_wb_memtoreg);
		mem_ctrl_wb_memtoreg->out(bus_mem_ctrl_wb_memtoreg);
		mem_ctrl_wb_memtoreg->w(bus_pipe_en);
		mem_ctrl_wb_memtoreg->clk(clk);
		mem_ctrl_wb_memtoreg->rst(rst);

		// Program counter
		pc->in(rom_addr);
		pc->out(bus_pc);
		pc->w(bus_hazard_pcwrite);
		pc->clk(clk);
		pc->rst(rst);

		// Add 1 (PC + 4)
		add1->a(bus_pc);
		add1->b(bus_ctrl_c4);
		add1->r(bus_add1);

		// Add 2 (add1 + shiftleft)
		add2->a(bus_id_pc);
		add2->b(bus_shiftleft);
		add2->r(bus_add2);

		// Shiftleft jump target
		shiftleft_jmp->in(bus_id_instr_25_0);
		shiftleft_jmp->out(bus_shiftleft_jmp);

		// Mux 5 (Select target for branch)
		mux5->in0(bus_add2);
		mux5->in1(bus_shiftleft_jmp);
		mux5->in2(bus_id_data_reg1);
		mux5->sel(bus_id_ctrl_ex_target);
		mux5->out(bus_mux5);

		// Mux 1 (add1 or add2)
		mux1->in0(bus_add1);
		mux1->in1(bus_mux5);
		mux1->sel(bus_branch_ctrl);
		mux1->out(rom_addr);

		// Shift left
		shiftleft->in(bus_id_immediate);
		shiftleft->out(bus_shiftleft);

		// Sign extend
		imm2word->in(bus_decoder_instr_15_0);
		imm2word->signextend(bus_ctrl_signextend);
		imm2word->out(bus_imm2word);

		// Decoder (Select correct part of instruction for registerfile)
		decoder->instr(bus_if_instr);
		decoder->instr_31_26(bus_decoder_instr_31_26);
		decoder->instr_25_0(bus_decoder_instr_25_0);
		decoder->instr_20_16(bus_decoder_instr_20_16);
		decoder->instr_15_11(bus_decoder_instr_15_11);
		decoder->instr_15_0(bus_decoder_instr_15_0);
		decoder->instr_10_6(bus_decoder_instr_10_6);
		decoder->instr_5_0(bus_decoder_instr_5_0);

		// Mux 4 (Select address for write to registerfile)
		mux4->in0(bus_id_instr_20_16);
		mux4->in1(bus_id_instr_15_11);
		mux4->in2(bus_ctrl_c31);
		mux4->sel(bus_id_ctrl_ex_regdst);
		mux4->out(bus_mux4);

		// ALU
		alu->a(bus_id_data_reg1);
		alu->b(bus_reg_mux2);
		alu->d(bus_d_div);
		alu->r(bus_alu_result);
		alu->r2(bus_alu_result_2);
		alu->z(bus_alu_zero);
		alu->ctrl(bus_reg_aluctrl);
		alu->alu_done(bus_hazard_div);
		alu->iin(bus_ito_div);
		alu->iout(bus_iti_div);


		// Hi/lo registers
		hi->in(bus_alu_result_2);
		hi->out(bus_register_hi);
		hi->w(bus_id_ctrl_ex_hilo_write);
		hi->clk(clk);
		hi->rst(rst);
		lo->in(bus_alu_result);
		lo->out(bus_register_lo);
		lo->w(bus_id_ctrl_ex_hilo_write);
		lo->clk(clk);
		lo->rst(rst);

		d_div->in(bus_alu_result);
		d_div->out(bus_d_div);
		d_div->w(bus_pipe_en);
		d_div->clk(clk);
		d_div->rst(rst);

		it_div->in(bus_iti_div);
		it_div->out(bus_ito_div);
		it_div->w(bus_pipe_en);
		it_div->clk(clk);
		it_div->rst(rst);

		// MUX8
		mux8->in0(bus_alu_result);
		mux8->in1(bus_register_lo);
		mux8->in2(bus_register_hi);
		mux8->sel(bus_id_ctrl_ex_hiloalu_sel);
		mux8->out(bus_mux8);

		// MUX 6 (Select value for register / memory write)
		// Can be 'next PC' or 'ALU result/Hi/Lo registers'
		mux6->in0(bus_mux8);
		mux6->in1(bus_if_pc);
		mux6->sel(bus_id_ctrl_ex_regvalue);
		mux6->out(bus_mux6); 

		// Mux 2 (Registerfile or signextend)
		mux2->in0(bus_mux10);
		mux2->in1(bus_imm2word);
		mux2->sel(bus_ctrl_alusrc);
		mux2->out(bus_mux2);

		// Mux 2 (Registerfile or signextend)
		mux9->in0(bus_registers_1);
		mux9->in1(bus_mux6);
		mux9->in2(bus_ex_alu_result);
		mux9->in3(bus_mux3);
		mux9->sel(bus_ex_fw1_select);
		mux9->out(bus_mux9);

		// Mux 2 (Registerfile or signextend)
		mux10->in0(bus_registers_2);
		mux10->in1(bus_mux6);
		mux10->in2(bus_ex_alu_result);
		mux10->in3(bus_mux3);
		mux10->sel(bus_ex_fw2_select);
		mux10->out(bus_mux10);

		// ALU ctrl
		aluctrl->ALUop(bus_ctrl_aluop);
		aluctrl->functionCode(bus_decoder_instr_5_0);
		aluctrl->Shamt(bus_decoder_instr_10_6);
		aluctrl->ALUctrl(bus_aluctrl);
		aluctrl->DIV(bus_hazard_div);

		// Signextend byte
		signextendbyte->in(bus_mem_dmem_data);
		signextendbyte->out(bus_signextendbyte);

		// Mux 3 (ALU result or memory result to register)
		mux3->in0(bus_mem_alu_result);
		mux3->in1(bus_mem_dmem_data);
		mux3->in2(bus_signextendbyte);
		mux3->sel(bus_mem_ctrl_wb_memtoreg);
		mux3->out(bus_mux3);

		// Branch controller
		branch_ctrl->BranchOp(bus_id_ctrl_mem_branch);
		branch_ctrl->AluZero(bus_alu_zero);
		branch_ctrl->Branch(bus_branch_ctrl);

		// Registerfile
		mux7->in0( bus_if_instr );
		mux7->in1( rom_dout );
		mux7->sel( bus_hazard_ifidwrite );
		mux7->out( bus_mux7 );

		decoder_nb->instr( bus_mux7 );
		decoder_nb->instr_25_21( bus_decoder_nb_instr_25_21 );
		decoder_nb->instr_20_16( bus_decoder_nb_instr_20_16 );

		registers->r_addr_reg1(bus_decoder_nb_instr_25_21);
		registers->r_addr_reg2(bus_decoder_nb_instr_20_16);
		registers->w_addr_reg(bus_mem_regdst_addr);
		registers->r_data_reg1(bus_registers_1);
		registers->r_data_reg2(bus_registers_2);
		registers->w_data_reg(bus_mux3);
		registers->w(bus_mem_ctrl_wb_regwrite);
		registers->clk(clk);

		// memory-mapped device and the wrapper
		memdev = new MEMDEV("memdev");

		memdev->clk(clk);
		memdev->a_read(bus_mux6);
		memdev->a_read_reg(bus_ex_alu_result);
		memdev->d_write(bus_id_data_reg2);
		memdev->r(bus_id_ctrl_mem_memread);
		memdev->w(bus_id_ctrl_mem_memwrite);
		memdev->d_read(bus_dmem_1);

		memdev->ram_dout(ram_dout);
		memdev->ram_wait(ram_wait);
		memdev->ram_addr(ram_addr);
		memdev->ram_din(ram_din);
		memdev->ram_w(ram_w);
		memdev->ram_r(ram_r);

		memdev->dev_dout( dev_din );
		memdev->dev_din( dev_dout );
		memdev->dev_w( dev_w );
		memdev->dev_r( dev_r );
		memdev->dev_wdata( dev_wdata );
		memdev->dev_waddr( dev_waddr );
		memdev->dev_send_eop( dev_send_eop );
		memdev->dev_rcv_eop( dev_rcv_eop );

		memdev->dev_rdyr( dev_rdyr );
		memdev->dev_rdyw( dev_rdyw );
		memdev->dmem_wait( bus_dmem_wait );

		// Controller
		ctrl->FunctionCode(bus_decoder_instr_5_0);
		ctrl->Opcode(bus_decoder_instr_31_26);
		ctrl->ALUop(bus_ctrl2hazard_aluop);
		ctrl->ALUSrc(bus_ctrl2hazard_alusrc);
		ctrl->Branch(bus_ctrl2hazard_branch);
		ctrl->c1(bus_ctrl_c1);
		ctrl->en(bus_ctrl_enable);
		ctrl->c31(bus_ctrl_c31);
		ctrl->c4(bus_ctrl_c4);
		ctrl->MemRead(bus_ctrl2hazard_memread);
		ctrl->MemtoReg(bus_ctrl2hazard_memtoreg);
		ctrl->MemWrite(bus_ctrl2hazard_memwrite);
		ctrl->RegDst(bus_ctrl2hazard_regdst);
		ctrl->RegValue(bus_ctrl2hazard_regvalue);
		ctrl->RegWrite(bus_ctrl2hazard_regwrite);
		ctrl->SignExtend(bus_ctrl_signextend);
		ctrl->Target(bus_ctrl2hazard_target);
		ctrl->HiLoWrite(bus_ctrl2hazard_hilo_write);
		ctrl->HiLoAluSel(bus_ctrl2hazard_hiloalu_sel);
		ctrl->enable(enable);
	}
};

#endif
