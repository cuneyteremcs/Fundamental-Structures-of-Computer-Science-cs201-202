#include "AirportNet.h"
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sstream>
using namespace std;

AirportNet::AirportNet(const string aname)
{
    number = 0;
    matrix = NULL;
    aNameArray = NULL;
    fstream file(aname.c_str());

    if(file.is_open()){
        string line;
        int lineNumber = 0;
        if(getline(file,line))
            lineNumber = atoi(line.c_str());

        string *lines = new string[lineNumber];//read all lines
        for(int i = 0; i < lineNumber; i++)
            getline (file,lines[i]);

        string *city = new string[lineNumber*2];
        int x = 0;
        for(int l = 0; l < lineNumber; l++)
        {
            string part = "";
            for(int i = 0; i < lines[l].length(); i++){
                if(lines[l].at(i) == ' '){
                    bool unique = true;
                    for(int j = 0; j < x; j++){
                        if(city[j].compare(part) == 0)
                            unique = false;
                    }
                    if(unique){
                        city[x] = part;
                        x++;
                    }
                    part = "";
                }
                else
                    part+= lines[l].at(i);
            }
        }
        number = x;
        aNameArray = new string[x];
        matrix = new int*[x];
        for(int i = 0; i < x; i++){
            aNameArray[i] = city[i];
            matrix[i] = new int[x];
            for(int j = 0; j < x; j++)
                matrix[i][j] = -1;
        }

        for(int l = 0; l < lineNumber; l++)
        {
            string part = "";
            int city1Index = -1;
            int city2Index = -1;
            int distance = -1;
            for(int i = 0; i < lines[l].length(); i++){
                if(lines[l].at(i) == ' '){
                    for(int j = 0; j < x; j++){
                        if(aNameArray[j].compare(part) == 0){
                            if(city1Index == -1)
                                city1Index = j;
                            else
                                city2Index = j;
                        }
                    }
                    part = "";
                }
                else
                    part+= lines[l].at(i);
            }
            distance = atoi(part.c_str());
            matrix[city1Index][city2Index] = distance;
            matrix[city2Index][city1Index] = distance;
        }
        delete city;
        delete lines;
    }
    else{
        cout<<"Could not open the text file. The system will be empty!!!!"<<endl;
    }
}

AirportNet::AirportNet(const AirportNet& aNet){
    number = aNet.number;
    aNameArray = new string[number];
    matrix = new int*[number];
    for(int i = 0; i < number; i++){
        aNameArray[i] = aNet.aNameArray[i];
        matrix[i] = new int[number];
        for(int j = 0; j < number; j++)
            matrix[i][j] = aNet.matrix[i][j];
    }
}

AirportNet::~AirportNet()
{
    delete aNameArray;
    for(int i = 0; i < number; i++)
        delete matrix[i];
    delete matrix;
}
void AirportNet::listDirectFlights(const string aname){
    int index = -1;
    for(int i = 0; i < number; i++)
        if(aNameArray[i].compare(aname) == 0){
            index = i;
            break;
        }
    if(index > -1){//ıf the city found
        string reachableCities = "";
        int reachableNumber = 0;
        for(int i = 0; i < number; i++){
            if(matrix[index][i] != -1){
                reachableNumber++;
                reachableCities += aNameArray[i] + ", ";
            }
        }
        cout<<"From "<<aname<< " " << reachableNumber << " airports are directly reachable: "<<reachableCities<<endl;
    }
    else{
        cout<< aname<<" does not exist in the airport network."<<endl;
    }
}
void AirportNet::listRoutesOnHubAirport(const string aname){
    int index = -1;
    for(int i = 0; i < number; i++)
        if(aNameArray[i].compare(aname) == 0){
            index = i;
            break;
        }
    if(index > -1){
        cout<<"If "<<aname<< "  is considered as hub these routes are possible: "<<endl;
        for(int i = 0; i < number; i++)
            for(int j = 0; j < number; j++){
                if(i != index && j != index && i != j && matrix[j][i] == -1 && matrix[i][index] > -1 && matrix[index][j] > -1){
                    cout<<"<"<<aNameArray[i]<<", "<<aNameArray[j]<<">"<<endl;
                }
            }
    }
    else{
        cout<< aname<<" does not exist in the airport network."<<endl;
    }
}
void AirportNet::findConnectedComponents(){
    int *connectionArray = new int[number];
    int connectionNo = 0;
    for(int i = 0; i < number ; i++)
        connectionArray[i] = -1;
    for(int i = 0; i < number; i++)
        if(connectionArray[i] == -1){
            connectionArray[i] = connectionNo;
            recursiveFindconnection(connectionArray,i,connectionNo);
            connectionNo++;
        }

    cout<<"There are "<<connectionNo<< " connected components:"<<endl;
    for(int i = 0; i < connectionNo; i++){
            int nodeNumber = 0;
            for(int j = 0; j < number; j++)
                if(connectionArray[j] == i)
                nodeNumber++;
            cout<<"For component "<<i+1 <<": "<<nodeNumber<< " nodes"<<endl;
    }
    delete connectionArray;
}
void AirportNet::recursiveFindconnection(int *connectionArray,int index, int connectionNo){
    for(int i = 0; i < number; i++)
        if(matrix[index][i] > -1 || matrix[i][index] > -1)
            if(connectionArray[i] != connectionNo){
                connectionArray[i] = connectionNo;
                recursiveFindconnection(connectionArray,i,connectionNo);
            }
}
void AirportNet::displayMostCentralAirport(){
    int *centerArray = new int[number];
    for(int i = 0; i < number; i++)
        centerArray[i] = 0;
    for(int i = 0; i < number; i++)
        for(int j = 0; j < number; j++)
            if(matrix[i][j] > -1){
                centerArray[i]++;
                centerArray[j]++;
            }
    int max = 0;
    for(int i = 1; i < number; i++)
        if(centerArray[i] > centerArray[max])
            max = i;
    cout<<"Most central airport in the network is: "<<aNameArray[max]<<endl;

}








