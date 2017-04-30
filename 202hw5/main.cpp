#include "AirportNet.h"
#include <iostream>
using namespace std;

int main(){
	AirportNet AN("anetname");
	AN.listDirectFlights("Istanbul");
	cout << endl;
	AN.listDirectFlights("Antalya");
	cout << endl;
	AN.listDirectFlights("Ankara");
	cout << endl;
	AN.listDirectFlights("Bayburt");
	cout << endl << endl;
	
	AN.listRoutesOnHubAirport("Ankara");
	cout << endl;
	AN.listRoutesOnHubAirport("Balikesir");
	cout << endl << endl;
	
	AN.findConnectedComponents();
	cout << endl;
	
	AN.displayMostCentralAirport();
	cout << endl;
	return 0;
}


