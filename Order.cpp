#include <iostream>
#include "Order.h"
using namespace std;

Order::Order(int ID, int custID, int restID,
        double Price, string Status, string Time)
    : id(ID), customerId(custID), restaurantId(restID),
      totalPrice(Price), status(Status), orderTime(Time){

      }
void Order::addItem(int menuItemId, int quantity){
    items.push_back({menuItemId, quantity});
}
int Order::getID() const{ 
    return id; 
}
int Order::getCustomerId() const{ 
    return customerId; 
}
int Order::getRestaurantId() const{ 
    return restaurantId; 
}
const vector<pair<int, int>> &Order::getItems() const{ 
    return items; 
}
double Order::getTotalPrice() const{ 
    return totalPrice; 
}
string Order::getStatus() const{ 
    return status; 
}
string Order::getOrderTime() const{ 
    return orderTime; 
}
void Order::setId(int newId){ 
    id = newId; 
}
void Order::setCustomerId(int id){ 
    customerId = id; 
}
void Order::setRestaurantId(int id){ 
    restaurantId = id; 
}
void Order::setTotalPrice(double price){ 
    totalPrice = price; 
}
void Order::setStatus(const string &newStatus){ 
    status = newStatus; 
}
void Order::setOrderTime(const string &time){ 
    orderTime = time; 
}
void Order::display() const{
    cout << "Order ID: " << id << endl;
    cout << "Customer ID: " << customerId << endl;
    cout << "Restaurant ID: " << restaurantId << endl;
    cout << "Total Price: " << totalPrice << " Tomans" << endl;
    cout << "Status: " << status << endl;
    cout << "Time: " << orderTime << endl;
    cout << "Items: ";
    int i;
    for(i=0; i < items.size(); i++){
        cout << "(ID " << items[i].first << " x" << items[i].second << ") "<< endl;;
    }
}