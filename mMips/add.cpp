/*
 *  TU Eindhoven
 *  Eindhoven, The Netherlands
 *
 *  Name            :   add.cc
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
 
#include "add.h"

void ADD::add()
{
	sc_int<DWORD> a_t, b_t, r_t;

	#ifdef VERBOSE
		clog << "ADD" << endl;
	#endif
	
	// Read input
	a_t = a.read();
	b_t = b.read();
	
	// Compute result
	r_t = a_t + b_t;
	
	// Put result on output
	r.write(r_t);
}
