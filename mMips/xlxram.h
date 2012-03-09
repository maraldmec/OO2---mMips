/*
  Simulation model of Xilinx FPGA BlockRAM memory
  2002 A.S.Slusarczyk@tue.nl
 */

#ifndef XLXRAM_H_INCLUDED
#define XLXRAM_H_INCLUDED

#include <systemc.h>
#include "mips.h"

#ifndef VERILOG
#include <vector>
using namespace std;
#endif


//////////////////////////////////////////////////////////////////////////////////
// Init/dump memory
//////////////////////////////////////////////////////////////////////////////////


#ifndef VERILOG // only used in simulation

// the init/dump routines assume that a set of W-bit memories is given 
// and a data word at address A is a concatenation of memory[0][A], memory[1][A], ...

template <int W>
void init_memory( vector<sc_int<W>* >* memories, const char* filename, int fileoffset, int memoffset, unsigned bytes  )

{
	unsigned words_read =0;
	unsigned char c;
	sc_int<32> w;
  	sc_int<W> mw;


	ifstream ramf(filename, ios::in | ios::binary);
	if( !ramf ) clog << "Cannot open memory file " << filename << endl;

        ramf.seekg(fileoffset, ios::beg);
	while (!ramf.eof()) {
	  // read word
	  w = 0;

	  for( int i = 0 ; i < 4; i++ ){
		c = ramf.get();
		// if EOF, pad word with zeros
		if(ramf.eof()) c=0;
                c &= 0xff;
		w <<= 8;
		w |= c;
	  }

	  for( unsigned mem = 0 ; mem < memories->size(); mem++ )
		{
		  mw = w.range( 31 - mem*W, 31 - mem*W - W+1 );
		  (*memories)[mem][ words_read+(memoffset/4) ] = mw;
		}

	  words_read++;
	  if( 4*words_read >= bytes ) { ramf.close(); return; }
	}
}

template <int W>
void dump_memory( vector<sc_int<W>* >* memories, const char* filename, int memoffset, unsigned bytes)
{
	ofstream ramf(filename, ios::out | ios::binary);
	unsigned char c;
	sc_int<W> mw;
	sc_int<32> w;
	unsigned words_written = 0;

	if( !ramf ) clog << "Cannot open memory file " << filename << endl;


	while( 4*words_written < bytes )
	  {
		w = 0;
		for( unsigned mem = 0 ; mem < memories->size(); mem++ )
		  w.range( 31 - mem*W, 31 - mem*W - W+1 ) = (*memories)[mem][ words_written+memoffset/4 ];

		for( int i = 0 ; i < 4; i++ )
		  {
			c = w.range(31,24);
			ramf.put(c);
			w <<= 8;
		  }
		words_written++;
	  }
	
}


#endif // VERILOG


//////////////////////////////////////////////////////////////////////////////////
// Dual-port memory 256x16
//////////////////////////////////////////////////////////////////////////////////

SC_MODULE(RAMB4_S16_S16){
	sc_int<16> memory[256];	
	
	sc_out<sc_int<16> > DOA;
	sc_in<sc_uint<8> > ADDRA;
	sc_in<sc_int<16> > DIA;
	sc_in<bool> ENA;
	sc_in<bool> CLKA;
	sc_in<bool> WEA;
	sc_in<bool> RSTA;

	sc_out<sc_int<16> > DOB;
	sc_in<sc_uint<8> > ADDRB;
	sc_in<sc_int<16> > DIB;
	sc_in<bool> ENB;
	sc_in<bool> CLKB;
	sc_in<bool> WEB;
	sc_in<bool> RSTB;


	void portA();
	void portB();
	
	SC_CTOR(RAMB4_S16_S16){
	  SC_METHOD(portA);
	  sensitive_pos << CLKA;
	  SC_METHOD(portB);
	  sensitive_pos << CLKB;
	}
	
};

//////////////////////////////////////////////////////////////////////////////////
// Dual-port memory 512x8
//////////////////////////////////////////////////////////////////////////////////

SC_MODULE(RAMB4_S8_S8){
	sc_int<8> memory[512];	
	
	sc_out<sc_int<8> > DOA;
	sc_in<sc_uint<9> > ADDRA;
	sc_in<sc_int<8> > DIA;
	sc_in<bool> ENA;
	sc_in<bool> CLKA;
	sc_in<bool> WEA;
	sc_in<bool> RSTA;

	sc_out<sc_int<8> > DOB;
	sc_in<sc_uint<9> > ADDRB;
	sc_in<sc_int<8> > DIB;
	sc_in<bool> ENB;
	sc_in<bool> CLKB;
	sc_in<bool> WEB;
	sc_in<bool> RSTB;


	void portA();
	void portB();
	
	SC_CTOR(RAMB4_S8_S8){
	  SC_METHOD(portA);
	  sensitive_pos << CLKA;
	  SC_METHOD(portB);
	  sensitive_pos << CLKB;
	}
	
};


//////////////////////////////////////////////////////////////////////////////////
// 18kb dual-port memory 512x36
//////////////////////////////////////////////////////////////////////////////////

SC_MODULE(RAMB16_S36_S36){

    sc_int<32> memory[512];
	sc_int<4> parity[512];
	
	sc_out<sc_int<32> > DOA;
	sc_out<sc_int<4> > DOPA;
	sc_in<sc_uint<9> > ADDRA;
	sc_in<sc_int<32> > DIA;
	sc_in<sc_int<4> > DIPA;
	sc_in<bool> ENA;
	sc_in<bool> CLKA;
	sc_in<bool> WEA;
	sc_in<bool> SSRA;

	sc_out<sc_int<32> > DOB;
	sc_out<sc_int<4> > DOPB;
	sc_in<sc_uint<9> > ADDRB;
	sc_in<sc_int<32> > DIB;
	sc_in<sc_int<4> > DIPB;
	sc_in<bool> ENB;
	sc_in<bool> CLKB;
	sc_in<bool> WEB;
	sc_in<bool> SSRB;


	void portA();
	void portB();
	
	SC_CTOR(RAMB16_S36_S36){
	  SC_METHOD(portA);
	  sensitive_pos << CLKA;
	  SC_METHOD(portB);
	  sensitive_pos << CLKB;
	}
	
};

//////////////////////////////////////////////////////////////////////////////////
// 18kb dual-port memory 2048x9
//////////////////////////////////////////////////////////////////////////////////

SC_MODULE(RAMB16_S9_S9){

    sc_int<8> memory[2048];
	sc_int<1> parity[2048];
	
	sc_out<sc_int<8> > DOA;
	sc_out<sc_int<1> > DOPA;
	sc_in<sc_uint<11> > ADDRA;
	sc_in<sc_int<8> > DIA;
	sc_in<sc_int<1> > DIPA;
	sc_in<bool> ENA;
	sc_in<bool> CLKA;
	sc_in<bool> WEA;
	sc_in<bool> SSRA;

	sc_out<sc_int<8> > DOB;
	sc_out<sc_int<1> > DOPB;
	sc_in<sc_uint<11> > ADDRB;
	sc_in<sc_int<8> > DIB;
	sc_in<sc_int<1> > DIPB;
	sc_in<bool> ENB;
	sc_in<bool> CLKB;
	sc_in<bool> WEB;
	sc_in<bool> SSRB;


	void portA();
	void portB();
	
	SC_CTOR(RAMB16_S9_S9){
	  SC_METHOD(portA);
	  sensitive_pos << CLKA;
	  SC_METHOD(portB);
	  sensitive_pos << CLKB;
	}
	
};


//////////////////////////////////////////////////////////////////////////////////
// 18kb dual-port memory 16Kx1
//////////////////////////////////////////////////////////////////////////////////

SC_MODULE(RAMB16_S1_S1){

    sc_int<1> memory[16384];
	
	sc_out<sc_int<1> > DOA;
	sc_in<sc_uint<14> > ADDRA;
	sc_in<sc_int<1> > DIA;
	sc_in<bool> ENA;
	sc_in<bool> CLKA;
	sc_in<bool> WEA;
	sc_in<bool> SSRA;

	sc_out<sc_int<1> > DOB;
	sc_in<sc_uint<14> > ADDRB;
	sc_in<sc_int<1> > DIB;
	sc_in<bool> ENB;
	sc_in<bool> CLKB;
	sc_in<bool> WEB;
	sc_in<bool> SSRB;


	void portA();
	void portB();
	
	SC_CTOR(RAMB16_S1_S1){
	  SC_METHOD(portA);
	  sensitive_pos << CLKA;
	  SC_METHOD(portB);
	  sensitive_pos << CLKB;
	}
	
};

//////////////////////////////////////////////////////////////////////////////////
// 18kb dual-port memory 8Kx2
//////////////////////////////////////////////////////////////////////////////////

SC_MODULE(RAMB16_S2_S2){

    sc_int<2> memory[8192];
	
	sc_out<sc_int<2> > DOA;
	sc_in<sc_uint<13> > ADDRA;
	sc_in<sc_int<2> > DIA;
	sc_in<bool> ENA;
	sc_in<bool> CLKA;
	sc_in<bool> WEA;
	sc_in<bool> SSRA;

	sc_out<sc_int<2> > DOB;
	sc_in<sc_uint<13> > ADDRB;
	sc_in<sc_int<2> > DIB;
	sc_in<bool> ENB;
	sc_in<bool> CLKB;
	sc_in<bool> WEB;
	sc_in<bool> SSRB;


	void portA();
	void portB();
	
	SC_CTOR(RAMB16_S2_S2){
	  SC_METHOD(portA);
	  sensitive_pos << CLKA;
	  SC_METHOD(portB);
	  sensitive_pos << CLKB;
	}
	
};

//////////////////////////////////////////////////////////////////////////////////
// 18kb dual-port memory 4Kx4
//////////////////////////////////////////////////////////////////////////////////

SC_MODULE(RAMB16_S4_S4){

    sc_int<4> memory[4096];
	
	sc_out<sc_int<4> > DOA;
	sc_in<sc_uint<12> > ADDRA;
	sc_in<sc_int<4> > DIA;
	sc_in<bool> ENA;
	sc_in<bool> CLKA;
	sc_in<bool> WEA;
	sc_in<bool> SSRA;

	sc_out<sc_int<4> > DOB;
	sc_in<sc_uint<12> > ADDRB;
	sc_in<sc_int<4> > DIB;
	sc_in<bool> ENB;
	sc_in<bool> CLKB;
	sc_in<bool> WEB;
	sc_in<bool> SSRB;


	void portA();
	void portB();
	
	SC_CTOR(RAMB16_S4_S4){
	  SC_METHOD(portA);
	  sensitive_pos << CLKA;
	  SC_METHOD(portB);
	  sensitive_pos << CLKB;
	}
	
};



#endif
