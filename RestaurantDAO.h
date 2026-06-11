#ifndef RESTAURANTDAO_H
#define RESTAURANTDAO_H
#include<iostream>
#include "Database.h"
#include "Restaurant.h"
#include <vector>

class RestaurantDAO{
    private:
    Database& db; 
    static int restaurantCall(void *data, int argc, char **argv, char **colNames);

    public:
    RestaurantDAO(Database &database);
    bool insert(const Restaurant &rest);
    Restaurant *Idfind(int id);
    vector<Restaurant> findAll();
    vector<Restaurant> findActive();
    bool update(const Restaurant &rest);
    bool IDdelete(int id);

};
#endif