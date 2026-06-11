#ifndef USERDAO_H
#define USERDAO_H
#include<iostream>
#include "Database.h"
#include "User.h"
#include <vector>
#include <string>
using namespace std;

class UserDAO{
    private:
    Database& db;
    static int userCall(void *data, int argc, char **argv, char **colNames);
    
    public:
    UserDAO(Database &database);
    bool insert(const User &user);
    User *IDfind(int id);
    User *Usernamefind(const string &userName);
    vector<User> findAll();
    bool update(const User &user);
    bool IDdelete(int id);
    User *login(const string &userName, const string &pass);
    

};
#endif