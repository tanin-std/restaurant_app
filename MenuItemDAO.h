#ifndef MENUITEMDAO_H
#define MENUITEMDAO_H
#include<iostream>
#include "Database.h"
#include "MenuItem.h"
#include <vector>

class MenuItemDAO{
    private:
    Database& db;
    static MenuItem *create(char **argv);
    static int menuItemCall(void *data, int argc, char **argv, char **colNames);

    public:
    MenuItemDAO(Database &database);
    bool insert(MenuItem *item);  
    MenuItem *IDfound(int id);
    std::vector<MenuItem*> RestFind(int restaurantId);
    std::vector<MenuItem*> findAvailable(int restaurantId);
    bool IDdelete(int id);
    bool availableChange(int id, bool available);
};
#endif