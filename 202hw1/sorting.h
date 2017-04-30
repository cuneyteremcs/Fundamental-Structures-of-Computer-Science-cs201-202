#ifndef SORTING_H
#define SORTING_H



class sorting
{
public:
    sorting();
    ~sorting();
    void merge(int outputArray[], int firstArray[], int sizeFirst, int secondArray[], int sizeSecond, int & compCount, int & moveCount);
    void mergesort(int numbers[], int size,  int & compCount, int &moveCount);
    void insertionsort(int numbers[], int size, int & compCount, int & moveCount);
    void swap(int a[],int i,int j);
    int partition(int a[],int l,int h, int & compCount, int & moveCount);
    void quick(int a[],int l,int h, int & compCount, int & moveCount);
    void quicksort(int a[], int n, int & compCount, int & moveCount);

};

#endif // SORTING_H
