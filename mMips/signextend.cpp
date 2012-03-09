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

#include "signextend.h"

void SIGNEXTEND::signextend()
{
	sc_bv<SIGNEXTENDBIT> a;
	sc_bv<DWORD> b;	
	sc_bv<DWORD-SIGNEXTENDBIT> zero(0);
	
	#ifdef VERBOSE
		clog << "SIGNEXTEND" << endl;
	#endif
	
	a = in.read();
	
	b = (zero , a);
	
	for (unsigned int i = SIGNEXTENDBIT; i < DWORD; i++)
		b[i] = a[SIGNEXTENDBIT - 1];
	
	out.write(b);
}

void SIGNEXTEND_BYTE::signextend()
{
    sc_bv<DWORD> a;
    sc_bv<DWORD> b;

    // Note: The GNU assembler assumes that signextension is not done on a LB instruction,
    // altough the MIPS instruction set description describes this. But as we use the GNU
    // tools we skip sign extension and make the upper 24 bits always 0. If we wouldn't
    // do this, the program will run into problems.

    #ifdef VERBOSE
        clog << "SIGNEXTEND BYTE" << endl;
    #endif

    a = in.read();
    b = a;
    for (int i = 8; i < DWORD; i++)
        b[i] = 0;

    out.write(b);
}
