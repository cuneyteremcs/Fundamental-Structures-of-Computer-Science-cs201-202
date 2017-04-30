#include <iostream>
#include <string>
#include "sorting.h"
using namespace std;

sorting::sorting() {}
sorting::~sorting() {}

void sorting::merge(int* outputArray, int* firstArray, int sizeFirst, int* secondArray, int sizeSecond, int & compCount, int & moveCount) {
	int p = 0, p1 = 0, p2 = 0;
	while (p1 < sizeFirst && p2 < sizeSecond) {
		if (firstArray[p1] < secondArray[p2])
			outputArray[p++] = firstArray[p1++];
		else
			outputArray[p++] = secondArray[p2++];
		compCount++;
		moveCount++;
	}

	while (p1 < sizeFirst) {
		outputArray[p++] = firstArray[p1++];
		moveCount++;
	}
	while (p2 < sizeSecond) {
		outputArray[p++] = secondArray[p2++];
		moveCount++;
	}
}


void sorting::mergesort(int* numbers, int size, int & compCount, int &moveCount) {

	if (size == 1) return;
	int mid = size / 2;
	int firstPartSize = mid;
	int secondPartSize = size - mid;

	int* firstArray =  new int[firstPartSize];
	int* secondArray = new int[secondPartSize];

	for (int i = 0; i < size;i++) {
		if (i < mid)
			firstArray[i] = numbers[i];
		else
			secondArray[i - mid] = numbers[i];

		moveCount++;
	}

	mergesort(firstArray, firstPartSize, compCount, moveCount);
	mergesort(secondArray, secondPartSize, compCount, moveCount);
	merge(numbers, firstArray, firstPartSize, secondArray, secondPartSize, compCount, moveCount);
}


void sorting::insertionsort(int* numbers, int size, int & compCount, int & moveCount) {
	compCount = 0;
	moveCount = 0;

	for (int i = 1;i<size;i++)
	{
		int  j;
		int temp = numbers[i];
		moveCount++;

		j = i - 1;
		while (temp<numbers[j] && j >= 0) {
			numbers[j + 1] = numbers[j];
			moveCount++;
			j--;
			compCount++;
		}

		/*
		for(j=i-1; j >= 0; j--) {
		comparison++;
		if(temp<numbers[j]) {
		numbers[j+1] = numbers[j];
		movement++;
		}
		}

		*/
		numbers[j + 1] = temp;
		moveCount++;
	}
	//cout<<" " << compCount<<endl;
	//cout<<" " << moveCount<<endl;
}


void sorting::swap(int* a, int i, int j) {
	int s = a[i];
	a[i] = a[j];
	a[j] = s;

}
int sorting::partition(int* a, int l, int h, int & compCount, int & moveCount) {
	int i = l, j = h, v = a[h];
	while (true) {
		while (a[i]<v) {
			i++;
			compCount++;
		}
		while (a[--j]>v) {
			if (j == i)  break;
			compCount++;
		}
		if (i >= j) break;
		swap(a, i, j);
		moveCount += 3;
	}

	swap(a, i, h);
	moveCount += 3;
	return i;
}
void sorting::quick(int* a, int l, int h, int & compCount, int & moveCount) {
	if (h <= l) return;
	int j = partition(a, l, h, compCount, moveCount);
	quick(a, l, j - 1, compCount, moveCount);
	quick(a, j + 1, h, compCount, moveCount);
}

void sorting::quicksort(int* a, int n, int & compCount, int & moveCount) {
	//n=sizeof(a)/sizeof(int);
	compCount = 0;
	moveCount = 0;
	quick(a, 0, n - 1, compCount, moveCount);
}
