#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include "heap.h"
//Cuneyt EREM
using namespace std;

int main(int argc,char** argv)
{
	//number of parameters that we will write to cmd for heapsort.exe, input.exe and output.exe
	if(argc != 3){
		cout<<"Wrong parameter number!"<<endl;
		return 0;
	}
    string line;
    ifstream inputFile(argv[1]);	//to read input
    ofstream outputFile(argv[2]);	//for output
    if(inputFile == NULL || outputFile == NULL){	//if either input or output do not exist, it prints error message
		cout<<"The files did not opened!"<<endl;
		return 0;
    }

    heap h;
	
	//it will read lines as integer from the input files
    while(getline(inputFile,line)){
        h.insert(atoi(line.c_str()));
    }
    inputFile.close();	//end of the input
	//It will pop the maximum element and write the values as sorted
    while(!h.isEmpty()){
        outputFile << h.popMaximum();
        outputFile << "\n";
    }
    outputFile.close();
	//prints the number of comparisons
    cout<<"Comparisions number = "<< h.getComparisons()<<endl;
    return 0;
}
