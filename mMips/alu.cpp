/*
 *  TU Eindhoven
 *  Eindhoven, The Netherlands
 *
 *  Name            :   alu.cc
 *
 *  Author          :   Sander Stuijk (sander@ics.ele.tue.nl)
 *
 *  Date            :   July 23, 2002
 *
 *  Function        :   Arithmetic  Logic Unit
 *
 *  History         :
 *      23-07-02    :   Initial version.
 *      13-12-02    :   Synthesizable version A.S.Slusarczyk@tue.nl
 *
 */

#include "alu.h"
 
void ALU::alu()
{
	sc_bv<DWORD> 			result, result_hi;
	sc_bv<1> 				zero, sign;
	sc_uint<DWORD> 			s;
	sc_uint<DWORD> 			t;
	sc_uint<W_ALUCTRL>		ctrl_t;
	sc_int<DWORD>			s_int, t_int;
	sc_int<64>				c;
	sc_uint<DWORD>			e;
	sc_uint<6>				it_in;
	sc_uint<6>				it_out;
	sc_bv<1>				hazard;

	#ifdef VERBOSE
		clog << "ALU" << endl;
	#endif

	// Read the inputs
	s = a.read();
	t = b.read();
	ctrl_t = ctrl.read();
    s_int = sc_int<DWORD> (s);
    t_int = sc_int<DWORD> (t);

	result = 0;
    result_hi = 0;
	hazard=1;
	// Calculate result using selected operation
	switch (ctrl_t) {
		case 0x0:	// And
					result = s & t;
					break;

		case 0x1:	// Or
					result = s | t;
					break;

		case 0x2:	// Add
					result = s_int + t_int;
					
					// Calculate the zero output
					if (sc_uint<DWORD>(result) == 0)
							zero = 1;
					else
						zero = 0;
					z.write(zero);
					break;

		case 0x3:	// Add unsigned
					result = s + t;
					// Calculate the zero output
					if (sc_uint<DWORD>(result) == 0)
						zero = 1;
					else
						zero = 0;
					z.write(zero);
					break;

		case 0x4:	// Xor
					result = s ^ t;
					break;

		case 0x6:	// Subtract unsigned
					result = s - t;
					// Calculate the zero output
					if (sc_uint<DWORD>(result) == 0)
						zero = 1;
					else
						zero = 0;
					z.write(zero);
					break;

		case 0x7:	// Set-on-less-than
					if (s_int < t_int)
						result = 1;
					else
						result = 0;
					// Calculate the zero output
						if (sc_uint<DWORD>(result) == 0)
							zero = 1;
						else
							zero = 0;
					z.write(zero);
					break;

		case 0x8:	// Set-on-less-than unsigned
					if (s < t)
						result = 1;
					else
						result = 0;
					// Calculate the zero output
						if (sc_uint<DWORD>(result) == 0)
							zero = 1;
						else
							zero = 0;
						z.write(zero);
					break;

		case 0x9:	// Load upper immediate
					result = t << 16;
					break;

		case 0xA:	// SLL (1 bit)
					result = t << 1;
					break;

		case 0xB:	// SLL (2 bit)
					result = t << 2;
					break;

		case 0xC:	// SLL (8 bit)
					result = t << 8;
					break;

		case 0xD:	// SRL (1 bit)
					result = t >> 1;
					break;

		case 0xE:	// SRL (2 bit)
					result = t >> 2;
					break;

		case 0xF:	// SRL (8 bit)
					result = t >> 8;
					break;

		case 0x10:	// SRA (1 bit)
					sign = t.range(DWORD-1,DWORD-1);
					result = t >> 1;
					result.range(DWORD-1,DWORD-1) = sign;
					break;

		case 0x11:	// SRA (2 bit)
					sign = t.range(DWORD-1,DWORD-1);
					result = t >> 2;
					result.range(DWORD-1,DWORD-2) = (sign, sign);
					break;

		case 0x12:	// SRA (8 bit)
					sign = t.range(DWORD-1,DWORD-1);
					result = t >> 8;
					result.range(DWORD-1,DWORD-8) = (sign, sign, sign, sign, sign, sign, sign, sign);
					break;

        case 0x13:  // Multu
                    c = sc_int<64>(s) * sc_int<64>(t);
					result = c.range(DWORD-1,0);
					result_hi = c.range(63, DWORD);
					r2.write(result_hi);
                    break;
		case 0x14:  //Clipping
                    if(t_int<0)
						result=0;
					else if(t_int>255)
						result=255;
					else 
						result=t_int;
                    break;
		case 0x15:  //Divide
					it_in=iin.read();
					if(it_in==0)
						e=0;
					else
						e=d.read();
					e |=(1<<(31-it_in));
					c = sc_int<32>(t) * e;
					if(c>sc_int<32>(s))
							e &= ~(1<<(31-it_in));

					if(e>255)
						result=255;
					else if(e<0)
						result=0;
					else
						result=e;

					if(it_in==31)
					{
						it_out=0;
						hazard=1;
					}
					else
					{
						it_out=it_in+1;
						hazard=0;
					}
					iout.write(it_out);
                    break;
		case 0x16:  //Add +1 or -1
			        c = sc_int<64>(s) * sc_int<64>(t);
					result = c.range(DWORD-1,0);
					result_hi = c.range(63, DWORD);
					r2.write(result_hi);
					r2.write(result_hi);
                    break;
	}

	// Write results to output
	alu_done.write(hazard);
	r.write(result);
}
