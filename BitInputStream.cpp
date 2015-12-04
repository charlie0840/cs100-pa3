/*****************************************************************************
  								Yiming Yu
  								cs100feu
 
  			         Assignment 3
 File name:	BitInputStream.cpp
 Description:	The BitInputStream will be used for the decompression part of 
		the assignment. 
*****************************************************************************/
#include "BitInputStream.hpp"
#include <iostream>

int BitInputStream::readBit()
{
	if(buf_index == 8)
	{
		buf = in.get();
		buf_index = 0;
	}
	int retVal = (buf & 1<<((7 - buf_index)));
	buf_index++;
	return retVal;
}

int BitInputStream::readByte()
{
	int retVal = 0;
	for(int i =7; i >= 0; i--) 
	{
		retVal = retVal * 2 + readBit();
	}
	return retVal;
}

int BitInputStream::readInt()
{
	int retVal = 0;
	for(int i = 31; i>=0; i--)
	{
		retVal = retVal * 2 + readBit();
	}
	return retVal;
}
