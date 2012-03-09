/*
 *  TU Eindhoven
 *  Eindhoven, The Netherlands
 *
 *  Name            :   memdev.h
 *
 *  Author          :   A.S.Slusarczyk@tue.nl
 *
 *  Date            :   
 *
 *  Function        :   Replacement for data memory to allow memory-mapped device
 *
 */

#ifndef MEMDEV_H_INCLUDED
#define MEMDEV_H_INCLUDED

#include <systemc.h>
#include "mips.h"

SC_MODULE(MEMDEV)
{
  // memdev has a regular memory interface
  sc_in< bool > clk;
  
  // we need both not-registered (before pipeline register) and registered 
  // address - both are available in mMIPS, so we use them
  sc_in < sc_bv<DWORD> > a_read;
  sc_in < sc_bv<DWORD> > a_read_reg; 
  sc_out< sc_bv<DWORD> > d_read;
  sc_in< sc_bv<DWORD> > d_write;
  sc_in< sc_bv<W_MEMWRITE> > w;
  sc_in< sc_bv<W_MEMREAD> > r;
  sc_out< bool > dmem_wait;
  
  // interface to communicate with 'regular' memory
  sc_in< sc_bv<DWORD> > ram_dout;
  sc_in< bool > ram_wait;
  sc_out< sc_bv<W_MEMWRITE> > ram_w;
  sc_out< sc_bv<W_MEMREAD> > ram_r;
  sc_out< sc_bv<DWORD> > ram_addr, ram_din;

  // interface to communicate with the device
  sc_in< sc_bv<DWORD> > dev_dout;
  sc_in<bool> dev_rdyr, dev_rdyw;
  sc_out< bool > dev_w, dev_r;
  sc_out< sc_bv<DWORD> > dev_din;
  sc_out< bool > dev_wdata, dev_waddr;
  sc_in< bool > dev_rcv_eop;
  sc_out< bool > dev_send_eop;
  
  // internal signals
  sc_signal<bool> bufw;
  sc_signal< sc_bv<DWORD> > dev_buffer;
  sc_signal<bool> sending, n_sending;
  
  // the actual logic 
  void memdev_process();
  // data buffering
  void buffer();
  
  SC_CTOR(MEMDEV){
	SC_METHOD(memdev_process);
	sensitive << a_read << a_read_reg << d_write << w << r << sending
			  << ram_dout << ram_wait << dev_rdyw << dev_rdyr 
			  << dev_buffer << dev_rcv_eop;
	
	SC_METHOD(buffer);
	sensitive_pos << clk;
  }
};


#endif
