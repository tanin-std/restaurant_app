#include <iostream>
#include "ManagerMenu.h"
#include "FoodItem.h"
#include "DrinkItem.h"
using namespace std;

ManagerMenu::ManagerMenu(int id, string username, string password, int restId)
    : User(id, username, password, "manager", restId), 
    managed(restId),
    restaurantDAO(nullptr), 
    menuItemDAO(nullptr), 
    orderDAO(nullptr){

    }
void ManagerMenu::setDAO(RestaurantDAO *rDAO, MenuItemDAO *mDAO, OrderDAO *oDAO, LoyaltyDAO *lDAO){
    restaurantDAO = rDAO;
    menuItemDAO = mDAO;
    orderDAO = oDAO;
    loyaltyDAO = lDAO;
}
void ManagerMenu::showRestaurantInfo(){
    Restaurant *r = restaurantDAO->Idfind(managed);
    if(r){
        cout << "\nRestaurant Info: \n";
        r->display();
        delete r;
    }
    else{
        cout << "Restaurant not found.\n";
    }
}
void ManagerMenu::updateRestaurantInfo(){
    Restaurant *r = restaurantDAO->Idfind(managed);
    if(!r){
        return;
    }
    cout << "\nUpdating restaurant info:\n";
    string name, addr, phone, desc;
    int prep;
    cout << "Name (" << r->getName() << "): ";
    cin.ignore(); 
    getline(cin, name);
    if(!name.empty()){
        r->setName(name);
    }
    cout << "Address (" << r->getAddress() << "): "; 
    getline(cin, addr);
    if(!addr.empty()){
        r->setAddress(addr);
    }
    cout << "Phone (" << r->getPhone() << "): "; 
    getline(cin, phone);
    if(!phone.empty()) r->setPhone(phone);
    cout << "Preparation time (" << r->getPrepareTime() << " min): "; 
    cin >> prep;
    if(prep > 0){
        r->setPrepareTime(prep);
    }
    cout << "Description (" << r->getDescription() << "): "; 
    cin.ignore(); 
    getline(cin, desc);
    if(!desc.empty()){
        r->setDescription(desc);
    }
    if(restaurantDAO->update(*r)){
        cout << "Update successful.\n";
    }
    else cout << "Update failed.\n";
    delete r;
}

void ManagerMenu::addMenuItem(){
    string name, desc, type;
    double price;
    cout << "Item name: "; 
    cin.ignore(); 
    getline(cin, name);
    cout << "Description: "; 
    getline(cin, desc);
    cout << "Price: "; 
    cin >> price;
    cout << "Type (food/drink): "; 
    cin >> type;
    if(type == "food"){
        int cookingTime;
        cout << "Cooking time (min): "; 
        cin >> cookingTime;
        FoodItem* item = new FoodItem(0, managed, name, desc, price, true, cookingTime);
        if(menuItemDAO->insert(item)) cout << "Food item added.\n";
        else{
            cout << "Failed.\n";
        }
        delete item;
    } 
    else if(type == "drink"){
        double volume;
        cout << "Volume (L): "; 
        cin >> volume;
        DrinkItem* item = new DrinkItem(0, managed, name, desc, price, true, volume);
        if(menuItemDAO->insert(item)){
            cout << "Drink item added.\n";
        }
        else cout << "Failed.\n";
        delete item;
    } else{
        cout << "Invalid type.\n";
    }
}
void ManagerMenu::editMenuItem(){
    int id;
    cout << "Enter menu item ID to edit: "; 
    cin >> id;
    menuItem* item = menuItemDAO->IDfound(id);
    if(!item){ 
       cout << "Item not found.\n";
       return; 
    }
    cout << "Editing: "; 
    item->display();
    string newName, newDesc;
    double newPrice;
    cout << "New name (current: " << item->getName() << "): "; 
    cin.ignore(); 
    getline(cin, newName);
    if(!newName.empty()){
        item->setName(newName);
    }
    cout << "New description (current: " << item->getDescript() << "): "; 
    getline(cin, newDesc);
    if(!newDesc.empty()){
        item->setDescription(newDesc);
    }
    cout << "New price (current: " << item->getPrice() << "): "; 
    cin >> newPrice;
    if(newPrice > 0){
        item->setPrice(newPrice);
    }
    if(menuItemDAO->update(item)){
        cout << "Item updated.\n";
    }
    else{
        cout << "Update failed.\n";
    }
    delete item;
}
void ManagerMenu::deleteMenuItem(){
    int id;
    cout << "Enter menu item ID to delete: "; 
    cin >> id;
    if(menuItemDAO->IDdelete(id)){
        cout << "Item deleted.\n";
    }
    else{
        cout << "Delete failed.\n";
    }
}
void ManagerMenu::showOrdersAndUpdate(){
    if(!orderDAO){
        return;
    }
    vector<Order> orders = orderDAO->Restaurantfind(managed);
    if(orders.empty()){
        cout << "\nNo orders for this restaurant.\n";
        return;
    }
    cout << "\n----Orders----\n";
    for(int i = 0; i < orders.size(); i++){
        cout << i+1 << ". Order #" << orders[i].getID() << " | Customer ID: " << orders[i].getCustomerId()
             << " | Total: " << orders[i].getTotalPrice() << " T" << " | Status: " << orders[i].getStatus() << endl;
    }
    cout << "Enter order number to update status: ";
    int ch; 
    cin >> ch;
    if(ch >= 1 && ch <= (int)orders.size()){
        int orderId = orders[ch-1].getID();
        cout << "New status (pending/preparing/ready/delivered): ";
        string newStatus; 
        cin >> newStatus;
        if(orderDAO->updateStatus(orderId, newStatus)){
            cout << "Status updated.\n";
        }
        else{
            cout << "Update failed.\n";
        }
    }
}

void ManagerMenu::showMenu(){
    int choice;
    do {
        cout << "\n----Restaurant Manager Menu----\n";
        cout << "1. View restaurant info\n";
        cout << "2. Update restaurant info\n";
        cout << "3. Add new menu item\n";
        cout << "4. Edit a menu item\n";
        cout << "5. Delete a menu item\n";
        cout << "6. View and update orders\n";
        cout << "0. Logout\n";
        cout << "Choice: ";
        cin >> choice;
        switch(choice){
            case 1: showRestaurantInfo(); 
            break;
            case 2: updateRestaurantInfo(); 
            break;
            case 3: addMenuItem(); 
            break;
            case 4: editMenuItem(); 
            break;
            case 5: deleteMenuItem(); 
            break;
            case 6: showOrdersAndUpdate(); 
            break;
            case 0: cout << "Logging out...\n"; 
            break;
            default: cout << "Invalid choice.\n";
        }
    } while(choice != 0);
}