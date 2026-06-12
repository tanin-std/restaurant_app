#ifndef ORDERDAO_H
#define ORDERDAO_H
#include<iostream>
#include<string>
#include "Database.h"
#include "Order.h"
#include <vector>

class OrderDAO{
private:
    Database &db;
    static int orderCall(void *data, int argc, char **argv, char **colNames);

public:
    OrderDAO(Database &database);
    bool insert(const Order &order);
    Order *IDfind(int id);
    std::vector<Order> Customerfind(int customerId);
    std::vector<Order> Restaurantfind(int restaurantId);
    bool updateStatus(int orderId, const string &newStatus);
    int getTotalOrders();
    double getTotalSales();
};

#endif