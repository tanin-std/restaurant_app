#ifndef USER_H
#define USER_H
#include<iostream>
#include<string>
using namespace std;

class User{
    protected:
    int id;
    string userName;
    string pass;
    string role;

    public:
    User(int ID = 0, string Name = "", string password = "", string Role = "");
    virtual ~User();
    int getID() const;
    string getName() const;
    string getPass() const;
    string getRole() const;
    void setID(int newID);
    void setName(const string &newName);
    void setPassword(const string &newPass);
    virtual void showMenu() = 0;
};
#endif  