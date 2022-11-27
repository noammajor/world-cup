#include <iostream>
#include "Team.h"

class Player
{
    Team *my_team;
    int team_Id;
    int player_id;
    int games_played;
    int goals;
    int cards;
    bool goalkeeper;
    int teamsGamesPlayed;

public:
    Player(int playerId, int teamId, int gamesPlayed, int goals, int cards, bool goalKeeper, Team *team):
            player_id(playerId), games_played(gamesPlayed), team_Id(teamId), goals(goals), cards(cards),
            goalkeeper(goalKeeper), my_team(team), teamsGamesPlayed(team->get_games_played()){}

    ~Player() = default;

    Player &operator=(const Player &player) = delete;

    Player(const Player &player) = delete;

    bool operator>(const Player &p1) const;

    bool operator==(const Player &p1) const;

    bool operator!=(const Player &p1) const;

    bool operator<=(const Player &p1) const;

    int points() const;

    int get_games_played() const;

    bool is_goalkeeper() const;

    int get_goals() const;

    int get_cards() const;

    template<class condition>
    bool order(const Player &p1, const condition con) const;

    class PlayerGoalsOrder
    {
        PlayerGoalsOrder();
        ~PlayerGoalsOrder();
        bool operator() (const Player& p1,const Player& p2) const;
    };

    class PlayerIDOrder
    {
        bool operator()(const Player& p1,const Player& p2) const;
    };

};