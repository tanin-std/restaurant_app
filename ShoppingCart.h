#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H
#include<iostream>
#include "MenuItem.h"
#include <vector>
#include <utility>
using namespace std;

class ShoppingCart{
    private:
    vector<pair<menuItem *, int>> items;
    double total;

    public:
    ShoppingCart();
    ~ShoppingCart();
    void addItem(menuItem *item, int quantity);
    void removeItem(int menuItemID);
    void Quantity(int menuItemId, int quantity);
    void clear();
    double Total();
    void display() const;
    bool Empty() const;
    vector<pair<menuItem *, int>> getItems() const;
};
#endif