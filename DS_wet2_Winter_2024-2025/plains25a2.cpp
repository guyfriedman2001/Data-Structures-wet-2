// You can edit anything you want in this file.
// However you need to implement all public Plains function, as provided below as a template

#include "plains25a2.h"

#include "Jockey.h"

#define MIN(a,b) (a<b)?a:b

#define ABS(a) ((a)<0?(-(a)):(a))

Plains::Plains()
{
    /*
    ChainHashArray<Record>* records;
    TeamUnionFind* teams;
    ChainHashArray<Jockey>* jockeys;
     */
    this->records = new ChainHashArray<Record>();
    this->teams = new TeamUnionFind();
    this->jockeys = new ChainHashArray<Jockey>();
}

Plains::~Plains()
{
    delete records;
    delete teams;
    delete jockeys;
}

StatusType Plains::add_team(int teamId) //todo verify
{
    try{
        if(teamId<=0) {
            return StatusType::INVALID_INPUT;
        }
        Team* team = this->teams->find(teamId);
        if (team != nullptr) { //if team already exists
            return StatusType::FAILURE;
        }

        //if we got here, we need to create this team
        team = new Team(teamId);

        //every new team belongs initially to record 0
        Record* zeroRecord = this->records->find(0);

        if (zeroRecord == nullptr) {
            zeroRecord = new Record(0);
            this->records->insert(0, zeroRecord);
        }

        //insert team into corresponding record
        zeroRecord->insert(teamId, team);

        //store team in dynamic array
        this->teams->insert(teamId, team);



        return StatusType::SUCCESS;
    } catch (std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
}


StatusType Plains::add_jockey(int jockeyId, int teamId) //todo verify
{
    try{
        if(jockeyId<=0 || teamId <= 0) {
            return StatusType::INVALID_INPUT;
        }
        Team* team = this->teams->find(teamId);
        Jockey* jockey = this->jockeys->find(jockeyId);
        if(team == nullptr || jockey != nullptr) {
            return StatusType::FAILURE;
        }
        jockey = new Jockey(jockeyId,teamId);
        this->jockeys->insert(jockeyId, jockey);



        return StatusType::SUCCESS;
    }catch (std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
}

//todo create
StatusType Plains::update_match(int victoriousJockeyId, int losingJockeyId) //todo verify
{
    try{
        //check input validity
        if(victoriousJockeyId<=0 || losingJockeyId <= 0||victoriousJockeyId == losingJockeyId) {
            return StatusType::INVALID_INPUT;
        }

        //find corresponding jockeys
        Jockey* winningJockey = this->jockeys->find(victoriousJockeyId);
        Jockey* losingJockey = this->jockeys->find(losingJockeyId);

        //if one of the jockeys does not exist in our system, invalid
        if(winningJockey == nullptr || losingJockey == nullptr) {
            return StatusType::FAILURE;
        }

        //retrieve initial group IDs
        int initial_winning_group_id = winningJockey->getTeamId();
        int initial_losing_group_id = losingJockey->getTeamId();

        //retrieve actual groups
        Team* winningTeam = this->teams->actuallGroupLeader(initial_winning_group_id);
        Team* losingTeam = this->teams->actuallGroupLeader(initial_losing_group_id);

        //as per da fooken horaot
        if(winningTeam == losingTeam) {
            return StatusType::FAILURE;
        }

        //this situation should not occur
        assert(winningTeam != nullptr);
        assert(losingTeam != nullptr);

        //retrieve original records
        Record* initial_winner_record = this->records->find(winningTeam->getRecord());
        Record* initial_loser_record = this->records->find(losingTeam->getRecord());

        //remove groups from records
        initial_winner_record->remove(winningTeam->getId());
        initial_loser_record->remove(losingTeam->getId());

        //check maybe they are empty
        if (initial_winner_record->isEmpty()) {
            this->records->deleteItem(initial_winner_record->get_records_val());
        }

        //if initial_loser_record == initial_winner_record, avoid deleting twice
        if ((initial_loser_record != initial_winner_record)&&(initial_loser_record->isEmpty())) {
            this->records->deleteItem(initial_loser_record->get_records_val());
        }

        //update game records for jockeys and teams
        winningJockey->winMatch();
        losingJockey->loseMatch();
        winningTeam->winMatch();
        losingTeam->loseMatch();

        //get updated records
        Record* winnerRecord = this->records->find(winningTeam->getRecord());
        Record* loserRecord = this->records->find(losingTeam->getRecord());

        //if records dont exist, create them and store them
        if(winnerRecord == nullptr) {
            winnerRecord = new Record(winningTeam->getRecord());
            this->records->insert(winningTeam->getRecord(), winnerRecord);
        }

        //same for loser record
        if(loserRecord == nullptr) {
            loserRecord = new Record(losingTeam->getRecord());
            this->records->insert(loserRecord->get_records_val(),loserRecord);
        }

        //store teams in their appropriate records
        winnerRecord->insert(winningTeam->getId(),winningTeam);
        loserRecord->insert(losingTeam->getId(),losingTeam);







        return StatusType::SUCCESS;
    }
    catch (std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
}


StatusType Plains::merge_teams(int teamId1, int teamId2) //todo verify
{
    try{
        if(teamId1<=0||teamId2<=0||teamId1==teamId2) {
            return StatusType::INVALID_INPUT;
        }
        Team* team1 = this->teams->find(teamId1);
        Team* team2 = this->teams->find(teamId2);
        if(team1==nullptr || team2==nullptr) {
            return StatusType::FAILURE;
        }
        if (!(team1->isActive()&&team2->isActive())) {
            return StatusType::FAILURE;
        }
        int preRec1 = team1->getRecord();
        int preRec2 = team2->getRecord();

        Record* preRecord1 = this->records->find(preRec1);
        Record* preRecord2 = this->records->find(preRec2);

        assert(preRecord1!=nullptr && preRecord2!=nullptr); // i made sure a group is always in a record

        preRecord1->remove(team1->getId()); //remove team1 from its record

        if (preRecord1->isEmpty()) { //if record of team 1 is empty, delete it
            this->records->deleteItem(preRec1);
        }

        preRecord2->remove(team2->getId()); //take team 2 out of its record

        if (preRecord2->isEmpty()) { //if the record of team 2 is empty now, delete it.
            this->records->deleteItem(preRec2);
        }

        int newRecordCombined = preRec1 + preRec2; //calc sum of 2 teams

        this->teams->uniteTeams(teamId1, teamId2); //unite 2 teams

        Record* newRecord = this->records->find(newRecordCombined); //find fitting record for the team union


        if (newRecord == nullptr) { //if the new record doesnt exist, create and store it
            newRecord = new Record(newRecordCombined);
            this->records->insert(newRecordCombined, newRecord);
        }


        Team* leadTeam = this->teams->getLeader(teamId1); //get the leader after the union

        newRecord->insert(leadTeam->getId(), leadTeam); //save the leader inside the new record






        return StatusType::SUCCESS;
    }
    catch(std::bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }
}


StatusType Plains::unite_by_record(int record) //todo verify
{
    try{
        if (record<=0) {
            return StatusType::INVALID_INPUT;
        }

        //get corresponding records
        Record* positive = this->records->find(record);
        Record* negative = this->records->find(-record);

        //check if the records exist
        if (positive==nullptr || negative==nullptr) {
            return StatusType::FAILURE;
        }

        //if we are not in an {each record == exactly one} situation, cannot unite by record.
        if (!(positive->isSingleton() && negative->isSingleton())) {
            return StatusType::FAILURE;
        }

        //retrieve teams
        Team* positive_team = positive->pop();
        Team* negative_team = negative->pop();

        //retrieve ID's
        int positive_team_id = positive_team->getId();
        int negative_team_id = negative_team->getId();

        //return state to controlled state - every team belongs to a record
        positive->insert(positive_team_id, positive_team);
        negative->insert(negative_team_id, negative_team);


        //utilise existing function to take care of union
        return this->merge_teams(positive_team_id, negative_team_id);
    }
    catch(std::bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }


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
    if (team==nullptr || !(team->isActive())) {
        return StatusType::FAILURE;
    }
    return team->getRecord();
}
