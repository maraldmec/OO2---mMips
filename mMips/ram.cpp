/*
 *  TU Eindhoven
 *  Eindhoven, The Netherlands
 *
 *  Name            :   ram.cpp
 *
 *  Author          :   Sander Stuijk (sander@ics.ele.tue.nl)
 *
 *  Date            :   January 23, 2006
 *
 *  Function        :   RAM memory (big-endian)
 *
 *  History         :
 *      26-01-06    :   Initial version.
 *
 */

#include "ram.h"

void RAM::read()
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
    addr_t = addr_t & RAMMASK;
    if (addr_t < RAMSIZE)
    {
        data = 0;

        // Read word?
        if (r.read() == 1)
        {
            // Make address word aligned
            addr_t = addr_t & 0xFFFFFFFC;

            for (int i = 0; i < (DWORD / 8); i++)
            {
                data = data << 8;
                data_t = mem[int(addr_t) + i];
                data = data | data_t;
            }
        }
        else
        {
            // Read byte
            data = mem[int(addr_t)];
        }
    }
    dout.write(data);

    // Assume no waiting needed
    wait.write(false);
}

void RAM::write()
{
    sc_uint<DWORD> addr_t, data, data_t;

    // Memory not enabled?
    if (!enable.read())
        return;

    // No write requested?
    if (w.read() == 0)
        return;

    // Assume no waiting needed
    wait.write(false);

    // Write word?
    if (w.read() == 1)
    {
        addr_t = addr.read();
        addr_t = addr_t & RAMMASK;
        data = din.read();

        // Make address word aligned
        addr_t = addr_t & 0xFFFFFFFC;

        if (addr_t < RAMSIZE)
        {
            for (int i = (DWORD / 8); i > 0; i--) {
	        mem[addr_t + i - 1] = data & 0xff;
                data = data >> 8;
            }
         }
         else
         {
             cout << "WARNING: writting to invalid memory location. (";
             cout << addr_t << ")" << endl;
         }
    }

    // Write byte?
    if (w.read() == 2)
    {
        addr_t = addr.read();
        addr_t = addr_t & RAMMASK;
        data = din.read();

        if (addr_t < RAMSIZE)
        {
             mem[addr_t] = data & 0xff;
        }
        else
        {
            cout << "WARNING: writting to invalid memory location. (";
            cout << addr_t << ")" << endl;
        }
    }
}

void RAM::mem_dump(const char *filename, int memoffset, int size)
{
    ofstream memf(filename, ios::out | ios::binary);
    int addr = memoffset;
    unsigned char c;
    sc_uint<8> a;

    while (addr < RAMSIZE && size > 0)
    {
        a = mem[addr];
        c = a;
        memf.put(c);
        addr++;
        size--;
    }

    memf.close();
}

void RAM::mem_init(const char *filename, int fileoffset, int memoffset, int size)
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

	if (addr >= RAMSIZE)
	    break;
    }

    memf.close();
}

