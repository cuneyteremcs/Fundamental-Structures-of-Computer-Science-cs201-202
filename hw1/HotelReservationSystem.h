#ifndef HOTELRESERVATIONSYSTEM_H
#define HOTELRESERVATIONSYSTEM_H
#include <iostream>
using namespace std;
class HotelReservationSystem
{
    public:
        HotelReservationSystem();

        ~HotelReservationSystem();

        void addHotel( const string name, const int numFloors, const int *numRooms );

        void deleteHotel( const string name );

        void makeReservation( const string name, const int floor, const int room );

        void cancelReservation( const string name, const int floor, const int room );

        void showHotels();

        void showRooms( const string name );

        void showReservations( const string name );

    protected:

    private:
        int hotelNumber;//current number of hotels in the system.
        string* hotelNames;//name array of hotels
        int* floorNumbers;//floor numbers of each hotel
        int** roomNumber;//room numbers of each floor of each hotel
        bool*** availableRooms;//availability of each room of each floor of each hotel

};

#endif // HOTELRESERVATIONSYSTEM_H
