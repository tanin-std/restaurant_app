#ifndef ORDER_H
#define ORDER_H
#include<iostream>
#include<string>
#include<vector>
#include<utility>
#include "MenuItem.h"
using namespace std;

class Order{
    private:
    int id;
    int customerId;
    int restaurantId;
    vector<pair<int, int>> items;
    double totalPrice;
    string status;
    string orderTime;

    public:
    Order(int ID = 0, int custID = 0, int restID = 0,
        double Price = 0, string Status = "pending", string Time = "");
    void addItem(int menuItemId, int quantity);
    int getID() const;
    int getCustomerId() const;
    int getRestaurantId() const;
    const vector<pair<int, int>> &getItems() const;
    double getTotalPrice() const;
    string getStatus() const;
    string getOrderTime() const;
    void setId(int newId);
    void setCustomerId(int id);
    void setRestaurantId(int id);
    void setTotalPrice(double price);
    void setStatus(const string& newStatus);
    void setOrderTime(const string& time);
    void display() const;
};
#endif