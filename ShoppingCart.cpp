#include <iostream>
#include "ShoppingCart.h"
using namespace std;

ShoppingCart::ShoppingCart() 
    : total(0){

    }
ShoppingCart::~ShoppingCart(){
    clear();
}
void ShoppingCart::addItem(MenuItem *item, int quantity){
    if(!item || quantity <= 0){
      return;
    } 
    int i;
    for(i=0; i < items.size();i++) {
        if(items[i].first->getId() == item->getId()){
            items[i].second += quantity;
            Total();
            return;
        }
    }
    
    items.push_back({item, quantity});
    Total();
}
void ShoppingCart::removeItem(int menuItemID){
    int i;
    for(i=0; i < items.size();i++){
        if(items[i].first->getId() == menuItemID){
            items.erase(items.begin() + i);
            Total();
            return;
        }
    }
}
void ShoppingCart::Quantity(int menuItemId, int quantity){
    if(quantity <= 0){
        removeItem(menuItemId);
        return;
    }
    int i;
    for(i=0; i < items.size();i++){
        if(items[i].first->getId() == menuItemId){
            items[i].second = quantity;
            Total();
            return;
        }
    }
}
void ShoppingCart::clear(){
    items.clear();
    total = 0;
}
double ShoppingCart::Total(){
    total = 0;
    int i;
    for(i=0; i < items.size();i++){
        total += items[i].first->FinalPrice() * items[i].second;
    }
    return total;
}
void ShoppingCart::display() const{
    if(items.empty()){
        cout << "Shopping cart is empty!" << endl;
        return;
    }
    
    cout << "Your shopping cart: " << endl;
    int i;
    for(i=0; i < items.size(); i++){
        cout << " " << items[i].first->getName() << " * " << items[i].second 
            << " = " << items[i].first->FinalPrice() * items[i].second << endl;
    }
    
    cout << "Total: " << total << endl;
}
bool ShoppingCart::Empty() const{
    return items.empty();
}

vector<pair<MenuItem *, int>> ShoppingCart::getItems() const{
    return items;
}