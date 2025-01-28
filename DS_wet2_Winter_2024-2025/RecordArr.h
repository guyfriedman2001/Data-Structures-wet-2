//
// Created by Guy Friedman on 28/01/2025.
//

#ifndef RECORDARR_H
#define RECORDARR_H
#include "Record.h"
#include "ChainHashArray.h"
#include "NewTeam.h" //todo maybe change this to a forward declaration instead of inclusion


class RecordArr : public ChainHashArray<Record> {
    public:

    RecordArr() : ChainHashArray<Record>() {}

    ~RecordArr() = default;

    void add_team_to_record(NewTeam* team, int team_id, int record_id) {
        //@brief - check if record exists, if so then add, if not create, store and then add

        //make sure input is valid
        assert(team_id > 0);
        assert(team != nullptr);

        //get relevant record
        Record* record = this->find(record_id);

        //if the record doesn't already exist, create it and store it.
        if (record == nullptr) {
            record = new Record(record_id);
            this->insert(record_id,record);
        }

        //add team to relevant record
        record->insert(team_id, team);
    }

    void remove_team_from_record( int team_id, int record_id) {
        //@brief - use this->remove(), then check if the record is empty, if it is - then delete it

        //retrieve relevant record
        Record* record = this->find(record_id);

        //verify input - make sure nothing funny is happening
        assert(record != nullptr);

        //remove relevant team from relevant record
        record->remove(team_id);

        //if the record is empty now, delete it.
        if(record->isEmpty()) {
            this->deleteItem(record_id);
        }
    }

    bool can_unite_by_record(int record_id) {
        //@brief - find record of (record_id) and record of (-record_id),
        //@brief - check if they are singletons,
        //@brief - if either of them isn't singleton or doesn't exist - return false
        //@brief - if both are singletons - return true

        //make sure input is valid
        assert(record_id > 0);

        //retrieve relevant records
        Record* positive_record = this->find(record_id);
        Record* negative_record = this->find(-record_id);

        //if either of them doesn't exist, can not unite by record
        if (positive_record == nullptr || negative_record == nullptr) {
            return false;
        }

        //if at least one of them is not a singleton, can not unite by record
        if (!((positive_record->isSingleton())&&(negative_record->isSingleton()))) {
            return false;
        }

        //if none of the previous checks failed
        return true;
    }

    int return_team_id_of_singleton_record(int record) {
        //@brief - get record, assert it is singleton, pop team, store team id, re-insert team, return saved id.

        //get proper record
        Record* record_singleton = this->find(record);

        //make sure record exists and is actually singleton
        assert(record_singleton != nullptr);
        assert(record_singleton->isSingleton());

        //get team from record
        NewTeam* team = record_singleton->pop();

        //save team id
        int team_id = team->get_id();

        //return team to its place in record_singleton
        record_singleton->insert(team_id, team);

        //return the id of the team that we got
        return team_id;

    }

};



#endif //RECORDARR_H
