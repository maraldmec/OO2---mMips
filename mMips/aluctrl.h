/*
 *  TU Eindhoven
 *  Eindhoven, The Netherlands
 *
 *  Name            :   aluctrl.h
 *
 *  Author          :   Sander Stuijk (sander@ics.ele.tue.nl)
 *
 *  Date            :   July 23, 2002
 *
 *  Function        :   ALU controller
 *
 *  History         :
 *      23-07-02    :   Initial version.
 *      13-12-02    :   Synthesizable version A.S.Slusarczyk@tue.nl
 *
 */
 
#ifndef ALUCTRL_H_INCLUDED
#define ALUCTRL_H_INCLUDED

#include "mips.h"

SC_MODULE(ALUCTRL) {
	sc_in< 	sc_bv<W_FUNCCODE> >	functionCode;	// Bit [0,5] of instruction
	sc_in< 	sc_bv<W_ALUOP> 	  >	ALUop;			// ALU operation code
	sc_in<	sc_bv<W_SHAMT>	  >	Shamt;			// Shift amount
	sc_in<	sc_bv<1>	  >	DIV;			// Shift amount
	sc_out< sc_bv<W_ALUCTRL>  >	ALUctrl;		// Control output to ALU

	void aluctrl();
	
	// Constructor
	SC_CTOR(ALUCTRL) {
		SC_METHOD(aluctrl);
		sensitive << functionCode << ALUop << Shamt;
	}
};

#endif
