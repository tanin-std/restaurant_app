#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H
#include<iostream>
#include "MenuItem.h"
#include <vector>
#include <utility>
using namespace std;

class ShoppingCart{
    private:
    vector<pair<MenuItem *, int>> items;
    double total;

    public:
    ShoppingCart();
    ~ShoppingCart();
    void addItem(MenuItem *item, int quantity);
    void removeItem(int menuItemID);
    void Quantity(int menuItemId, int quantity);
    void clear();
    double Total();
    void display() const;
    bool Empty() const;
    vector<pair<MenuItem *, int>> getItems() const;
};
#endif