#ifndef AIRPORTNET_H
#define AIRPORTNET_H

#include <string>
using namespace std;
class AirportNet{
    public:
        AirportNet(const string aname);
        AirportNet(const AirportNet& aNet); // copy contructor
        ~AirportNet(); // destructor
        void listDirectFlights(const string aname);
        void listRoutesOnHubAirport(const string aname);
        void findConnectedComponents();
        void displayMostCentralAirport();
        // ...
        // define other public member functions here,
        // if you have any
    private:
        int number;
        int** matrix;
        string* aNameArray;
        void recursiveFindconnection(int *connectionArray,int index, int connectionNo);
};

#endif // AIRPORTNET_H
