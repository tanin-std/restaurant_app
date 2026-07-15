#include "LoyaltyDAO.h"
#include<sstream>
using namespace std;

LoyaltyDAO::LoyaltyDAO(Database &database) 
          : db(database){

          }
int LoyaltyDAO::loyaltyCall(void *data, int argc, char **argv, char **colNames){
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

LoyaltySystem *LoyaltyDAO::load(int userId){
    stringstream Sql;
    Sql << "SELECT loyalty_points, membership_level, id FROM users WHERE id = " << userId << ";";
    LoyaltySystem *loyalty = nullptr;
    db.Query(Sql.str(), loyaltyCall, &loyalty);
    return loyalty;
}
bool LoyaltyDAO::save(int userId, int points, const string &level){
    stringstream Sql;
    Sql << "UPDATE users SET loyalty_points = " << points 
        << ", membership_level = '" << level << "' WHERE id = " << userId << ";";
    return db.Apply(Sql.str());
}
void LoyaltyDAO::LevelChange(int userId, const string &oldLevel, const string &newLevel, const string &actor){
    stringstream Sql;
    Sql << "INSERT INTO level_history (user_id, old_level, new_level, changed_by) VALUES ("
        << userId << ", '" << oldLevel << "', '" << newLevel << "', '" << actor << "');";
    db.Apply(Sql.str());
}
bool LoyaltyDAO::executeQuery(const string &sql, int (*callback)(void*, int, char**, char**), void* data){
    return db.Query(sql, callback, data);
}

static int historyCallback(void *data, int argc, char **argv, char **col){
    vector<string>* history = static_cast<vector<string>*>(data);
    if(argc >= 4){
        string oldLevel;
        if(argv[0] != nullptr){
            oldLevel = argv[0];
        } 
        else{
            oldLevel = "Unknown";
        }
        string newLevel;
        if(argv[1] != nullptr){
            newLevel = argv[1];
        } else {
            newLevel = "Unknown";
        }
        string date;
        if(argv[2] != nullptr){
            date = argv[2];
        } 
        else{
            date = "";
        }
        string actor;
        if(argv[3] != nullptr){
            actor = argv[3];
        } 
		else{
            actor = "system";
        }
        string entry = "Old: " + oldLevel + " -> New: " + newLevel + " Date: " + date + " By: " + actor;
        history->push_back(entry);
    }
    return 0;
}
vector<string> LoyaltyDAO::getHistory(int userId){
    vector<string> history;
    stringstream Sql;
    Sql << "SELECT old_level, new_level, change_date, changed_by FROM level_history WHERE user_id = " << userId << " ORDER BY change_date DESC;";
    db.Query(Sql.str(), historyCallback, &history);
    return history;
}
bool LoyaltyDAO::updatePoints(int userId, int points) {
    stringstream Sql;
    Sql << "UPDATE users SET loyalty_points = " << points << " WHERE id = " << userId << ";";
    return db.Apply(Sql.str());
}
bool LoyaltyDAO::updateLevel(int userId, const string &level){
    stringstream Sql;
    Sql << "UPDATE users SET membership_level = '" << level << "' WHERE id = " << userId << ";";
    return db.Apply(Sql.str());
}