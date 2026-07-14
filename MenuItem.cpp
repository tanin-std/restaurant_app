#include<iostream>
#include "MenuItem.h"
using namespace std;

menuItem::menuItem(int ID, int resID, string Name,
        string DES, double Price, 
            string Type, bool Available)
        :id(ID), restaurantID(resID),
        name(Name), desc(DES),
        basePrice(Price), type(Type), available(Available){

        }
menuItem::~menuItem(){

}
int menuItem::getID() const{
    return id;
}
string menuItem::getName() const{
     return name;
}
string menuItem::getDescript() const{
    return desc;
}
int menuItem::getRestaurantID() const{
    return restaurantID;
}
double menuItem::getPrice() const{
    return basePrice;
}
string menuItem::getType() const{
    return type;
}
bool menuItem::getAvailable() const{
    return available;
}
void menuItem::setName(const string &newName){
    name = newName;
}
void menuItem::setPrice(double Price){
    basePrice = Price;
}
void menuItem::setAvailable(bool Available){
     available = Available;
}
void menuItem::setDescription(const string &newDesc){
    desc = newDesc;
}
double menuItem::FinalPrice() const{
    return basePrice;
}
void menuItem::display() const{
    cout << "   ?? " << name << " - " << basePrice << endl;
    cout << desc << endl;
    if(available){
        cout << "Available"<< endl;
    }
    else{
        cout << "Unavailable"<< endl;
    }
}