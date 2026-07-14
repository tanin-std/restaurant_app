#ifndef MENUITEM_H
#define MENUITEM_H
#include<string>
#include<iostream>
using namespace std;

class menuItem{
    protected:
    int id;
    string name;
    int restaurantID;
    string desc;
    double basePrice;
    string type;
    bool available;

    public:
    menuItem(int ID = 0, int resID = 0,string Name = "",
        string DES = "", double Price = 0, 
            string Type = "", bool Available = true);
    virtual ~menuItem();

    int getID() const;
    string getName() const;
    string getDescript() const;
    int getRestaurantID() const;
    double getPrice() const;
    string getType() const;
    bool getAvailable() const;
    void setName(const string &newName);
    void setPrice(double Price);
    void setAvailable(bool Available);
    void setDescription(const string &newDesc);
    virtual double FinalPrice() const;
    virtual void display() const;

};
#endif