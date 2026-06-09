#ifndef DRINKITEM_H
#define DRINKITEM_H
#include<iostream>
#include "MenuItem.h"
using namespace std;

class DrinkItem : public menuItem{
    private:
    double volume;

    public:
    DrinkItem(int ID = 0, int restId = 0, string Name = "",
            string descript = "", double Price = 0,
            bool Available = true, double Volume = 0);
    double FinalPrice() const override;
    void display() const override;
    double getVolume() const;

};
#endif