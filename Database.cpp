#include <iostream>
#include "Database.h"
using namespace std;

Database::Database(const string &fileName)
  :Db(nullptr),
  Connection(false){
    int product;
    product = sqlite3_open(fileName.c_str(), &Db);
    if(product == SQLITE_OK){
        Connection = true;
        cout << "connected to the database " << fileName <<endl;
    }
    else{
        cout << "failed to connect" <<endl;
    }
  }
Database::~Database(){
    if(Db){
        sqlite3_close(Db);
        cout << "connection with database closed" <<endl;
    }
}
bool Database::Open() const{
    return Connection;
}
bool Database::Apply(const string &Sq){
    if(Connection != true){
        return false;
    }
    char *errorNote = nullptr;
    int result;
    result = sqlite3_exec(Db, Sq.c_str(), nullptr,nullptr,&errorNote);
    if(result != SQLITE_OK){
        cout << errorNote <<endl;
        sqlite3_free(errorNote);
        return false;
    }
    return true;
}
bool Database::Query(const string &Sq,int (*Call)(void *, int, char **, char **), void *data){
        if(Connection != true){
            return false;
        }
        char *errorNote = nullptr;
        int product;
        product = sqlite3_exec(Db, Sq.c_str(), Call,data, &errorNote);
        if(product != SQLITE_OK){
            cout << errorNote <<endl;
            sqlite3_free(errorNote);
            return false;
        }
        return true;
    }
    sqlite3 *Database::getDb(){
        return Db;
    }