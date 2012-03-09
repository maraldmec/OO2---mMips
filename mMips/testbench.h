/*
 *  TU Eindhoven
 *  Eindhoven, The Netherlands
 *
 *  Name            :   testbench.h
 *
 *  Author          :   Sander Stuijk (sander@ics.ele.tue.nl)
 *
 *  Date            :   January 23, 2006
 *
 *  Function        :   MIPS testbench
 *
 *  History         :
 *      26-01-06    :   Initial version.
 *
 */

#ifndef TESTBENCH_H_INCLUDED
#define TESTBENCH_H_INCLUDED

#include "mmips.h"
#include "rom.h"
#include "ram.h"
#include "dev.h"

SC_MODULE(TESTBENCH)
{
  sc_in< bool > clk;
  sc_in< bool > enable;
  sc_in< bool > rst;

  // Modules
  mMIPS *mmips;
  ROM   *imem;
  RAM   *dmem;
  DEV   *dev;

  // Signals
  sc_signal< sc_bv<DWORD> >     bus_rom_dout;
  sc_signal< bool >             bus_rom_wait;
  sc_signal< sc_bv<DWORD> >     bus_rom_addr;
  sc_signal< sc_bv<1> >         bus_rom_r;
  sc_signal< sc_bv<DWORD> >     bus_ram_dout;
  sc_signal< bool >             bus_ram_wait;
  sc_signal< sc_bv<DWORD> >     bus_ram_din;
  sc_signal< sc_bv<DWORD> >     bus_ram_addr;
  sc_signal< sc_bv<W_MEMREAD> > bus_ram_r;
  sc_signal< sc_bv<W_MEMWRITE> > bus_ram_w;
  sc_signal< sc_bv<DWORD> >     bus_dev_dout;
  sc_signal< sc_bv<DWORD> >     bus_dev_din;
  sc_signal< bool >             bus_dev_r;
  sc_signal< bool >             bus_dev_w;
  sc_signal< bool >             bus_dev_rdyr;
  sc_signal< bool >             bus_dev_rdyw;
  sc_signal< bool >             bus_dev_wdata;
  sc_signal< bool >             bus_dev_waddr;
  sc_signal< bool >             bus_dev_send_eop;
  sc_signal< bool >             bus_dev_rcv_eop;

  SC_CTOR(TESTBENCH)
  {
    // Modules
    mmips = new mMIPS("mmips");
    imem = new ROM("imem");
    dmem = new RAM("dmem");
    dev = new DEV("dev");

    // Connections
    mmips->clk(clk);
    mmips->enable(enable);
    mmips->rst(rst);
    mmips->rom_dout(bus_rom_dout);
    mmips->rom_wait(bus_rom_wait);
    mmips->rom_addr(bus_rom_addr);
    mmips->rom_r(bus_rom_r);
    mmips->ram_dout(bus_ram_dout);
    mmips->ram_wait(bus_ram_wait);
    mmips->ram_din(bus_ram_din);
    mmips->ram_addr(bus_ram_addr);
    mmips->ram_r(bus_ram_r);
    mmips->ram_w(bus_ram_w);
    mmips->dev_dout(bus_dev_dout);
    mmips->dev_din(bus_dev_din);
    mmips->dev_r(bus_dev_r);
    mmips->dev_w(bus_dev_w);
    mmips->dev_rdyr(bus_dev_rdyr);
    mmips->dev_rdyw(bus_dev_rdyw);
    mmips->dev_wdata(bus_dev_wdata);
    mmips->dev_waddr(bus_dev_waddr);
    mmips->dev_send_eop(bus_dev_send_eop);
    mmips->dev_rcv_eop(bus_dev_rcv_eop);

    imem->clock(clk);
    imem->enable(enable);
    imem->dout(bus_rom_dout);
    imem->wait(bus_rom_wait);
    imem->addr(bus_rom_addr);
    imem->r(bus_rom_r);

    dmem->clock(clk);
    dmem->enable(enable);
    dmem->dout(bus_ram_dout);
    dmem->wait(bus_ram_wait);
    dmem->din(bus_ram_din);
    dmem->addr(bus_ram_addr);
    dmem->r(bus_ram_r);
    dmem->w(bus_ram_w);

    dev->clock(clk);
    dev->enable(enable);
    dev->dout(bus_dev_dout);
    dev->din(bus_dev_din);
    dev->r(bus_dev_r);
    dev->w(bus_dev_w);
    dev->rdyr(bus_dev_rdyr);
    dev->rdyw(bus_dev_rdyw);
    dev->wdata(bus_dev_wdata);
    dev->waddr(bus_dev_waddr);
    dev->send_eop(bus_dev_send_eop);
    dev->rcv_eop(bus_dev_rcv_eop);
  }
};

#endif

