//
// Created by Guy Friedman on 27/01/2025.
//

#ifndef JOCKEY_H
#define JOCKEY_H



class Jockey {
protected:
    int id;
    int record;
    int team_id;
public:
    Jockey() = delete;

    Jockey(int id) {
        this->id = id;
        this->record = 0;
        this->team_id = 0;
    }

    Jockey(int id, int team_id) {
        this->id = id;
        this->record = 0;
        this->team_id = team_id;
    }

    virtual ~Jockey() = default;

    int getId() const {
        return this->id;
    }

    int getRecord() const {
        return this->record;
    }

    int getTeamId() const {
        return this->team_id;
    }

    void setId(int id) {
        this->id = id;
    }

    void setRecord(int record) {
        this->record = record;
    }

    void setTeamId(int team_id) {
        this->team_id = team_id;
    }

    void winMatch() {
        ++this->record;
    }

    void loseMatch() {
        --this->record;
    }
};



#endif //JOCKEY_H
