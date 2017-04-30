
//Cüneyt EREM 21202398 SEC1

#include <iostream>
#include <string>
#include <cstdlib>
#include "AVLTree.h"
using namespace std;

int main(int argc, char **argv)
{
	if(argc != 2){
		cout<<"Input error!"<<endl;
		return 0;
	}

    AVLTree tree;
    tree.wordfreqs.open("wordfreqs");
    tree.statistics.open("statistics");
    tree.inputFile.open(argv[1]);
    tree.generateTree();
    tree.printWordFrequencies();
    tree.printTotalWordCount();
    tree.printHeight();
    tree.printMostFrequent();
    tree.printLeastFrequent();
    tree.printStandartDeviation();
    return 0;
}
