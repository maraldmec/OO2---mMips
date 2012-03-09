/*
  Simulation model of Xilinx FPGA BlockRAM memory
  2002 A.S.Slusarczyk@tue.nl
 */

#include "xlxram.h"

//////////////////////////////////////////////////////////////////////////////////
// Dual-port memory 256x16
//////////////////////////////////////////////////////////////////////////////////

void RAMB4_S16_S16::portA()
{
  		sc_uint<8> _address = ADDRA.read();
		sc_int<16> _v;
		
#ifdef VERBOSE
		clog << "BlockRAM:A ADDR=" << _address << " EN=" << ENA.read() << " WE=" << WEA.read() << " DI=" << DIA.read() << " RST=" << RSTA.read() << endl;
#endif
		if( ENA.read() )
		  {
			if( RSTA.read() )
			  {
				DOA.write(0);
			  }
			else
			  {
				if( WEA.read() ){
				  _v = DIA.read();
				  memory[_address]=_v;
				  DOA.write(_v);
				} else {
				  _v = memory[_address];
				  DOA.write(_v);
				}
#ifdef VERBOSE
				clog << "RAM[" << _address << "]=" << _v << endl;
#endif
			  }
		  }

}
void RAMB4_S16_S16::portB()
{
  		sc_uint<8> _address = ADDRB.read();
		sc_int<16> _v;
		
#ifdef VERBOSE
		clog << "BlockRAM ADDR=" << _address << " EN=" << ENB.read() << " WE=" << WEB.read() << " DI=" << DIB.read() << " RST=" << RSTB.read() << endl;
#endif
		if( ENB.read() )
		  {
			if( RSTB.read() )
			  {
				DOB.write(0);
			  }
			else
			  {
				if( WEB.read() ){
				  _v = DIB.read();
				  memory[_address]=_v;
				  DOB.write(_v);
				} else {
				  _v = memory[_address];
				  DOB.write(_v);
				}
#ifdef VERBOSE
				clog << "RAM[" << _address << "]=" << _v << endl;
#endif
			  }
		  }

}

//////////////////////////////////////////////////////////////////////////////////
// Dual-port memory 512x8
//////////////////////////////////////////////////////////////////////////////////

void RAMB4_S8_S8::portA()
{
  		sc_uint<9> _address = ADDRA.read();
		sc_int<8> _v;
		
#ifdef VERBOSE
		clog << "BlockRAM:A ADDR=" << _address << " EN=" << ENA.read() << " WE=" << WEA.read() << " DI=" << DIA.read() << " RST=" << RSTA.read() << endl;
#endif
		if( ENA.read() )
		  {
			if( RSTA.read() )
			  {
				DOA.write(0);
			  }
			else
			  {
				if( WEA.read() ){
				  _v = DIA.read();
				  memory[_address]=_v;
				  DOA.write(_v);
				} else {
				  _v = memory[_address];
				  DOA.write(_v);
				}
#ifdef VERBOSE
				clog << "RAM[" << _address << "]=" << _v << endl;
#endif
			  }
		  }

}
void RAMB4_S8_S8::portB()
{
  		sc_uint<9> _address = ADDRB.read();
		sc_int<8> _v;
		
#ifdef VERBOSE
		clog << "BlockRAM ADDR=" << _address << " EN=" << ENB.read() << " WE=" << WEB.read() << " DI=" << DIB.read() << " RST=" << RSTB.read() << endl;
#endif
		if( ENB.read() )
		  {
			if( RSTB.read() )
			  {
				DOB.write(0);
			  }
			else
			  {
				if( WEB.read() ){
				  _v = DIB.read();
				  memory[_address]=_v;
				  DOB.write(_v);
				} else {
				  _v = memory[_address];
				  DOB.write(_v);
				}
#ifdef VERBOSE
				clog << "RAM[" << _address << "]=" << _v << endl;
#endif
			  }
		  }

}

//////////////////////////////////////////////////////////////////////////////////
// 18kb dual-port memory 512x36
//////////////////////////////////////////////////////////////////////////////////

void RAMB16_S36_S36::portA()
{
  		sc_uint<9> _address = ADDRA.read();
		
		if( ENA.read() )
		  {
			if( SSRA.read() )
			  {
				DOA.write(0);
                DOPA.write(0);
			  }
			else
			  {
                // !!!!!!!!!!!! read-before-write !!!!! ( WRITE_MODE_A = READ_FIRST )
                DOA.write(memory[_address]);
                DOPA.write(parity[_address]);
                
				if( WEA.read() ){
				  memory[_address]=DIA.read();
				  parity[_address]=DIPA.read();
				}
			  }
		  }

}

void RAMB16_S36_S36::portB()
{
  		sc_uint<9> _address = ADDRB.read();
		
		if( ENB.read() )
		  {
			if( SSRB.read() )
			  {
				DOB.write(0);
                DOPB.write(0);
			  }
			else
			  {
                // !!!!!!!!!!!! read-before-write !!!!! ( WRITE_MODE_B = READ_FIRST )
                DOB.write(memory[_address]);
                DOPB.write(parity[_address]);
                
				if( WEB.read() ){
				  memory[_address]=DIB.read();
				  parity[_address]=DIPB.read();
				}
			  }
		  }

}

//////////////////////////////////////////////////////////////////////////////////
// 18kb dual-port memory 2048x9
//////////////////////////////////////////////////////////////////////////////////

void RAMB16_S9_S9::portA()
{
  		sc_uint<11> _address = ADDRA.read();
		
		if( ENA.read() )
		  {
			if( SSRA.read() )
			  {
				DOA.write(0);
                DOPA.write(0);
			  }
			else
			  {
                // !!!!!!!!!!!! read-before-write !!!!! ( WRITE_MODE_A = READ_FIRST )
                DOA.write(memory[_address]);
                DOPA.write(parity[_address]);
                
				if( WEA.read() ){
				  memory[_address]=DIA.read();
				  parity[_address]=DIPA.read();
				}
			  }
		  }

}

void RAMB16_S9_S9::portB()
{
  		sc_uint<11> _address = ADDRB.read();
		
		if( ENB.read() )
		  {
			if( SSRB.read() )
			  {
				DOB.write(0);
                DOPB.write(0);
			  }
			else
			  {
                // !!!!!!!!!!!! read-before-write !!!!! ( WRITE_MODE_B = READ_FIRST )
                DOB.write(memory[_address]);
                DOPB.write(parity[_address]);
                
				if( WEB.read() ){
				  memory[_address]=DIB.read();
				  parity[_address]=DIPB.read();
				}
			  }
		  }

}

//////////////////////////////////////////////////////////////////////////////////
// 18kb dual-port memory 16Kx1
//////////////////////////////////////////////////////////////////////////////////

void RAMB16_S1_S1::portA()
{
  		sc_uint<14> _address = ADDRA.read();
		
		if( ENA.read() )
		  {
			if( SSRA.read() )
			  {
				DOA.write(0);
			  }
			else
			  {
                // !!!!!!!!!!!! read-before-write !!!!! ( WRITE_MODE_A = READ_FIRST )
                DOA.write(memory[_address]);
                
				if( WEA.read() ){
				  memory[_address]=DIA.read();
				}
			  }
		  }

}

void RAMB16_S1_S1::portB()
{
  		sc_uint<14> _address = ADDRB.read();
		
		if( ENB.read() )
		  {
			if( SSRB.read() )
			  {
				DOB.write(0);
			  }
			else
			  {
                // !!!!!!!!!!!! read-before-write !!!!! ( WRITE_MODE_B = READ_FIRST )
                DOB.write(memory[_address]);
                
				if( WEB.read() ){
				  memory[_address]=DIB.read();
				}
			  }
		  }

}

//////////////////////////////////////////////////////////////////////////////////
// 18kb dual-port memory 8Kx2
//////////////////////////////////////////////////////////////////////////////////

void RAMB16_S2_S2::portA()
{
  		sc_uint<13> _address = ADDRA.read();
		
		if( ENA.read() )
		  {
			if( SSRA.read() )
			  {
				DOA.write(0);
			  }
			else
			  {
                // !!!!!!!!!!!! read-before-write !!!!! ( WRITE_MODE_A = READ_FIRST )
                DOA.write(memory[_address]);
                
				if( WEA.read() ){
				  memory[_address]=DIA.read();
				}
			  }
		  }

}

void RAMB16_S2_S2::portB()
{
  		sc_uint<13> _address = ADDRB.read();
		
		if( ENB.read() )
		  {
			if( SSRB.read() )
			  {
				DOB.write(0);
			  }
			else
			  {
                // !!!!!!!!!!!! read-before-write !!!!! ( WRITE_MODE_B = READ_FIRST )
                DOB.write(memory[_address]);
                
				if( WEB.read() ){
				  memory[_address]=DIB.read();
				}
			  }
		  }

}

//////////////////////////////////////////////////////////////////////////////////
// 18kb dual-port memory 4Kx4
//////////////////////////////////////////////////////////////////////////////////

void RAMB16_S4_S4::portA()
{
  		sc_uint<12> _address = ADDRA.read();
		
		if( ENA.read() )
		  {
			if( SSRA.read() )
			  {
				DOA.write(0);
			  }
			else
			  {
                // !!!!!!!!!!!! read-before-write !!!!! ( WRITE_MODE_A = READ_FIRST )
                DOA.write(memory[_address]);
                
				if( WEA.read() ){
				  memory[_address]=DIA.read();
				}
			  }
		  }

}

void RAMB16_S4_S4::portB()
{
  		sc_uint<12> _address = ADDRB.read();
		
		if( ENB.read() )
		  {
			if( SSRB.read() )
			  {
				DOB.write(0);
			  }
			else
			  {
                // !!!!!!!!!!!! read-before-write !!!!! ( WRITE_MODE_B = READ_FIRST )
                DOB.write(memory[_address]);
                
				if( WEB.read() ){
				  memory[_address]=DIB.read();
				}
			  }
		  }

}
