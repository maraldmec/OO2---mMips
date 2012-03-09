/*
 *  TU Eindhoven
 *  Eindhoven, The Netherlands
 *
 *  Name            :   signextend.h
 *
 *  Author          :   Sander Stuijk (sander@ics.ele.tue.nl)
 *
 *  Date            :   July 23, 2002
 *
 *  Function        :   Sign extension
 *
 *  History         :
 *      23-07-02    :   Initial version.
 *      13-12-02    :   Synthesizable version A.S.Slusarczyk@tue.nl
 *
 */

#ifndef SIGNEXTEND_H_INCLUDED
#define SIGNEXTEND_H_INCLUDED

#include "mips.h"

SC_MODULE(SIGNEXTEND) {
	sc_in< sc_bv<SIGNEXTENDBIT> > 	in;
	sc_out< sc_bv<DWORD> >	out;
	
	void signextend();
	
	// Constructor
	SC_CTOR(SIGNEXTEND) {
		SC_METHOD(signextend);
		sensitive << in;
	}
};

/*
 *	Module sign extends low order byte of word
 */
SC_MODULE(SIGNEXTEND_BYTE) {
	sc_in< sc_bv<DWORD> > 	in;
	sc_out< sc_bv<DWORD> >	out;
	
	void signextend();
	
	// Constructor
	SC_CTOR(SIGNEXTEND_BYTE) {
		SC_METHOD(signextend);
		sensitive << in;
	}
};

#endif
