/*
 *  TU Eindhoven
 *  Eindhoven, The Netherlands
 *
 *  Name            :   ram.h
 *
 *  Author          :   Sander Stuijk (sander@ics.ele.tue.nl)
 *
 *  Date            :   January 23, 2006
 *
 *  Function        :   RAM memory (big-endian)
 *
 *  History         :
 *      26-01-06    :   Initial version.
 *
 */
 
#ifndef RAM_H_INCLUDED
#define RAM_H_INCLUDED

#include "mips.h"

SC_MODULE(RAM)
{
  sc_in< bool >                 clock;
  sc_in< bool >                 enable;
  sc_out< sc_bv<DWORD> >        dout;
  sc_out< bool >                wait;
  sc_in< sc_bv<DWORD> >         din;
  sc_in< sc_bv<DWORD> >         addr;
  sc_in< sc_bv<W_MEMREAD> >     r;
  sc_in< sc_bv<W_MEMWRITE> >    w;

  // Memory
  sc_bv<8> *mem;

  void mem_dump(const char *filename, int memoffset, int size=RAMSIZE);
  void mem_init(const char *filename, int fileoffset, int memoffset,
                        int size=RAMSIZE);

  void read();
  void write();
  
  SC_CTOR(RAM)
  {
    mem = new sc_bv<8> [RAMSIZE];

    SC_METHOD(read);
    sensitive_pos << clock;

    SC_METHOD(write);
    sensitive_pos << clock;
  }
};

#endif

