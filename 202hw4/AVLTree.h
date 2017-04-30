
//Cüneyt EREM 21202398 SEC1

#ifndef AVLTREE_H
#define AVLTREE_H
#include <iostream>
#include <string>
#include <cmath>
#include "fstream"
using namespace std;

struct node // the structure for representing tree nodes
{
    string word;
    int count;
    node* left;
    node* right;
    node(string w) {
        word = w;
        left = NULL;
        right = NULL;
        count = 1;
    }
};

class AVLTree
{
    public:
        ifstream inputFile;
        ofstream wordfreqs;
        ofstream statistics;
        AVLTree();
        ~AVLTree();
        void addWord(string addedWord);
        int printHeight();
        int printTotalWordCount();
        void printWordFrequencies();
        void printMostFrequent();
        void printLeastFrequent();
        int printStandartDeviation();
        void generateTree();
        node *root;
    protected:
    private:
        int height(node *ptr);
        int recursiveWordCount(node *ptr);
        void recursiveWordFrequent(node *ptr);
        void findMostFrequent(node *ptr,node*&max);
        void findLeastFrequent(node *ptr,node*&min);
        void insert(node * &ptr,string addedWord);
        void recursiveDelete(node * &ptr);
        int recursiveSum(node * &ptr);
        double recursiveStandartDeviationSum(node * &ptr,double mean);
        node* balance(node* ptr);
        node* rightRotation(node*parent);
        node* leftRotation(node*parent);
        node* rightLeftRotation(node*parent);
        node* leftRightRotation(node*parent);
};

#endif // AVLTREE_H
