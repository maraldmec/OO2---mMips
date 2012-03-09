/*
 *  TU Eindhoven
 *  Eindhoven, The Netherlands
 *
 *  Name            :   rom.h
 *
 *  Author          :   Sander Stuijk (sander@ics.ele.tue.nl)
 *
 *  Date            :   January 23, 2006
 *
 *  Function        :   ROM memory (big-endian)
 *
 *  History         :
 *      26-01-06    :   Initial version.
 *
 */
 
#ifndef ROM_H_INCLUDED
#define ROM_H_INCLUDED

#include "mips.h"

SC_MODULE(ROM)
{
  sc_in< bool >                 clock;
  sc_in< bool >                 enable;
  sc_out< sc_bv<DWORD> >        dout;
  sc_out< bool >                wait;
  sc_in< sc_bv<DWORD> >         addr;
  sc_in< sc_bv<1> >             r;

  // Memory
  sc_bv<8> *mem;

  void mem_dump(const char *filename, int memoffset, int size=ROMSIZE);
  void mem_init(const char *filename, int fileoffset, int memoffset,
                        int size=ROMSIZE);

  void read();
  
  SC_CTOR(ROM)
  {
    mem = new sc_bv<8> [RAMSIZE];

    SC_METHOD(read);
    sensitive_pos << clock;
  }
};

#endif

