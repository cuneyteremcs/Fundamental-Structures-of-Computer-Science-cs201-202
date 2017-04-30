
//Cüneyt EREM 21202398 SEC1

#include "AVLTree.h"

AVLTree::AVLTree()
{
    root = NULL;
}

AVLTree::~AVLTree()
{
    recursiveDelete(root);
}
void AVLTree::recursiveDelete(node * &ptr){
	if(ptr != NULL){
		recursiveDelete(ptr->left);
		recursiveDelete(ptr->right);
		delete ptr;
	}
}

void AVLTree::addWord(string addedWord){
    if(root == NULL){
        root = new node(addedWord);
    }
    else
        insert(root,addedWord);
}
void AVLTree::insert(node * &ptr,string addedWord){
    int result =ptr->word.compare(addedWord);
    if(result == 0)
        ptr->count++;
    else if(result > 0){
        if(ptr->left != NULL)
            insert(ptr->left,addedWord);
        else{
            ptr->left = new node(addedWord);
            ptr = balance(ptr);//call for balance
        }
    }
    else{
        if(ptr->right != NULL)
            insert(ptr->right,addedWord);
        else{
            ptr->right = new node(addedWord);
            ptr = balance(ptr);//call for balance
        }

    }
}
node* AVLTree::balance(node* ptr){
    int difference = height(ptr->left)-height(ptr->right);
    if (difference > 1)             //if difference bigger than 1 it will need a rotation
    {
        if ( height(ptr->left->left) - height(ptr->left->right) > 0)  //if left child has taller left child we will do a single right rotation
            ptr = rightRotation(ptr);
        else
            ptr = leftRightRotation(ptr);
    }
    else if (difference < -1)       //if difference smaller than -1 it will need a rotation
    {
        if (height(ptr->right->right) - height(ptr->right->left) > 0)
            ptr = leftRotation(ptr);
        else
            ptr = rightLeftRotation(ptr);
    }
    return ptr;
}

node* AVLTree::rightRotation(node*parent){
    node * temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}
node* AVLTree::leftRotation(node*parent){
    node * temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}
node* AVLTree::rightLeftRotation(node*parent){
    parent->right = rightRotation(parent->right);
    parent = leftRotation(parent);
    return parent;
}
node* AVLTree::leftRightRotation(node*parent){
    parent->left = leftRotation(parent->left);
    parent = rightRotation(parent);
    return parent;
}

int AVLTree::printHeight(){
    int totalH = height(root);
    statistics<<"Tree Height: ";
    statistics<<totalH;
    statistics <<"\n";
    cout<<"Tree Height: "<<totalH<<endl;
    return totalH;
}
int AVLTree::height(node *ptr){
    int h = 0;
    if(ptr != NULL){
        int leftH = height(ptr->left);
        int rightH = height(ptr->right);
        if(leftH > rightH)
            h = leftH +1;
        else
            h = rightH +1;
    }
    return h;
}
int AVLTree::printTotalWordCount(){
    int number = recursiveWordCount(root);
    statistics<<"Total Word Count: ";
    statistics<<number;
    statistics <<"\n";
    cout<<"Total Word Count: "<<number<<endl;
    return number;
}
int AVLTree::recursiveWordCount(node *ptr){
    int number = 0;
    if(ptr != NULL){
        number++;
        number+=recursiveWordCount(ptr->left);
        number+=recursiveWordCount(ptr->right);
    }
    return number;
}
void AVLTree::printWordFrequencies(){
    if (!wordfreqs.is_open())
        return;
    recursiveWordFrequent(root);
}
void AVLTree::recursiveWordFrequent(node *ptr){
    if(ptr != NULL){
        recursiveWordFrequent(ptr->left);
        wordfreqs <<ptr->word;
        wordfreqs <<" ";
        wordfreqs <<ptr->count;
        wordfreqs <<"\n";
        cout << ptr->word  << " " <<ptr->count<<endl;
        recursiveWordFrequent(ptr->right);
    }
}
void AVLTree::printMostFrequent(){
    if(root != NULL){
        node*temp = root;
        findMostFrequent(root,temp);
        cout<<"Most Frequent: "<<temp->word<<" "<<temp->count<<endl;

        statistics<<"Most Frequent: ";
        statistics<<temp->word;
        statistics<<" ";
        statistics<<temp->count;
        statistics <<"\n";
    }
    else
        cout<<"No word in the tree!!"<<endl;
}
void AVLTree::findMostFrequent(node *ptr,node*&max){
    if(ptr != NULL){
        if(ptr->count > max->count)
            max = ptr;
        findMostFrequent(ptr->left,max);
        findMostFrequent(ptr->right,max);
    }
}
void AVLTree::printLeastFrequent(){
    if(root != NULL){
        node*temp = root;
        findLeastFrequent(root,temp);
        cout<<"Least Frequent: "<<temp->word<<" "<<temp->count<<endl;

        statistics<<"Least Frequent: ";
        statistics<<temp->word;
        statistics<<" ";
        statistics<<temp->count;
        statistics <<"\n";
    }
    else
        cout<<"No word in the tree!!"<<endl;
}
void AVLTree::findLeastFrequent(node *ptr,node*&min){
    if(ptr != NULL){
        if(ptr->count < min->count)
            min = ptr;
        findLeastFrequent(ptr->left,min);
        findLeastFrequent(ptr->right,min);
    }
}
int AVLTree::printStandartDeviation(){
    if(root != NULL){
    	double sum = recursiveSum(root);
    	double number = recursiveWordCount(root);
    	double average = sum/number;
    	double standartDeaviation = sqrt(recursiveStandartDeviationSum(root,average)/number);
        cout<<"Standard Deviation: "<<standartDeaviation<<endl;
        statistics<<"Standard Deviation: ";
        statistics<<standartDeaviation;
        statistics <<"\n";
    }
    else
        cout<<"No word in the tree!!"<<endl;

}
double AVLTree::recursiveStandartDeviationSum(node * &ptr,double mean){
	if(ptr != NULL){
		double number = recursiveStandartDeviationSum(ptr->left,mean);
		number+= recursiveStandartDeviationSum(ptr->right,mean);
		return number+(ptr->count-mean)*(ptr->count-mean) ;
	}
	return 0;
}
int AVLTree::recursiveSum(node * &ptr){
	if(ptr != NULL){
		int number = recursiveSum(ptr->left);
		number+= recursiveSum(ptr->right);
		return number+ptr->count;
	}
	return 0;
}
void AVLTree::generateTree(){
    if (!inputFile.is_open()) return;

    string word;
    while (inputFile >> word)
    {
        string tempWord = "";
        for(int i = 0; i < word.length(); i++){
            if( (word.at(i) >= 65 && word.at(i) <= 90) || (word.at(i) >= 97 && word.at(i) <= 122) )
                tempWord+=word.at(i);
            else{
                if(tempWord.length() > 0)
                    addWord(tempWord);
                tempWord = "";
            }
        }
        if(tempWord.length() > 0)
            addWord(tempWord);
    }
}
