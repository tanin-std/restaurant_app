#include "AdminMenu.h"
#include <iostream>
#include<string>
using namespace std;

AdminMenu::AdminMenu(int id, string username, string password)
    : User(id, username, password, "admin", 0),
     restaurantDAO(nullptr),
      userDAO(nullptr), 
      orderDAO(nullptr),
	  loyaltyDAO(nullptr){

      }
void AdminMenu::setDAO(RestaurantDAO *rDAO, UserDAO *uDAO, OrderDAO *oDAO, LoyaltyDAO *lDAO){
    restaurantDAO = rDAO;
    userDAO = uDAO;
    orderDAO = oDAO;
    loyaltyDAO = lDAO;
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

static int levelCall(void* data, int argc, char** argv, char** col){
    if(argc >= 2){
        string level;
        if(argv[0] != nullptr){
            level = argv[0];
        } 
        else{
            level = "Unknown";
        }
        int count;
        if(argv[1] != nullptr){
            count = atoi(argv[1]);
        } 
        else{
            count = 0;
        }
        cout << level << ": " << count << " users" << endl;
    }
    return 0;
}
void AdminMenu::showLevel(){
    cout << "\n-- Level Statistics --\n";
    if(loyaltyDAO == nullptr){
        cout << "Loyalty system not available.\n";
        return;
    }
    string Sql = "SELECT membership_level, COUNT(*) FROM users GROUP BY membership_level;";
    loyaltyDAO->executeQuery(Sql, levelCall, nullptr);
}
void AdminMenu::manageLevel(){
    int userId, points;
    string newLevel;
    cout << "\n--Manual Level Management--\n";
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter new level (Normal/Silver/Gold/VIP): ";
    cin >> newLevel;
    cout << "Enter new points: ";
    cin >> points;
    if(newLevel != "Normal" && newLevel != "Silver" &&
        newLevel != "Gold" && newLevel != "VIP"){
        cout << "Invalid level!\n";
        return;
    }
    if(points < 0){
        cout << "Points cannot be negative\n";
        return;
    }
    if (loyaltyDAO == nullptr) {
    cout << "Loyalty system not available\n";
    return;
    }

  LoyaltySystem* oldLoyalty = loyaltyDAO->load(userId);
   string oldLevel;

  if(oldLoyalty != nullptr){
    oldLevel = oldLoyalty->getLevel();
  } 
  else{
    oldLevel = "Normal";
}
bool levelUpdate = loyaltyDAO->updateLevel(userId, newLevel);
bool pointsUpdate = loyaltyDAO->updatePoints(userId, points);
    if(levelUpdate && pointsUpdate){
        loyaltyDAO->LevelChange(userId, oldLevel, newLevel, "admin");
        cout << "User level updated successfully!\n";
        cout << "User ID: " << userId << endl;
        cout << "New Level: " << newLevel << endl;
        cout << "New Points: " << points << endl;
    } 
	else{
        cout << "Update failed" << endl;
    }
    delete oldLoyalty;
}

void AdminMenu::LevelHistory(){
    int userId;
    cout << "\nLevel Change History: \n";
    cout << "Enter user ID: ";
    cin >> userId;
    if(loyaltyDAO == nullptr){
        cout << "Loyalty system not available\n";
        return;
    }
    vector<string> history = loyaltyDAO->getHistory(userId);
    if(history.empty()){
        cout << "No history found for user " << userId << endl;
        return;
    }
    cout << "\nHistory for user " << userId << endl;
    int i;
    for(i = 0; i < history.size(); i++){
        cout << (i + 1) << history[i] << endl;
    }
}
void AdminMenu::showMenu(){
    int choice;
    do {
        cout << "\n----System Admin Menu----\n";
        cout << "1. View all restaurants\n";
        cout << "2. Add a new restaurant\n";
        cout << "3. Activate/Deactivate a restaurant\n";
        cout << "4. View reports\n";
        cout << "5. Level statistics\n";         
        cout << "6. Manual level management\n";  
        cout << "7. View level history\n";         
        cout << "0. Logout\n";
        cout << "Choice: ";
        cin >> choice;
        switch(choice){
            case 1: {
            	showAllRestaurants();
                break;
            }
            case 2:{
            	addNewRestaurant();
                break;
            }
            case 3:{
            	toggleRestaurantStatus();
                break;
            }
            case 4:{
            	showReports();
                break;
            }
            case 5:{
            	showLevel();
                break;
            }
            case 6:{
            	manageLevel();
                break;
            }
            case 7:{
            	LevelHistory();
                break; 
            }
            case 0:{
            	cout << "Logging out..\n";
                break;
            }
            default: cout << "Invalid choice\n";
        }
    } while(choice != 0);
}
