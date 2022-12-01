#include "worldcup23a1.h"
#include "Player.h"
#include "Team.h"
#include "wet1util.h"

world_cup_t::world_cup_t()
{
}

world_cup_t::~world_cup_t() = default;


StatusType world_cup_t::add_team(int teamId, int points)
{
    if (teamId <= 0 || points < 0)
        return StatusType::INVALID_INPUT;
    try
    {
        Team t1(teamId, points);
        if(!all_teams.insert_to_tree(&t1))
            return StatusType::FAILURE;
    }
    catch (std::bad_alloc&)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    num_teams++;
	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId)
{
    if (teamId <= 0)
        return StatusType::INVALID_INPUT;
    Team* team = all_teams.get_data(all_teams.search(teamId));
    if (team && team->get_num_players() == 0) {
        try
        {
            all_teams.remove(teamId);
        }
        catch (std::bad_alloc&) {
            return StatusType::ALLOCATION_ERROR;
        }
        num_teams--;
        return StatusType::SUCCESS;
    }
	return StatusType::FAILURE;
}

StatusType world_cup_t::add_player(int playerId, int teamId, int gamesPlayed,
                                   int goals, int cards, bool goalKeeper)
{
    if (playerId <= 0 || teamId <= 0 || gamesPlayed < 0 || goals < 0 || cards < 0 || (gamesPlayed == 0 && (goals > 0 || cards > 0)))
        return StatusType::INVALID_INPUT;
    try
    {
        Node<Team*, TeamIDOrder>* node = all_teams.search(teamId);
        if (node == nullptr || playersID.search(playerId))
            return StatusType::FAILURE;
        Team* team = all_teams.get_data(node);
        Player player(playerId, teamId, gamesPlayed, goals, cards, goalKeeper);
        player.change_team(team);
        playersID.insert_to_tree(&player);
        playersGoals.insert_to_tree(&player);
        Node<Player*, Player::PlayerGoalsOrder>* temp2 = playersGoals.search(&player);
        Node<Player*, Player::PlayerGoalsOrder>* temp1 = playersGoals.set_closests_small(temp2);
        if(!(playersGoals.isSmallest(temp1)))
        {
            player.set_closest_bottom(playersGoals.get_data(temp1));
        }
       else
        {
           player.set_lowest(playersGoals.get_data(temp1));
        }

        if (all_teams.get_data(node)->is_legal())
        {
            if (team->get_num_players() == 11 || (team->get_num_goalkeepers() == 1 && goalKeeper))
                legel_teams.insert_to_tree(team);
        }
    }
    catch (std::bad_alloc&)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    num_players++;
	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_player(int playerId)
{
	if(playerId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    try
    {
        Node<Player*, Player::PlayerIDOrder>* player_node = playersID.search(playerId);
        if (!player_node)
            return StatusType::FAILURE;
        Player* player_to_remove = playersID.get_data(player_node);
        Team* team = player_to_remove->get_team();
        team->remove_player(playerId);
        if (!team->is_legal() && (team->get_num_players() == 10 ||
                            (team->get_num_goalkeepers() == 0 && player_to_remove->is_goalkeeper())))
            legel_teams.remove(team->get_ID());
        playersID.remove(playerId);
        playersGoals.remove(player_to_remove);
    }
    catch (std::bad_alloc&)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    num_players--;
    return StatusType::SUCCESS;
}

StatusType world_cup_t::update_player_stats(int playerId, int gamesPlayed,
                                        int scoredGoals, int cardsReceived)
{
    if (playerId <=0 || gamesPlayed < 0 || scoredGoals < 0 || cardsReceived < 0)
    {
        return StatusType::INVALID_INPUT;
    }
    Node<Player*, Player::PlayerIDOrder>* temp = playersID.search(playerId);
    if(temp == nullptr)
    {
        return StatusType::FAILURE;
    }
    Player* player = playersID.get_data(temp);
    player->add_games(gamesPlayed);
    player->add_goals(scoredGoals);
    player->add_cards(cardsReceived);
	return StatusType::SUCCESS;
}

StatusType world_cup_t::play_match(int teamId1, int  teamId2)
{
    if(teamId1 <= 0 || teamId2 <= 0 || teamId2 == teamId1)
    {
        return StatusType::INVALID_INPUT;
    }
    Node<Team*,TeamIDOrder>* node_team1 = all_teams.search( teamId1);
    Node<Team*,TeamIDOrder>* node_team2 = all_teams.search( teamId2);
    if(!node_team1 || !node_team2)
    {
        return StatusType::FAILURE;
    }
    Team* team1 = all_teams.get_data(node_team1);
    Team* team2 = all_teams.get_data(node_team2);
    if (!team1->is_legal() || !team2->is_legal())
        return StatusType::FAILURE;
    if(team1->tot_game_points() == team2->tot_game_points())
    {
        team1->add_points(1);
        team2->add_points(1);
    }
    else
        team1->tot_game_points() > team2->tot_game_points() ? team1->add_points(3) : team2->add_points(3);
    team1->more_game_played();
    team2->more_game_played();
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_num_played_games(int playerId)
{
	if(playerId <= 0)
       return output_t<int>(StatusType::INVALID_INPUT);
    Node<Player*,Player::PlayerIDOrder>* temp1 = playersID.search(playerId);
    if(!temp1)
    {
        return output_t<int>(StatusType::FAILURE);
    }
    Player* player = playersID.get_data(temp1);
    int teams_games_played = player->get_team()->get_games_played();
    return output_t<int>(player->get_games_played() + teams_games_played - player->get_team_games());
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
    if(teamId <= 0)
    {
        return output_t<int>(StatusType::INVALID_INPUT);
    }
    Node<Team*, TeamIDOrder>* node_team = all_teams.search( teamId);
    if(node_team)
    {
        return output_t<int>(all_teams.get_data(node_team)->get_points());
    }
    return output_t<int>(StatusType::FAILURE);
}
//later
StatusType world_cup_t::unite_teams(int teamId1, int teamId2, int newTeamId)
{
    if(teamId1 <= 0 || teamId2 <= 0 || newTeamId <= 0 || teamId2 == teamId1)
        return StatusType::INVALID_INPUT;
    Node<Team*,TeamIDOrder>* node_team1 = all_teams.search( teamId1);
    Node<Team*,TeamIDOrder>* node_team2 = legel_teams.search( teamId2);
    Node<Team*,TeamIDOrder>* node_new_team = all_teams.search( newTeamId);
    if(!node_team1 || !node_team2 || (node_new_team && newTeamId != teamId1 && newTeamId != teamId2))
        return StatusType::FAILURE;
    Team* team1 = all_teams.get_data(node_team1);
    Team* team2 = all_teams.get_data(node_team2);
    Team* newTeam = team1->new_united_team(team2, newTeamId);
    all_teams.insert_to_tree(newTeam);
    if (newTeam->is_legal())
        legel_teams.insert_to_tree(newTeam);
    remove_team(team1->get_ID());
    remove_team(team2->get_ID());
    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_top_scorer(int teamId)
{
	if(teamId == 0)
    {
        return output_t<int>(StatusType::INVALID_INPUT);
    }
    if(teamId < 0)
    {
        if (num_players == 0)
            return output_t<int>(StatusType::FAILURE);
        return output_t<int>(playersID.get_higher()->get_playerID());
    }
    Node<Team*,TeamIDOrder>* node_team = all_teams.search( teamId);
    if(node_team)
    {
       return output_t<int>(all_teams.get_data(node_team)->get_top_player()->get_playerID());
    }
    return output_t<int>(StatusType::INVALID_INPUT);
}

output_t<int> world_cup_t::get_all_players_count(int teamId)
{
	if(teamId == 0)
    {
        return output_t<int>(StatusType::INVALID_INPUT);
    }
    if(teamId > 0)
    {
        Node<Team*, TeamIDOrder>* node_team = all_teams.search( teamId);
        if(node_team)
            return output_t<int>(all_teams.get_data(node_team)->get_num_players());
    }
    return output_t<int>(num_players);
}
/*
StatusType world_cup_t::get_all_players(int teamId, int *const output)
{
	if (teamId == 0 || !output)
        return StatusType::FAILURE;
    else if (teamId < 0)
    {
        if (num_players == 0)
            return StatusType::FAILURE;
        try
        {
            playersGoals.print_tree(output);
        }
        catch (std::bad_alloc&)
        {
            return StatusType::ALLOCATION_ERROR;
        }
    }
    else
    {
        try
        {
            Node<Team*,TeamIDOrder>* node_team = all_teams.search(teamId);
            if (!node_team)
                return StatusType::FAILURE;
            Team* team = all_teams.get_data(node_team);
            if (team->get_num_players() == 0)
                return StatusType::FAILURE;
            team->get_players()->print_tree(output);
        }
        catch (std::bad_alloc&)
        {
            return StatusType::ALLOCATION_ERROR;
        }
    }
	return StatusType::SUCCESS;
}*/

output_t<int> world_cup_t::get_closest_player(int playerId, int teamId)
{
	if (playerId <= 0 || teamId <= 0)
        return output_t<int>(StatusType::INVALID_INPUT);
    Node<Team*,TeamIDOrder>* ptr = all_teams.search(teamId);
    Node<Player*, Player::PlayerIDOrder>* ptr1= ptr->get_data_Node()->get_players()->search(playerId);
    if(ptr1== nullptr)
        return output_t<int>(StatusType::FAILURE);
    return output_t<int>(ptr1->get_data_Node()->get_closest());
}

output_t<int> world_cup_t::knockout_winner(int minTeamId, int maxTeamId)
{
	if (minTeamId < 0 || maxTeamId < 0 || maxTeamId < minTeamId)
        return output_t<int>(StatusType::INVALID_INPUT);
    int winner = legel_teams.knockout_tree(minTeamId, maxTeamId);
    if (winner == 0)
        return output_t<int>(StatusType::FAILURE);
    return output_t<int>(winner);
}

