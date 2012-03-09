/*
 *  TU Eindhoven
 *  Eindhoven, The Netherlands
 *
 *  Name            :   ctrl.h
 *
 *  Author          :   Sander Stuijk (sander@ics.ele.tue.nl)
 *
 *  Date            :   July 23, 2002
 *
 *  Function        :   Single cycle controller
 *
 *  History         :
 *      23-07-02    :   Initial version.
 *      13-12-02    :   Synthesizable version A.S.Slusarczyk@tue.nl
 *
 */
 
#include "ctrl.h"

void CTRL::ctrl()
{
	sc_uint<W_OPCODE> opcode;
	sc_uint<W_FUNCCODE> functioncode;
	
	c4.write(0x4);// Write constant 4 to output
	c1.write(0x1);// Write constant 1 to output
	c31.write(31);// Write constant 31 to output
	en.write( ((enable.read() == true) ? 1 : 0) );
	
	RegDst.write(0);
	RegValue.write(0);
	Target.write(0);
	ALUSrc.write(0);
	MemtoReg.write(0);
	RegWrite.write(0);
	MemRead.write(0);
	MemWrite.write(0);
	Branch.write(0);
	ALUop.write(0);
	SignExtend.write(0);
        	
	#ifdef VERBOSE
		clog << "CTRL" << endl;
	#endif
	
	// Read the input
	opcode = Opcode.read();
	functioncode = FunctionCode.read();
	
	// Determine output
	switch (opcode) {
		case 0:		// R-format instruction
					switch (functioncode)
					{
						case 8:		// Instruction: Jr
									RegDst.write(1);
									RegValue.write(0);
									Target.write(2);
									ALUSrc.write(0);
									MemtoReg.write(0);
									RegWrite.write(0);
									MemRead.write(0);
									MemWrite.write(0);
									Branch.write(3);
									ALUop.write(0x2);
                                    SignExtend.write(1);
                                    HiLoWrite.write(0);
									HiLoAluSel.write(0);
                                    break;
						
						case 9:		// Instruction: Jalr
									RegDst.write(1);
									RegValue.write(1);
									Target.write(2);
									ALUSrc.write(0);
									MemtoReg.write(0);
									RegWrite.write(1);
									MemRead.write(0);
									MemWrite.write(0);
									Branch.write(3);
									ALUop.write(0x2);
                                    SignExtend.write(1);
									HiLoWrite.write(0);
                                    HiLoAluSel.write(0);
                                    break;
						
                        case 0x10:  // Move hi register
									RegDst.write(1);
									RegValue.write(0);
									Target.write(0);
									ALUSrc.write(0);
									MemtoReg.write(0);
									RegWrite.write(1);
									MemRead.write(0);
									MemWrite.write(0);
									Branch.write(0);
									ALUop.write(0x2);
                                    SignExtend.write(1);
									HiLoWrite.write(0);
                                    HiLoAluSel.write(2);
                                    break;
                        
                        case 0x12:  // Move lo register
									RegDst.write(1);
									RegValue.write(0);
									Target.write(0);
									ALUSrc.write(0);
									MemtoReg.write(0);
									RegWrite.write(1);
									MemRead.write(0);
									MemWrite.write(0);
									Branch.write(0);
									ALUop.write(0x2);
                                    SignExtend.write(1);
									HiLoWrite.write(0);
                                    HiLoAluSel.write(1);
                                    break;
                        
                        case 0x19:  // Multiply unsigned
									RegDst.write(0); // No destination
									RegValue.write(0);
									Target.write(0);
									ALUSrc.write(0);
									MemtoReg.write(0);
									RegWrite.write(1);
									MemRead.write(0);
									MemWrite.write(0);
									Branch.write(0);
									ALUop.write(0x2);
                                    SignExtend.write(1);
                                    HiLoWrite.write(1);
                                    HiLoAluSel.write(0);
									break;
                        
						default:	// Others
									RegDst.write(1);
									RegValue.write(0);
									Target.write(0);
									ALUSrc.write(0);
									MemtoReg.write(0);
									RegWrite.write(1);
									MemRead.write(0);
									MemWrite.write(0);
									Branch.write(0);
									ALUop.write(0x2);
                                    SignExtend.write(1);
									HiLoWrite.write(0);
                                    HiLoAluSel.write(0);
                                    break;
					}
					break;

		case 2:		// Instruction: J
					RegDst.write(0);
					RegValue.write(0);
					Target.write(1);
					ALUSrc.write(0);
					MemtoReg.write(0);
					RegWrite.write(0);
					MemRead.write(0);
					MemWrite.write(0);
					Branch.write(3);
					ALUop.write(0x2);
                    SignExtend.write(1);
					HiLoWrite.write(0);
                    HiLoAluSel.write(0);
                    break;

		case 3:		// Instruction: Jal
					RegDst.write(2);
					RegValue.write(1);
					Target.write(1);
					ALUSrc.write(0);
					MemtoReg.write(0);
					RegWrite.write(1);
					MemRead.write(0);
					MemWrite.write(0);
					Branch.write(3);
					ALUop.write(0x2);
                    SignExtend.write(1);
					HiLoWrite.write(0);
                    HiLoAluSel.write(0);
                    break;
					
		case 4:		// beq instruction
					RegDst.write(0);
					RegValue.write(0);
					Target.write(0);
					ALUSrc.write(0);
					MemtoReg.write(0);
					RegWrite.write(0);
					MemRead.write(0);
					MemWrite.write(0);
					Branch.write(0x1);
					ALUop.write(0x1);
                    SignExtend.write(1);
					HiLoWrite.write(0);
                    HiLoAluSel.write(0);
                    break;

		case 5:		// bne instruction
					RegDst.write(0);
					RegValue.write(0);
					Target.write(0);
					ALUSrc.write(0);
					MemtoReg.write(0);
					RegWrite.write(0);
					MemRead.write(0);
					MemWrite.write(0);
					Branch.write(0x2);
					ALUop.write(0x1);
                    SignExtend.write(1);
					HiLoWrite.write(0);
                    HiLoAluSel.write(0);
                    break;

		case 9:		// ADDIU
					RegDst.write(0);
					RegValue.write(0);
					Target.write(0);
					ALUSrc.write(1);
					MemtoReg.write(0);
					RegWrite.write(1);
					MemRead.write(0);
					MemWrite.write(0);
					Branch.write(0);
					ALUop.write(0x3);
                    SignExtend.write(1);
					HiLoWrite.write(0);
                    HiLoAluSel.write(0);
                    break;

		case 10:	// SLTI
					RegDst.write(0);
					RegValue.write(0);
					Target.write(0);
					ALUSrc.write(1);
					MemtoReg.write(0);
					RegWrite.write(1);
					MemRead.write(0);
					MemWrite.write(0);
					Branch.write(0);
					ALUop.write(0x7);
                    SignExtend.write(1);
					HiLoWrite.write(0);
                    HiLoAluSel.write(0);
                    break;
					
		case 11:	// SLTIU
					RegDst.write(0);
					RegValue.write(0);
					Target.write(0);
					ALUSrc.write(1);
					MemtoReg.write(0);
					RegWrite.write(1);
					MemRead.write(0);
					MemWrite.write(0);
					Branch.write(0);
					ALUop.write(0x8);
                    SignExtend.write(1);
					HiLoWrite.write(0);
                    HiLoAluSel.write(0);
                    break;
					
		case 12:	// ANDI  
					RegDst.write(0);
					RegValue.write(0);
					Target.write(0);
					ALUSrc.write(1);
					MemtoReg.write(0);
					RegWrite.write(1);
					MemRead.write(0);
					MemWrite.write(0);
					Branch.write(0);
					ALUop.write(0x4);
                    SignExtend.write(0);
					HiLoWrite.write(0);
                    HiLoAluSel.write(0);
                    break;
					
		case 13:	// ORI
					RegDst.write(0);
					RegValue.write(0);
					Target.write(0);
					ALUSrc.write(1);
					MemtoReg.write(0);
					RegWrite.write(1);
					MemRead.write(0);
					MemWrite.write(0);
					Branch.write(0);
					ALUop.write(0x5);
                    SignExtend.write(0);
					HiLoWrite.write(0);
                    HiLoAluSel.write(0);
                    break;
					
		case 14:	// XORI
					RegDst.write(0);
					RegValue.write(0);
					Target.write(0);
					ALUSrc.write(1);
					MemtoReg.write(0);
					RegWrite.write(1);
					MemRead.write(0);
					MemWrite.write(0);
					Branch.write(0);
					ALUop.write(0x6);
                    SignExtend.write(0);
					HiLoWrite.write(0);
                    HiLoAluSel.write(0);
                    break;
					
		case 15:	// LUI
					RegDst.write(0);
					RegValue.write(0);
					Target.write(0);
					ALUSrc.write(1);
					MemtoReg.write(0);
					RegWrite.write(1);
					MemRead.write(0);
					MemWrite.write(0);
					Branch.write(0);
					ALUop.write(0x9);
                    SignExtend.write(1);
					HiLoWrite.write(0);
                    HiLoAluSel.write(0);
                    break;

		case 32:	// lb instruction
					RegDst.write(0);
					RegValue.write(0);
					Target.write(0);
					ALUSrc.write(1);
					MemtoReg.write(2);
					RegWrite.write(1);
					MemRead.write(2);
					MemWrite.write(0);
					Branch.write(0);
					ALUop.write(0);
                    SignExtend.write(1);
					HiLoWrite.write(0);
                    HiLoAluSel.write(0);
                    break;
					
		case 35:	// lw instruction
					RegDst.write(0);
					RegValue.write(0);
					Target.write(0);
					ALUSrc.write(1);
					MemtoReg.write(1);
					RegWrite.write(1);
					MemRead.write(1);
					MemWrite.write(0);
					Branch.write(0);
					ALUop.write(0);
                    SignExtend.write(1);
					HiLoWrite.write(0);
                    HiLoAluSel.write(0);
                    break;

		case 40:	// sb instruction
					RegDst.write(0);
					RegValue.write(0);
					Target.write(0);
					ALUSrc.write(1);
					MemtoReg.write(0);
					RegWrite.write(0);
					MemRead.write(0);
					MemWrite.write(2);
					Branch.write(0);
					ALUop.write(0);
                    SignExtend.write(1);
					HiLoWrite.write(0);
                    HiLoAluSel.write(0);
                    break;
		
		case 43:	// sw instruction
					RegDst.write(0);
					RegValue.write(0);
					Target.write(0);
					ALUSrc.write(1);
					MemtoReg.write(0);
					RegWrite.write(0);
					MemRead.write(0);
					MemWrite.write(1);
					Branch.write(0);
					ALUop.write(0);
                    SignExtend.write(1);
					HiLoWrite.write(0);
                    HiLoAluSel.write(0);
                    break;
	}
}
