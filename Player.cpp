#include <iostream>
#include "Team.h"
#include "Player.h"




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

template<class condition>
bool Player::order(const Player& p1,const condition con) const
{
    if(con(*this,p1))
    {
        return true;
    }
    else
        return false;
}



bool Player::PlayerGoalsOrder::operator() (const Player& p1,const Player& p2) const
{
    if(p1.goals > p2.goals)
    {
        return true;
    }
    else if(p1 == p2)
    {
        if (p1.cards > p2.cards)
        {
            return true;
        }
        else if (p1.cards == p2.cards)
        {
            if (p1.player_id > p2.player_id)
            {
                return true;
            }
        }
    }
    return false;
}

 bool Player::PlayerIDOrder::operator()(const Player& p1,const Player& p2) const
 {
    return p1 > p2;
 }






