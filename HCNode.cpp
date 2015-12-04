/*****************************************************************************
  								Yiming Yu
  								cs100feu
 
  			         Assignment 3
 File name:	HCNode.cpp
 Description:	nodes, each holding pointers to the left and right children of 
		that node as well as a pointer to the parent node. What's new 
		in the nodes of your Huffman tree are the members count and 
		symbol, which hold the frequency of a particular symbol and 
		its symbol ID, respectively. 
*****************************************************************************/
#include "HCNode.hpp"

bool HCNode::operator<(const HCNode& other)
{
	if(count  != other.count)
		return count > other.count;
	else
		return symbol < other.symbol;
}
bool comp(HCNode* one, HCNode* other)
{
	return *one < *other;
}

