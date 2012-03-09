/*
 *  TU Eindhoven
 *  Eindhoven, The Netherlands
 *
 *  Name            :   bregisterfile16.h
 *
 *  Author          :   A.S.Slusarczyk@tue.nl
 *
 *  Date            :   
 *
 *  Function        :   Xilinx-Block-RAM-based register file
 *
 *
 */
  
#ifndef BREGISTERFILE16_H_INCLUDED
#define BREGISTERFILE16_H_INCLUDED

#include "mips.h"
#include "xlxram.h"

SC_MODULE(BRAM512x32_CONV) {
  
	sc_in< 	sc_bv<AWORDREG>	>	r_addr;
	sc_out< sc_bv<DWORD> 	>	r_data;
	
	sc_in< 	sc_bv<AWORDREG>	>	w_addr;
	sc_in< 	sc_bv<DWORD> 	>	w_data;
	sc_in<  sc_bv<1>  >         w;
	sc_in<	bool		    >   clk;

	sc_in<sc_int<32> > DOA;
	sc_in<sc_int<4> > DOPA;
	sc_out<sc_uint<9> > ADDRA;
	sc_out<sc_int<32> > DIA;
	sc_out<sc_int<4> > DIPA;
	sc_out<bool> ENA;
	sc_out<bool> CLKA;
	sc_out<bool> WEA;
	sc_out<bool> SSRA;

	sc_in<sc_int<32> > DOB;
	sc_in<sc_int<4> > DOPB;
	sc_out<sc_uint<9> > ADDRB;
	sc_out<sc_int<32> > DIB;
	sc_out<sc_int<4> > DIPB;
	sc_out<bool> ENB;
	sc_out<bool> CLKB;
	sc_out<bool> WEB;
	sc_out<bool> SSRB;

	void clock();
	void out();
	void in();
	
	SC_CTOR(BRAM512x32_CONV) {
	  SC_METHOD(in);
	  sensitive << r_addr << w_addr << w_data << w ;
	  
	  SC_METHOD(clock);
	  sensitive << clk;
		
	  SC_METHOD(out);
	  sensitive << DOA << DOB << DOPA << DOPB; 

	};
	
};

// 512x32 memory with separate read/write ports
SC_MODULE(BRAM512x32)
{
	sc_in< 	sc_bv<AWORDREG>	>	r_addr;
	sc_out< sc_bv<DWORD> 	>	r_data;
	
	sc_in< 	sc_bv<AWORDREG>	>	w_addr;
	sc_in< 	sc_bv<DWORD> 	>	w_data;
	sc_in<  sc_bv<1>  >         w;
	sc_in<	bool		    >   clk;

	RAMB16_S36_S36 *bram;
	BRAM512x32_CONV *conv;
	
	sc_signal<sc_int<32> > DOA;
	sc_signal<sc_uint<9> > ADDRA;
	sc_signal<sc_int<32> > DIA;
	sc_signal<bool> ENA;
	sc_signal<bool> CLKA;
	sc_signal<bool> WEA;
	sc_signal<bool> SSRA;
	sc_signal<sc_int<4> > DOPA, DIPA;

	sc_signal<sc_int<32> > DOB;
	sc_signal<sc_uint<9> > ADDRB;
	sc_signal<sc_int<32> > DIB;
	sc_signal<bool> ENB;
	sc_signal<bool> CLKB;
	sc_signal<bool> WEB;
	sc_signal<bool> SSRB;
	sc_signal<sc_int<4> > DOPB, DIPB;
	
	SC_CTOR(BRAM512x32) {
	  bram = new RAMB16_S36_S36("bramh");
	  conv = new BRAM512x32_CONV("conv");
	  
	  bram->ADDRA(ADDRA);
	  conv->ADDRA(ADDRA);
	  bram->ADDRB(ADDRB);
	  conv->ADDRB(ADDRB);
	  
	  bram->DIA(DIA);
	  conv->DIA(DIA);
	  bram->DIB(DIB);
	  conv->DIB(DIB);
	  
	  bram->DOA(DOA);
	  conv->DOA(DOA);
	  bram->DOB(DOB);
	  conv->DOB(DOB);

	  bram->DOPA(DOPA);
	  conv->DOPA(DOPA);
	  bram->DOPB(DOPB);
	  conv->DOPB(DOPB);
	  bram->DIPA(DIPA);
	  conv->DIPA(DIPA);
	  bram->DIPB(DIPB);
	  conv->DIPB(DIPB);

	  bram->CLKA(CLKA);
	  conv->CLKA(CLKA);
	  bram->CLKB(CLKB);
	  conv->CLKB(CLKB);
	  
	  bram->ENA(ENA);
	  conv->ENA(ENA);
	  bram->ENB(ENB);
	  conv->ENB(ENB);
	  
	  bram->WEA(WEA);
	  conv->WEA(WEA);
	  bram->WEB(WEB);
	  conv->WEB(WEB);
	  
	  bram->SSRA(SSRA);
	  conv->SSRA(SSRA);
	  bram->SSRB(SSRB);
	  conv->SSRB(SSRB);
	  
	  
	  conv->r_addr(r_addr);
	  conv->r_data(r_data);
	  conv->w_data(w_data);
	  conv->w_addr(w_addr);
	  conv->w(w);
	  conv->clk(clk);
	  
	};
  
};

// register file module with original interface
SC_MODULE(REGFILE16) {
	sc_in< 	sc_bv<AWORDREG>	>	r_addr_reg1;
	sc_out< sc_bv<DWORD> 	>	r_data_reg1;

	sc_in< 	sc_bv<AWORDREG>	>	r_addr_reg2;
	sc_out< sc_bv<DWORD> 	>	r_data_reg2;
	
	sc_in< 	sc_bv<AWORDREG>	>	w_addr_reg;
	sc_in< 	sc_bv<DWORD> 	>	w_data_reg;
	sc_in< 	sc_bv<1>	 	>	w;
	
	
	sc_in< 	bool > clk;
	
	BRAM512x32 *regs1, *regs2;
		
	SC_CTOR(REGFILE16) {
	  regs1 = new BRAM512x32("regs1");
	  regs2 = new BRAM512x32("regs2");
	  
	  regs1->r_addr(r_addr_reg1);
	  regs1->r_data(r_data_reg1);
	  regs1->w_data(w_data_reg);
	  regs1->w_addr(w_addr_reg);
	  regs1->w(w);
	  regs1->clk(clk);

	  regs2->r_addr(r_addr_reg2);
	  regs2->r_data(r_data_reg2);
	  regs2->w_data(w_data_reg);
	  regs2->w_addr(w_addr_reg);
	  regs2->w(w);
	  regs2->clk(clk);
	  
	};
};


#endif
