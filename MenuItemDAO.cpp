#include <iostream>
#include "MenuItemDAO.h"
#include "FoodItem.h"
#include "DrinkItem.h"
#include <sstream>
using namespace std;

MenuItemDAO::MenuItemDAO(Database &database)
     : db(database){

     }
menuItem *MenuItemDAO::create(char **argv){
    if(argv[0] == nullptr){
       return nullptr;
    } 
    int id;
    int restId;
    id = stoi(argv[0]);
    restId = stoi(argv[1]);
    string name;
    if(argv[2] != nullptr){
        name = argv[2];
    } 
    else{
        name = "";
    } 
    string desc;
    if(argv[3] != nullptr){
        desc = argv[3];
    }
    else{
        desc = "";
    }
    double price = stod(argv[4]);
    string type;
    if(argv[5] != nullptr){
        type = argv[5];
    }
    else{
        type = "";
    }
    bool available;
    if(argv[6] != nullptr){
        available = (stoi(argv[6]) == 1);
    }
    else{
        available = true;
    }
    if(type == "food"){
        int cookingTime;
        if(argv[7] != nullptr){
            cookingTime = stoi(argv[7]);
        }
        else{
            cookingTime = 0;
        }
        FoodItem *ftemp = new FoodItem(id, restId, name, desc, price, available, cookingTime);
        return ftemp;
    }
    else if(type == "drink"){
        double volume;
        if(argv[8] != nullptr){
            volume = stod(argv[8]);
        }
        else{
            volume = 0.0;
        }
        DrinkItem *Dtemp = new DrinkItem(id, restId, name, desc, price, available, volume);
        return Dtemp;
    }
    return nullptr;
}
int MenuItemDAO::menuItemCall(void *data, int argc, char **argv, char **colNames){
    vector<menuItem*>* items = static_cast<vector<menuItem*>*>(data);
    if(argc >= 7){
        menuItem *item = create(argv);
        if(item){
            items->push_back(item);
        }
    }
    return 0;
}
bool MenuItemDAO::insert(menuItem *item){
    stringstream sql;
    sql << "INSERT INTO menu_items (restaurant_id, name, description, base_price, type, is_available";
    if(item->getType() == "food"){
        FoodItem *f = dynamic_cast<FoodItem*>(item);
        if(f){
            sql << ", cooking_time) VALUES ("<< item->getRestaurantID() << ", '"<< item->getName() << "', '"
                << item->getDescript() << "', "<< item->getPrice() << ", 'food', "<< item->getAvailable() << ", "<< f->getCookingTime() << ");";
        }
         else{
            return false;
         }
    }
    else if(item->getType() == "drink"){
        DrinkItem *d = dynamic_cast<DrinkItem*>(item);
        if(d){
            sql << ", volume) VALUES ("<< item->getRestaurantID() << ", '"<< item->getName() << "', '"
                << item->getDescript() << "', "<< item->getPrice() << ", 'drink', "<< item->getAvailable() << ", "<< d->getVolume() << ");";
        } 
        else{
            return false;
        }
    }
    else{
        return false;
    }
    return db.Apply(sql.str()); 
}
menuItem *MenuItemDAO::IDfound(int id){
    stringstream sql;
    sql << "SELECT id, restaurant_id, name, description, base_price, type, is_available, cooking_time, volume "
        << "FROM menu_items WHERE id = " << id << ";";
    vector<menuItem*> items;
    db.Query(sql.str(), menuItemCall, &items);
    if(items.empty()){
        return nullptr;
    }
    return items[0];
}
vector<menuItem*> MenuItemDAO::RestFind(int restaurantId){
    stringstream sql;
    sql << "SELECT id, restaurant_id, name, description, base_price, type, is_available, cooking_time, volume "
        << "FROM menu_items WHERE restaurant_id = " << restaurantId << ";";
    vector<menuItem*> items;
    db.Query(sql.str(), menuItemCall, &items);
    return items;
}
vector<menuItem*> MenuItemDAO::findAvailable(int restaurantId){
    stringstream sql;
    sql << "SELECT id, restaurant_id, name, description, base_price, type, is_available, cooking_time, volume "
        << "FROM menu_items WHERE restaurant_id = " << restaurantId << " AND is_available = 1;";
    vector<menuItem*> items;
    db.Query(sql.str(), menuItemCall, &items);
    return items;
}
bool MenuItemDAO::update(menuItem *item){
    if(!item){
    	return false;
	}
    stringstream sql;
    sql << "UPDATE menu_items SET name = '" << item->getName()<< "', description = '" << item->getDescript()
        << "', base_price = " << item->getPrice()<< ", is_available = " << item->getAvailable()<< " WHERE id = " << item->getID() << ";";
    
    return db.Apply(sql.str());
}
bool MenuItemDAO::IDdelete(int id){
    stringstream sql;
    sql << "DELETE FROM menu_items WHERE id = " << id << ";";
    return db.Apply(sql.str());
}
bool MenuItemDAO::availableChange(int id, bool available){
    stringstream sql;
    sql << "UPDATE menu_items SET is_available = " << available << " WHERE id = " << id << ";";
    return db.Apply(sql.str());
}