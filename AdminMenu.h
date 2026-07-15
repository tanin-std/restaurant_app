#ifndef ADMINMENU_H
#define ADMINMENU_H
#include<iostream>
#include<string>
#include "User.h"
#include "RestaurantDAO.h"
#include "UserDAO.h"
#include "OrderDAO.h"
#include "LoyaltyDAO.h"

class AdminMenu : public User{
private:
    RestaurantDAO *restaurantDAO;
    UserDAO *userDAO;
    OrderDAO *orderDAO;
    LoyaltyDAO *loyaltyDAO;
    
    void showAllRestaurants();
    void addNewRestaurant();
    void toggleRestaurantStatus();
    void showReports();
    void showLevel();
    void manageLevel();
    void LevelHistory();

public:
    AdminMenu(int id, string username, string password);
    void setDAO(RestaurantDAO *rDAO, UserDAO *uDAO, OrderDAO *oDAO, LoyaltyDAO *lDAO);
    void showMenu() override;
};
#endif