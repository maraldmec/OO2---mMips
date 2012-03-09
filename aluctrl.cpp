/*
 *  TU Eindhoven
 *  Eindhoven, The Netherlands
 *
 *  Name            :   aluctrl.cc
 *
 *  Author          :   Sander Stuijk (sander@ics.ele.tue.nl)
 *
 *  Date            :   July 23, 2002
 *
 *  Function        :   ALU controller
 *
 *  History         :
 *      23-07-02    :   Initial version.
 *      13-12-02    :   Synthesizable version A.S.Slusarczyk@tue.nl
 *
 */
 
#include "aluctrl.h"

void ALUCTRL::aluctrl()
{
	sc_uint<W_ALUCTRL> aluCtrl;
	sc_uint<W_ALUOP> aluop;
	sc_uint<W_SHAMT> shamt;
	sc_uint<W_FUNCCODE> functioncode;
	
	#ifdef VERBOSE
		clog << "ALUCTRL" << endl;
	#endif
	
	// Determine output
	aluop = ALUop.read();
	shamt = Shamt.read();
	
	switch (aluop) {
		case 0x0:	// Add signed
					aluCtrl = 0x2;
					break;
		
		case 0x1:	// Subtract unsigned
					aluCtrl = 0x6;
					break;
		
		case 0x2:	// R-type instruction, look to functionCode
					functioncode = functionCode.read();
					functioncode = functioncode.range(5,0); 
					switch (functioncode) {
						case 0x0:	// Sll
									switch (shamt) {
										case 1: aluCtrl = 0xA; break;
										case 2: aluCtrl = 0xB; break;
										case 8: aluCtrl = 0xC; break;
										default : aluCtrl = 0x0; break;
									}
									break;
						
						case 0x2:	// Srl
									switch (shamt) {
										case 1: aluCtrl = 0xD; break;
										case 2: aluCtrl = 0xE; break;
										case 8: aluCtrl = 0xF; break;
										default : aluCtrl = 0x0; break;
									}
									break;
						
						case 0x3:	// Sra
									switch (shamt) {
										case 1: aluCtrl = 0x10; break;
										case 2: aluCtrl = 0x11; break;
										case 8: aluCtrl = 0x12; break;
										default : aluCtrl = 0x0; break;
									}
									break;
						
                        case 0x10:  // Move hi register (nop in ALU)
                                    aluCtrl = 0x0;
                                    break;
                        
                        case 0x12:  // Move hi register (nop in ALU)
                                    aluCtrl = 0x0;
                                    break;
                        
                        case 0x19:  // Multiply unsigned
                                    aluCtrl = 0x13;
                                    break;
                                    
						case 0x20:	// Add signed
									aluCtrl = 0x2;
									break;
						
						case 0x21:	// Add unsigned
									aluCtrl = 0x3;
									break;
									
						case 0x23:	// Subtract unsigned
									aluCtrl = 0x6;
									break;
						
						case 0x24:	// And
									aluCtrl = 0x0;
									break;
						
						case 0x25:	// Or
									aluCtrl = 0x1;
									break;
						
						case 0x26:	// Xor
									aluCtrl = 0x4;
									break;
									
						case 0x2A:	// Set-on-less-than (2's complement)
									aluCtrl = 0x7;
									break;

						case 0x2B:	// Set-on-less-than (unsigned)
									aluCtrl = 0x8;
									break;
						case 0x31:  // Multiply unsigned
                                    aluCtrl = 0x14;
                                    break;

						default : aluCtrl = 0x0; break;
	
					}
					break;
		
		case 0x3:	// Add unsigned
					aluCtrl = 0x3;
					break;
		
		case 0x4:	// And
					aluCtrl = 0x0;
					break;
		
		case 0x5:	// Or
					aluCtrl = 0x1;
					break;
		
		case 0x6:	// Xor
					aluCtrl = 0x4;
					break;
		
		case 0x7:	// Slt
					aluCtrl = 0x7;
					break;
		
		case 0x8:	// Sltu
					aluCtrl = 0x8;
					break;
		
		case 0x9:	// Lui
					aluCtrl = 0x9;
					break;
		default : aluCtrl = 0x0; break;
	}
	
	// Set result on output
	ALUctrl.write(aluCtrl);
}
