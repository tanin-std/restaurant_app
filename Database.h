#ifndef DATABASE_H
#define DATABASE_H
#include <string>
#include "sqlite3.h"
using namespace std;

class Database{
    private:
    sqlite3 *Db;
    bool Connection;

    public:
    Database(const string &fileName);
    ~Database();
    bool Open() const;
    bool Apply(const string &Sq);
    bool Query(const string &Sq,int (*Call)(void *, int, char **, char **), void *data);
    sqlite3 *getDb();

};
#endif