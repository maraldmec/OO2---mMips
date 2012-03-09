/*
 *  TU Eindhoven
 *  Eindhoven, The Netherlands
 *
 *  Name            :   mips_trace.h
 *
 *  Author          :   A.S.Slusarczyk@tue.nl
 *
 *  Date            :   
 *
 *  Function        :   Tracing functions
 *                      The functions add the tracing of the signals of their argument
 *                      module to the tracefile 'tf'. The names of the traced signals
 *                      will start with 'prefix'.
 *
 */

#ifndef MIPS_TRACE_H_INCLUDED
#define MIPS_TRACE_H_INCLUDED

#include "mmips.h"

void trace_mips( sc_trace_file *tf, mMIPS *mips, const char *prefix );

#endif
