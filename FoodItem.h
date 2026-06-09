#ifndef FOODITEM_H
#define FOODITEM_H
#include<iostream>
#include "MenuItem.h"
using namespace std;

class FoodItem : public menuItem{
    private:
    int cookingTime;

    public:
    FoodItem(int ID = 0, int restId = 0, string Name = "",
            string descript = "", double Price = 0,
            bool Free = true, int Time = 0);
    double FinalPrice() const override;
    void display() const override;
    int getCookingTime() const;
};
#endif