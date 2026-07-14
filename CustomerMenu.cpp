#include "CustomerMenu.h"
#include <iostream>
#include <limits>
#include <cstdlib>
using namespace std;

CustomerMenu::CustomerMenu(int id, string username, string password)
    : User(id, username, password, "customer", 0), 
    restaurantDAO(nullptr), 
    menuItemDAO(nullptr), 
    orderDAO(nullptr){

    }
CustomerMenu::~CustomerMenu(){

}
void CustomerMenu::setDAO(RestaurantDAO *rDAO, MenuItemDAO *mDAO, OrderDAO *oDAO){
    restaurantDAO = rDAO;
    menuItemDAO = mDAO;
    orderDAO = oDAO;
}
void CustomerMenu::showRestaurants(){
    if(!restaurantDAO){
        return;
    }
    vector<Restaurant> restaurants = restaurantDAO->findActive();
    cout << "\n---Active Restaurants---\n";
    int i;
    for(i = 0; i < restaurants.size(); i++){
        cout << "ID: " << restaurants[i].getId() << " | Name: " << restaurants[i].getName()
             << " | Address: " << restaurants[i].getAddress() << " | Prep Time: " << restaurants[i].getPrepareTime() << " min\n";
    }
}
void CustomerMenu::showRestaurantMenu(int restaurantId){
    if(!menuItemDAO){
        return;
    }
    vector<menuItem*> items = menuItemDAO->findAvailable(restaurantId);
    if(items.empty()){
        cout << "No items available in this restaurant.\n";
        return;
    }
    cout << "\n----Menu----\n";
    for(int i = 0; i < items.size(); i++){
        cout << i+1 << ". ";
        items[i]->display();
        cout << "-------------------\n";
    }
    int choice, qty;
    cout << "Enter item number: ";
    cin >> choice;
    if(choice > 0 && choice <= (int)items.size()){
        cout << "Quantity: ";
        cin >> qty;
        if(qty > 0){
            cart.addItem(items[choice-1], qty);
            cout << "Added to cart. Total now: " << cart.Total() << " Tomans\n";
        }
    }
    for(int i = 0; i < items.size(); i++){
        delete items[i];
    }
}
void CustomerMenu::showCart(){
    cart.display();
    if(cart.Empty()){
        return;
    }
    cout << "\n1. Remove item\n2. Checkout\n0. Back\nChoice: ";
    int opt; 
    cin >> opt;
    if(opt == 1){
        int idx;
        cout << "Enter item number to remove: ";
        cin >> idx;
        if(idx >= 1 && idx <= (int)cart.getItems().size()){
            int itemId = cart.getItems()[idx-1].first->getID();
            cart.removeItem(itemId);
            cout << "Item removed.\n";
        }
    } 
    else if(opt == 2){
        checkout();
    }
}
void CustomerMenu::checkout(){
    if(cart.Empty()){
        return;
    }
    cart.display();
    int confirm;
    cout << "Do you Confirm order? (1=Yes, 0=No): ";
    cin >> confirm;
    if(confirm == 1){
        int restId = 0;
        if(!cart.getItems().empty()){
            restId = cart.getItems()[0].first->getRestaurantID();
        }
        double total = cart.Total();
        Order newOrder(0, getID(), restId, total, "pending", "");
        if(orderDAO->insert(newOrder)){
            cout << "\nOrder placed successfully!" << endl;
            cout << "Status: Pending \n";
            cout << "Restaurant has been notified\n";
            cart.clear();
        } 
        else{
            cout << "Failed to place order. Please try again.\n";
        }
    }
}
void CustomerMenu::showOrderHistory(){
    if(!orderDAO){
        return;
    }
    vector<Order> orders = orderDAO->Customerfind(getID());
    if(orders.empty()){
        cout << "\nNo orders found.\n";
        return;
    }
    cout << "\n---- Order History ---\n";
    for(int i = 0; i < orders.size(); i++){
        cout << "Order #" << orders[i].getID() << " | Restaurant ID: " << orders[i].getRestaurantId()
             << " | Total: " << orders[i].getTotalPrice() << " Tomans" << " | Status: " << orders[i].getStatus() << endl;
    }
}
void CustomerMenu::showMenu(){
    int choice, restId;
    do {
        cout << "\n---Customer Menu---\n";
        cout << "1. View active restaurants\n";
        cout << "2. View restaurant menu\n";
        cout << "3. View shopping cart\n";
        cout << "4. Order history\n";
        cout << "0. Logout\n";
        cout << "Choice: ";
        cin >> choice;
        switch(choice){
            case 1: showRestaurants(); 
            break;
            case 2:
                cout << "Enter restaurant ID: ";
                cin >> restId;
                showRestaurantMenu(restId);
                break;
            case 3: showCart(); 
            break;
            case 4: showOrderHistory(); 
            break;
            case 0: cout << "Logging out...\n"; 
            break;
            default: cout << "Invalid choice.\n";
        }
    } while(choice != 0);
}