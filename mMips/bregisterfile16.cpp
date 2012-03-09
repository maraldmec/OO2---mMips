/*
 *  TU Eindhoven
 *  Eindhoven, The Netherlands
 *
 *  Name            :   bregisterfile16.cpp
 *
 *  Author          :   A.S.Slusarczyk@tue.nl
 *
 *  Date            :   
 *
 *  Function        :   Xilinx-Block-RAM-based register file
 *
 *
 */
 
#include "bregisterfile16.h"

void BRAM512x32_CONV::clock()
{
  bool c = clk.read();
  CLKA.write(c);  
  // writing B - port on falling edge
  CLKB.write(!c);
}

void BRAM512x32_CONV::in()
{  
  // pad read/write address to 9 bits
  sc_bv<4> zero4(0);
  sc_bv<9> w_addr9 = ( zero4, w_addr.read() );
  sc_bv<9> r_addr9 = ( zero4, r_addr.read() );
  
  ADDRA.write(r_addr9); ADDRB.write(w_addr9); 

  // route write data to B ports of the memory
  sc_bv<DWORD> dwr = w_data.read();
  DIB.write(dwr); DIPB.write(0);
  // B-port write enable
  WEB.write(w.read()[0]!=0);

  // A port never writes
  DIA.write(0); DIPA.write(0); WEA.write(0);

  // always enabled
  ENA.write(1); ENB.write(1);
  SSRA.write(0); SSRB.write(0);
}

void BRAM512x32_CONV::out()
{
  sc_bv<DWORD> data;
  
  data = DOA.read();
  r_data.write(data);
}

