/*
 *  TU Eindhoven
 *  Eindhoven, The Netherlands
 *
 *  Name            :   decoder.cc
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
 
#include "decoder.h"

void DECODER::decoder()
{
	sc_uint<DWORD> 		t_instr;
	sc_uint<DWORD>		t_instr_25_0;
	sc_uint<AWORDREG> 	t_instr_20_16, t_instr_15_11;
	sc_uint<6> 		t_instr_31_26, t_instr_5_0;
	sc_uint<5>		t_instr_10_6;
	sc_uint<16> 		t_instr_15_0;
	
	// Read input
	t_instr = instr.read();
	
	// Compute output
	t_instr_31_26 = t_instr.range(31,26);
	t_instr_25_0 = t_instr.range(25,0);
	t_instr_20_16 = t_instr.range(20,16);
	t_instr_15_11 = t_instr.range(15,11);
	t_instr_15_0 = t_instr.range(15,0);
	t_instr_10_6 = t_instr.range(10,6);
	t_instr_5_0 = t_instr.range(5,0);

	// Write output
	instr_31_26.write(t_instr_31_26);
	instr_25_0.write(t_instr_25_0);
	instr_20_16.write(t_instr_20_16);
	instr_15_11.write(t_instr_15_11);
	instr_15_0.write(t_instr_15_0);
	instr_10_6.write(t_instr_10_6);
	instr_5_0.write(t_instr_5_0);
}

void DECODER_NBUF::decoder_nbuf()
{
	sc_uint<DWORD> 		t_instr;
	sc_uint<AWORDREG> 	t_instr_25_21, t_instr_20_16;

	// Read input
	t_instr = instr.read();

	t_instr_25_21 = t_instr.range(25,21);
	t_instr_20_16 = t_instr.range(20,16);

	// Write output
	instr_25_21.write(t_instr_25_21);
	instr_20_16.write(t_instr_20_16);
}
