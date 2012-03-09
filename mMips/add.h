/*
 *  TU Eindhoven
 *  Eindhoven, The Netherlands
 *
 *  Name            :   add.h
 *
 *  Author          :   Sander Stuijk (sander@ics.ele.tue.nl)
 *
 *  Date            :   July 23, 2002
 *
 *  Function        :   Adder
 *
 *  History         :
 *      23-07-02    :   Initial version.
 *      13-12-02    :   Synthesizable version A.S.Slusarczyk@tue.nl
 *
 */
 
#ifndef ADD_H_INCLUDED
#define ADD_H_INCLUDED

#include "mips.h"

SC_MODULE(ADD) {
	sc_in< 	sc_bv<DWORD> > 	a;	// First operand
	sc_in< 	sc_bv<DWORD> > 	b;	// Second operand
	sc_out< sc_bv<DWORD> > 	r;	// Result
	
	void add();
	
	// Constructor
	SC_CTOR(ADD) {
		SC_METHOD(add);
		sensitive << a << b;
	}
};

#endif
