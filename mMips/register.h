/*
 *  TU Eindhoven
 *  Eindhoven, The Netherlands
 *
 *  Name            :   register.h
 *
 *  Author          :   Sander Stuijk (sander@ics.ele.tue.nl)
 *
 *  Date            :   July 23, 2002
 *
 *  Function        :   Register
 *
 *  History         :
 *      23-07-02    :   Initial version.
 *      13-12-02    :   Synthesizable version A.S.Slusarczyk@tue.nl
 *
 */
 
#ifndef REGISTER_H_INCLUDED 
#define REGISTER_H_INCLUDED

#include "mips.h"

SC_MODULE(REGISTER_DWORD) {
  sc_in< sc_bv<DWORD> > in;
  sc_in< sc_bv<1> > w;
  sc_out< sc_bv<DWORD> > out;
  
  sc_in<bool> rst, clk;
  
  SC_CTOR(REGISTER_DWORD) {
	SC_METHOD(reg);
	sensitive_pos << clk << rst;
  }
  void reg(){
	if( rst.read() == 1 )
	  out.write(0);
	else{
	  if(w.read()[0] == 1)
		out.write(in.read());
	  else
		out.write(out.read());
	}
  }
};

SC_MODULE(REGISTER_AWORDREG) {
  sc_in< sc_bv<AWORDREG> > in;
  sc_in< sc_bv<1> > w;
  sc_out< sc_bv<AWORDREG> > out;
  
  sc_in<bool> rst, clk;
  
  SC_CTOR(REGISTER_AWORDREG) {
	SC_METHOD(reg);
	sensitive_pos << clk << rst;
  }
  void reg(){
	if( rst.read() == 1 )
	  out.write(0);
	else{
	  if(w.read()[0] == 1)
		out.write(in.read());
	  else
		out.write(out.read());
	}
  }
};

SC_MODULE(REGISTER_1) {
  sc_in< sc_bv<1> > in;
  sc_in< sc_bv<1> > w;
  sc_out< sc_bv<1> > out;
  
  sc_in<bool> rst, clk;
  
  SC_CTOR(REGISTER_1) {
	SC_METHOD(reg);
	sensitive_pos << clk << rst;
  }
  void reg(){
	if( rst.read() == 1 )
	  out.write(0);
	else{
	  if(w.read()[0] == 1)
		out.write(in.read());
	  else
		out.write(out.read());
	}
  }
};

SC_MODULE(REGISTER_5) {
  sc_in< sc_bv<5> > in;
  sc_in< sc_bv<1> > w;
  sc_out< sc_bv<5> > out;
  
  sc_in<bool> rst, clk;
  
  SC_CTOR(REGISTER_5) {
	SC_METHOD(reg);
	sensitive_pos << clk << rst;
  }
  void reg(){
	if( rst.read() == 1 )
	  out.write(0);
	else{
	  if(w.read()[0] == 1)
		out.write(in.read());
	  else
		out.write(out.read());
	}
  }
};

SC_MODULE(REGISTER_6) {
  sc_in< sc_bv<6> > in;
  sc_in< sc_bv<1> > w;
  sc_out< sc_bv<6> > out;
  
  sc_in<bool> rst, clk;
  
  SC_CTOR(REGISTER_6) {
	SC_METHOD(reg);
	sensitive_pos << clk << rst;
  }
  void reg(){
	if( rst.read() == 1 )
	  out.write(0);
	else{
	  if(w.read()[0] == 1)
		out.write(in.read());
	  else
		out.write(out.read());
	}
  }
};

SC_MODULE(REGISTER_W_ALUSRC) {
  sc_in< sc_bv<W_ALUSRC> > in;
  sc_in< sc_bv<1> > w;
  sc_out< sc_bv<W_ALUSRC> > out;
  
  sc_in<bool> rst, clk;
  
  SC_CTOR(REGISTER_W_ALUSRC) {
	SC_METHOD(reg);
	sensitive_pos << clk << rst;
  }
  void reg(){
	if( rst.read() == 1 )
	  out.write(0);
	else{
	  if(w.read()[0] == 1)
		out.write(in.read());
	  else
		out.write(out.read());
	}
  }
};



SC_MODULE(REGISTER_W_ALUOP) {
  sc_in< sc_bv<W_ALUOP> > in;
  sc_in< sc_bv<1> > w;
  sc_out< sc_bv<W_ALUOP> > out;
  
  sc_in<bool> rst, clk;
  
  SC_CTOR(REGISTER_W_ALUOP) {
	SC_METHOD(reg);
	sensitive_pos << clk << rst;
  }
  void reg(){
	if( rst.read() == 1 )
	  out.write(0);
	else{
	  if(w.read()[0] == 1)
		out.write(in.read());
	  else
		out.write(out.read());
	}
  }
};

SC_MODULE(REGISTER_W_REGDST) {
  sc_in< sc_bv<W_REGDST> > in;
  sc_in< sc_bv<1> > w;
  sc_out< sc_bv<W_REGDST> > out;
  
  sc_in<bool> rst, clk;
  
  SC_CTOR(REGISTER_W_REGDST) {
	SC_METHOD(reg);
	sensitive_pos << clk << rst;
  }
  void reg(){
	if( rst.read() == 1 )
	  out.write(0);
	else{
	  if(w.read()[0] == 1)
		out.write(in.read());
	  else
		out.write(out.read());
	}
  }
};

SC_MODULE(REGISTER_W_REGVAL) {
  sc_in< sc_bv<W_REGVAL> > in;
  sc_in< sc_bv<1> > w;
  sc_out< sc_bv<W_REGVAL> > out;
  
  sc_in<bool> rst, clk;
  
  SC_CTOR(REGISTER_W_REGVAL) {
	SC_METHOD(reg);
	sensitive_pos << clk << rst;
  }
  void reg(){
	if( rst.read() == 1 )
	  out.write(0);
	else{
	  if(w.read()[0] == 1)
		out.write(in.read());
	  else
		out.write(out.read());
	}
  }
};

SC_MODULE(REGISTER_W_TARGET) {
  sc_in< sc_bv<W_TARGET> > in;
  sc_in< sc_bv<1> > w;
  sc_out< sc_bv<W_TARGET> > out;
  
  sc_in<bool> rst, clk;
  
  SC_CTOR(REGISTER_W_TARGET) {
	SC_METHOD(reg);
	sensitive_pos << clk << rst;
  }
  void reg(){
	if( rst.read() == 1 )
	  out.write(0);
	else{
	  if(w.read()[0] == 1)
		out.write(in.read());
	  else
		out.write(out.read());
	}
  }
};

SC_MODULE(REGISTER_W_BRANCHOP) {
  sc_in< sc_bv<W_BRANCHOP> > in;
  sc_in< sc_bv<1> > w;
  sc_out< sc_bv<W_BRANCHOP> > out;
  
  sc_in<bool> rst, clk;
  
  SC_CTOR(REGISTER_W_BRANCHOP) {
	SC_METHOD(reg);
	sensitive_pos << clk << rst;
  }
  void reg(){
	if( rst.read() == 1 )
	  out.write(0);
	else{
	  if(w.read()[0] == 1)
		out.write(in.read());
	  else
		out.write(out.read());
	}
  }
};

SC_MODULE(REGISTER_W_MEMWRITE) {
  sc_in< sc_bv<W_MEMWRITE> > in;
  sc_in< sc_bv<1> > w;
  sc_out< sc_bv<W_MEMWRITE> > out;
  
  sc_in<bool> rst, clk;
  
  SC_CTOR(REGISTER_W_MEMWRITE) {
	SC_METHOD(reg);
	sensitive_pos << clk << rst;
  }
  void reg(){
	if( rst.read() == 1 )
	  out.write(0);
	else{
	  if(w.read()[0] == 1)
		out.write(in.read());
	  else
		out.write(out.read());
	}
  }
};

SC_MODULE(REGISTER_W_MEMREAD) {
  sc_in< sc_bv<W_MEMREAD> > in;
  sc_in< sc_bv<1> > w;
  sc_out< sc_bv<W_MEMREAD> > out;
  
  sc_in<bool> rst, clk;
  
  SC_CTOR(REGISTER_W_MEMREAD) {
	SC_METHOD(reg);
	sensitive_pos << clk << rst;
  }
  void reg(){
	if( rst.read() == 1 )
	  out.write(0);
	else{
	  if(w.read()[0] == 1)
		out.write(in.read());
	  else
		out.write(out.read());
	}
  }
};


SC_MODULE(REGISTER_W_REGWRITE) {
  sc_in< sc_bv<W_REGWRITE> > in;
  sc_in< sc_bv<1> > w;
  sc_out< sc_bv<W_REGWRITE> > out;
  
  sc_in<bool> rst, clk;
  
  SC_CTOR(REGISTER_W_REGWRITE) {
	SC_METHOD(reg);
	sensitive_pos << clk << rst;
  }
  void reg(){
	if( rst.read() == 1 )
	  out.write(0);
	else{
	  if(w.read()[0] == 1)
		out.write(in.read());
	  else
		out.write(out.read());
	}
  }
};

SC_MODULE(REGISTER_W_MEMTOREG) {
  sc_in< sc_bv<W_MEMTOREG> > in;
  sc_in< sc_bv<1> > w;
  sc_out< sc_bv<W_MEMTOREG> > out;
  
  sc_in<bool> rst, clk;
  
  SC_CTOR(REGISTER_W_MEMTOREG) {
	SC_METHOD(reg);
	sensitive_pos << clk << rst;
  }
  void reg(){
	if( rst.read() == 1 )
	  out.write(0);
	else{
	  if(w.read()[0] == 1)
		out.write(in.read());
	  else
		out.write(out.read());
	}
  }
};

SC_MODULE(REGISTER_W_HILO_W) {
  sc_in< sc_bv<W_HILO_W> > in;
  sc_in< sc_bv<1> > w;
  sc_out< sc_bv<W_HILO_W> > out;

  sc_in<bool> rst, clk;

  SC_CTOR(REGISTER_W_HILO_W) {
	SC_METHOD(reg);
	sensitive_pos << clk << rst;
  }
  void reg(){
	if( rst.read() == 1 )
	  out.write(0);
	else{
	  if(w.read()[0] == 1)
		out.write(in.read());
	  else
		out.write(out.read());
	}
  }
};

SC_MODULE(REGISTER_W_HILOALU_S) {
  sc_in< sc_bv<W_HILOALU_S> > in;
  sc_in< sc_bv<1> > w;
  sc_out< sc_bv<W_HILOALU_S> > out;

  sc_in<bool> rst, clk;

  SC_CTOR(REGISTER_W_HILOALU_S) {
	SC_METHOD(reg);
	sensitive_pos << clk << rst;
  }
  void reg(){
	if( rst.read() == 1 )
	  out.write(0);
	else{
	  if(w.read()[0] == 1)
		out.write(in.read());
	  else
		out.write(out.read());
	}
  }
};

#endif
