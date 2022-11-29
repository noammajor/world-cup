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
    Player* closest_top;
    Player* closest_bottom;


public:

    Player(int playerId, int teamId, int gamesPlayed, int goals, int cards, bool goalKeeper, Team *team):
            my_team(team), team_Id(teamId), player_id(playerId), games_played(gamesPlayed),  goals(goals), cards(cards),
            goalkeeper(goalKeeper), teamsGamesPlayed(team->get_games_played()),closest_bottom(nullptr),closest_top(nullptr) {}

    Player(int playerID);

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

    int get_teamID() const;

    int get_playerID() const;

    int get_team_games() const;

    void add_games(int gamesPlayed);

    void add_goals(int scoredGoals);

    void add_cards(int cardsReceived);

    Team* get_team() const;

    void set_closest_bottom(Player* p);
    void set_lowest();

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
        bool operator()(const Player& p1, const Player& p2) const;
        bool operator()(const Player& p1, int num) const;
        bool operator()(int num, const Player& p1) const;
    };

};