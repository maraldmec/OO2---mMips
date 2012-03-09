/*
 *  TU Eindhoven
 *  Eindhoven, The Netherlands
 *
 *  Name            :   alu.h
 *
 *  Author          :   Sander Stuijk (sander@ics.ele.tue.nl)
 *
 *  Date            :   July 23, 2002
 *
 *  Function        :   Arithmetic  Logic Unit
 *
 *  History         :
 *      23-07-02    :   Initial version.
 *      13-12-02    :   Synthesizable version A.S.Slusarczyk@tue.nl
 *
 */

#ifndef ALU_H_INCLUDED
#define ALU_H_INCLUDED

#include "mips.h"
 
SC_MODULE(ALU) {
	sc_in< 	sc_bv<W_ALUCTRL> >	ctrl;	// Control input
	sc_in< 	sc_bv<DWORD> >		a;		// First operand input 
	sc_in< 	sc_bv<DWORD> >		b;		// Second operand input
	sc_out<	sc_bv<DWORD> >		r;		// Result
	sc_out<	sc_bv<DWORD> >		r2;		// Result (hi 32b output, 64b results)
	sc_out< sc_bv<1> >			z;		// Zero (one in case result equal zero)
	
	void alu();
	
	// Constructor
	SC_CTOR(ALU) {
		SC_METHOD(alu);
		sensitive << ctrl << a << b;
	}
};

#endif
