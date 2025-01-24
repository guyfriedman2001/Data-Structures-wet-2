#ifndef UPTREE_JOCKEYS_H
#define UPTREE_JOCKEYS_H
#include "ChainHashArray.h"

// Node for a jockey
struct JockeyNode {
    int jockeyId;               
    int personalRecord;         
    int subtreeRecord;          
    JockeyNode* parent;         

    JockeyNode(int id, int record = 0);
};

// Node for a team
struct TeamNode {
    int teamId;                 
    int size;                   
    int record;                 
    bool exists; // Indicates whether the team is active
    JockeyNode* root;           

    TeamNode(int id = -1);
};

// UpTreeJockeys class using dynamic hash tables
class UpTreeJockeys {
private:
    ChainHashArray<TeamNode> teams;         // Dynamic hash table for teams
    ChainHashArray<JockeyNode*> jockeys;   // Dynamic hash table for jockey pointers
    JockeyNode* findRoot(JockeyNode* jockey); // Find the root of a jockey with path compression

public:

    UpTreeJockeys(); 
    void addTeam(int teamId);              
    void addJockey(int teamId, int jockeyId); 
    void unionTeams(int teamId1, int teamId2); 
    int findTeam(int jockeyId);          
    int getJockeyRecord(int jockeyId);     
    int getTeamRecord(int teamId);        
};

#endif // UPTREE_JOCKEYS_H
