#ifndef CUSTOMERMENU_H
#define CUSTOMERMENU_H
#include<iostream>
#include<string>
#include "User.h"
#include "ShoppingCart.h"
#include "RestaurantDAO.h"
#include "MenuItemDAO.h"
#include "OrderDAO.h"

class CustomerMenu : public User{
private:
    ShoppingCart cart;
    RestaurantDAO *restaurantDAO;
    MenuItemDAO *menuItemDAO;
    OrderDAO *orderDAO;

    void showRestaurants();
    void showRestaurantMenu(int restaurantId);
    void showCart();
    void checkout();
    void showOrderHistory();

public:
    CustomerMenu(int id, string username, string password);
    void setDAO(RestaurantDAO *rDAO, MenuItemDAO *mDAO, OrderDAO *oDAO);
    void showMenu() override;
    ~CustomerMenu();
};
#endif