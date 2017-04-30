#ifndef PHONEBOOK_H
#define PHONEBOOK_H
#include <iostream>
using namespace std;


class PhoneBook
{
    public:
        PhoneBook();

        ~PhoneBook();

        void addPerson( const string firstName, const string lastName );

        void deletePerson( const string firstName, const string lastName );

        void addPhoneNumber( const string firstName, const string lastName,const int areaCode, const int number);

        void deletePhoneNumber( const string firstName, const string lastName,const int areaCode, const int number);

        void showPerson( const string firstName, const string lastName );

        void showPhoneNumber( const int areaCode, const int number );

        void showAll();

    private:
        struct PhoneNumber{
            int areaCode;
            int number;
            PhoneNumber* next = NULL;
            PhoneNumber(const int areaCode, const int number){
                this->areaCode = areaCode;
                this->number = number;
            }
        };
        struct Person{
            string firstName;
            string lastName;
            Person* next = NULL;
            Person* previous = NULL;
            PhoneNumber* phoneRoot = NULL;
            Person(const string firstName, const string lastName){
                this->firstName = firstName;
                this->lastName = lastName;
                this->next = NULL;
                this->previous = NULL;
                this->phoneRoot = NULL;
            }
            void printPhoneList(){
                if(this->phoneRoot != NULL){
                    PhoneNumber* current = this->phoneRoot;
                    do{
                        cout<<current->areaCode<<"-"<<current->number<<endl;
                        current = current->next;
                    }while(current != this->phoneRoot);
                }
            }
            ~Person(){
                if(this->phoneRoot != NULL){
                    PhoneNumber* currentPhoneNumber = phoneRoot;
                    do{
                        PhoneNumber* nextTemp = currentPhoneNumber->next;
                        delete currentPhoneNumber;
                        currentPhoneNumber = nextTemp;
                    }while(currentPhoneNumber != this->phoneRoot);
                }
            }
        };
        Person* personRoot;
        Person* findPerson(const string firstName, const string lastName);
        PhoneNumber* findPhoneNumber(PhoneNumber* phoneRoot, const int areaCode, const int number);
};

#endif // PHONEBOOK_H
