#include <iostream>
class Team{};
class player
        {
    Team* my_team;
    int team_Id;
    int player_id;
    int games_played;
    int goals;
    int cards;
    bool goalkeeper;
    int teamsGamesPlayed;
        public:
           player(int playerId, int teamId, int gamesPlayed, int goals, int cards, bool goalKeeper,Team* team)
           {
               player_id=playerId;
               games_played=gamesPlayed;
               team_Id=teamId;
               this->goals=goals;//same name, use this ptr
               this->cards=cards;
               goalkeeper=goalKeeper;
               my_team=team;
               teamsGamesPlayed=team->gamesPlayed;
           }
~player()=default;
    player& operator=(const player& player) = delete;
   player(const player& player) = delete;
    bool operator>(const player& p1) const
    {
        if(p1.player_id<this->player_id)
        {
            return true;
        }
        else
            return false;
    }
    bool operator==(const player& p1) const
    {
        if (this->player_id==p1.player_id)
        {
            return true;
        }
        else
            return false;
    }
    bool operator !=(const player& p1) const
    {
        return !(*this==p1);
    }
    bool operator <= (const player& p1) const
    {
        return !(*this>p1);
    }
    int points() const
    {
        return this->goals-this->cards;
    }
    int gamesplayed() const
    {
        return this->games_played;
    }
    bool isgoalkeeper() const
    {
        return this->goalkeeper;
    }

    template<class condition>
    bool order(const player& p1,const condition con) const
    {
        if(con(*this,p1))
        {
            return true;
        }
        else
            return false;

    }
    class playerorder
    {
    public:
playerorder();
~playerorder();
bool operator() (const player& p1,const player& p2) const
{
    if(p1>p2)
    {
        return true;
    }
    if(p1==p2) {
        if (p1.cards > p2.cards) {
            return true;
        }
        if (p1.cards == p2.cards) {
            if (p1.player_id > p2.player_id) {
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }

        {

        }
    }
    else
    {
        return false;
    }
}

    };
};
class playerorder
        {
public:

};
