#include "MembershipLevel.h"
#include <iostream>
using namespace std;

MembershipLevel::MembershipLevel(string name, int threshold, double mult,
                             double disc, double delivery, string benefit)
           : levelName(name), PointsThreshold(threshold), multiplier(mult),
              discount(disc), deliveryCost(delivery), benefits(benefit){
                
              }
string MembershipLevel::getLevelName() const{ 
    return levelName; 
}
int MembershipLevel::getPoints() const{ 
    return PointsThreshold; 
}
double MembershipLevel::getMultiplier() const{ 
    return multiplier; 
}
double MembershipLevel::getDiscount() const{ 
    return discount; 
}
double MembershipLevel::getDeliveryCost() const{ 
    return deliveryCost; 
}
string MembershipLevel::getBenefits() const{ 
    return benefits; 
}
double MembershipLevel::calculateDiscount(double totalPrice) const {
    double result;
    result = totalPrice * (discount / 100.0);
    return result;
}
double MembershipLevel::calculateCost(double baseCost) const{
    double cost = baseCost * deliveryCost;
    return cost;
}
int MembershipLevel::calculatePoints(int basePoints) const{
    return (int)(basePoints * multiplier);
}
void MembershipLevel::displayInfo() const{
    cout << "Level: " << levelName << endl;
    cout << "Threshold: " << PointsThreshold << " points" << endl;
    cout << "Multiplier: " << multiplier << "x" << endl;
    cout << "Discount: " << discount << "%" << endl;
    cout << "Delivery: ";
    if(deliveryCost == 0.0){
        cout << "Free";
    } 
    else if(deliveryCost == 0.5){
        cout << "Half price";
    } 
    else{
        cout << "Full price";
    }
    cout << endl;
    cout << "Benefits: " << benefits << endl;
}