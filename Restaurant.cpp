#include <iostream>
#include "Restaurant.h"
using namespace std;

Restaurant::Restaurant(int ID, string Name, string Address,
            bool Act, int Time,
            string phoneNo, string desc)
        : id(ID), name(Name), address(Address), Active(Act),
      prepareTime(Time), phone(phoneNo), description(desc){

      }
int Restaurant::getId() const{ 
    return id;
}
string Restaurant::getName() const{ 
    return name; 
}
string Restaurant::getAddress() const{
    return address; 
}
bool Restaurant::getActive() const{ 
    return Active; 
}
int Restaurant::getPrepareTime() const{ 
    return prepareTime;
}
string Restaurant::getPhone() const{ 
    return phone; 
}
string Restaurant::getDescription() const{ 
    return description; 
}
void Restaurant::setId(int newID){ 
    id = newID; 
}
void Restaurant::setName(const string &newName){ 
    name = newName; 
}
void Restaurant::setAddress(const string &newAdd){ 
    address = newAdd; 
}
void Restaurant::setActive(bool act){
    Active = act; 
}
void Restaurant::setPrepareTime(int time){ 
    prepareTime = time; 
}
void Restaurant::setPhone(const string &newPhone){ 
    phone = newPhone; 
}
void Restaurant::setDescription(const string &newDesc){ 
    description = newDesc; 
}
void Restaurant::display() const {
    cout << "Restaurant ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Address: " << address << endl;
    if(Active){
        cout << "Active"<< endl;
    }
    else{
        cout << "Deactive"<< endl;
    }
    cout << "Prep Time: " << prepareTime << " min" << endl;
    cout << "Phone: " << phone << endl;
    cout << "Description: " << description << endl;
}