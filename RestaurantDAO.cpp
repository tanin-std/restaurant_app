#include "RestaurantDAO.h"
#include <sstream>
#include <iostream>
using namespace std;

RestaurantDAO::RestaurantDAO(Database &database)
            : db(database){

            }
int RestaurantDAO::restaurantCall(void *data, int argc, char **argv, char **colNames){
    vector<Restaurant>* restaurants = static_cast<vector<Restaurant>*>(data);
    if(argc >= 7){
        int id;
        if(argv[0] != nullptr){
           id = stoi(argv[0]);
        }
        else{
            id = -1;
        }
        string name;
        if(argv[1] != nullptr){
            name = argv[1];
        }
        else{
            name = "";
        }
        string address;
        if(argv[2] != nullptr){
            address = argv[2];
        }
        else{
            address = "";
        }
        bool Active;
        if(argv[3] != nullptr){
            Active = (stoi(argv[3]) == 1);
        }
        else{
            Active = true;
        }
        int prepTime;
        if(argv[4] != nullptr){
            prepTime = stoi(argv[4]);
        }
        else{
            prepTime = 0;
        }
        string phone;
        if(argv[5] != nullptr){
            phone = argv[5];
        }
        else{
            phone = "";
        }
        string desc;
        if(argv[6] != nullptr){
            desc = argv[6];
        }
        else{
            desc = "";
        }
        restaurants->push_back(Restaurant(id, name, address, Active, prepTime, phone, desc));
    }
    return 0;
}
bool RestaurantDAO::insert(const Restaurant& r){
    stringstream sql;
    sql << "INSERT INTO restaurants (name, address, is_active, preparation_time, phone, description) VALUES ('"
        << r.getName() << "', '"
        << r.getAddress() << "', "
        << r.getActive() << ", "
        << r.getPrepareTime() << ", '"
        << r.getPhone() << "', '"
        << r.getDescription() << "');";
    return db.Apply(sql.str()); 
}
Restaurant *RestaurantDAO::Idfind(int id){
    stringstream sql;
    sql << "SELECT id, name, address, is_active, preparation_time, phone, description FROM restaurants WHERE id = " << id << ";";
    vector<Restaurant> restaurants;
    db.Query(sql.str(), restaurantCall, &restaurants);
    if(restaurants.empty()){
       return nullptr;
    } 
    Restaurant *temp = new Restaurant(restaurants[0]);
    return temp;
}
vector<Restaurant> RestaurantDAO::findAll(){
    vector<Restaurant> restaurants;
    db.Query("SELECT id, name, address, is_active, preparation_time, phone, description FROM restaurants;", restaurantCall, &restaurants);
    return restaurants;
}
vector<Restaurant> RestaurantDAO::findActive(){
    vector<Restaurant> restaurants;
    db.Query("SELECT id, name, address, is_active, preparation_time, phone, description FROM restaurants WHERE is_active = 1;", restaurantCall, &restaurants);
    return restaurants;
}
bool RestaurantDAO::update(const Restaurant &r){
    stringstream sql;
    sql << "UPDATE restaurants SET name = '" << r.getName()<< "', address = '" << r.getAddress()
        << "', is_active = " << r.getActive()<< ", preparation_time = " << r.getPrepareTime()
        << ", phone = '" << r.getPhone()<< "', description = '" << r.getDescription()<< "' WHERE id = " << r.getId() << ";";
    return db.Apply(sql.str());
}
bool RestaurantDAO::IDdelete(int id){
    stringstream sql;
    sql << "DELETE FROM restaurants WHERE id = " << id << ";";
    return db.Apply(sql.str());
}