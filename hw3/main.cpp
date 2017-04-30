//Cüneyt EREM, sec1, 21202398, hw3

#include <iostream>
#include "PhoneBook.h"
using namespace std;

int main()
{
    PhoneBook deneme1;
    deneme1.addPerson("cigdem gunduz","demir");
    deneme1.addPerson("selim","aksoy");
    deneme1.addPerson("ercument","cicek");

    deneme1.addPerson("altay","guvenir");

    deneme1.addPhoneNumber("selim","aksoy",312,2903405);
    deneme1.addPhoneNumber("selim","aksoy",312,1234567);

    deneme1.addPhoneNumber("ercument","cicek",312,2906941);
    deneme1.addPhoneNumber("ercument","cicek",312,9876543);

    deneme1.addPhoneNumber("altay","guvenir",312,2901252);
    deneme1.addPhoneNumber("altay","guvenir",312,2901218);
    deneme1.showAll();

    cout << "after delete" << endl;

    deneme1.deletePhoneNumber("ercument","cicek",312,9876543);
    deneme1.deletePhoneNumber("ercument","cicek",312,9876543);

    deneme1.deletePerson("ercument","cicek");

    deneme1.showAll();
    cout << "End" << endl;
    return 0;
}
