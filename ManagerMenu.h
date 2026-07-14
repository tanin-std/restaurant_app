#ifndef MANAGERMENU_H
#define MANAGERMENU_H
#include<iostream>
#include<string>
#include "User.h"
#include "RestaurantDAO.h"
#include "MenuItemDAO.h"
#include "OrderDAO.h"

class ManagerMenu : public User{
private:
    RestaurantDAO *restaurantDAO;
    MenuItemDAO *menuItemDAO;
    OrderDAO *orderDAO;
    int managed;
    void showRestaurantInfo();
    void updateRestaurantInfo();
    void addMenuItem();
    void editMenuItem();
    void deleteMenuItem();
    void showOrdersAndUpdate();

public:
    ManagerMenu(int id, string username, string password, int restId);
    void setDAO(RestaurantDAO *rDAO, MenuItemDAO *mDAO, OrderDAO *oDAO);
    void showMenu() override;
};
#endif