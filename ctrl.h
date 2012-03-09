/*
 *  TU Eindhoven
 *  Eindhoven, The Netherlands
 *
 *  Name            :   ctrl.h
 *
 *  Author          :   Sander Stuijk (sander@ics.ele.tue.nl)
 *
 *  Date            :   July 23, 2002
 *
 *  Function        :   Single cycle controller
 *
 *  History         :
 *      23-07-02    :   Initial version.
 *      13-12-02    :   Synthesizable version A.S.Slusarczyk@tue.nl
 *
 */
 
#ifndef CTRL_H_INCLUDED
#define CTRL_H_INCLUDED

#include "mips.h"

SC_MODULE(CTRL) {
	sc_in<bool>				enable;
	sc_out< sc_bv<1> >			en;

	sc_in< 	sc_bv<W_OPCODE> >		Opcode;	// Instruction bits [31,26]
	sc_in<	sc_bv<W_FUNCCODE> >		FunctionCode; // Instruction bits [6,0]
	sc_out<	sc_bv<W_REGDST> >		RegDst;
	sc_out<	sc_bv<W_REGVAL> >		RegValue;
	sc_out<	sc_bv<W_TARGET> >		Target;
	sc_out< sc_bv<W_BRANCHOP> >		Branch;
	sc_out< sc_bv<W_MEMREAD> >		MemRead;
	sc_out< sc_bv<W_MEMTOREG> >		MemtoReg;
	sc_out< sc_bv<W_ALUOP> >		ALUop;
	sc_out< sc_bv<W_MEMWRITE> >		MemWrite;
	sc_out< sc_bv<W_ALUSRC> >		ALUSrc;
	sc_out< sc_bv<W_REGWRITE> >		RegWrite;
    sc_out< sc_bv<W_SIGNEXTEND> >   SignExtend;
	sc_out< sc_bv<DWORD> >			c4;	// Constant value 4
	sc_out< sc_bv<1> >				c1;	// Constant value 1
	sc_out< sc_bv<AWORDREG> >		c31;// Constant value 31
    sc_out< sc_bv<W_HILO_W> >       HiLoWrite;
    sc_out< sc_bv<W_HILOALU_S> >    HiLoAluSel;
	
	void ctrl();
	
	// Constructor
	SC_CTOR(CTRL) {
		SC_METHOD(ctrl);
		sensitive << Opcode << FunctionCode << enable;
	}
};
#endif
