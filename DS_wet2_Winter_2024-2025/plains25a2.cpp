// You can edit anything you want in this file.
// However you need to implement all public Plains function, as provided below as a template

#include "plains25a2.h"

#include "Jockey.h"

#define MIN(a,b) (a<b)?a:b

#define ABS(a) ((a)<0?(-(a)):(a))

Plains::Plains()
{
    /*
    RecordArr* records;
    NewTeamArr* teams;
    ChainHashArray<Jockey>* jockeys;
     */
    this->records = new RecordArr();
    this->teams = new NewTeamArr();
    this->jockeys = new ChainHashArray<Jockey>();

}

Plains::~Plains()
{
    delete records;
    delete teams;
    delete jockeys;
}

StatusType Plains::add_team(int teamId)
{
    try{
        if(teamId<=0) {
            return StatusType::INVALID_INPUT;
        }

        //check if team already exists (don't care if active or not)
        NewTeam* newTeam = this->teams->find(teamId);
        if (newTeam != nullptr) {
            return StatusType::FAILURE;
        }

        //after we checked that there is no and was no team for 'teamId', create it.
        newTeam = new NewTeam(teamId);

        //the record for every beginner team
        int initial_record = 0;

        //add team to corresponding record
        this->records->add_team_to_record(newTeam,teamId,initial_record);

        return StatusType::SUCCESS;
    } catch (std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
}


StatusType Plains::add_jockey(int jockeyId, int teamId)
{
    try{
        if(jockeyId<=0 || teamId <= 0) {
            return StatusType::INVALID_INPUT;
        }

        //make sure team is valid, without path modification
        if(!this->teams->check_active_immediate(teamId)) {
            return StatusType::FAILURE;
        }

        //make sure jockey doesn't already exist
        Jockey* jockey = this->jockeys->find(jockeyId);
        if(jockey != nullptr) {
            return StatusType::FAILURE;
        }

        //create jockey
        jockey = new Jockey(jockeyId,teamId);

        //store jockey in our system
        this->jockeys->insert(jockeyId,jockey);

        return StatusType::SUCCESS;
    } catch (std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
}


StatusType Plains::update_match(int victoriousJockeyId, int losingJockeyId)
{
    try{
        //check input validity
        if(victoriousJockeyId<=0 || losingJockeyId <= 0||victoriousJockeyId == losingJockeyId) {
            return StatusType::INVALID_INPUT;
        }

        //@brief - check jockeys exist, check jockeys are not in the same team, remove teams from their records
        //@brief - update score for jockeys and teams, put teams in their new records

        //check that winning jockey exists
        Jockey* winningJockey = this->jockeys->find(victoriousJockeyId);
        if (winningJockey == nullptr) {
            return StatusType::FAILURE;
        }

        //check that losing jockey exists
        Jockey* losingJockey = this->jockeys->find(losingJockeyId);
        if (losingJockey == nullptr) {
            return StatusType::FAILURE;
        }

        //get team of winning jockey
        NewTeam* winningTeam = this->teams->get_root_of(winningJockey->getTeamId());

        //get team of losing jockey
        NewTeam* losingTeam = this->teams->get_root_of(losingJockey->getTeamId());

        //make sure it is not the same group
        if (winningTeam==losingTeam) {
            return StatusType::FAILURE;
        }

        //make sure no funny business is going on
        assert(winningTeam != nullptr);
        assert(losingTeam != nullptr);

        //remove each team from their record
        this->records->remove_team_from_record(winningTeam->get_id(),winningTeam->get_record());
        this->records->remove_team_from_record(losingTeam->get_id(),losingTeam->get_record());

        //update scores
        winningJockey->winMatch();
        losingJockey->loseMatch();
        winningTeam->winMatch();
        losingTeam->loseMatch();

        //store teams in their new records
        this->records->add_team_to_record(winningTeam,winningTeam->get_id(),winningTeam->get_record());
        this->records->add_team_to_record(losingTeam,losingTeam->get_id(),losingTeam->get_record());

        return StatusType::SUCCESS;
    } catch (std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
}


StatusType Plains::merge_teams(int teamId1, int teamId2)
{
    try{
        if(teamId1<=0||teamId2<=0||teamId1==teamId2) {
            return StatusType::INVALID_INPUT;
        }

        //make sure team1 is active
        if (!this->teams->team_active(teamId1)) {
            return StatusType::FAILURE;
        }

        //make sure team2 is active
        if (!this->teams->team_active(teamId2)) {
            return StatusType::FAILURE;
        }

        //retrieve team1 and team2
        NewTeam* teamOne = this->teams->get_root_of(teamId1);
        NewTeam* teamTwo = this->teams->get_root_of(teamId2);

        //make sure no funny business is happening
        assert(teamOne->get_id() == teamId1);
        assert(teamTwo->get_id() == teamId2);

        //if they are the same team - cant merge
        if (teamOne == teamTwo) {
            return StatusType::FAILURE;
        }

        //remove each team from their record
        this->records->remove_team_from_record(teamId1,teamOne->get_record());
        this->records->remove_team_from_record(teamId2,teamTwo->get_record());

        //use logic in TeamArr to handle merging of teams
        this->teams->unite_teams(teamId1,teamId2);

        //make sure all is going good and no funny business, should be ok if merge went ok in TeamArr.
        assert(teamOne->get_id() == teamTwo->get_id());

        //now ID will be updated in both teams, get the new root (would automatically select either teamOne or teamTwo, according to the merge)
        NewTeam* newRoot = this->teams->get_root_of(teamOne->get_id());

        //store merged team in the appropriate record
        this->records->add_team_to_record(newRoot, newRoot->get_id(), newRoot->get_record());

        return StatusType::SUCCESS;
    } catch(std::bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }
}


StatusType Plains::unite_by_record(int record)
{
    try{
        if (record<=0) {
            return StatusType::INVALID_INPUT;
        }

        //make sure that we can unite by record
        if (!this->records->can_unite_by_record(record)) {
            return StatusType::FAILURE;
        }

        //get id of teams in singleton records
        int positive_team_id = this->records->return_team_id_of_singleton_record(record);
        int negative_team_id = this->records->return_team_id_of_singleton_record(-record);

        //utilise existing logic and code to handle merging execution
        return this->merge_teams(positive_team_id,negative_team_id);

    } catch(std::bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }
}


output_t<int> Plains::get_jockey_record(int jockeyId)
{
    try{
        if (jockeyId<=0) {
            return StatusType::INVALID_INPUT;
        }
        Jockey* jock = this->jockeys->find(jockeyId);
        if (jock==nullptr) {
            return StatusType::FAILURE;
        }
        return jock->getRecord();
    } catch(std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
}


output_t<int> Plains::get_team_record(int teamId)
{
    try{
        if (teamId<=0) {
            return StatusType::INVALID_INPUT;
        }

        //make sure team is active without path modifications
        if (!this->teams->check_active_immediate(teamId)) {
            return StatusType::FAILURE;
        }

        //get root of team
        NewTeam* newTeam = this->teams->get_root_of(teamId);

        //make sure no funny business is going on
        assert(newTeam->get_id() == teamId);

        //the record of our team
        int record = newTeam->get_record();

        //return it
        return record;

    } catch(std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
}
