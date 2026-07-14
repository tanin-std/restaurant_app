#include<iostream>
#include "DrinkItem.h"
using namespace std;

DrinkItem::DrinkItem(int ID, int restId, string Name, string descript, double Price,
            bool Free, double Volume)
        : menuItem(ID, restId, Name, descript, Price, "drink", Free),
      volume(Volume){

      }
double DrinkItem::FinalPrice() const{
    return basePrice;
}
void DrinkItem::display() const{
    cout << "DRINK: " << name << " - " << FinalPrice() << endl;
    cout << desc << endl;
    cout << "Volume: " << volume << " Liters" << endl;
    if(getAvailable()){
        cout << "Available!" <<endl;
    }
    else{
        cout << "Not available" << endl;
    }
    
}
double DrinkItem::getVolume() const{
    return volume; 
}