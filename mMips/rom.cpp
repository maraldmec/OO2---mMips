/*
 *  TU Eindhoven
 *  Eindhoven, The Netherlands
 *
 *  Name            :   rom.cpp
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

#include "rom.h"

void ROM::read()
{
    sc_uint<DWORD> addr_t, data, data_t;

    // Memory not enabled?
    if (!enable.read())
        return;

    // No read requested?
    if (r.read() == 0)
        return;

    // Read the data from the requested address and put it on the output
    addr_t = addr.read();
    addr_t = addr_t % ROMSIZE;
    if (addr_t < ROMSIZE)
    {
        data = 0;
	for (int i = 0; i < (DWORD/8); i++) {
	    data = data << 8;
	    data_t = mem[int(addr_t) + i];
	    data = data | data_t;
	}
    }
    dout.write(data);

    // Assume no waiting needed
    wait.write(false);
}

void ROM::mem_dump(const char *filename, int memoffset, int size)
{
    ofstream memf(filename, ios::out | ios::binary);
    int addr = memoffset;
    unsigned char c;
    sc_uint<8> a;

    while (addr < ROMSIZE && size > 0)
    {
        a = mem[addr];
        c = a;
        memf.put(c);
        addr++;
        size--;
    }

    memf.close();
}

void ROM::mem_init(const char *filename, int fileoffset, int memoffset, int size)
{
    sc_bv<8> byte;
    int addr = memoffset;
    int c;

    ifstream memf(filename, ios::in | ios::binary);
    memf.seekg(fileoffset);
    
    while (!memf.eof() && size > 0)
    {
	c = memf.get();
        if (memf.eof()) break;

	byte = c;
	mem[addr] = byte;
	addr++;
        size--;

	if (addr >= ROMSIZE)
	    break;
    }

    memf.close();
}

