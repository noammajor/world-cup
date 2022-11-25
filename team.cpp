#include "team.h"


Team:: operator int()
{
    return teamID;
}

int Team::get_ID () const
{
    return teamID;
}

void Team::remove_player(int playerID)
{
    Player* to_remove = players->search(playerID);
    num_players--;
    if (is_goalkeeper(to_remove))
        num_goalkeepers--;
    tot_goals_cards -= player->get_goals;
    tot_goals_cards += player->get_cards;
    players->remove(playerID);
}

void Team::add_player (const Player* player)
{
    players->insert(player);
    num_players++;
    if (is_goalkeeper(player))
        num_goalkeepers++;
    tot_goals_cards += player->get_goals;
    tot_goals_cards -= player->get_cards;
    player->team_games(games_played);
}




bool bigger_team (const Team* t1, const Team* t2)
{
    return t1->get_ID() > t2->get_ID();
}
