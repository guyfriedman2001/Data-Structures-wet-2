// You can edit anything you want in this file.
// However you need to implement all public Plains function, as provided below as a template

#include "plains25a2.h"

#include "Jockey.h"


Plains::Plains()
{
    
}

Plains::~Plains()
{
    this->records->clear();
    delete records;
    delete teams;
    delete jockeys;

}

StatusType Plains::add_team(int teamId)
{
    try{
        if(teamId<=0) {
            return StatusType::INVALID_INPUT;
        }else if (!this->teams->find(teamId)) {
            return StatusType::FAILURE;
        } else {
            Team* newTeam = new Team(teamId);
            this->teams->insert(teamId, newTeam); //insert(int id, T* value)
        }
    }
    catch (std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
}


StatusType Plains::add_jockey(int jockeyId, int teamId)
{
    try{
        if(jockeyId<=0 || teamId <= 0) {
            return StatusType::INVALID_INPUT;
        }else if (!this->teams->find(teamId) || this->teams->find(jockeyId)) { //if team doesnt exist or jockey does exist
            return StatusType::FAILURE;
        } else {
            Jockey* newJockey = new Jockey(jockeyId,teamId);
            this->jockeys->insert(teamId, newJockey); //insert(int id, T* value)
        }
    }
    catch (std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType Plains::update_match(int victoriousJockeyId, int losingJockeyId) //todo
{
    return StatusType::FAILURE;
}

StatusType Plains::merge_teams(int teamId1, int teamId2){
    try{
        if(teamId1<=0||teamId2<=0||teamId1==teamId2) { //todo check last condition
            return StatusType::INVALID_INPUT;
        }
        //Team* team1 = this->teams->find(teamId1);
        //Team* team2 = this->teams->find(teamId2);
        Team* leader1 = this->teams->getLeader(teamId1);
        Team* leader2 = this->teams->getLeader(teamId2);
        if (leader1==nullptr || leader2==nullptr || leader1==leader2) {
            return StatusType::FAILURE;
        }
        this->teams->uniteTeams(teamId1, teamId2);
        return StatusType::SUCCESS;
    }
    catch(std::bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType Plains::unite_by_record(int record) //todo
{
    return StatusType::FAILURE;
}

output_t<int> Plains::get_jockey_record(int jockeyId)
{
    if (jockeyId<=0) {
        return StatusType::INVALID_INPUT;
    }
    Jockey* jock = this->jockeys->find(jockeyId);
    if (jock==nullptr) {
        return StatusType::FAILURE;
    }
    return jock->getRecord();
}

output_t<int> Plains::get_team_record(int teamId)
{
    if (teamId<=0) {
        return StatusType::INVALID_INPUT;
    }
    Team* team = this->teams->find(teamId);
    if (team==nullptr) {
        return StatusType::FAILURE;
    }
    Team* team_leader = this->teams->getLeader(teamId);
    if (team!=team_leader) { //if the team does not lead itself it means that it has been deleted
        return StatusType::FAILURE;
    }
    assert(team_leader!=nullptr); //just make sure that there isnt some problem
    return team->getRecord();
}
