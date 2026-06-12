#include <iostream>
#include "UserDAO.h"
#include <sstream>
using namespace std;

UserDAO::UserDAO(Database &database) 
        : db(database){

        }
int UserDAO::userCall(void *data, int argc, char **argv, char **colNames){
    vector<User> *users = static_cast<vector<User >*>(data);
    if(argc >= 5){
        int id;
        if(argv[0] != nullptr){
            id = stoi(argv[0]);
        }
        else{
            id = 0;
        } 
        string userName;
        if(argv[1] != nullptr){
            userName = argv[1];
        }
        else{
            userName = "";
        } 
        string pass;
        if(argv[2] != nullptr){
            pass = argv[2];
        }
        else{
            pass = "";
        } 
        string role;
        if(argv[3] != nullptr){
            role = argv[3];
        }
        else{
            role = "";
        } 
        int restId;
        if(argv[4] != nullptr){
            restId = stoi(argv[4]);
        }
        else{
            restId = 0;
        }
        users->push_back(User(id, userName, pass, role, restId));
    }
    return 0;
}
bool UserDAO::insert(const User &user){
    stringstream sql;
    sql << "INSERT INTO users (username, password, role) VALUES ('"
        << user.getName() << "', '"
        << user.getPass() << "', '"
        << user.getRole() << "');";
    return db.Apply(sql.str());
}
User *UserDAO::IDfind(int id){
    stringstream sql;
    sql << "SELECT id, username, password, role, restaurant_id FROM users WHERE id = " << id << ";";
    vector<User> users;
    db.Query(sql.str(), userCall, &users);
    if(users.empty()){
       return nullptr;
    } 
    User *temp = new User(users[0]);
    return temp;
}
User *UserDAO::Usernamefind(const string &userName){
    stringstream sql;
    sql << "SELECT id, username, password, role, restaurant_id FROM users WHERE username = '"
        << userName << "';";
    vector<User> users;
    db.Query(sql.str(), userCall, &users);
    if(users.empty()){
       return nullptr;
    } 
    User *temp = new User(users[0]);
    return temp;
}
vector<User> UserDAO::findAll(){
    vector<User> users;
    db.Query("SELECT id, username, password, role, restaurant_id FROM users;", userCall, &users);
    return users;
}

bool UserDAO::update(const User &user){
    stringstream sql;
    sql << "UPDATE users SET username = '" << user.getName()
        << "', password = '" << user.getPass()
        << "', role = '" << user.getRole()
        << "' WHERE id = " << user.getID() << ";";
    return db.Apply(sql.str());
}
bool UserDAO::IDdelete(int id){
    stringstream sql;
    sql << "DELETE FROM users WHERE id = " << id << ";";
    return db.Apply(sql.str());
}

User *UserDAO::login(const string &userName, const string &pass){
    stringstream sql;
    sql << "SELECT id, username, password, role, restaurant_id FROM users WHERE username = '"
        << userName << "' AND password = '" << pass << "';";
    vector<User> users;
    db.Query(sql.str(), userCall, &users);
    if(users.empty()){
       return nullptr;
    } 
    User *temp = new User(users[0]);
    return temp;
}