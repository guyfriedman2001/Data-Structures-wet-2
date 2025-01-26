//
// Created by Guy Friedman on 26/01/2025.
//


#ifndef RECORD_H
#define RECORD_H
#include "ChainHashArray.h"

typedef int what_to_hold;

class Record {
protected:
    ChainHashArray<what_to_hold> held_items;


};



#endif //RECORD_H
