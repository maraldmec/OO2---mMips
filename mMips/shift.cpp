/*
 *  TU Eindhoven
 *  Eindhoven, The Netherlands
 *
 *  Name            :   shift.cc
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
 
#include "shift.h"

void SHIFTRIGHT::shiftright()
{
	sc_bv<DWORD> a;
	sc_bv<DWORD> b;
	
	#ifdef VERBOSE
		clog << "SHIFT" << endl;
	#endif
	
	a = in.read();
	b = a >> SHIFTBIT;

	out.write(b);

	#ifdef VERBOSE
		clog << "Shifter: " << a;
		clog << " -> ";
		clog << b << endl;
	#endif
}

void SHIFTLEFT::shiftleft()
{
	sc_bv<DWORD> a;
	sc_bv<DWORD> b;
	
	#ifdef VERBOSE
		clog << "SHIFT" << endl;
	#endif
	
	a = in.read();
	b = a << SHIFTBIT;

	out.write(b);
	
	#ifdef VERBOSE
		clog << "Shifter: " << a;
		clog << " -> ";
		clog << b << endl;
	#endif
}
