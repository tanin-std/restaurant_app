#include <iostream>
#include <string>
#include "sqlite3.h"
using namespace std;

int Call(void *data, int colCount, char **values, char **colNames){
    for (int i = 0; i < colCount; i++) {
        string value = (values[i] ? values[i] : "NULL");
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
                 "role TEXT NOT NULL,"
                 "restaurant_id INTEGER);";
    product = sqlite3_exec(Db, Sql.c_str(), nullptr, nullptr, &errorNote);
    if(product != SQLITE_OK){
        cout << "Error creating table: " << errorNote << endl;
        sqlite3_free(errorNote);
    } 
	else{
        cout << "Users table created" << endl;
    }
    Sql = "INSERT OR IGNORE INTO users (username, password, role, restaurant_id) VALUES ('admin', 'admin123', 'admin', 0);";
    sqlite3_exec(Db, Sql.c_str(), nullptr, nullptr, &errorNote);

    Sql = "INSERT OR IGNORE INTO users (username, password, role, restaurant_id) VALUES ('customer1', 'pass123', 'customer', 0);";
    sqlite3_exec(Db, Sql.c_str(), nullptr, nullptr, &errorNote);

    Sql = "INSERT OR IGNORE INTO users (username, password, role, restaurant_id) VALUES ('manager1', 'mgr123', 'manager', 1);";
    sqlite3_exec(Db, Sql.c_str(), nullptr, nullptr, &errorNote);
    Sql = "CREATE TABLE IF NOT EXISTS restaurants ("
      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
      "name TEXT NOT NULL,"
      "address TEXT NOT NULL,"
      "is_active INTEGER DEFAULT 1,"
      "preparation_time INTEGER,"
      "phone TEXT,"
      "description TEXT);";
    sqlite3_exec(Db, Sql.c_str(), nullptr, nullptr, &errorNote);
    cout << "Restaurants table created" << endl;
    Sql = "CREATE TABLE IF NOT EXISTS menu_items ("
      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
      "restaurant_id INTEGER NOT NULL,"
      "name TEXT NOT NULL,"
      "description TEXT,"
      "base_price REAL NOT NULL,"
      "type TEXT CHECK(type IN ('food','drink')),"
      "is_available INTEGER DEFAULT 1,"
      "cooking_time INTEGER,"
      "volume REAL,"
      "FOREIGN KEY(restaurant_id) REFERENCES restaurants(id));";
    sqlite3_exec(Db, Sql.c_str(), nullptr, nullptr, &errorNote);
    cout << "Menu items table created" << endl;
    Sql = "INSERT OR IGNORE INTO restaurants (name, address, is_active, preparation_time, phone, description) "
      "VALUES ('Pizza Hot', 'Tehran - Valiasr St', 1, 30, '021-88991234', 'Best pizza in town');";
    sqlite3_exec(Db, Sql.c_str(), nullptr, nullptr, &errorNote);
    cout << "Sample restaurant added" << endl;
    Sql = "INSERT OR IGNORE INTO menu_items (restaurant_id, name, description, base_price, type, is_available, cooking_time) "
      "VALUES (1, 'Margherita Pizza', 'Fresh tomatoes and mozzarella', 95000, 'food', 1, 20);";
    sqlite3_exec(Db, Sql.c_str(), nullptr, nullptr, &errorNote);

    Sql = "INSERT OR IGNORE INTO menu_items (restaurant_id, name, description, base_price, type, is_available, cooking_time) "
      "VALUES (1, 'Pepperoni Pizza', 'Spicy pepperoni', 120000, 'food', 1, 25);";
    sqlite3_exec(Db, Sql.c_str(), nullptr, nullptr, &errorNote);

    Sql = "INSERT OR IGNORE INTO menu_items (restaurant_id, name, description, base_price, type, is_available, volume) "
      "VALUES (1, 'Coca-Cola 1.5L', 'Family size', 25000, 'drink', 1, 1.5);";
    sqlite3_exec(Db, Sql.c_str(), nullptr, nullptr, &errorNote);
    cout << "Sample menu items added" << endl;
    Sql = "CREATE TABLE IF NOT EXISTS orders ("
      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
      "customer_id INTEGER NOT NULL,"
      "restaurant_id INTEGER NOT NULL,"
      "total_price REAL NOT NULL,"
      "status TEXT DEFAULT 'pending',"
      "order_time DATETIME DEFAULT CURRENT_TIMESTAMP,"
      "FOREIGN KEY(customer_id) REFERENCES users(id),"
      "FOREIGN KEY(restaurant_id) REFERENCES restaurants(id));";
    sqlite3_exec(Db, Sql.c_str(), nullptr, nullptr, &errorNote);
    cout << "Orders table created" << endl;
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