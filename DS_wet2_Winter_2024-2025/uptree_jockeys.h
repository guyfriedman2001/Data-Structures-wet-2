#ifndef UPTREE_JOCKEYS_H
#define UPTREE_JOCKEYS_H

#include "ChainHashArray.h"

// Node for a jockey
struct JockeyNode {
    int jockeyId;
    int personalRecord;         
    int subtreeRecord; // Used as "rank" for union-find     
    bool exists; // Indicates whether the jockey is active     
    JockeyNode* parent;         

    JockeyNode(int id) 
        : jockeyId(id), personalRecord(0), subtreeRecord(1), exists(true), parent(this) {}
};

// Node for a team
struct TeamNode {
    int teamId;                 
    int size;                   
    bool exists; // Indicates whether the team is active
    JockeyNode* root; // The root of the jockey UpTree, nullptr initially   

    TeamNode(int id) 
        : teamId(id), size(0), exists(true), root(nullptr) {}
};

// UpTreeJockeys class using dynamic hash tables
class UpTreeJockeys {
private:
    ChainHashArray<TeamNode> teams;         // Hash table for teams
    ChainHashArray<JockeyNode*> jockeys;    // Hash table for jockey pointers

    // Find the root of a jockey with path compression
    JockeyNode* findRoot(JockeyNode* jockey) {
        if (jockey->parent != jockey) {
            jockey->parent = findRoot(jockey->parent); // Path compression
        }
        return jockey->parent;
    }

public:
    UpTreeJockeys() {}
    ~UpTreeJockeys() {}

    // Add a new team to the system
    void addTeam(int teamId) {
        if (teams.contains(teamId)) return; // Team already exists
        teams.insert(teamId, TeamNode(teamId));
    }

    // Add a new jockey to a specific team
    void addJockey(int teamId, int jockeyId) {
        if (!teams.contains(teamId)) return; // Team does not exist
        if (jockeys.contains(jockeyId)) return; // Jockey already exists

        TeamNode* team = teams.get(teamId);
        JockeyNode* jockey = new JockeyNode(jockeyId);
        jockeys.insert(jockeyId, jockey);

        if (team->root == nullptr) {
            team->root = jockey; // First jockey becomes the root
        } else {
            unionSets(team->root, jockey); // Add jockey to team's tree
        }
        team->size++; // Increment team size
    }

    // Combine two teams into one
    void unionTeams(int teamId1, int teamId2) {
        if (!teams.contains(teamId1) || !teams.contains(teamId2)) return;

        TeamNode* team1 = teams.get(teamId1);
        TeamNode* team2 = teams.get(teamId2);

        if (team1->root && team2->root) {
            unionSets(team1->root, team2->root); // Combine the two trees
            team1->size += team2->size; // Update size of team1
            team2->exists = false; // Mark team2 as inactive
        }
    }

    // Find the team ID of a given jockey
    int findTeam(int jockeyId) {
        if (!jockeys.contains(jockeyId)) return -1; // Jockey does not exist
        JockeyNode* jockey = jockeys.get(jockeyId);
        JockeyNode* root = findRoot(jockey);

        // Iterate over teams to find which team the root belongs to
        for (auto& pair : teams) {
            if (pair.value.root == root) {
                return pair.key; // Return team ID
            }
        }
        return -1; // Not found
    }

    // Retrieve a record/statistic of a specific jockey
    int getJockeyRecord(int jockeyId) {
        if (!jockeys.contains(jockeyId)) return -1;
        return jockeys.get(jockeyId)->personalRecord;
    }

    // Retrieve a record/statistic of a specific team
    int getTeamRecord(int teamId) {
        if (!teams.contains(teamId)) return -1;
        return teams.get(teamId)->size; // Example: return team size
    }

    // Find the root node of a jockey (wrapper for findRoot)
    JockeyNode* find(int jockeyId) {
        if (!jockeys.contains(jockeyId)) return nullptr;
        return findRoot(jockeys.get(jockeyId));
    }

    // Union two jockey nodes in the union-find structure
    void unionSets(JockeyNode* node1, JockeyNode* node2) {
        JockeyNode* root1 = findRoot(node1);
        JockeyNode* root2 = findRoot(node2);

        if (root1 == root2) return; // Already in the same set

        // Union by subtree record (aggregate size or score)
        if (root1->subtreeRecord < root2->subtreeRecord) {
            root1->parent = root2;
            root2->subtreeRecord += root1->subtreeRecord;
        } else {
            root2->parent = root1;
            root1->subtreeRecord += root2->subtreeRecord;
        }
    }
};

#endif // UPTREE_JOCKEYS_H
