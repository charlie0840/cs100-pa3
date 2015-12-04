
#include "BitOutputStream.hpp"
#include <iostream>

void BitOutputStream::writeBit(int bit)
{
	if(buf_index == 8)
		flush();
	int i = bit<<(7 - buf_index);
	buf_index++;
	buf = buf | i;
}

void BitOutputStream::writeByte(int i)
{
	for(int i = 0; i < 4; i++)
	{
		writeBit((i & (1 << (3-i))) >> (3-i));
	}
}

void BitOutputStream::writeInt(int i)
{
	for(int i = 0; i<32; i++)
	{
		writeBit((i & (1 << (31 - i))) >> (31 - i));
	}
}

void BitOutputStream::flush()
{
	out.put(buf);
	buf = 0;
	buf_index = 0;
}
