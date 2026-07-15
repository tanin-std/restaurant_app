#ifndef MEMBERSHIPLEVEL_H
#define MEMBERSHIPLEVEL_H
#include<iostream>
#include<string>
using namespace std;

class MembershipLevel{
protected:
    string levelName;
    int PointsThreshold;
    double multiplier;
    double discount;
    double deliveryCost;
    string benefits;

public:
    MembershipLevel(string name, int threshold, double mult, 
                    double disc, double delivery, string benefit);
    virtual ~MembershipLevel(){

    }
    string getLevelName() const;
    int getPoints() const;
    double getMultiplier() const;
    double getDiscount() const;
    double getDeliveryCost() const;
    string getBenefits() const;
    virtual double calculateDiscount(double totalPrice) const;
    virtual double calculateCost(double baseCost) const;
    virtual int calculatePoints(int basePoints) const;
    virtual void displayInfo() const;
};
#endif