#ifndef HEAP_H
#define HEAP_H
//Cuneyt EREM

//heap.h class, int size and comparison will be used, and we need other methods. 
class heap
{
    public:
        int* heapArray;
        int MAXSIZE;
        int size;
        int comparisons;
        heap();
        ~heap();
        void insert(const int a);
        int maximum();
        int popMaximum();
        int getSize();
        int getComparisons();
        bool isEmpty();
    protected:
    private:
        void buildHeap(int index);
        void swap(int i,int j);
};

#endif // HEAP_H
