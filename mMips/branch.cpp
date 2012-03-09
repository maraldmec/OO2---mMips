/*
 *  TU Eindhoven
 *  Eindhoven, The Netherlands
 *
 *  Name            :   branch.cc
 *
 *  Author          :   Sander Stuijk (sander@ics.ele.tue.nl)
 *
 *  Date            :   July 23, 2002
 *
 *  Function        :   Branch controller
 *
 *  History         :
 *      23-07-02    :   Initial version.
 *      13-12-02    :   Synthesizable version A.S.Slusarczyk@tue.nl
 *
 */
 
#include "branch.h"

void BRANCH_CTRL::branch_ctrl()
{
	sc_uint<W_BRANCHOP> 	branchop;
	sc_uint<W_BRANCHFLAG>	branch;
	sc_uint<1> aluzero;

	#ifdef VERBOSE
		clog << "BRANCH CTRL" << endl;
	#endif
	
	// Read inputs
	branchop = BranchOp.read();
	aluzero = AluZero.read();
	
	// Compute result
	switch (branchop)
	{
		case 0:	// No branch
				branch = 0;
				break;
		
		case 1:	// Branch on equal
				branch = (aluzero == 1 ? 1:0); 
				break;
				
		case 2:	// Branch on non equal
				branch = (aluzero != 1 ? 1:0); 
				break;
		
		case 3:	// Jump
				branch = 1;
				break;
	}
				
	// Set result on output
	Branch.write(branch);
}
