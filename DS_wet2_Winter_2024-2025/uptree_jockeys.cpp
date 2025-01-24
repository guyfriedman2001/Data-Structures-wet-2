#include "uptree_jockeys.h"

// Constructor for a JockeyNode
JockeyNode::JockeyNode(int id, int record) 
    : jockeyId(id), personalRecord(record), subtreeRecord(record), parent(nullptr) {}

// Constructor for a TeamNode
TeamNode::TeamNode(int id) 
    : teamId(id), size(0), record(0), exists(false), root(nullptr) {}

// Constructor to initialize data
UpTreeJockeys::UpTreeJockeys() {
    initializeArrays();
}

// Helper function to initialize arrays
void UpTreeJockeys::initializeArrays() {
    memset(teams, 0, sizeof(teams));
    memset(jockeys, 0, sizeof(jockeys));
}

// Find the root of a jockey with path compression
JockeyNode* UpTreeJockeys::findRoot(JockeyNode* jockey) {
    if (jockey->parent == nullptr) {
        return jockey; // Root node
    }
    jockey->parent = findRoot(jockey->parent); // Path compression
    return jockey->parent;
}

// Add a new team
void UpTreeJockeys::addTeam(int teamId) {
    if (teamId < 0 || teamId >= MAX_TEAMS || teams[teamId].exists) return; // Invalid or existing team
    teams[teamId] = TeamNode(teamId);
    teams[teamId].exists = true;
}

// Add a jockey to a team
void UpTreeJockeys::addJockey(int teamId, int jockeyId, int personalRecord) {
    if (teamId < 0 || teamId >= MAX_TEAMS || jockeyId < 0 || jockeyId >= MAX_JOCKEYS) return; // Invalid IDs
    if (!teams[teamId].exists || jockeys[jockeyId] != nullptr) return; // Team must exist and jockey must not exist

    JockeyNode* jockey = new JockeyNode(jockeyId, personalRecord);
    jockey->parent = teams[teamId].root; // Attach jockey to the team's root

    if (!teams[teamId].root) {
        teams[teamId].root = jockey; // If no root exists, this jockey becomes the root
    }

    teams[teamId].size++;
    teams[teamId].record += personalRecord;
    jockey->subtreeRecord = personalRecord;
    jockeys[jockeyId] = jockey; // Add jockey to the array
}

// Union two teams
void UpTreeJockeys::unionTeams(int teamId1, int teamId2) {
    if (teamId1 < 0 || teamId1 >= MAX_TEAMS || teamId2 < 0 || teamId2 >= MAX_TEAMS) return; // Invalid IDs
    if (!teams[teamId1].exists || !teams[teamId2].exists) return; // Teams must exist

    JockeyNode* root1 = findRoot(teams[teamId1].root);
    JockeyNode* root2 = findRoot(teams[teamId2].root);

    if (root1 == root2) return; // Already merged

    // Union by size
    if (teams[teamId1].size >= teams[teamId2].size) {
        root2->parent = root1;
        teams[teamId1].size += teams[teamId2].size;
        teams[teamId1].record += teams[teamId2].record;
        teams[teamId2].exists = false;
    } else {
        root1->parent = root2;
        teams[teamId2].size += teams[teamId1].size;
        teams[teamId2].record += teams[teamId1].record;
        teams[teamId1].exists = false;
    }
}

// Find the team of a jockey
int UpTreeJockeys::findTeam(int jockeyId) {
    if (jockeyId < 0 || jockeyId >= MAX_JOCKEYS || jockeys[jockeyId] == nullptr) return -1; // Jockey does not exist

    JockeyNode* root = findRoot(jockeys[jockeyId]);
    for (int i = 0; i < MAX_TEAMS; i++) {
        if (teams[i].exists && teams[i].root == root) {
            return i;
        }
    }
    return -1; // No active team found
}

// Get the record of a jockey
int UpTreeJockeys::getJockeyRecord(int jockeyId) {
    if (jockeyId < 0 || jockeyId >= MAX_JOCKEYS || jockeys[jockeyId] == nullptr) return 0; // Jockey does not exist
    return jockeys[jockeyId]->personalRecord;
}

// Get the total record of a team
int UpTreeJockeys::getTeamRecord(int teamId) {
    if (teamId < 0 || teamId >= MAX_TEAMS || !teams[teamId].exists) return 0; // Team does not exist or is inactive
    return teams[teamId].record;
}
