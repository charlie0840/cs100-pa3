/*****************************************************************************
  								Yiming Yu
  								cs100feu
 
  			         Assignment 3
 File name:	uncompress.cpp
 Description:	The uncompress.cpp file will contain the code needed for the 
		decompression portion of this assignment. When run, this 
		program will read the contents of the file named by its first 
		command line argument.
*****************************************************************************/
#include <iostream>
#include <vector>
#include "HCTree.hpp"
#include <fstream>
#include <iomanip>

int main(int argc, char* argv[])
{
	//see if the number of arguments is correct
	if(argc != 3)
	{
		cerr<<"./uncompress called with incorrect arguments." << endl;
		cerr<<"Usage: ./reuncompress infile outfile"<<endl;
		return 0;
	}

	int code = 0;
	int total = 0;
	int inSize = 0;
	int outSize = 0; 
	int num = 0;
	float ratio = 0;
	char buf;

	char * infileName = argv[1];
	char * outfileName = argv[2];

	ifstream inFile;
	ofstream outFile;

	vector<int> freqs(256, 0);
	
	inFile.open(infileName, ios::binary);
	outFile.open(outfileName, ios::binary);

	if(inFile.fail() || outFile.fail())
	{
		cout<<"Error opening \"" <<inFile.is_open()<<"\"."<< endl;
		return 0;
	}

	BitInputStream iStream(inFile);


	cout<<"Reading header from file \""<<infileName<<"\"... ";	
	for(int i = 0; i < freqs.size(); i++)
	{
		if(!inFile.good())
		{
			cout<<"Problem: EOF while reading header."<<endl;
			return 0;
		}
		inFile >> code;
		freqs[i] = code;
		if(freqs[i] != 0)
			num++;
		total = total + code;
	}
	cout<<"done."<<endl;

	cout<<"Found "<<num<<" unique symbols in input file of size "<<total
		<<" bytes."<<endl;
	
	cout<<"Building Huffman code tree... ";
	HCTree hufTree;
	hufTree.build(freqs);
	cout<<"done."<<endl;
	
	cout<<"Writing to file \""<<outfileName<<"\"... ";
	for(int i = 0; i < total; i++)
	{
		buf = hufTree.decode(iStream);
		outFile << buf;
	}
	cout<<"done."<<endl;
	outSize = outFile.tellp();
	ratio = (float)outSize/(float)total;
	cout<<"Uncompression ratio: "<<std::fixed<<std::setprecision(6)
			<<ratio<<endl;
	outFile.close();
	inFile.close();		

	return 0;
}
