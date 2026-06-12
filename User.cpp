#include "User.h"
#include<iostream>
using namespace std;

User::User(int ID, string Name, string password, string Role, int restId)
   :id(ID),
   userName(Name),
   pass(password),
   role(Role),
   restaurantId(restId){

   }
User::~User(){

}
int User::getID() const{
    return id;
}
string User::getName() const{
    return userName;
}
string User::getPass() const{
    return pass;
}
string User::getRole() const{
    return role;
}
int User::getRestaurantId() const{
    return restaurantId;
}
void User::setID(int newID){
    id = newID;
}
void User::setName(const string &newName){
    userName = newName;
}
void User::setPassword(const string &newPass){
    pass = newPass;
}
void setRestaurantId(int restId){
    restaurantId = restId;
}