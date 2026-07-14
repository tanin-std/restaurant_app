#include "LoyaltySystem.h"
#include "NormalLevel.h"
#include "SilverLevel.h"
#include "GoldLevel.h"
#include "VIPLevel.h"
#include <iostream>
using namespace std;

LoyaltySystem::LoyaltySystem(int userId) 
            : userId(userId), totalPoints(0), Level("Normal") {
            updateLevel();
}

void LoyaltySystem::updateLevel(){
    if(Level == "VIP"){
        levelStrategy = make_unique<VIPLevel>();
    } 
    else if(Level == "Gold"){
        levelStrategy = make_unique<GoldLevel>();
    } 
    else if(Level == "Silver"){
        levelStrategy = make_unique<SilverLevel>();
    } 
    else{
        levelStrategy = make_unique<NormalLevel>();
    }
}

void LoyaltySystem::addPoint(int points){
    totalPoints += points;
    cout << "Added " << points << " points, Total: " << totalPoints << endl;
    Upgrade();
}
bool LoyaltySystem::Upgrade(){
    string newLevel = Level;
    if(totalPoints >= 700 && Level != "VIP"){
        newLevel = "VIP";
    }
    else if(totalPoints >= 300 && Level != "VIP" && Level != "Gold"){
        newLevel = "Gold";
    }
    else if (totalPoints >= 100 && Level == "Normal"){
        newLevel = "Silver";
    }
    else{
        return false;
    }
    if (newLevel != Level){
        string oldLevel = Level;
        Level = newLevel;
        updateLevel();
        cout << "CONGRATULATIONS! Upgraded from " << oldLevel << " to " << Level << endl;
        return true;
    }
    return false;
}

void LoyaltySystem::downLevel(){
    if (Level == "VIP"){
        Level = "Gold";
    }
    else if (Level == "Gold"){
        Level = "Silver";
    }
    else if (Level == "Silver"){
        Level = "Normal";
    }
    else { 
        cout << "Cannot downgrade from Normal." << endl;
        return; 
    }
    updateLevel();
    cout << "Downgraded to " << Level << endl;
}
double LoyaltySystem::calculateDiscount(double totalPrice) const{
    return levelStrategy->calculateDiscount(totalPrice);
}
double LoyaltySystem::calculateCost(double baseCost) const{
    return levelStrategy->calculateCost(baseCost);
}
int LoyaltySystem::calculatePoints(int basePoints) const{
    return levelStrategy->calculatePoints(basePoints);
}
void LoyaltySystem::displayInfo() const{
    cout << "+-----------------------------+" << endl;
    cout << "Level: " << Level << endl;
    cout << "Points: " << totalPoints << endl;
    cout << "Discount: " << levelStrategy->getDiscount() << "%" << endl;
    cout << "Delivery: ";
    if(levelStrategy->getDeliveryCost() == 0){
        cout << "Free";
    }
    else if(levelStrategy->getDeliveryCost() == 0.5){
        cout << "Half price";
    }
    else{
        cout << "Full price";
    }
    cout << endl;
    cout << "+-----------------------------+" << endl;
}
int LoyaltySystem::getUserId() const { 
    return userId; 
}
int LoyaltySystem::getTotalPoints() const { 
    return totalPoints; 
}
string LoyaltySystem::getLevel() const { 
    return currentLevel; 
}
void LoyaltySystem::setLevel(const string &newlevel) { 
    Level = newlevel; 
    updateLevel(); 
}
void LoyaltySystem::setPoints(int points) { 
    totalPoints = points; 
}