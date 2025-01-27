//
// Created by Guy Friedman on 27/01/2025.
//

#ifndef TEAMUNIONFIND_H
#define TEAMUNIONFIND_H
#include "UnionFindTwo.h"
#include "Team.h"


class TeamUnionFind : public UnionFind<Team> {
public:

    TeamUnionFind() : UnionFind<Team>() {}

    ~TeamUnionFind() = default;

    UnionFindNode<Team>* getTeamNode(int key) {
        return this->findNode(key);
    }

/*
    bool uniteGroup(int id1, int id2) override {
            UnionFindNode<Team>* node1 = this->findNode(id1);
            UnionFindNode<Team>* node2 = this->findNode(id2);
            UnionFindNode<Team>* groupOne = node1->getGroup();
            UnionFindNode<Team>* groupTwo = node2->getGroup();
            if (groupOne == nullptr || groupTwo == nullptr) {
                return false;
            }
            if (groupOne == groupTwo) {
                return false; //fixme what if unite is called on the same group twice?
            }
            Team* team1 = groupOne->getData(); //now i have the teams before the merge
            Team* team2 = groupTwo->getData(); //i want to make it so the team with the higher record is in the bigger tree head
            if (team1->getRecord() > team2->getRecord() && !(groupOne > groupTwo)) {
                groupOne->swapData(groupTwo);
            }
            if (team1->getRecord() < team2->getRecord() && !(groupOne < groupTwo)) {
                groupOne->swapData(groupTwo);
            }


            bool answer = groupOne->unite(groupTwo);

        }
 */

    /*
    void uniteTeam(int id1, int id2) {
        assert(id1 != id2);
        UnionFindNode<Team>* node1 = this->findNode(id1);
        UnionFindNode<Team>* node2 = this->findNode(id2);
        assert(node1 != nullptr && node2 != nullptr);
        assert(node1 != node2);
        UnionFindNode<Team>* rootNodeOne = node1->getGroup();
        UnionFindNode<Team>* rootNodeTwo = node2->getGroup();
        assert(rootNodeOne != nullptr && rootNodeTwo != nullptr);
        assert(rootNodeOne != rootNodeTwo);
        Team* record_leader1 = rootOne->getData(); //now i have the teams before the merge
        Team* record_leader2 = rootTwo->getData(); //i want to make it so the team with the higher record is in the bigger tree head
        assert(record_leader1 != nullptr && record_leader2 != nullptr);
        assert(record_leader1 != record_leader2);
        assert(record_leader1->getRecord() != record_leader2->getRecord());
        if (record_leader1->getRecord() > record_leader2->getId()) {
            rootOne->followTeam(record_leader1);

        }
        */

    void uniteTeams(int id1, int id2) { //todo check in main if teams are the same or not
        Team* root_team1 = this->find(id1);
        Team* root_team2 = this->find(id2);
        int record_leader1_id = root_team1->getLeaderID();
        int record_leader2_id = root_team2->getLeaderID();
        Team* record_leader1 = this->find(record_leader1_id);
        Team* record_leader2 = this->find(record_leader2_id);
        int record1 = record_leader1->getRecord();
        int record2 = record_leader2->getRecord();
        int records_sum = record1 + record2;
        if (record1 >= record2) {
            record_leader2->followTeam(record_leader1);
            root_team1->followTeam(record_leader1);
            root_team2->followTeam(record_leader1);
        }
        if (record2 > record1) {
            record_leader1->followTeam(record_leader2);
            root_team1->followTeam(record_leader2);
            root_team2->followTeam(record_leader2);
        }
        root_team1->setRecord(records_sum);
        root_team2->setRecord(records_sum);
        record_leader1->setRecord(records_sum);
        record_leader2->setRecord(records_sum);
        this->uniteGroup(id1, id2);
    }





    Team* getLeader(int team_id) {
        Team* root_team = this->find(team_id);
        if (root_team == nullptr) {
            return nullptr;
        }
        int leader_id = root_team->getId();
        Team* record_holder = this->find(leader_id);
        if (record_holder == nullptr) {
            throw "some problem in TeamUnionFind::getLeader()";
            return nullptr;
        }
        return record_holder;
    }





};



#endif //TEAMUNIONFIND_H
