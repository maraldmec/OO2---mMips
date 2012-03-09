/*
 *  TU Eindhoven
 *  Eindhoven, The Netherlands
 *
 *  Name            :   branch.h
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
 
#ifndef BRANCH_H_INCLUDED
#define BRANCH_H_INCLUDED

#include "mips.h"

SC_MODULE(BRANCH_CTRL) {
	sc_in< 	sc_bv<W_BRANCHOP> > 	BranchOp;	// Branch operation
	sc_in< 	sc_bv<1> > 				AluZero;	// ALU zero
	sc_out< sc_bv<W_BRANCHFLAG> > 	Branch;		// Result
	
	void branch_ctrl();
	
	// Constructor
	SC_CTOR(BRANCH_CTRL) {
		SC_METHOD(branch_ctrl);
		sensitive << BranchOp << AluZero;
	}
};

#endif
