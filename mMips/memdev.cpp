/*
 *  TU Eindhoven
 *  Eindhoven, The Netherlands
 *
 *  Name            :   memdev.cpp
 *
 *  Author          :   A.S.Slusarczyk@tue.nl
 *
 *  Date            :   
 *
 *  Function        :   Replacement for data memory to allow memory-mapped device
 *
 */

#include "memdev.h"

void MEMDEV::buffer()
{
  if( bufw.read() )
    dev_buffer = dev_dout.read();
  
  sending.write( n_sending ); 
}

void MEMDEV::memdev_process()
{
  // device is selected by setting the 31st bit of the address (address 0x80000000)
  bool dev_select = (a_read.read()[31]==1), reg_dev_select = (a_read_reg.read()[31]==1);
  // the control word is at address 0x80000004 - hence testing bit 2
  bool addr = (a_read.read()[2]==1), addr_reg = (a_read_reg.read()[2]==1);
  // send action is triggered by writing bit #17 to control word (0x80000004)
  bool send = (d_write.read()[17]==1);
  // packet is closed by asserting bit #20 together with send (#17)
  bool eop = (d_write.read()[20]==1);
  
  // just forward data and address to memory
  ram_addr.write( a_read.read() );
  ram_din.write( d_write.read() );
  // ... but switch-off writing and reading in the device-access-mode
  sc_bv<2> z2(0);
  ram_w.write( !dev_select ? w.read() : z2 );
  ram_r.write( !dev_select ? r.read() : z2 );

  // if device is selected, register its output
  bufw.write( dev_select );

  dev_din.write( d_write.read() );
  bool wr = (dev_select && (w.read()[0]!=0)), rd = (dev_select && (r.read()[0]!=0));
  // we're sending (s) if the device is selected, control word is written and the 
  // value of bit #17 is one
  // we're reading if the read request for address 0x80000000 is present
  bool s = wr && send && addr,  r = rd && !addr;

  dev_w.write( s );
  dev_r.write( r );
  dev_send_eop.write( s && eop );
  
  dev_wdata.write( wr && !addr );
  dev_waddr.write( wr && addr );
  
  // 's' triggers 'sending' state, which lasts until device-write-ready appears
  n_sending = s || (sending.read() && !dev_rdyw.read());

#ifdef NETPRINT
  if( s ) cout << name() << " send to address " << d_write.read().range(15,8).to_uint() << ',' << d_write.read().range(7,0).to_uint() << " @" << sc_time_stamp() << endl; 
  if( wr && !addr ) cout << name() << " writing data 0x" << hex << d_write.read().to_uint() << " @" << sc_time_stamp() << endl; 
#endif
  
  // when reading control word (0x80000004) you get only three bits set:
  // #16 - device has new data, #18 - device is ready to send, 
  // #19 - with #16 (new data) means it's the last data word of a packet
  sc_bv<32> status(0);
  status[16] = dev_rdyr.read();
  status[18] = ! sending.read();
  status[19] = dev_rcv_eop.read();
  

  // select output - device data (buffered), device status, or regular memory
  d_read.write( reg_dev_select ? (addr_reg ? status : dev_buffer.read()) : ram_dout.read() );

  // we can only wait for regular memory - the device access is non-blocking 
  // (if you're not careful, i.e. reading when status[16] is zero or writing
  // when status[18] is zero,  you may overwrite data or read garbage)
  dmem_wait.write( !reg_dev_select && ram_wait.read() );
  
}

