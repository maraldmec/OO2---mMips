/*
 *  TU Eindhoven
 *  Eindhoven, The Netherlands
 *
 *  Name            :   mips.h
 *
 *  Author          :   Sander Stuijk (sander@ics.ele.tue.nl)
 *
 *  Date            :   July 23, 2002
 *
 *  Function        :   MIPS
 *
 *  History         :
 *      23-07-02    :   Initial version.
 *      13-12-02    :   Synthesizable version A.S.Slusarczyk@tue.nl
 *
 */
 
#ifndef MIPS_H_INCLUDED
#define MIPS_H_INCLUDED

#include "systemc.h"

// Memory sizes
#define RAMSIZE         4194304  // Size (in bytes) of RAM
#define RAMMASK         0x3FFFFF // Mask used in address mapping
#define ROMSIZE         163840   // Size (in bytes) of ROM
#define REGSIZE         32       // Size (in words) of registerfile

// Module settings
#define SIGNEXTENDBIT   16      // Half of dataword size
#define SHIFTBIT        2       // Nr position word shifted in shifter

// Width (in bits) of various operands
#define DWORD           32      // Dataword size
#define AWORD           32      // Address word size
#define AWORDREG        5       // Address word size of registerfile
#define W_IMMEDIATE     16      // Immediate size

#define W_ALUCTRL       6       // ALU control code
#define W_ALUOP         5       // ALU operation code
#define W_ALUSRC        1       // Select 'b' input of ALU 
#define W_BRANCHFLAG    1       // Flag for branching
#define W_BRANCHOP      2       // Branch controller operation code
#define W_FUNCCODE      6       // Function code (instr[5,0])
#define W_HAZARDFLAG    1       // Flag for hazard
#define W_IFIDWRITEFLAG 1       // Update IF/ID registers flag
#define W_MEMREAD       2       // Read data from memory
#define W_MEMTOREG      2       // Write memory output to register 
#define W_MEMWRITE      2       // Write data to memory
#define W_OPCODE        6       // Operation code (instr[31,26])
#define W_PCWRITEFLAG   1       // Update program counter flag
#define W_REGDST        2       // Select address destination register
#define W_REGVAL        1       // Select value destination register
#define W_REGWRITE      1       // Write to register
#define W_SHAMT         5       // Shift amount
#define W_SIGNEXTEND    1       // Sign extend immediate value
#define W_TARGET        2       // Select branch target address
#define W_HILO_W        1       // Write signal to hi/lo registers
#define W_HILOALU_S     2       // Control signal to mux8

#define clog cout
#endif
