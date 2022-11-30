#include "Team.h"


int Team::get_num_players() const
{
    return num_players;
}

int Team::get_num_goalkeepers() const
{
    return num_goalkeepers;
}

int Team::get_ID () const
{
    return teamID;
}

void Team::add_points(int points_add)
{
    points += points_add;
}

void Team::add_goals_cards(int to_add)
{
    tot_goals_cards += to_add;
}

void Team::more_game_played()
{
    games_played++;
}

Player* Team::get_top_player() const
{
    return players->get_higher();
}

AVL_Tree<Player*, Player::PlayerIDOrder>* Team::get_players() const
{
    return players;
}

void Team::remove_player(int playerID)
{
    Player* to_remove = players->get_data(players->search(playerID));
    if (!to_remove)
        return;
    num_players--;
    if (to_remove->is_goalkeeper())
        num_goalkeepers--;
    tot_goals_cards -= to_remove->get_goals();
    tot_goals_cards += to_remove->get_cards();
    players->remove(playerID);
}

void Team::add_player (Player* player)
{
    players->insert_to_tree(player);
    num_players++;
    if (player->is_goalkeeper())
        num_goalkeepers++;
    tot_goals_cards += player->get_goals();
    tot_goals_cards -= player->get_cards();
    player->add_games(games_played);
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

int Team::tot_game_points() const
{
    return points + tot_goals_cards;
}

int Team::get_points() const
{
    return points;
}

void Team::match (int* table) const
{
    if (table[0] == 0)
    {
        table[0] = get_ID();
        table[1] = tot_game_points();
    }
    else
    {
        table[1] += tot_game_points() + 3;
        if (tot_game_points() > table[1])
        {
            table[0] = get_ID();
        }
    }
}

Team* Team::new_united_team (Team* t1, int newTeamID)
{
    Team* new_team = new Team(newTeamID, this->points + t1->points);
    new_team->num_players = this->num_players + t1->num_players;
    new_team->num_goalkeepers = this->num_goalkeepers + t1->num_goalkeepers;
    new_team->tot_goals_cards = this->tot_goals_cards + t1->tot_goals_cards;
    new_team->players = this->players->unite(t1->players);

    this->num_players = 0;
    t1->num_players = 0;
    return new_team;
}

bool TeamIDOrder::operator()(const Team* t1, const Team* t2) const
{
    return t1->get_ID() > t2->get_ID();
}

bool TeamIDOrder::operator()(const Team* t1, int num) const
{
    return t1->get_ID() > num;
}

bool TeamIDOrder::operator()(int num, const Team* t1) const
{
    return num > t1->get_ID();
}

