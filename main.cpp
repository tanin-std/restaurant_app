#include <iostream>
#include <string>
#include "Database.h"
#include "UserDAO.h"
#include "RestaurantDAO.h"
#include "MenuItemDAO.h"
#include "OrderDAO.h"
#include "CustomerMenu.h"
#include "ManagerMenu.h"
#include "AdminMenu.h"
#include "LoyaltyDAO.h"
using namespace std;

User* login(UserDAO &userDAO){
    string username, password;
    cout << "\n========== LOGIN ==========\n";
    cout << "Username: "; 
    cin >> username;
    cout << "Password: "; 
    cin >> password;
    return userDAO.login(username, password);
}

int main(){
    cout << "   Food Ordering System \n";
    cout << "========================================\n";
    Database db("restaurant_app.db");
    if(!db.Open()){
        cout << "Cannot connect to database\n";
        return 1;
    }
    UserDAO userDAO(db);
    RestaurantDAO restaurantDAO(db);
    MenuItemDAO menuItemDAO(db);
    OrderDAO orderDAO(db);
    LoyaltyDAO loyaltyDAO(db);
    int mainChoice;
    do{
        cout << "\n1. Login\n0. Exit\nChoice: ";
        cin >> mainChoice;
        if(mainChoice == 1){
            User* user = login(userDAO);
            if(user){
                cout << "\nWelcome " << user->getName() << " Role: " << user->getRole() << endl;
                if(user->getRole() == "customer"){
                    CustomerMenu *customer = new CustomerMenu(user->getID(), user->getName(), user->getPass());
                    customer->setDAO(&restaurantDAO, &menuItemDAO, &orderDAO, &loyaltyDAO);
                    customer->showMenu();
                    delete customer;
                }
                else if(user->getRole() == "manager"){
                    int restId = user->getRestaurantId(); 
                    ManagerMenu* manager = new ManagerMenu(user->getID(), user->getName(), user->getPass(), restId);
                    manager->setDAO(&restaurantDAO, &menuItemDAO, &orderDAO, &loyaltyDAO);
                    manager->showMenu();
                    delete manager;
                }
                else if(user->getRole() == "admin"){
                    AdminMenu* admin = new AdminMenu(user->getID(), user->getName(), user->getPass());
                    admin->setDAO(&restaurantDAO, &userDAO, &orderDAO, &loyaltyDAO);
                    admin->showMenu();
                    delete admin;
                }
                delete user;
            } 
            else{
                cout << "Invalid username or password.\n";
            }
        }
    } while(mainChoice != 0);
    cout << "Thank you for using our service.\n";
    return 0;
}