// You can edit anything you want in this file.
// However you need to implement all public Plains function, as provided below as a template

#include "plains25a2.h"


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
        if(teamId<=0) 
            return StatusType::INVALID_INPUT; 
        else if (!unionFindJockeys.teamExist(teamId))
            return StatusType::FAILURE;
        else
            unionFindJockeys.addTeam(teamId);
    }
    catch (std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
}


StatusType Plains::add_jockey(int jockeyId, int teamId)
{
    return StatusType::FAILURE;
}

StatusType Plains::update_match(int victoriousJockeyId, int losingJockeyId)
{
    return StatusType::FAILURE;
}

StatusType Plains::merge_teams(int teamId1, int teamId2){
    try{
        if(teamId1<=0||teamId2<=0)
            return StatusType::INVALID_INPUT;
        else if(!unionFindJockeys.teamExist(teamId1)||!unionFindJockeys.teamExist(teamId2))
            return StatusType::FAILURE;
        unionFindJockeys.unionTeams(teamId1,teamId2);
    }
    catch(std::bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType Plains::unite_by_record(int record)
{
    return StatusType::FAILURE;
}

output_t<int> Plains::get_jockey_record(int jockeyId)
{
    return 0;
}

output_t<int> Plains::get_team_record(int teamId)
{
    return 0;
}
