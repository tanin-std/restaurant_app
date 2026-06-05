#include <iostream>
#include <string>
#include "sqlite3.h"
using namespace std;


int Call(void *data, int colCount, char **values, char **colNames){
    int i;
    for(i = 0; i < colCount; i++){
        string value; 
        if(values[i] != nullptr){
            value = values[i];
        }
        else{
            value = "NULL";
        }
        cout << "   " << colNames[i] << ": " << value << endl;
    }
    cout << "   ---" << endl;
    return 0;
}

int main(){
    sqlite3 *Db;
    int product = sqlite3_open("restaurant_app.db", &Db);
    if(product != SQLITE_OK){
        cout << "Unable to open database" << endl;
        return 1;
    }
    cout << "Database opened successfully" << endl;

    char *errorNote = nullptr;
    string Sql = "CREATE TABLE IF NOT EXISTS users ("
                 "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                 "username TEXT UNIQUE NOT NULL,"
                 "password TEXT NOT NULL,"
                 "role TEXT NOT NULL);";
    product = sqlite3_exec(Db, Sql.c_str(), nullptr, nullptr, &errorNote);
    if(product != SQLITE_OK){
        cout << "Error creating table: " << errorNote << endl;
        sqlite3_free(errorNote);
    } 
    else{
        cout << "Users table created" << endl;
    }

    sql = "INSERT OR IGNORE INTO users (username, password, role) VALUES ('test', '123', 'customer');";
    product = sqlite3_exec(Db, Sql.c_str(), nullptr, nullptr, &errorNote);
    if(product != SQLITE_OK){
        cout << "Error inserting: " << errorNote << endl;
        sqlite3_free(errorNote);
    } 
    else{
        cout << "Test user inserted" << endl;
    }

    cout << "\nCurrent users:" << endl;
    Sql = "SELECT * FROM users;";
    product = sqlite3_exec(Db, Sql.c_str(), Call, nullptr, &errorNote);
    if(product != SQLITE_OK){
        cout << "Error selecting: " << errorNote << endl;
        sqlite3_free(errorNote);
    }

    sqlite3_close(Db);
    cout << "\nDatabase setup completed!" << endl;
    return 0;
}