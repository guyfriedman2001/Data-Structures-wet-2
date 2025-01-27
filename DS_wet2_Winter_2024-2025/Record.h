//
// Created by Guy Friedman on 26/01/2025.
//


#ifndef RECORD_H
#define RECORD_H
#include "ChainHashArray.h"
#include "uptree_jockeys.h"
#include "Team.h"
typedef Team what_to_hold;

class Record {
protected:
    ChainHashArray<what_to_hold>* held_items;
    int record_value;
public:
    Record() = delete;

    Record(int record_value) : record_value(record_value) {
        this->held_items = new ChainHashArray<what_to_hold>();
    }

    ~Record() {
        this->held_items->clear();
        delete this->held_items;
    }

    bool isEmpty() {
        return this->held_items->size() == 0;
    }

    bool isSingleton() {
        return this->held_items->size() == 1;
    }

    what_to_hold* pop() {
        return this->held_items->popRandom();
    }

    what_to_hold* remove(int key) {
        return this->held_items->remove(key);
    }

    void insert(int key, what_to_hold* value) {
        this->held_items->insert(key, value);
    }

    int get_records_val() {
        return this->record_value;
    }



};



#endif //RECORD_H
