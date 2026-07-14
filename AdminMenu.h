#ifndef ADMINMENU_H
#define ADMINMENU_H
#include<iostream>
#include<string>
#include "User.h"
#include "RestaurantDAO.h"
#include "UserDAO.h"
#include "OrderDAO.h"

class AdminMenu : public User{
private:
    RestaurantDAO *restaurantDAO;
    UserDAO *userDAO;
    OrderDAO *orderDAO;
    void showAllRestaurants();
    void addNewRestaurant();
    void toggleRestaurantStatus();
    void showReports();

public:
    AdminMenu(int id, string username, string password);
    void setDAO(RestaurantDAO *rDAO, UserDAO *uDAO, OrderDAO *oDAO);
    void showMenu() override;
};
#endif