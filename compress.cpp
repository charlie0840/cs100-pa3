
#include "HCTree.hpp"
#include <iostream>
#include <iomanip>
#include <fstream> 
#include <vector>
#include <stdio.h>
int main(int argc, char* argv[])
{
	//see if the number of arguments is correct
	if(argc != 3)
	{
		cout << "./compress called with incorrect arguments." << endl;
		cout << "Usage: ./compress infile outfile"<<endl;
		return 0;
	}

	vector<int> freqs(256, 0);
	unsigned char nextChar;

	int size = 0, outSize = 0, sizeTemp = 0;
	int num = 0;
	float ratio = 0; 
	//get the name of the files
	char * infileName = argv[1];
	char * outfileName = argv[2];

	ifstream inFile;
	ofstream outFile;

	//open the files
	inFile.open(infileName, ios::binary);
	outFile.open(outfileName, ios::binary);

	//see if the files are valid
	if(inFile.fail() || outFile.fail())
	{
		cout<<"error opening \""<<inFile.is_open()<<"\"."<<endl;
		return 0;
	}
	BitOutputStream oStream(outFile);

	cout<<"Reading from file \""<<infileName<<"\"... done"<<endl;	
	while(1)
	{
		//if the file is closed or get to the end of file, break
		if(inFile.eof() || inFile.peek() == EOF)
		{
			break;
		}
		//get one char from the inFile
		nextChar = inFile.get();
		int symbol = (int) nextChar;
		if(freqs[symbol] == 0)
			num++;
		size++;
		//record the number of the appearence of the  character
		freqs[symbol]++;
	}
	cout<<"Found "<<num<<" unique symbols in input file of size "
		<<size<<" bytes."<<endl;
	//close the file
	inFile.close();

	//build the huffman tree
	HCTree hufTree;
	hufTree.build(freqs);

	//make the header and store it into the outFile so that the tree can
	//be rebuilt
	cout<<"Writing to file \""<<outfileName<<"\"... done."<<endl;
	for(int i = 0; i < freqs.size(); i++)
	{	
		outSize ++;		
		outFile << " " << freqs.at(i);
	}
	outSize = outSize * 4;
	inFile.open(infileName, ios::binary);

	//encode every char
	while(inFile.peek() != EOF)
	{
		nextChar = inFile.get();	
		hufTree.encode(nextChar, oStream);		
	}	
	oStream.flush();
	sizeTemp = outFile.tellp();
	ratio = (float)sizeTemp / (float)size;
	cout<<"Output file has size "<<sizeTemp<<" bytes."<<endl;
	cout<<"Compression ratio: "<<std::fixed<<
			std::setprecision(6)<<ratio<<endl;
	inFile.close();
	outFile.close();
	return 0;
	
}
