#include "Team.h"


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

int Team::get_games_played() const
{
    return games_played;
}

bool Team::is_legal() const
{
    if (num_goalkeepers > 0 && num_players >= 11)
        return true;
    return false;
}

bool Team::operator >(const Team* p1) const
{
    if(p1->teamID  < this->teamID)
    {
        return true;
    }
    else
        return false;
}





