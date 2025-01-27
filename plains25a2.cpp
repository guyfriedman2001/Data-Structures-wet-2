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
    //this->records->clear(); //fixme
    delete records;
    delete teams;
    delete jockeys;

}

StatusType Plains::add_team(int teamId)
{
    try{
        if(teamId<=0) {
            return StatusType::INVALID_INPUT;
        }else if (this->teams->find(teamId) != nullptr) {
            return StatusType::FAILURE;
        }
        Team* newTeam = new Team(teamId);
        this->teams->insert(teamId, newTeam); //insert(int id, T* value)
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
        }else if ((this->jockeys->find(jockeyId) != nullptr) || this->teams->find(teamId)==nullptr) { //if team doesnt exist or jockey does exist
            return StatusType::FAILURE;
        } else {
            Jockey* newJockey = new Jockey(jockeyId,teamId);
            this->jockeys->insert(jockeyId, newJockey); //insert(int id, T* value)
            return StatusType::SUCCESS;
        }
    }catch (std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType Plains::update_match(int victoriousJockeyId, int losingJockeyId) //todo
{
    try{
        if(victoriousJockeyId<=0 || losingJockeyId <= 0||victoriousJockeyId == losingJockeyId) {
            return StatusType::INVALID_INPUT;
        }
        Jockey* jockVic = this->jockeys->find(victoriousJockeyId);
        Jockey* jockLos = this->jockeys->find(losingJockeyId);
        if(jockVic==nullptr || jockLos==nullptr) {
            return StatusType::FAILURE;
        }
        Team* teamVic = this->teams->getLeader(jockVic->getTeamId());
        Team* teamLos = this->teams->getLeader(jockLos->getTeamId());
        if(teamVic == teamLos) {
            return StatusType::FAILURE;
        }
        int oldVicRec = teamVic->getRecord();
        int oldLosRec = teamLos->getRecord();
        jockVic->winMatch();
        jockLos->loseMatch();
        teamVic->winMatch();
        teamLos->loseMatch();
        Record* oldWin = this->records->find(oldVicRec);
        Record* oldLos = this->records->find(oldLosRec);
        if (oldWin != nullptr) {
            oldWin->remove(teamVic->getId());
            if (oldWin->isEmpty()) {
                this->records->deleteItem(oldWin->get_records_val());
            }
        }
        if (oldLos != nullptr) {
            oldLos->remove(teamLos->getId());
            if (oldLos->isEmpty()) {
                this->records->deleteItem(oldLos->get_records_val());
            }
        }
        int newVicRec = teamVic->getRecord();
        int newLosRec = teamLos->getRecord();
        assert(newVicRec==(oldVicRec+1));
        assert(newLosRec==(oldLosRec-1));
        Record* newWin = this->records->find(newVicRec);
        Record* newLos = this->records->find(newLosRec);
        if (newWin == nullptr) {
            newWin = new Record(newVicRec);
            this->records->insert(newVicRec, newWin);
        }
        if (newLos == nullptr) {
            newLos = new Record(newLosRec);
            this->records->insert(newLosRec, newLos);
        }
        newWin->insert(teamVic->getId(),teamVic);
        newLos->insert(teamLos->getId(),teamLos);
        return StatusType::SUCCESS;
    }
    catch (std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
}

/*
StatusType Plains::merge_teams(int teamId1, int teamId2){ //fixme
    try{
        if(teamId1<=0||teamId2<=0||teamId1==teamId2) {
            return StatusType::INVALID_INPUT;
        }
        //Team* team1 = this->teams->find(teamId1);
        //Team* team2 = this->teams->find(teamId2);
        Team* leader1 = this->teams->find(teamId1); //if 'isActive()' is redundant then func should be
        Team* leader2 = this->teams->find(teamId2); //findLeader() instead of find
        if (leader1==nullptr || leader2==nullptr || leader1==leader2) {
            return StatusType::FAILURE;
        }
        //todo add 'isActive()' check
        if (!leader1->isActive() || !leader2->isActive()) {
            return StatusType::FAILURE;
        }
        int initial_rec1 = leader1->getRecord();
        int initial_rec2 = leader2->getRecord();
        this->teams->uniteTeams(teamId1, teamId2);
        Record* record = nullptr;
        if (initial_rec1 > initial_rec2) {
            record = this->records->find(initial_rec2);
            record->remove(leader2->getId());
        }
        if (initial_rec1 < initial_rec2) {
            record = this->records->find(initial_rec1);
            record->remove(leader1->getId());
        }
        assert(initial_rec1!=initial_rec2);
        if (record->isEmpty()) {
            this->records->deleteItem(MIN(initial_rec1, initial_rec2));
        }


        return StatusType::SUCCESS;
    }
    catch(std::bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }
}
*/

/*
StatusType Plains::merge_teams(int teamId1, int teamId2){
    try{
        if(teamId1<=0||teamId2<=0||teamId1==teamId2) {
            return StatusType::INVALID_INPUT;
        }
        //Team* team1 = this->teams->find(teamId1);
        //Team* team2 = this->teams->find(teamId2);
        Team* leader1 = this->teams->find(teamId1); //if 'isActive()' is redundant then func should be
        Team* leader2 = this->teams->find(teamId2); //findLeader() instead of find
        if (leader1==nullptr || leader2==nullptr || leader1==leader2) {
            return StatusType::FAILURE;
        }
        //todo add 'isActive()' check
        if (!leader1->isActive() || !leader2->isActive()) {
            return StatusType::FAILURE;
        }
        int initial_rec1 = leader1->getRecord();
        int initial_rec2 = leader2->getRecord();
        this->teams->uniteTeams(teamId1, teamId2);
        Record* record = nullptr;
        if (initial_rec1 >= initial_rec2) {
            record = this->records->find(initial_rec2);
            if (record != nullptr) {
                record->remove(leader2->getId());
            }
        }
        if (initial_rec1 < initial_rec2) {
            record = this->records->find(initial_rec1);
            if (record != nullptr) {
                record->remove(leader1->getId());
            }
        }
        //assert(initial_rec1!=initial_rec2);
        if ((record != nullptr)&&(record->isEmpty())) {
            this->records->deleteItem(MIN(initial_rec1, initial_rec2));
        }


        return StatusType::SUCCESS;
    }
    catch(std::bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }
}
 */

StatusType Plains::merge_teams(int teamId1, int teamId2){
    try{
        if(teamId1<=0||teamId2<=0||teamId1==teamId2) {
            return StatusType::INVALID_INPUT;
        }
        Team* team1 = this->teams->find(teamId1); //if team is not active then should return failure;
        Team* team2 = this->teams->find(teamId2);
        if (team1==nullptr || team2==nullptr || !(team1->isActive()&&team2->isActive())) {
            return StatusType::FAILURE;
        }
        int record1 = team1->getRecord();
        int record2 = team2->getRecord();
        int new_record = record1 + record2;
        Record* old1 = this->records->find(record1);
        if (old1 != nullptr) {
            old1->remove(teamId1);
            if(old1->isEmpty()) {
                this->records->deleteItem(old1->get_records_val());
            }
        }
        Record* old2 = this->records->find(record2);
        if (old2 != nullptr) {
            old2->remove(teamId2);
            if(old2->isEmpty()) {
                this->records->deleteItem(old2->get_records_val());
            }
        }
        Record* newRecord = this->records->find(new_record);
        if (newRecord == nullptr) {
            newRecord = new Record(new_record);
            this->records->insert(newRecord->get_records_val(),newRecord);
        }
        if (team1->getRecordWithoutActive() >= team2->getRecordWithoutActive()) {
            team2->followTeam(team1);
        }
        if (team2->getRecordWithoutActive() > team1->getRecordWithoutActive()) {
            team1->followTeam(team2);
        }
        team1->setRecord(new_record);
        team2->setRecord(new_record);





        return StatusType::SUCCESS;
    }
    catch(std::bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType Plains::unite_by_record(int record)
{
    if (record<=0) {
        return StatusType::INVALID_INPUT;
    }
    int pos_rec = ABS(record);
    Record* pos_record = this->records->find(pos_rec);
    Record* neg_record = this->records->find(-pos_rec);
    if (pos_record == nullptr || neg_record == nullptr) {
        return StatusType::FAILURE;
    }
    if (!((pos_record->isSingleton())&&(neg_record->isSingleton()))) {
        return StatusType::FAILURE;
    }
    Team* negative_team = neg_record->pop();
    Team* positive_team = pos_record->pop();
    int negative_id = negative_team->getId();
    int positive_id = positive_team->getId();
    neg_record->insert(negative_id, negative_team);
    pos_record->insert(positive_id, positive_team);
    /**
     *basically i just made sure that there is just one team for +rec and for -rec,
     *then i got the team to get its id, then put the teams back in their corresponding records
     *so the rest of the code would work as expected, and then i just used the built in merge teams function.
     */
    return this->merge_teams(positive_id, negative_id);
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
