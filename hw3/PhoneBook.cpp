//Cüneyt EREM, sec1, 21202398, hw3

#include "PhoneBook.h"

PhoneBook::PhoneBook()
{
    this->personRoot = NULL;
}

PhoneBook::~PhoneBook(){
    if(this->personRoot != NULL){
        Person* current = this->personRoot;
        while(current != NULL){
            Person* nextTemp = current->next;
            delete current;
            current = nextTemp;
        }
    }
}
void PhoneBook::addPerson( const string firstName, const string lastName ){
    cout<<endl;
    //check the user is exist or not
    if(findPerson(firstName,lastName) != NULL){
        cout<<"ERROR: Person "<<firstName<<" "<<lastName <<" is already exist in the Phone Book"<<endl;
        return;
    }
    Person* newPerson = new Person(firstName,lastName);
    // if the root is null than add it to the root
    if(this->personRoot == NULL){
        this->personRoot = newPerson;
        cout<<"Root is created!"<<endl;
    }
    //if we need to add this new user before the current root
    else if((this->personRoot->lastName).compare(lastName) > 0
            || ((this->personRoot->lastName).compare(lastName) == 0 && (this->personRoot->firstName).compare(firstName) > 0) ){
        cout<<"Add new person before the root"<<endl;
        newPerson->next = this->personRoot;
        this->personRoot->previous = newPerson;
        this->personRoot = newPerson;
    }
    //if the user come after the root
    else{
        for(Person* current = this->personRoot; current != NULL;current=current->next){
            //Add new person before the current
            if((current->lastName).compare(lastName) > 0
                || ((current->lastName).compare(lastName) == 0 && (current->firstName).compare(firstName) > 0)){
                cout<<"Add new person before the current"<<endl;
                newPerson->previous = current->previous;
                newPerson->next = current;
                current->previous->next = newPerson;
                current->previous = newPerson;
                break;
            }
            //Add new person after the current
            else if(current->next == NULL){
                cout<<"Add new person after the current"<<endl;
                newPerson->previous = current;
                current->next = newPerson;
                break;
            }
        }
    }
    cout<<"Person "<<firstName<<" "<<lastName <<" is added to the Phone Book"<<endl;
}
PhoneBook::Person* PhoneBook::findPerson(const string firstName, const string lastName){
    if(this->personRoot != NULL){
        for(Person* current = this->personRoot; current != NULL;current=current->next){
            if( (current->lastName).compare(lastName) == 0 &&  (current->firstName).compare(firstName) == 0)
                return current;
            if((current->lastName).compare(lastName) > 0)
                return NULL;
        }
    }
    return NULL;
}

void PhoneBook::deletePerson( const string firstName, const string lastName ){
    cout<<endl;
    Person* deletedPerson = findPerson(firstName,lastName);
    //check the user is exist or not
    if(deletedPerson == NULL){
        cout<<"ERROR: Person "<<firstName<<" "<<lastName <<" is not exist in the Phone Book"<<endl;
        return;
    }
    //if the person is in the root
    else if(deletedPerson == this->personRoot){
        cout<<"person root is deleted!"<<endl;
        this->personRoot = this->personRoot->next;
        if(this->personRoot != NULL)
            this->personRoot->previous = NULL;
        delete deletedPerson;
    }
    //if it is an ordinary person
    else{
        cout<<"ordinary person is deleted!"<<endl;
        deletedPerson->previous->next = deletedPerson->next;
        if(deletedPerson->next != NULL)
            deletedPerson->next->previous = deletedPerson->previous;
        delete deletedPerson;
    }
    cout<<"Person "<<firstName<<" "<<lastName <<" is deleted from the Phone Book"<<endl;
}

void PhoneBook::addPhoneNumber( const string firstName, const string lastName,const int areaCode, const int number){
    cout<<endl;
    Person* person = findPerson(firstName,lastName);
    //check person is exist
    if(person == NULL){
        cout<<"ERROR: Person "<<firstName<<" "<<lastName <<" is not exist in the Phone Book"<<endl;
        return;
    }
    //check phone number is exist
    if(findPhoneNumber(person->phoneRoot,areaCode,number) != NULL){
        cout<<"ERROR: Person "<<firstName<<" "<<lastName <<" is already have number "<<areaCode<<"-"<<number<<endl;
        return;
    }
    PhoneNumber* newPhoneNumber = new PhoneNumber(areaCode,number);
    //If the list is empty create the root
    if(person->phoneRoot == NULL){
        person->phoneRoot = newPhoneNumber;
        person->phoneRoot->next = person->phoneRoot;
        cout<<"Phone Root is created!"<<endl;
    }
    //if the list is not empty, add it at the end of list
    else{
        PhoneNumber* currentPhoneNumber = person->phoneRoot;
        while(currentPhoneNumber->next != person->phoneRoot)
            currentPhoneNumber = currentPhoneNumber->next;
        newPhoneNumber->next = person->phoneRoot;
        currentPhoneNumber->next = newPhoneNumber;
        cout<<"Phone number added at the end of list!"<<endl;
    }
    cout<<"Person "<<firstName<<" "<<lastName <<" with number "<<areaCode<<"-"<<number<<" is added to the Phone Book"<<endl;
}
PhoneBook::PhoneNumber* PhoneBook::findPhoneNumber(PhoneNumber* phoneRoot, const int areaCode, const int number){
    if(phoneRoot != NULL){
        PhoneNumber* currentPhoneNumber = phoneRoot;
        do{
            if(currentPhoneNumber->areaCode == areaCode && currentPhoneNumber->number == number)
                return currentPhoneNumber;
            currentPhoneNumber = currentPhoneNumber->next;
        }while(currentPhoneNumber != phoneRoot);
    }
    return NULL;
}

void PhoneBook::deletePhoneNumber( const string firstName, const string lastName,const int areaCode, const int number){
    cout<<endl;
    Person* person = findPerson(firstName,lastName);
    //check person is exist
    if(person == NULL){
        cout<<"ERROR: Person "<<firstName<<" "<<lastName <<" is not exist in the Phone Book"<<endl;
        return;
    }
    //check phone number is exist
    PhoneNumber* deletedPhoneNumber = findPhoneNumber(person->phoneRoot,areaCode,number);
    if(deletedPhoneNumber == NULL){
        cout<<"ERROR: Person "<<firstName<<" "<<lastName <<" is not have number "<<areaCode<<"-"<<number<<endl;
        return;
    }
    //if the number is in the root
    if(person->phoneRoot == deletedPhoneNumber ){
        // if there is only one phone in the system
        if(person->phoneRoot->next == person->phoneRoot){
            cout<<"Single Phone root deleted!"<<endl;
            delete person->phoneRoot;
            person->phoneRoot = NULL;
        }
        //If there is more than one element
        else{
            cout<<"Phone root deleted!"<<endl;
            PhoneNumber* currentPhoneNumber = person->phoneRoot;
            while(currentPhoneNumber->next != person->phoneRoot)
                currentPhoneNumber = currentPhoneNumber->next;
            currentPhoneNumber->next = person->phoneRoot->next;
            delete person->phoneRoot;
            person->phoneRoot = currentPhoneNumber->next;
        }
    }
    // if the number is not in the root
    else{
        cout<<"Phone node deleted!"<<endl;
        PhoneNumber* currentPhoneNumber = person->phoneRoot;
        while(currentPhoneNumber->next != deletedPhoneNumber)
            currentPhoneNumber = currentPhoneNumber->next;
        currentPhoneNumber->next = currentPhoneNumber->next->next;
        delete deletedPhoneNumber;
    }
}

void PhoneBook::showPerson( const string firstName, const string lastName ){
    cout<<endl;
    Person* person = findPerson(firstName,lastName);
    //check person is exist
    if(person == NULL){
        cout<<"ERROR: Person "<<firstName<<" "<<lastName <<" is not exist in the Phone Book"<<endl;
        return;
    }
    cout<<person->firstName<<" "<<person->lastName<<endl;
    person->printPhoneList();
}

void PhoneBook::showPhoneNumber( const int areaCode, const int number ){
    cout<<endl;
    if(this->personRoot != NULL)
        for(Person* current = this->personRoot; current != NULL;current=current->next)
            if(findPhoneNumber(current->phoneRoot,areaCode,number) != NULL){
                cout<<current->firstName<<" "<<current->lastName<<endl;
                cout<<areaCode<<"-"<<number<<endl;
                return;
            }
    cout<<"ERROR: Number "<<areaCode<<"-"<<number <<" is not exist in the Phone Book"<<endl;
}

void PhoneBook::showAll(){
    cout<<endl;
    for(Person* current = this->personRoot; current != NULL; current = current->next){
            cout<<current->firstName<<" "<<current->lastName<<endl;
            current->printPhoneList();
            cout<<endl;
    }
}
