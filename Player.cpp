#include <iostream>
#include "Team.h"
#include "Player.h"

void Player::set_closest_bottom(Player* p)
{
   this->closest_bottom = p;
    if(p->closest_top == nullptr)
    {
        p->closest_top = this;
        this->closest_top = nullptr;
        return;
    }
    closest_top = p->closest_top;
    p->closest_top->closest_bottom = this;
    p->closest_top = this;
}

void Player::set_lowest(Player* lowest_player)
{
    this->closest_bottom = nullptr;
    this->closest_top = lowest_player;
}

int Player::get_closest() const
{
    int distance_top;
    int distance_bottom;
    distance_top=this->goals-(this->closest_top->goals);
    distance_bottom=-(this->goals-(this->closest_bottom->goals));
    if(distance_bottom!=distance_top)
    {
        return distance_top>distance_bottom ? this->closest_bottom->player_id : this->closest_top->player_id;
    }
    else
    {
        distance_bottom=this->cards-(this->closest_bottom->cards);
        distance_top=this->cards-(this->closest_top->cards);
        if(distance_top<0)
        {
            distance_top=-distance_top;
        }
        if(distance_bottom<0)
        {
            distance_bottom=-distance_bottom;
        }
        if(distance_bottom!=distance_top)
        {
            return distance_top>distance_bottom ? this->closest_bottom->player_id : this->closest_top->player_id;
        }
        else
        {
           distance_bottom=this->closest_bottom->player_id;
           distance_top=this->closest_top->player_id;
            return distance_top>distance_bottom ? this->closest_bottom->player_id : this->closest_top->player_id;
        }
    }
}
bool Player::operator >(const Player& p1) const
{
    if(p1.player_id  < this->player_id)
    {
        return true;
    }
    else
        return false;
}

void Player::add_games(int gamesPlayed)
{
    games_played += gamesPlayed;
}

void Player::add_goals(int scoredGoals)
{
    goals += scoredGoals;
    my_team->add_goals_cards(scoredGoals);
}

void Player::add_cards(int cardsReceived)
{
    cards += cardsReceived;
    my_team->add_goals_cards(-cardsReceived);
}

Team* Player::get_team() const
{
    return my_team;
}

void Player::change_team (Team* team)
{
    my_team = team;
    team_Id = team->get_ID();
    teamsGamesPlayed = 0;
}

bool Player::operator ==(const Player& p1) const
{
    if (this->player_id == p1.player_id)
    {
        return true;
    }
    else
        return false;
}

bool Player::operator !=(const Player& p1) const
{
    return !(*this == p1);
}

bool Player::operator <=(const Player& p1) const
{
    return !(*this>p1);
}

int Player::points() const
{
    return this->goals - this->cards;
}

int Player::get_games_played() const
{
    return this->games_played;
}

bool Player::is_goalkeeper() const
{
    return goalkeeper;
}

int Player::get_goals() const
{
    return goals;
}

int Player::get_cards() const
{
    return goals;
}

int Player::get_teamID() const
{
    return team_Id;
}

int Player::get_playerID() const
{
    return player_id;
}

int Player::get_team_games() const
{
    return teamsGamesPlayed;
}

template<class Condition>
bool Player::order(const Player& p1,const Condition con) const
{
    if(con(*this,p1))
    {
        return true;
    }
    else
        return false;
}



bool Player::PlayerGoalsOrder::operator() (const Player* p1,const Player* p2) const
{
    if(p1->goals > p2->goals)
    {
        return true;
    }
    else if(p1->goals == p2->goals)
    {
        if (p1->cards > p2->cards)
        {
            return true;
        }
        else if (p1->cards == p2->cards)
        {
            if (p1->player_id > p2->player_id)
            {
                return true;
            }
        }
    }
    return false;
}

 bool Player::PlayerIDOrder::operator()(const Player* p1, const Player* p2) const
 {
    return p1->get_playerID() > p2->get_playerID();
 }

bool Player::PlayerIDOrder::operator()(const Player* p1, int num) const
{
    return p1->get_playerID() > num;
}

bool Player::PlayerIDOrder::operator()(int num, const Player* p1) const
{
    return num > p1->get_playerID();
}



