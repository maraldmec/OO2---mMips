/*
 *  TU Eindhoven
 *  Eindhoven, The Netherlands
 *
 *  Name            :   dev.h
 *
 *  Author          :   Sander Stuijk (sander@ics.ele.tue.nl)
 *
 *  Date            :   January 23, 2006
 *
 *  Function        :   Device handler (shell)
 *
 *  History         :
 *      26-01-06    :   Initial version.
 *
 */

#ifndef DEV_H_INCLUDED
#define DEV_H_INCLUDED

#include "mips.h"

SC_MODULE(DEV)
{
  sc_in< bool >             clock;
  sc_in< bool >             enable;
  sc_in< sc_bv<DWORD> >     dout;
  sc_out< sc_bv<DWORD> >    din;
  sc_in< bool >             r;
  sc_in< bool >             w;
  sc_out< bool >            rdyr;
  sc_out< bool >            rdyw;
  sc_in< bool >             wdata;
  sc_in< bool >             waddr;
  sc_in< bool >             send_eop;
  sc_out< bool >            rcv_eop;

  SC_CTOR(DEV)
  {
  }
};

#endif

