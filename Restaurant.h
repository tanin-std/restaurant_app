#ifndef RESTAURANT_H
#define RESTAURANT_H
#include<iostream>
#include <string>
using namespace std;

class Restaurant{
    private:
    int id;
    string name;
    string address;
    bool Active;
    int prepareTime;
    string phone;
    string description;

    public:
    Restaurant(int ID = 0, string Name = "", string Address = "",
            bool Act = true, int Time = 0,
            string phoneNo = "", string desc = "");
    int getId() const;
    string getName() const;
    string getAddress() const;
    bool getActive() const;
    int getPrepareTime() const;
    string getPhone() const;
    string getDescription() const;
    void setId(int newID);
    void setName(const string &newName);
    void setAddress(const string &newAdd);
    void setActive(bool act);
    void setPrepareTime(int time);
    void setPhone(const string &newPhone);
    void setDescription(const string &newDesc);
    void display() const;
};
#endif