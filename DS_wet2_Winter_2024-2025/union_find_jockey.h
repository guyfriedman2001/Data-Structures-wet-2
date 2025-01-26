#ifndef UPTREE_JOCKEYS_H
#define UPTREE_JOCKEYS_H

#include "ChainHashArray.h"

struct JockeyNode {
    int jockeyId;
    int personalRecord;
    JockeyNode* parent;
    //int rank; // Used for rank-based union
    bool exists;
    TeamNode* team;

    JockeyNode(int id, TeamNode* team) 
        : jockeyId(id), personalRecord(0), parent(this), rank(0), team(team) {}
};

struct TeamNode {
    int teamId;
    int size;
    bool exists;
    int teamRecord; // Record held by the group (team)
    JockeyNode* root;//root of jockey uptree

    TeamNode(int id) 
        : teamId(id), size(0), exists(true), teamRecord(0), root(nullptr) {}
};

class UnionFindJockeys {

private:
    ChainHashArray<TeamNode> teams;
    ChainHashArray<JockeyNode*> jockeys;

    // Find the root of a jockey up-tree
    JockeyNode* findRoot(JockeyNode* jockey) {
        if (jockey->parent != jockey) {
            jockey->parent = findRoot(jockey->parent);//here path compression happens recursivly 
        }
        return jockey->parent;
    }

public:
    UnionFindJockeys() {}
    ~UnionFindJockeys() {
        //  for (int i = 0; i < teams.getArraySize(); ++i) {
        //     auto& bucket = teams.getBucket(i);
        //     for (int j = 0; j < bucket.getSize(); ++j) {
        //         delete bucket[j]->value;
        //     }
        // }
        // for (int i = 0; i < jockeys.getArraySize(); ++i) {
        //     auto& bucket = jockeys.getBucket(i);
        //     for (int j = 0; j < bucket.getSize(); ++j) {
        //         delete bucket[j]->value;
        //     }
        // }
    }
    
    bool teamExist(int teamId){
        return (teams.find(teamId)!= nullptr);
    }

    void addTeam(int teamId) {
        teams.insert(teamId, new TeamNode(teamId));
    }

    void addJockey(int teamId, int jockeyId) {
        TeamNode* team = teams.find(teamId);
        JockeyNode* jockey = new JockeyNode(jockeyId);
        jockey->team = team;
        jockeys.insert(jockeyId, jockey);

        if (team->root == nullptr) 
            team->root = jockey;

        else 
            unionJockeys(team->root, jockey);

        team->size++;
    }

    
    void unionTeams(int teamId1, int teamId2) {

        TeamNode* team1 = teams.find(teamId1);
        TeamNode* team2 = teams.find(teamId2);


        //unite by size for time complexity
        JockeyNode* biggerRoot = nullptr;
        if(team1->size>team2->size){
            team2->root->parent=team1->root;            
            biggerRoot = team1->root;
        }
        else{
            team1->root->parent=team2->root;
            biggerRoot = team2->root;
        }
        int newSize= team1->size+team2->size;
        
        //leading team by record

        if(team1->teamRecord>=team2->teamRecord){
            team2->root->team=team1;
            team2->root=nullptr;
            team2->exists=false;
            team1->root = biggerRoot
            team1->size=newSize;
        }
        else{
            team1->root->team=team2;
            team1->root=nullptr;
            team1->exists=flase;
            team2->root = biggerRoot
            team2->size=newSize;
        }

    }

    // Find the team ID of a given jockey
    int findTeam(int jockeyId) {
        JockeyNode* jockey = find(jockeyId);
        if (jockey == nullptr) {
            return -1;
        }

        JockeyNode* root = findRoot(jockey);
        return root->team->teamId;
    }

    // Retrieve a record of a specific jockey
    int getJockeyRecord(int jockeyId) {
        if (jockeys.find(jockeyId) == nullptr) {
            return -1;
        }
        return jockeys.find(jockeyId)->personalRecord;
    }

    // Retrieve the record of a specific team
    int getTeamRecord(int teamId) {
        TeamNode* team = teams.find(teamId);
        if (team == nullptr) {
            return -1;
        }
        return team->teamRecord;
    }

    JockeyNode* find(int jockeyId) {
        return jockeys.find(jockeyId);
    }
};

#endif // UPTREE_JOCKEYS_H
