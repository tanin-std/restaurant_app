#ifndef LOYALTYSYSTEM_H
#define LOYALTYSYSTEM_H
#include "MembershipLevel.h"
#include <memory>

class LoyaltySystem{
private:
    int userId;
    int totalPoints;
    string Level;
    unique_ptr<MembershipLevel> levelStrategy;
    void updateLevel();

public:
    LoyaltySystem(int userId = 0);
    void addPoint(int points);
    void deductPoint(int points);
    bool Upgrade();
    void downLevel();
    double calculateDiscount(double totalPrice) const;
    double calculateCost(double baseCost) const;
    int calculatePoints(int basePoints) const;
    void displayInfo() const;

    int getUserId() const;
    int getPoints() const;
    string getLevel() const;
    void setLevel(const string& level);
    void setPoints(int points);
};
#endif