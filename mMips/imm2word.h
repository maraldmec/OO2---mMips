/*
 *  TU Eindhoven
 *  Eindhoven, The Netherlands
 *
 *  Name            :   imm2word.h
 *
 *  Author          :   Sander Stuijk (sander@ics.ele.tue.nl)
 *
 *  Date            :   July 23, 2002
 *
 *  Function        :   Immediate to word conversion (with or withour sign
 *                      extension). Immediate is halfword size
 *
 *  History         :
 *      16-12-03    :   Initial version.
 *
 */

#ifndef IMM2WORD_H_INCLUDED
#define IMM2WORD_H_INCLUDED

#include "mips.h"

SC_MODULE(IMM2WORD) {
	sc_in< sc_bv<W_IMMEDIATE>  > 	in;
    sc_in< sc_bv<W_SIGNEXTEND> >    signextend;
	sc_out< sc_bv<DWORD>       >    out;
	
	void imm2word();
	
	// Constructor
	SC_CTOR(IMM2WORD) {
		SC_METHOD(imm2word);
		sensitive << in << signextend;
	}
};

#endif
