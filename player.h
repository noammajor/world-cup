#include <iostream>
#include "team.h"

class player {
    team *my_team;
    int team_Id;
    int player_id;
    int games_played;
    int goals;
    int cards;
    bool goalkeeper;
    int teamsGamesPlayed;
public:
    player(int playerId, int teamId, int gamesPlayed, int goals, int cards, bool goalKeeper, Team *team);

    ~player() = default;

    player &operator=(const player &player) = delete;

    player(const player &player) = delete;

    bool operator>(const player &p1) const;

    bool operator==(const player &p1) const;

    bool operator!=(const player &p1) const;

    bool operator<=(const player &p1) const;

    int points() const;

    int gamesplayed() const;

    bool isgoalkeeper() const;

    template<class condition>
    bool order(const player &p1, const condition con) const;
    class playerorder
            {
        playerGoalsOrder();
        ~playerGoalsOrder();
        bool operator() (const player& p1,const player& p2) const;
    };
    class PlayerIDOrder
            {
        bool operator()(const player& p1,const player& p2) const
    };
};