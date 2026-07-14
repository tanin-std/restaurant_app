#include "AdminMenu.h"
#include <iostream>
#include<string>
using namespace std;

AdminMenu::AdminMenu(int id, string username, string password)
    : User(id, username, password, "admin", 0),
     restaurantDAO(nullptr),
      userDAO(nullptr), 
      orderDAO(nullptr){

      }
void AdminMenu::setDAO(RestaurantDAO *rDAO, UserDAO *uDAO, OrderDAO *oDAO){
    restaurantDAO = rDAO;
    userDAO = uDAO;
    orderDAO = oDAO;
}
void AdminMenu::showAllRestaurants(){
    vector<Restaurant> restaurants = restaurantDAO->findAll();
    cout << "\n========== All Restaurants ==========\n";
    for(int i = 0; i < restaurants.size(); i++) {
        restaurants[i].display();
        cout << "--------------------------------\n";
    }
}
void AdminMenu::addNewRestaurant(){
    string name, addr, phone, desc;
    int prep;
    cout << "Enter restaurant name: "; 
    cin.ignore(); 
    getline(cin, name);
    cout << "Address: "; 
    getline(cin, addr);
    cout << "Phone: "; 
    getline(cin, phone);
    cout << "Preparation time (min): "; 
    cin >> prep;
    cout << "Description: "; 
    cin.ignore(); 
    getline(cin, desc);
    Restaurant newRest(0, name, addr, true, prep, phone, desc);
    if(restaurantDAO->insert(newRest)){
        cout << "Restaurant added successfully.\n";
    }
    else cout << "Failed to add restaurant.\n";
}
void AdminMenu::toggleRestaurantStatus(){
    int id;
    cout << "Enter restaurant ID: "; 
    cin >> id;
    Restaurant *r = restaurantDAO->Idfind(id);
    if(r){
        bool newStatus = !r->getActive();
        r->setActive(newStatus);
        if(restaurantDAO->update(*r)){
            cout << "Restaurant " << id << " is now " << (newStatus ? "ACTIVE" : "INACTIVE") << endl;
        }
        else{
            cout << "Update failed.\n";
        }
        delete r;
    } else{
        cout << "Restaurant not found.\n";
    }
}
void AdminMenu::showReports(){
    int totalRest = restaurantDAO->findAll().size();
    vector<User> users = userDAO->findAll();
    int totalUsers = users.size();
int totalOrders = orderDAO->getTotalOrders();
double totalSales = orderDAO->getTotalSales();
    cout << "\n---System Reports---\n";
    cout << "Total restaurants: " << totalRest << endl;
    cout << "Total users: " << totalUsers << endl;
    cout << "Total orders: " << totalOrders << endl;
    cout << "Total sales: " << totalSales << " Tomans\n";
}

void AdminMenu::showMenu(){
    int choice;
    do{
        cout << "\n------System Admin Menu------\n";
        cout << "1. View all restaurants\n";
        cout << "2. Add a new restaurant\n";
        cout << "3. Activate/Deactivate a restaurant\n";
        cout << "4. View reports\n";
        cout << "0. Logout\n";
        cout << "Choice: ";
        cin >> choice;
        switch(choice){
            case 1: showAllRestaurants(); 
            break;
            case 2: addNewRestaurant(); 
            break;
            case 3: toggleRestaurantStatus(); 
            break;
            case 4: showReports(); 
            break;
            case 0: cout << "Logging out...\n"; 
            break;
            default: cout << "Invalid choice.\n";
        }
    } while(choice != 0);
}