#include "OrderDAO.h"
#include <sstream>
#include <iostream>
#include<string>
using namespace std;

OrderDAO::OrderDAO(Database &database) 
          : db(database){

          }

int OrderDAO::orderCall(void *data, int argc, char **argv, char **colNames){
    vector<Order>* orders = static_cast<vector<Order>*>(data);
    if(argc >= 6){
        int id = (argv[0] ? stoi(argv[0]) : 0);
        int custId = (argv[1] ? stoi(argv[1]) : 0);
        int restId = (argv[2] ? stoi(argv[2]) : 0);
        double total = (argv[3] ? stod(argv[3]) : 0.0);
        string status = (argv[4] ? argv[4] : "pending");
        string orderTime = (argv[5] ? argv[5] : "");
        orders->push_back(Order(id, custId, restId, total, status, orderTime));
    }
    return 0;
}
bool OrderDAO::insert(const Order &order){
    stringstream sql;
    sql << "INSERT INTO orders (customer_id, restaurant_id, total_price, status, order_time) VALUES ("
        << order.getCustomerId() << ", "<< order.getRestaurantId() << ", "
        << order.getTotalPrice() << ", '"<< order.getStatus() << "', datetime('now'));";
    return db.Apply(sql.str());
}
Order *OrderDAO::IDfind(int id){
    stringstream sql;
    sql << "SELECT id, customer_id, restaurant_id, total_price, status, order_time FROM orders WHERE id = " << id << ";";
    vector<Order> orders;
    db.Query(sql.str(), orderCall, &orders);
    if(orders.empty()){
        return nullptr;
    }
    return new Order(orders[0]);
}
vector<Order> OrderDAO::Customerfind(int customerId){
    stringstream sql;
    sql << "SELECT id, customer_id, restaurant_id, total_price, status, order_time FROM orders WHERE customer_id = " << customerId << " ORDER BY order_time DESC;";
    vector<Order> orders;
    db.Query(sql.str(), orderCall, &orders);
    return orders;
}
vector<Order> OrderDAO::Restaurantfind(int restaurantId){
    stringstream sql;
    sql << "SELECT id, customer_id, restaurant_id, total_price, status, order_time FROM orders WHERE restaurant_id = " << restaurantId << " ORDER BY order_time DESC;";
    vector<Order> orders;
    db.Query(sql.str(), orderCall, &orders);
    return orders;
}
bool OrderDAO::updateStatus(int orderId, const string &newStatus){
    stringstream sql;
    sql << "UPDATE orders SET status = '" << newStatus << "' WHERE id = " << orderId << ";";
    return db.Apply(sql.str());
}
int OrderDAO::getTotalOrders(){
    stringstream sql;
    sql << "SELECT COUNT(*) FROM orders;";
    int count = 0;
    auto callback = [](void* data, int argc, char** argv, char** col) -> int {
        if(argc > 0 && argv[0]) *((int*)data) = atoi(argv[0]);
        return 0;
    };
    db.Query(sql.str(), callback, &count);
    return count;
}
double OrderDAO::getTotalSales(){
    stringstream sql;
    sql << "SELECT SUM(total_price) FROM orders;";
    double total = 0.0;
    auto callback = [](void* data, int argc, char** argv, char** col) -> int {
        if(argc > 0 && argv[0]) *((double*)data) = atof(argv[0]);
        return 0;
    };
    db.Query(sql.str(), callback, &total);
    return total;
}