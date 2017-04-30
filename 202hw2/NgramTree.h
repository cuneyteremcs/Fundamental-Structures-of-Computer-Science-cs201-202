#ifndef HW2_H
#define HW2_H
#include <string>
#include <iostream>
#include "TreeNode.h"

using namespace std;


// hw2.h …
//NgramTree class

class NgramTree {
    public:
        NgramTree();
        ~NgramTree();
        void addNgram(string ngram);
        void addNgram2(TreeNode *& ptr, string ngram);
        int get_dict_order(string str1, string str2);
        int getTotalNgramCount();
        void getNgramCount(TreeNode* & node);
        void printNgramFrequencies();
        void print_inorder(TreeNode* &node);
        bool isComplete();
        bool isFull();
        void generateTree(string fileName, int n);

private:
    TreeNode *root;
	int count;

};

#endif // HW2_H
