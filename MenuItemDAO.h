#ifndef MENUITEMDAO_H
#define MENUITEMDAO_H
#include<iostream>
#include "Database.h"
#include "MenuItem.h"
#include <vector>

class MenuItemDAO{
    private:
    Database& db;
    static menuItem *create(char **argv);
    static int menuItemCall(void *data, int argc, char **argv, char **colNames);

    public:
    MenuItemDAO(Database &database);
    bool insert(menuItem *item);  
    menuItem *IDfound(int id);
    std::vector<menuItem*> RestFind(int restaurantId);
    std::vector<menuItem*> findAvailable(int restaurantId);
    bool update(menuItem *item);
    bool IDdelete(int id);
    bool availableChange(int id, bool available);
};
#endif