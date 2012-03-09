/*
 *  TU Eindhoven
 *  Eindhoven, The Netherlands
 *
 *  Name            :   mux.cc
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
 
#include "mux.h"

void MUX2::mux()
{
	sc_bv<DWORD> data;
	
	#ifdef VERBOSE
		clog << "MUX '" << name() << "'" <<endl;
	#endif
	
	// Read correct input
	if(sc_uint<1>(sel.read()) == 0)
		data = in0.read();
	else
		data = in1.read();
	
	// Write output
	out.write(data);
}

void MUX3::mux()
{
	sc_bv<DWORD> data;
	sc_uint<2> sel_t;
	
	#ifdef VERBOSE
		clog << "MUX '" << name() << "'" <<endl;
	#endif
	
	// Read correct input
	sel_t = sel.read();
	if(sel_t == 0)
		data = in0.read();
	else if (sel_t == 1)
		data = in1.read();
	else
		data = in2.read();
		
	// Write output
	out.write(data);
}

void MUX3_AWORDREG::mux()
{
	sc_bv<AWORDREG> data;
	sc_uint<2> sel_t;
	
	#ifdef VERBOSE
		clog << "MUX '" << name() << "'" <<endl;
	#endif
	
	// Read correct input
	sel_t = sel.read();
	if(sel_t == 0)
		data = in0.read();
	else if (sel_t == 1)
		data = in1.read();
	else
		data = in2.read();
		
	// Write output
	out.write(data);
}
