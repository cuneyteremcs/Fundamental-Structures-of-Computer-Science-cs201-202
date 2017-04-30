#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "heap.h"
//Cuneyt EREM
using namespace std;

//constructor that has initial values
heap::heap()
{
	MAXSIZE = 2500;
	size = 0;
	comparisons = 0;
    heapArray = new int[MAXSIZE];
}

//destructor deletes the array not to cause memory leak
heap::~heap()
{
    delete heapArray;
}

//if size is not enough, then it will increase the size of array, and newitem will be inserted last index
//after the insertion, we rebuild the heap and increase the size
void heap::insert(const int a){
    if(size >= MAXSIZE){
        int *tempArray = new int[2*MAXSIZE];
        for(int i = 0; i < MAXSIZE; i++)
            tempArray[i] = heapArray[i];
        delete heapArray;
        MAXSIZE*= 2;
        heapArray = tempArray;
    }

    heapArray[size] = a;
    buildHeap(size++);
}

//
void heap::buildHeap(int index){
    comparisons++;	//counter for using buildheap everytime
    int leftChildIndex = 2*index+1;	//we have a array structure that to find left and right children indexes
    int rightChildIndex = 2*index+2;
    if(leftChildIndex < size){
        if(rightChildIndex < size){	//if childrens are less than size, than we sont have to check other array elements after the last elemenets we have to check
            //This comparison is to find item's exact place, then rebuld the heap
			if(heapArray[rightChildIndex] >= heapArray[index] && heapArray[rightChildIndex] >= heapArray[leftChildIndex] ){
                swap(rightChildIndex,index);
                buildHeap(rightChildIndex);
            }
            else if(heapArray[leftChildIndex] >= heapArray[index] && heapArray[leftChildIndex] >= heapArray[rightChildIndex] ){
                swap(leftChildIndex,index);
                buildHeap(leftChildIndex);
            }
        }
		//it is to insert element to last index of left child
        else{
            if(heapArray[leftChildIndex] >= heapArray[index])
                swap(leftChildIndex,index);
        }
    }
	
	//it is to find parent index and go to upper location and swap
    int parentIndex = (index-1)/2;
    if(heapArray[index] > heapArray[parentIndex]){
        swap(parentIndex,index);
        buildHeap(parentIndex);
    }
}

//swaps the value
void heap::swap(int i,int j){
    int temp = heapArray[i];
    heapArray[i] = heapArray[j];
    heapArray[j] = temp;
}

//it will returns the head of the tree
int heap::maximum(){
    if(size > 0)
        return heapArray[0];
    return -1;
}

//we swap the last element with head element and decrease the size of element, after then rebuild heap.
int heap::popMaximum(){
    if(size > 0){
        size--;
        int max = heapArray[0];
        swap(size,0);
        buildHeap(0);
        return max;
    }
    return -1;
}
int heap::getSize(){	//returns size
    return size;
}
bool heap::isEmpty(){	//check whether array is empty 
    return size == 0;
}
int heap::getComparisons(){	//comparison number
    return comparisons;
}
