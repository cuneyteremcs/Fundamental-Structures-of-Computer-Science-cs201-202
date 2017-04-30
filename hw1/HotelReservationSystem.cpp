#include "HotelReservationSystem.h"

HotelReservationSystem::HotelReservationSystem()
{
        //simple constructor that construct the system
        //system will start with 0 hotel
        hotelNumber = 0;
        hotelNames = new string[hotelNumber];
        floorNumbers = new int[hotelNumber];
        roomNumber = new int*[hotelNumber];
        availableRooms = new bool**[hotelNumber];
}

HotelReservationSystem::~HotelReservationSystem()
{
    //simple destructor that destruct the system (another word deallocate the memory)
    delete []hotelNames;
    for(int i = 0; i < hotelNumber; i++){
        for(int j = 0; j < floorNumbers[i]; j++)
            delete [] availableRooms[i][j];
        delete [] availableRooms[i];
        delete [] roomNumber[i];
    }
    delete []floorNumbers;
    delete []roomNumber;
    delete []availableRooms;
}
void HotelReservationSystem::addHotel( const string name, const int numFloors, const int *numRooms ){
    //This method add a new hotel to the system.
    //First check for existence
    bool alreadyExist = false;
    for(int i = 0; i < hotelNumber && !alreadyExist; i++ )
        if(name.compare(hotelNames[i]) == 0)
            alreadyExist = true;
    //if it is exist give error message and return
    if(alreadyExist){
        cout<<"Hotel "<<name<<" already exists"<<endl;
        return;
    }
    //if it is unique,than create new arrays with size+1
    int newHotelNumber = hotelNumber+1;
    string* newHotelNames = new string[newHotelNumber];
    int* newFloorNumbers = new int[newHotelNumber];
    int** newRoomNumber = new int*[newHotelNumber];
    bool*** newAvailableRooms = new bool**[newHotelNumber];

    //swap old values
    for(int i = 0; i < hotelNumber; i++ ){
        newHotelNames[i] = hotelNames[i];
        newFloorNumbers[i] = floorNumbers[i];
        newRoomNumber[i] = roomNumber[i];
        newAvailableRooms[i] = availableRooms[i];
    }
    //add new values
    newHotelNames[hotelNumber] = name;
    newFloorNumbers[hotelNumber] = numFloors;
    newRoomNumber[hotelNumber] = new int[numFloors];
    for(int i = 0; i <numFloors; i++)
        newRoomNumber[hotelNumber][i] = numRooms[i];
    newAvailableRooms[hotelNumber] = new bool*[numFloors];
    for(int i = 0; i < numFloors; i++){
        newAvailableRooms[hotelNumber][i] = new bool[newRoomNumber[hotelNumber][i]];
        for(int j = 0; j < newRoomNumber[hotelNumber][i]; j++)
            newAvailableRooms[hotelNumber][i][j] = true;
    }
    //delete old array references
    delete []hotelNames;
    delete []floorNumbers;
    delete []roomNumber;
    delete []availableRooms;
    //use new references
    hotelNumber = newHotelNumber;
    hotelNames = newHotelNames;
    floorNumbers = newFloorNumbers;
    roomNumber = newRoomNumber;
    availableRooms = newAvailableRooms;
    //give the message
    cout<<"Hotel "<<name <<" is added"<<endl;
}

void HotelReservationSystem::deleteHotel( const string name ){
    //This method delete a hotel from the system.
    //First check for existence
    int index = -1;
    for(int i = 0; i < hotelNumber && index == -1; i++ )
        if(name.compare(hotelNames[i]) == 0)
            index = i;

    //if it is not exist give error message and return
    if(index < 0){
        cout<<"Hotel "<<name<<" does not exist for deletion"<<endl;
        return;
    }
    //if it is exist,than create new arrays with size-1
    int newHotelNumber = hotelNumber-1;
    string* newHotelNames = new string[newHotelNumber];
    int* newFloorNumbers = new int[newHotelNumber];
    int** newRoomNumber = new int*[newHotelNumber];
    bool*** newAvailableRooms = new bool**[newHotelNumber];


    //swap old values except for the deleted hotel
    for(int i = 0; i < index; i++ ){
        newHotelNames[i] = hotelNames[i];
        newFloorNumbers[i] = floorNumbers[i];
        newRoomNumber[i] = roomNumber[i];
        newAvailableRooms[i] = availableRooms[i];
    }

    for(int i = index+1; i < hotelNumber; i++ ){
        newHotelNames[i-1] = hotelNames[i];
        newFloorNumbers[i-1] = floorNumbers[i];
        newRoomNumber[i-1] = roomNumber[i];
        newAvailableRooms[i-1] = availableRooms[i];
    }
    //delete the data that belong to hotel which will deleted
    for(int i = 0; i < floorNumbers[index]; i++)
        delete[] availableRooms[index][i];
    delete[] availableRooms[index];
    delete[] roomNumber[index];

    //delete old array references
    delete []hotelNames;
    delete []floorNumbers;
    delete []roomNumber;
    delete []availableRooms;
    //use new references
    hotelNumber = newHotelNumber;
    hotelNames = newHotelNames;
    floorNumbers = newFloorNumbers;
    roomNumber = newRoomNumber;
    availableRooms = newAvailableRooms;
    //give the message
    cout<<"Hotel "<<name <<" is deleted"<<endl;
}

void HotelReservationSystem::makeReservation( const string name, const int floor, const int room ){
    //This method make a reservation from a given hotel.
    //First check for existence of hotel
    int index = -1;
    for(int i = 0; i < hotelNumber && index == -1; i++ )
        if(name.compare(hotelNames[i]) == 0)
            index = i;

    //if it is not exist give error message and return
    if(index < 0){
        cout<<"Hotel "<<name<<" does not exist for reservation"<<endl;
        return;
    }
    //if the room is not exist give error message and return
    if(floor > floorNumbers[index] || floor < 1){
        cout<<"Room "<<room<<" on floor "<<floor<<" does not exist at hotel "<<name<<endl;
        return;
    }
    if(room < 1 || room > roomNumber[index][floor-1]){
        cout<<"Room "<<room<<" on floor "<<floor<<" does not exist at hotel "<<name<<endl;
        return;
    }
    //if the room is not available give error message and return
    if(availableRooms[index][floor-1][room-1] == false){
        cout<<"Room "<<room<<" on floor "<<floor<<" is not available at hotel "<<name<<endl;
        return;
    }
    //if the room is available make the reservation and give the message
    availableRooms[index][floor-1][room-1] = false;
    cout<<"Room "<<room<<" on floor "<<floor<<" is reserved at hotel "<<name<<endl;

}

void HotelReservationSystem::cancelReservation( const string name, const int floor, const int room ){
    //This method cancel a reservation from a given hotel.
    //First check for existence of hotel
    int index = -1;
    for(int i = 0; i < hotelNumber && index == -1; i++ )
        if(name.compare(hotelNames[i]) == 0)
            index = i;
    //if it is not exist give error message and return
    if(index < 0){
        cout<<"Hotel "<<name<<" does not exist for reservation"<<endl;
        return;
    }
    //if the room is not exist give error message and return
    if(floor > floorNumbers[index] || floor < 1){
        cout<<"Room "<<room<<" on floor "<<floor<<" does not exist at hotel "<<name<<endl;
        return;
    }
    if(room < 1 || room > roomNumber[index][floor-1]){
        cout<<"Room "<<room<<" on floor "<<floor<<" does not exist at hotel "<<name<<endl;
        return;
    }
    //if the room is available give error message and return
    if(availableRooms[index][floor-1][room-1]){
        cout<<"Reservation for room "<<room<<" on floor "<<floor<<" does not exist at hotel "<<name<<endl;
        return;
    }
    //if the room is not available(if there is a valid reservation) cancel the reservation and give the message
    availableRooms[index][floor-1][room-1] = true;
    cout<<"Reservation for room "<<room<<" on floor "<<floor<<" is cancelled at hotel "<<name<<endl;
}

void HotelReservationSystem::showHotels(){
    cout<<endl<<"Name\t#Floors\t#Rooms"<<endl;
    for(int i = 0; i <hotelNumber; i++){
        int totalRoomNumber = 0;
        for(int j = 0; j <floorNumbers[i]; j++)
            totalRoomNumber += roomNumber[i][j];
        cout<<hotelNames[i]<<"\t"<<floorNumbers[i]<<"\t"<<totalRoomNumber<<endl;
    }
    cout<<endl;
}

void HotelReservationSystem::showRooms( const string name ){
    //This method show the rooms of a given hotel.
    //First check for existence of hotel
    int index = -1;
    for(int i = 0; i < hotelNumber && index == -1; i++ )
        if(name.compare(hotelNames[i]) == 0)
            index = i;
    //if it is not exist give error message and return
    if(index < 0){
        cout<<"Hotel "<<name<<" does not exist for showing rooms"<<endl;
        return;
    }
    //if it is exist,print the rooms
    cout<<endl<<"Hotel "<<name<<" rooms:"<<endl;
    for(int i = 0; i <floorNumbers[index]; i++){
        cout<<i+1<<": ";
        for(int j = 0; j <roomNumber[index][i]; j++)
            if(availableRooms[index][i][j])
                cout<<"o";
            else
                cout<<"x";
        cout<<endl;
    }
    cout<<endl;

}

void HotelReservationSystem::showReservations( const string name ){
    //This method show the reservations of a given hotel.
    //First check for existence of hotel
    int index = -1;
    for(int i = 0; i < hotelNumber && index == -1; i++ )
        if(name.compare(hotelNames[i]) == 0)
            index = i;
    //if it is not exist give error message and return
    if(index < 0){
        cout<<"Hotel "<<name<<" does not exist for showing reservations"<<endl;
        return;
    }
    //if it is exist,print the reservations
    cout<<endl<<"Hotel "<<name<<" reservations:"<<endl;
    cout<<"Floor\tRoom"<<endl;
    for(int i = 0; i <floorNumbers[index]; i++){
        for(int j = 0; j <roomNumber[index][i]; j++)
            if(availableRooms[index][i][j] == false)
                cout<<i+1<<"\t"<<j+1<<endl;
    }
    cout<<endl;

}
