//
// Created by Guy Friedman on 27/01/2025.
//

#ifndef TEAM_H
#define TEAM_H

#include <cassert>

class Team {
private:
    int actual_id;
    int curr_id;
    int record;
    Team* next; // isn't used, but already mixed up in the code
    int team_size;
public:
    Team() = delete;

    Team(int id) : actual_id(id), curr_id(id), record(0), next(nullptr), team_size(1) {}

    ~Team() = default;

    void winMatch() {
        ++this->record;
    }

    void loseMatch() {
        --this->record;
    }

    int getId() const {
        return this->curr_id;
    }

    int getRecord() const {
        assert(this->actual_id == this->curr_id); //fixme return the assert
        return this->record;
    }

    int getLeaderID() {
        return this->curr_id;
    }

    void followTeam(Team* t) {
        this->curr_id = t->getId();
    }

    void setRecord(int r) {
        this->record = r;
    }

    int getRecord() {
        assert(this->isActive()); //fixme return the assert
        return this->record;
    }

    int getActualID() {
        return this->actual_id;
    }

    bool isActive() {
        return this->curr_id == this->actual_id;
    }

    int getRecordWithoutActive() {
        //no assertion that this is active
        return this->record;
    }


    Team* testGetTeamRootByMass() {
        if (this->next == nullptr) {
            return this;
        }
        Team* leader = this->next->testGetTeamRootByMass();
        this->next = leader;
        return leader;
    }

    int getRecordHolderIDOfRoot() {
        Team* rootByMass = this->testGetTeamRootByMass();
        return rootByMass->getLeaderID();
    }

    void testUniteTeams(Team* teamOther) {
        Team* rootByMassThis = this->testGetTeamRootByMass();
        Team* rootByMassOther = teamOther->testGetTeamRootByMass();
        if (rootByMassThis->team_size >= rootByMassOther->team_size) {
            rootByMassOther->testJoinTeam(rootByMassThis);
        } else {
            rootByMassThis->testJoinTeam(rootByMassOther);
        }
        if (this->getRecord() >= teamOther->getRecord()) {
            rootByMassOther->followTeam(this); //todo this must be group 1
            teamOther->followTeam(this);
        } else {
            rootByMassThis->followTeam(teamOther);
            this->followTeam(teamOther);
        }

    }

    void testJoinTeam(Team* teamOther) {
        this->next = teamOther;
    }















};
#endif //TEAM_H
