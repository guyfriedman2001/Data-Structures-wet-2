//
// Created by Guy Friedman on 28/01/2025.
//

#ifndef NEWTEAMARR_H
#define NEWTEAMARR_H
#include "NewTeam.h"
#include "ChainHashArray.h"


class NewTeamArr : public ChainHashArray<NewTeam> {
public:

    NewTeamArr() : ChainHashArray<NewTeam>() {}

    ~NewTeamArr() = default;

    bool team_outdated(int team_id) {
        //@brief - get team root, compare root id to 'team_id'
        //legacy function, instead of rewriting the code to remove it,
        //I just utilised existing code and logic.
        bool team_is_active = this->team_active(team_id);
        return !team_is_active;
    }

    bool team_active(int team_id) {
        //done - cri8 dis foonktzion

        //find root of team with 'team_id' key
        NewTeam* root_team_of_team_id = this->get_root_of(team_id);

        //if team doesn't exist return false
        if (root_team_of_team_id == nullptr) {
            return false;
        }

        //get the id of the root
        int id_of_root = root_team_of_team_id->get_id();

        return id_of_root == team_id;
    }

    void unite_teams(int team1, int team2) {
        //@brief - team1->unite_team(other);

        //make sure that we got existing teams
        assert(this->team_active(team1));
        assert(this->team_active(team2));

        //get the roots of team1 and team2
        NewTeam* team_one = this->get_root_of(team1);
        NewTeam* team_two = this->get_root_of(team2);

        //make sure that we received valid teams
        assert(team_one->get_id() == team1);
        assert(team_two->get_id() == team2);

        //execute union by utilising existing code and logic
        team_one->unite_team(team_two);
    }

    NewTeam* get_root_of(int team_id) {
        //@brief - get_root_by_mass() of team held by key 'team_id'

        //get team with key 'team_id'
        NewTeam* temp_placeholder = this->find(team_id);

        //maybe there isnt any team in initial 'team_id'
        if (temp_placeholder == nullptr) {
            return nullptr;
        }

        //get root of team 'hana"l'
        NewTeam* root_team = temp_placeholder->get_root_by_mass();

        return root_team;
    }

    NewTeam* get_jockeys_actual_team(int id) {
        //@brief - get team with id, get root of team with id, return root

        //get root of team corresponding with key of 'id'
        NewTeam* temp_placeholder = this->get_root_of(id);

        //make sure no funny business is going on
        assert(temp_placeholder != nullptr);
        assert(this->team_active(temp_placeholder->get_id()));

        return temp_placeholder;
    }

    bool check_active_immediate(int team_id) {
        NewTeam* temp_placeholder = this->find(team_id);
        if (temp_placeholder == nullptr) {
            return false;
        }
        return temp_placeholder->check_active_immediate();
    }

};



#endif //NEWTEAMARR_H
