/*
 *  TU Eindhoven
 *  Eindhoven, The Netherlands
 *
 *  Name            :   shift.h
 *
 *  Author          :   Sander Stuijk (sander@ics.ele.tue.nl)
 *
 *  Date            :   July 23, 2002
 *
 *  Function        :   Shifter
 *
 *  History         :
 *      23-07-02    :   Initial version.
 *      13-12-02    :   Synthesizable version A.S.Slusarczyk@tue.nl
 *
 */
 
#ifndef SHIFT_H_INCLUDED
#define SHIFT_H_INCLUDED

#include "mips.h"

SC_MODULE(SHIFTRIGHT) {
	sc_in< sc_bv<DWORD> > in;
	sc_out< sc_bv<DWORD> > out;
	
	void shiftright();
	
	SC_CTOR(SHIFTRIGHT) {
		SC_METHOD(shiftright);
		sensitive << in;
	}
};

SC_MODULE(SHIFTLEFT) {
	sc_in< sc_bv<DWORD> > in;
	sc_out< sc_bv<DWORD> > out;
	
	void shiftleft();
	
	SC_CTOR(SHIFTLEFT) {
		SC_METHOD(shiftleft);
		sensitive << in;
	}
};

#endif
