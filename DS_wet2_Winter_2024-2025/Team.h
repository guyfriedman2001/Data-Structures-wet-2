//
// Created by Guy Friedman on 27/01/2025.
//

#ifndef TEAM_H
#define TEAM_H



class Team {
private:
    int actual_id;
    int curr_id;
    int record;
    Team* next;
public:
    Team() = delete;

    Team(int id) : actual_id(id), curr_id(id), record(0), next(nullptr) {}

    ~Team() = default;

    void winMatch() {
        ++this->record;
    }

    void loseMatch() {
        --this->record;
    }

    int getId() const {
        return this->id;
    }

    int getRecord() const {
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
        return this->record;
    }

};



#endif //TEAM_H
