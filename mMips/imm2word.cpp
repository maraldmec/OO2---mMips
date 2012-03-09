/*
 *  TU Eindhoven
 *  Eindhoven, The Netherlands
 *
 *  Name            :   imm2word.cpp
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

#include "imm2word.h"

void IMM2WORD::imm2word()
{
	sc_bv<W_IMMEDIATE> a;
	sc_bv<DWORD>       b;
	sc_bv<DWORD-W_IMMEDIATE> zero(0);
	
	#ifdef VERBOSE
		clog << "IMM2WORD" << endl;
	#endif
	
	// Read the input
    a = in.read();
	b = (zero, a);
	
    // Check for sign extension
    if (signextend.read().to_uint() == 1)
    {
	    for (unsigned int i = SIGNEXTENDBIT; i < DWORD; i++)
		    b[i] = a[SIGNEXTENDBIT - 1];
	}
    
    // Write the output
	out.write(b);
}
