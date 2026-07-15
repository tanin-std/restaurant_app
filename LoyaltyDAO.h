#ifndef LOYALTYDAO_H
#define LOYALTYDAO_H
#include<iostream>
#include "Database.h"
#include "LoyaltySystem.h"

class LoyaltyDAO{
private:
    Database &db;
    static int loyaltyCall(void *data, int argc, char **argv, char **colNames);

public:
    LoyaltyDAO(Database &database);
    bool save(int userId, int points, const string &level);
    LoyaltySystem *load(int userId);
    bool updatePoints(int userId, int points);
    bool updateLevel(int userId, const string &level);
    void LevelChange(int userId, const string &oldLevel, const string &newLevel, const string &actor);
};
#endif