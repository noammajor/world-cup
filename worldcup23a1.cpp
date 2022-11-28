#include "worldcup23a1.h"

world_cup_t::world_cup_t()
{
	// TODO: Your code goes here
}

world_cup_t::~world_cup_t()
{
	// TODO: Your code goes here
}


StatusType world_cup_t::add_team(int teamId, int points)
{
    if (teamId <= 0 || points < 0)
        return StatusType::INVALID_INPUT;
    try
    {
        Team t1(teamId, points);
        if(!illegel_teams.insert_to_tree(&t1))
            return StatusType::FAILURE;
    }
    catch (std::bad_alloc&)
    {
        return StatusType::ALLOCATION_ERROR;
    }
	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId)
{
    if (teamId <= 0)
        return StatusType::INVALID_INPUT;
    try
    {
        if (legel_teams.remove(teamId) || illegel_teams.remove(teamId))
            return StatusType::SUCCESS;
    }
    catch (...)
    {
        return StatusType::ALLOCATION_ERROR;
    }
	return StatusType::FAILURE;
}

StatusType world_cup_t::add_player(int playerId, int teamId, int gamesPlayed,
                                   int goals, int cards, bool goalKeeper)
{
    if (playerId <= 0 || teamId <= 0 || gamesPlayed < 0 || goals < 0 || cards < 0 || (gamesPlayed == 0 && (goals > 0 || cards > 0)))
        return StatusType::INVALID_INPUT;
    bool legal_team = true;
    try
    {
        Node<Team*, TeamIDOrder>* node = legel_teams.search(teamId);
        if (node == nullptr)
        {
            node = illegel_teams.search(teamId);
            legal_team = false;
        }
        if (node == nullptr || playersID.search(playerId))
            return StatusType::FAILURE;
        if (legal_team)
        {
            Player player(playerId, teamId, gamesPlayed, goals, cards, goalKeeper, legel_teams.get_data(node));
            playersID.insert_to_tree(&player);
            playersGoals.insert_to_tree(&player);
        }
        else
        {
            Player player(playerId, teamId, gamesPlayed, goals, cards, goalKeeper, illegel_teams.get_data(node));
            playersID.insert_to_tree(&player);
            playersGoals.insert_to_tree(&player);
        }

    }
    catch (std::bad_alloc&)
    {
        return StatusType::ALLOCATION_ERROR;
    }
	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_player(int playerId)
{
	if(playerId<=0)
    {
        return StatusType::INVALID_INPUT;
    }
    Node<Player,TeamIDOrder>* temp1 = playersID.search(playerId);
    Node<Team,TeamIDOrder>* tempteam1=legel_teams.search(*temp1.get_team());
    Node<Team,TeamIDOrder>* tempteam2=illegel_teams.search(*temp1.get_team());
    if(tempteam2 != nullptr)
    {
        try{
            tempteam2->data.remove_player(playerId);
        }
        catch (std::bad_alloc&)
        {
            return StatusType::ALLOCATION_ERROR;
        }
    }
    if(tempteam1 != nullptr)
    {
        try{
            tempteam1->data.remove_player(playerId);
        }
        catch (std::bad_alloc&)
        {
            return StatusType::ALLOCATION_ERROR;
        }
        if (!(tempteam1->data.is_legal()))
        {
            try{
                illegel_teams.insert_to_tree(*tempteam1);
                legel_teams.remove(tempteam1->data.get_ID());
            }
            catch (std::bad_alloc&)
            {
                return StatusType::ALLOCATION_ERROR;
            }

        }
        try{
            if(!(playersID.remove(playerId) && playersGoals.remove(playerId)))
            {
                return StatusType::FAILURE;
            }
            return StatusType::SUCCESS;
        }
        catch (std::bad_alloc&)
        {
            return StatusType::ALLOCATION_ERROR;
        }
        return StatusType::SUCCESS;
    }
    }


StatusType world_cup_t::update_player_stats(int playerId, int gamesPlayed,
                                        int scoredGoals, int cardsReceived)
{
    if (playerId<=0 || gamesPlayed <0 || scoredGoals<0 || cardsReceived<0)
    {
        return StatusType::INVALID_INPUT;
    }
    playersID.Node<T, Cond>*  temp =playersID.search(playerId);
    if(temp== nullptr)
    {
        return StatusType::INVALID_INPUT;
    }
    temp->set_games(gamesPlayed);
    temp->set_goals(scoredGoals);
    temp->set_cards(cardsReceived);
	return StatusType::SUCCESS;
}

StatusType world_cup_t::play_match(int teamId1, int  teamId2)
{
    if(teamId1<=0 || teamId2<=0 || teamId2==teamId1)
    {
        return StatusType::INVALID_INPUT;
    }
    Node<Team,TeamIDOrder>* tempteam1=legel_teams.search( teamId1);
    Node<Team,TeamIDOrder>* tempteam2=legel_teams.search( teamId2);
    if(tempteam2== nullptr||tempteam1== nullptr)
    {
        return StatusType::INVALID_INPUT;
    }
    if(tempteam2->tot_points()==tempteam1->tot_points())
    {
        tempteam1->add_points(1);
        tempteam2->add_points(1);
    }
    if (tempteam2->tot_points()>tempteam1->tot_points())
    {
        tempteam2->add_points(3);
    }
    else
    {
        tempteam1->add_points(3);
    }
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_num_played_games(int playerId)
{
	if(playerId<=0)
    {
       return StatusType::INVALID_INPUT;
    }
    Node<Player,TeamIDOrder>* temp1 = playersID.search(playerId);
    if(temp1== nullptr)
    {
        return StatusType::INVALID_INPUT;
    }
    return temp1->get_games_played();
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
    if(teamId<=0)
    {
        return StatusType::INVALID_INPUT;
    }
    Node<Team,TeamIDOrder>* tempteam1=illegel_teams.search( teamId);
    Node<Team,TeamIDOrder>* tempteam2=legel_teams.search( teamId);
    if(tempteam1!= nullptr)
    {
        return tempteam1->tot_points();
    }
    if (tempteam2!= nullptr)
    {
        return tempteam1->tot_points();
    }
    else
        return StatusType::INVALID_INPUT;
}
//later
StatusType world_cup_t::unite_teams(int teamId1, int teamId2, int newTeamId)
{
    if(teamId1<=0 || teamId2<=0 || newTeamId<=0 || teamId2==teamId1)
        return StatusType::INVALID_INPUT;
    Node<Team,TeamIDOrder>* tempteam1=illegel_teams.search( teamId1);
    Node<Team,TeamIDOrder>* tempteam2=legel_teams.search( teamId1);
    Node<Team,TeamIDOrder>* tempteam3=illegel_teams.search( teamId2);
    Node<Team,TeamIDOrder>* tempteam4=legel_teams.search( teamId2);
    if(tempteam1!= nullptr&& tempteam3!= nullptr)
    {
        Team newTeam= new Team(newTeamId, tempteam1->tot_points()+tempteam3->tot_points())



    }

	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_top_scorer(int teamId)
{
	if(teamId==0)
    {
        return StatusType::INVALID_INPUT;
    }
    if(teamId<0)
    {

    }
    Node<Team,TeamIDOrder>* tempteam1=illegel_teams.search( teamId);
    Node<Team,TeamIDOrder>* tempteam2=legel_teams.search( teamId);
    if(tempteam2!= nullptr)
    {
       return tempteam2->max();
    }
    if(tempteam1!= nullptr)
    {
        return tempteam1->max();
    }
    return StatusType::INVALID_INPUT;
}

output_t<int> world_cup_t::get_all_players_count(int teamId)
{
	if(teamId==0)
    {
        return StatusType::INVALID_INPUT;
    }
    if(teamId>0)
    {
        Node<Team,TeamIDOrder>* tempteam1=illegel_teams.search( teamId);
        Node<Team,TeamIDOrder>* tempteam2=legel_teams.search( teamId);
        if(tempteam1!= nullptr)
            return tempteam1->get_num_players();
        if(tempteam2!= nullptr)
            return  tempteam2->get_num_players();
    }
    if(teamId<0)//need to see what to do with size
    {

    }
}

StatusType world_cup_t::get_all_players(int teamId, int *const output)
{
	// TODO: Your code goes here
    output[0] = 4001;
    output[1] = 4002;
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_closest_player(int playerId, int teamId)
{
	// TODO: Your code goes here
	return 1006;
}

output_t<int> world_cup_t::knockout_winner(int minTeamId, int maxTeamId)
{
	// TODO: Your code goes here
	return 2;
}

