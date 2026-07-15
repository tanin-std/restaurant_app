#include "LoyaltyDAO.h"
#include<sstream>
using namespace std;

LoyaltyDAO::LoyaltyDAO(Database &database) 
          : db(database){

          }
int LoyaltyDAO::loyaltyCallback(void *data, int argc, char **argv, char **colNames){
    LoyaltySystem **loyalty = static_cast<LoyaltySystem**>(data);
    if(argc >= 3){
        int points;
        if(argv[0] != nullptr){
            points = atoi(argv[0]);
        } 
        else{
            points = 0;
        }
        string level;
        if(argv[1] != nullptr){
            level = argv[1];
        } 
        else{
            level = "Normal";
        }
        int userId;
        if(argv[2] != nullptr){
            userId = atoi(argv[2]);
        } 
        else{
            userId = 0;
        }
    
        *loyalty = new LoyaltySystem(userId);
        (*loyalty)->setPoints(points);
        (*loyalty)->setLevel(level);
    }
    return 0;
}

LoyaltySystem* LoyaltyDAO::load(int userId){
    stringstream Sql;
    Sql << "SELECT loyalty_points, membership_level, id FROM users WHERE id = " << userId << ";";
    LoyaltySystem *loyalty = nullptr;
    db.Query(sql.str(), loyaltyCall, &loyalty);
    return loyalty;
}
bool LoyaltyDAO::save(int userId, int points, const string &level){
    stringstream Sql;
    Sql << "UPDATE users SET loyalty_points = " << points 
        << ", membership_level = '" << level << "' WHERE id = " << userId << ";";
    return db.Apply(sql.str());
}
void LoyaltyDAO::LevelChange(int userId, const string &oldLevel, const string &newLevel, const string &actor){
    stringstream Sql;
    Sql << "INSERT INTO level_history (user_id, old_level, new_level, changed_by) VALUES ("
        << userId << ", '" << oldLevel << "', '" << newLevel << "', '" << actor << "');";
    db.Apply(sql.str());
}