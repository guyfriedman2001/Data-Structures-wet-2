//
// Created by Guy Friedman on 26/01/2025.
//


#ifndef RECORD_H
#define RECORD_H
#include "ChainHashArray.h"
#include "uptree_jockeys.h"
typedef TeamNode what_to_hold;

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



};



#endif //RECORD_H
