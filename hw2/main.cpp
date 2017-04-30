#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include "findMedian.h"
using namespace std;


int* createRandomArray(int size){
    //create random array with srand
    srand (time(NULL));
    int* randomArray = new int[size];
    for(int i=0; i < size;i++)
        randomArray[i] = rand()*10;
    return randomArray;
}
//Duplicate the random array inorder to have exactly same arrays
int* duplicateRandomArray(int* originalArray,int size){
    int* duplicateArray = new int[size];
    for(int i=0; i < size;i++)
        duplicateArray[i] = originalArray[i];
    return duplicateArray;
}
//Main function for testing algorithms execution time.
void testAlgorithms(int size){
    int *randomArray1,*randomArray2,*randomArray3;                      //Pointers to store arrays
    int result1,result2,result3;                                        //Variables to store and compare results median values.
    //necessary variables for calculating time
    std::chrono::time_point< std::chrono::system_clock > startTime;
    std::chrono::duration< double, milli > elapsedTime;

    randomArray1 = createRandomArray(size);
    randomArray2 = duplicateRandomArray(randomArray1,size);
    randomArray3 = duplicateRandomArray(randomArray1,size);
	cout<<endl<<"***************************************************"<<endl;
    cout<<"Arrays are created with size = "<<size<<endl;

    //Store the starting time
    startTime = std::chrono::system_clock::now();
    //Code block
    result1 = FIND_MEDIAN_1(randomArray1,size);
    //Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Algorithm-1 Execution took " << elapsedTime.count() << " milliseconds." << endl;
	
	 //Store the starting time
    startTime = std::chrono::system_clock::now();
    //Code block
    result2 = FIND_MEDIAN_2(randomArray2,size);
    //Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Algorithm-2 Execution took " << elapsedTime.count() << " milliseconds." << endl;
	
		
	 //Store the starting time
    startTime = std::chrono::system_clock::now();
    //Code block
    result3 = FIND_MEDIAN_3(randomArray3,size);
    //Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Algorithm-3 Execution took " << elapsedTime.count() << " milliseconds." << endl;
	
	delete[] randomArray1;
	delete[] randomArray2;
	delete[] randomArray3;
	//if the results are different give an error message!
	if(result1 != result2 || result1 != result3){
		cout<<"Error the results are different!!"<<endl;
		exit(0);
	}

}

int main()
{
	for(int i = 1000; i < 600000; i*=2)
		testAlgorithms(i);
    return 0;
}

