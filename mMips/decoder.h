/*
 *  TU Eindhoven
 *  Eindhoven, The Netherlands
 *
 *  Name            :   decoder.h
 *
 *  Author          :   Sander Stuijk (sander@ics.ele.tue.nl)
 *
 *  Date            :   July 23, 2002
 *
 *  Function        :   Decoder
 *
 *  History         :
 *      23-07-02    :   Initial version.
 *      13-12-02    :   Synthesizable version A.S.Slusarczyk@tue.nl
 *
 */
 
#ifndef DECODER_H_INCLUDED
#define DECODER_H_INCLUDED

#include "mips.h"

SC_MODULE(DECODER) {
	sc_in< 	sc_bv<DWORD> > 	instr;
	sc_out< sc_bv<6> >		instr_31_26;
	sc_out< sc_bv<DWORD> > 	instr_25_0;
	sc_out< sc_bv<5> > 		instr_20_16;
	sc_out< sc_bv<5> > 		instr_15_11;
	sc_out< sc_bv<16> > 	instr_15_0;
	sc_out< sc_bv<5> > 		instr_10_6;
	sc_out< sc_bv<6> > 		instr_5_0;
	
	void decoder();
	
	SC_CTOR(DECODER) {
		SC_METHOD(decoder);
		sensitive << instr;
	}
};

// decoder for non-registered instructions
SC_MODULE(DECODER_NBUF) {
	sc_in< 	sc_bv<DWORD> > 	instr;
	sc_out< sc_bv<5> > 		instr_25_21;	
	sc_out< sc_bv<5> > 		instr_20_16;	
	
	void decoder_nbuf();
	
	SC_CTOR(DECODER_NBUF) {
		SC_METHOD(decoder_nbuf); 
		sensitive << instr;
	}
};

#endif
