/*****************************************************************************
  								Yiming Yu
  								cs100feu
 
  			         Assignment 3
 File name:	HCTree.cpp
 Description:	a binary tree that represents the Huffman tree and further 
		provides the encoding and decoding functionalities.implements 
		the interfaces specified in HCTree.hpp.
*****************************************************************************/
#include "HCTree.hpp"
#include <queue>
#include <vector>
#include <stack>

void deleteTree(HCNode*node);

HCTree::~HCTree()
{
	deleteTree(root);	
}

void HCTree::build(const vector<int>& freqs)
{
	priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> forest;
	for(int i = 0; i < freqs.size(); i++)
	{
		//if the symbol exists, then construct a node for it
		if(freqs[i] != 0)
		{
			HCNode* node = new HCNode(freqs[i],i);
			leaves[i] = node;
			forest.push(node);
		}	
	} 

	//if there is only one node
	if(forest.size() == 1)
		forest.push(new HCNode(0,0));
	
	//start to build the tree 
	while(forest.size() > 1)
	{
		HCNode* parent = new HCNode(0,0);
		parent->c0 = forest.top();
		parent->c0->p = parent;
		forest.pop();
		
		parent->c1 = forest.top();
		parent->c1->p = parent;
		forest.pop();
		
		parent->count = parent->c0->count + parent->c1->count;

		//put small tree back into the forest
		forest.push(parent);
	}
	if( forest.size() == 0)
		root = new HCNode(0,0);
	else
	root = forest.top();
}

void HCTree::encode(byte symbol, BitOutputStream& out) const
{
	HCNode* node = leaves[symbol];
	stack<int> code;
	while(node != root)
	{
		if(node->p->c0 == node)
			code.push(0);
		else
			code.push(1);
		node = node->p;
	}
	while(!code.empty())
	{
		out.writeBit(code.top());
		code.pop();
	}
}

int HCTree::decode(BitInputStream& in)const
{
	HCNode* node = root;

	while(node->c0 != NULL && node->c1 != NULL)
	{
		if(in.readBit() == 0)
			node = node->c0;
		else
			node = node->c1;
	}
	return node->symbol;
}

void deleteTree(HCNode * node)
{
	if( node == NULL)
	 return;
	deleteTree(node->c0);
	deleteTree(node->c1);
	delete node;
}
