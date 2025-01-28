//
// Created by Guy Friedman on 28/01/2025.
//

#ifndef NEWTEAM_H
#define NEWTEAM_H

#define SELECT_ID_BY_MAX_RECORD(record1,record2,id1,id2) (record1>=record2?id1:id2)
#include <cassert>


class NewTeam {
protected:
    int id;
    int size;
    int record;
    NewTeam* root_by_mass;
    NewTeam* root_by_record; //for now, it is not used
public:

    NewTeam() = delete;

    NewTeam(int id) : id(id), size(1), record(0), root_by_mass(this), root_by_record(this) {}

    /*
    NewTeam(int id,int newRec, int newSize) : NewTeam(id) { //todo maybe can delete
        this->record = newRec;
        this->size = newSize;
    }
    */

    ~NewTeam() = default;

    NewTeam* get_root_by_mass() {
        if (this->root_by_mass == this) {
            return this;
        }
        NewTeam* actual_root_by_mass = this->root_by_mass->get_root_by_mass();
        this->root_by_mass = actual_root_by_mass;
        return actual_root_by_mass;
    }

    int get_id() {
        return this->id;
    }

    int get_record() {
        //make sure that it's only called on the leader
        assert(this ==  this->root_by_mass);

        return this->record;
    }

    bool isTeam(int id) {
        //make sure that it's only called on the leader
        assert(this ==  this->root_by_mass);
        return this->id == id;
    }

    void unite_team(NewTeam* other) { //done - make sure in main that 'this' is team 1 and 'other' is team 2
        //make sure main has taken care of its responsibilities for union
        this->verify_main_for_union(other);

        //get new parameters after union
        int new_id = SELECT_ID_BY_MAX_RECORD(this->record, other->record, this->id, other->id); //SELECT_ID_BY_MAX_RECORD(record1,record2,id1,id2) (record1>=record2?id1:id2)
        int new_size = this->size + other->size;
        int new_record = this->get_record() + other->get_record(); //        int new_record = this->record + other->record;

        //regular unite
        this->unite_helper(other,0);

        //update_merge_details(int new_id, int new_size, int new_record)
        //I don't care who is actually the root, I'll just update both to save me the hassle of checking
        this->update_merge_details(new_id,new_size,new_record);
        other->update_merge_details(new_id,new_size,new_record);
    }

    /**
     *just unite by size, don't care about id, record and other stuff,
     *unite team takes care of this
     */
    void unite_helper(NewTeam* other, int make_signature_different_to_prevent_confusion) {
        //make sure main has taken care of its responsibilities for union
        this->verify_main_for_union(other);

        //retrieve original team sizes
        int this_size = this->size;
        int other_size = other->size;

        //unify by moving small (not small 'mamash') tree root to point at big tree root
        if (this_size <= other_size) {
            this->root_by_mass = other; //other->root_by_mass;
        } else {
            other->root_by_mass = this; //this->root_by_mass;
        }

        //update sizes (even though it's updated in 'unite_team', make sure)
        int sum_size = this_size + other_size;
        this->size = sum_size;
        other->size = sum_size;
    }


    void verify_main_for_union(NewTeam* other) {
        //should only call to unite by roots - responsibility of the main
        assert(other == other->root_by_mass);
        assert(this == this->root_by_mass);
    }

    void update_merge_details(int new_id, int new_size, int new_record) {
        this->id = new_id;
        this->record = new_record;
        this->size = new_size;
    }

    bool check_active_immediate() {
        return this->root_by_mass == this || this->root_by_mass->id == this->id;
    }

    void winMatch() {
        assert(this->root_by_mass == this);
        ++this->record;
    }

    void loseMatch() {
        assert(this->root_by_mass == this);
        --this->record;
    }






};



#endif //NEWTEAM_H
