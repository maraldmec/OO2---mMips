/*
 *  TU Eindhoven
 *  Eindhoven, The Netherlands
 *
 *  Name            :   mux.h
 *
 *  Author          :   Sander Stuijk (sander@ics.ele.tue.nl)
 *
 *  Date            :   July 23, 2002
 *
 *  Function        :   Multiplexer
 *
 *  History         :
 *      23-07-02    :   Initial version.
 *      13-12-02    :   Synthesizable version A.S.Slusarczyk@tue.nl
 *
 */
 
#ifndef MUX_H_INCLUDED
#define MUX_H_INCLUDED

#include "mips.h"

SC_MODULE(MUX2) {
	sc_in< 	sc_bv<DWORD> > 	in0;	// First input
	sc_in< 	sc_bv<DWORD> > 	in1;	// Second input
	sc_in< 	sc_bv<1> >		sel;	// Selection bit
	sc_out< sc_bv<DWORD> > 	out;	// Output
	
	void mux();
	
	SC_CTOR(MUX2) {
		SC_METHOD(mux);
		sensitive << in0 <<in1 << sel;
	}
};

SC_MODULE(MUX3) {
	sc_in< 	sc_bv<DWORD> > 	in0;	// First input
	sc_in< 	sc_bv<DWORD> > 	in1;	// Second input
	sc_in< 	sc_bv<DWORD> > 	in2;	// Third input
	sc_in< 	sc_bv<2> >		sel;	// Selection bit
	sc_out< sc_bv<DWORD> > 	out;	// Output
	
	void mux();
	
	SC_CTOR(MUX3) {
		SC_METHOD(mux);
		sensitive << in0 <<in1 << in2 << sel;
	}
};

SC_MODULE(MUX4) {
	sc_in< 	sc_bv<DWORD> > 	in0;	// First input
	sc_in< 	sc_bv<DWORD> > 	in1;	// Second input
	sc_in< 	sc_bv<DWORD> >	in2;	// Third bit
	sc_in< 	sc_bv<DWORD> > 	in3;	// Fourth input
	sc_in< 	sc_bv<2> >		sel;	// Selection bit
	sc_out< sc_bv<DWORD> > 	out;	// Output
	
	void mux();
	
	SC_CTOR(MUX4) {
		SC_METHOD(mux);
		sensitive << in0 <<in1 << in2 << in3 << sel;
	}
};

SC_MODULE(MUX3_AWORDREG) {
	sc_in< 	sc_bv<AWORDREG> > 	in0;	// First input
	sc_in< 	sc_bv<AWORDREG> > 	in1;	// Second input
	sc_in< 	sc_bv<AWORDREG> > 	in2;	// Third input
	sc_in< 	sc_bv<2> >			sel;	// Selection bit
	sc_out< sc_bv<AWORDREG> > 	out;	// Output
	
	void mux();
	
	SC_CTOR(MUX3_AWORDREG) {
		SC_METHOD(mux);
		sensitive << in0 << in1 << in2 << sel;
	}
};

#endif
