#include "UserDAO.h"
#include <sstream>
#include <iostream>
using namespace std;

UserDAO::UserDAO(Database &database) 
       : db(database){
}
int UserDAO::userCall(void *data, int argc, char **argv, char **colNames){
    vector<User>* users = static_cast<vector<User>*>(data);
    if(argc >= 4){
        int id = (argv[0] ? atoi(argv[0]) : 0);
        string userName = (argv[1] ? argv[1] : "");
        string pass = (argv[2] ? argv[2] : "");
        string role = (argv[3] ? argv[3] : "");
        int restId = 0;
        if (argc >= 5 && argv[4] != nullptr){
            restId = atoi(argv[4]);
        }
        users->push_back(User(id, userName, pass, role, restId));
    }
    return 0;
}
bool UserDAO::insert(const User &user){
    stringstream sql;
    sql << "INSERT INTO users (username, password, role, restaurant_id) VALUES ('"
        << user.getName() << "', '" << user.getPass() << "', '"
        << user.getRole() << "', " << user.getRestaurantId() << ");";
    return db.Apply(sql.str());
}
vector<User> UserDAO::findAll(){
    vector<User> users;
    db.Query("SELECT id, username, password, role, restaurant_id FROM users;", userCall, &users);
    return users;
}
User *UserDAO::login(const string &userName, const string &pass){
    stringstream sql;
    sql << "SELECT id, username, password, role, restaurant_id FROM users WHERE username = '"
        << userName << "' AND password = '" << pass << "';";
    vector<User> users;
    db.Query(sql.str(), userCall, &users);
    if (users.empty()) return nullptr;
    return new User(users[0]); 
}




