/*
 *  TU Eindhoven
 *  Eindhoven, The Netherlands
 *
 *  Name            :
 *
 *  Author          :   A.S.Slusarczyk@tue.nl
 *
 *  Date            :
 *
 *  Function        :
 *
 */

// undefine NOVCD to enable tracing of mMIPS internal signals
//#define NOVCD 1

// GCC/Borland compatibility issue
#define TRUE 1

#include "mips_trace.h"
#include "testbench.h"

//
//  MAIN
//
int sc_main(int argc, char *argv[])
{
	sc_uint<32> pc;
	int period = 10, sim_time=0;

	// Signals
	sc_signal< bool > CLOCK;
	sc_signal< bool > ENABLE;
	sc_signal< bool > RESET;

	// Testbench
	TESTBENCH testbench("testbench");
	testbench.clk(CLOCK);
	testbench.enable(ENABLE);
	testbench.rst(RESET);

	// Tracing
	#ifndef NOVCD
	sc_trace_file *tf;
	tf = sc_create_vcd_trace_file("mips");
	trace_mips(tf, testbench.mmips, "mips.");
	#endif

	// Initialize memories
	testbench.imem->mem_init("mips_mem.bin", 0, 0);
	testbench.dmem->mem_init("mips_mem.bin", 0x400000, 0);

	// Dump memory to disk
	testbench.imem->mem_dump("mips_rom.0.dump", 0);
	testbench.dmem->mem_dump("mips_ram.0.dump", 0);

	// Start simulation
	sc_initialize();

	// Enable the system
	ENABLE = 1;

	// Reset the system
	RESET = 1;
	CLOCK = 0; sc_cycle(period/2);
	CLOCK = 1; sc_cycle(period/2);
	RESET = 0;

	// Run till  pc == 40
	while( TRUE )
	{
		CLOCK = 0; sc_cycle(period/2);
		CLOCK = 1; sc_cycle(period/2);
		sim_time += 2*period;
		pc = sc_uint<32>(testbench.mmips->bus_pc.read());
		if( pc == 0x44 )
		{
			cout << "END: " << sim_time/period << " cycles " << sc_time_stamp() << endl;
			break;
		}
	}

	// Disable the system
	ENABLE = 0;

	// Dump memory to disk
	testbench.dmem->mem_dump("mips_ram.dump", 0);

	#ifndef NOVCD
	sc_close_vcd_trace_file(tf);
	#endif

	return 0;
}

