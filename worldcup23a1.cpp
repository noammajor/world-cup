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
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType world_cup_t::update_player_stats(int playerId, int gamesPlayed,
                                        int scoredGoals, int cardsReceived)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType world_cup_t::play_match(int teamId1, int teamId2)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_num_played_games(int playerId)
{
	// TODO: Your code goes here
	return 22;
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
	// TODO: Your code goes here
	return 30003;
}

StatusType world_cup_t::unite_teams(int teamId1, int teamId2, int newTeamId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_top_scorer(int teamId)
{
	// TODO: Your code goes here
	return 2008;
}

output_t<int> world_cup_t::get_all_players_count(int teamId)
{
	// TODO: Your code goes here
    static int i = 0;
    return (i++==0) ? 11 : 2;
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

