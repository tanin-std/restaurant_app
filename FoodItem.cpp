#include<iostream>
#include "FoodItem.h"
using namespace std;

FoodItem::FoodItem(int ID, int restId, string Name,
            string descript, double Price,
            bool Free, int Time)
        :menuItem(ID, restId, Name, descript, Price, "food", Free),
        cookingTime(Time){

        }
double FoodItem::FinalPrice() const{
    double tax;
    double Final;
    tax = basePrice * 0.09;
    Final = basePrice + tax;
    return Final;
}
void FoodItem::display() const{
     cout << "FOOD: " << name << " - " << FinalPrice() << endl;
    cout << desc << endl;
    cout << "Cooking time: " << cookingTime << " minutes" << endl;
    if(getAvailable()){
        cout << "Available!" <<endl;
    }
    else{
        cout << "Not available" << endl;
    }
}
int FoodItem::getCookingTime() const{
    return cookingTime;
}