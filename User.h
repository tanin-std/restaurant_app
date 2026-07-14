#ifndef USER_H
#define USER_H
#include<iostream>
#include<string>
using namespace std;

class User{
    protected:
    int id;
    string userName;
    string pass;
    string role;
    int restaurantId;

    public:
    User();
    User(const User &other); 
    User(int ID, string Name, string password, string Role, int restId);
    virtual ~User();
    int getID() const;
    string getName() const;
    string getPass() const;
    string getRole() const;
    int getRestaurantId() const;
    void setID(int newID);
    void setName(const string &newName);
    void setPassword(const string &newPass);
    void setRestaurantId(int restId);
    virtual void showMenu(){}
	};
#endif 