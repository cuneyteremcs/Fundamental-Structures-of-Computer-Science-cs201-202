#include "NgramTree.h"
#include <string>
#include <iostream>

using namespace std;

NgramTree::NgramTree()
{
    root = NULL;
}

NgramTree::~NgramTree()
{

}

void NgramTree::addNgram(string ngram) {
    addNgram2(root, ngram);
};

void NgramTree::addNgram2(TreeNode *& ptr, string ngram) {
    if (ptr == NULL)
	{
		ptr = new TreeNode(ngram, NULL, NULL);
	}
	else if (order(ngram, ptr->item) == 1)
	{
		addNgram2(ptr->left_child_ptr, ngram);
	}
	else if (order(ngram, ptr->item) == 2)
	{
		addNgram2(ptr->right_child_ptr, ngram);
	}
	else
		ptr->increment_count();
};

int NgramTree::order(string str1, string str2)
{

}

void NgramTree::generateTree(string fileName, int n) {
    FILE * pFile;
    if (! (pFile = fopen("input.txt","r")))
        return 1;
    while (fscanf(pFile, "%s", ngram) != EOF)  {
        string s(ngram);
        NgramTree.addNgram(s);
        printf("%s ", ngram);
    }
        fclose(pFile);
}



int NgramTree::getTotalNgramCount()
{
	count = 0;
	getNgramCount(root);
	return count;
}

void NgramTree::getNgramCount(TreeNode* & node)
{
    count++;
	if (node != NULL)
	{
		getNgramCount(node->left_child_ptr);
		getNgramCount(node->right_child_ptr);
		count++;
	}
}


void NgramTree::printNgramFrequencies()
{
	print_inorder(root);
}

void NgramTree::print_inorder(TreeNode* &node)
{
	if (node != NULL)
	{
		print_inorder(node->left_child_ptr);
		cout << endl << "\"" << node->item << "\" appears " << node->count + 1 << " time(s)";
		print_inorder(node->right_child_ptr);
	}
}

bool isComplete();

bool NgramTree::is_full(TreeNode* & node)
{
	if (node != NULL)
	{
		if ((node->left_child_ptr == NULL && node->right_child_ptr == NULL))
		{
			return true;
		}
	}

	return false;
}

