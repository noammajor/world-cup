#ifndef MAIN_CPP_TEAM_H
#define MAIN_CPP_TEAM_H

#include "AVL_tree.h"

class Team
{
    int teamID;
    int points;
    int num_players;
    int num_goalkeepers;
    int tot_goals_cards;
    int games_played;
    AVL_Tree<Player*, playerGoalsOrder> *players;

public:
    Team(int ID, int points): teamID(ID), points(points), num_players(0), num_goalkeepers(0),
        tot_goals_cards(0),games_played(0), players(nullptr){}

    Team& operator=(const Team&) = delete;

    Team(const Team&) = delete;

    ~Team() = default; //do later

    explicit operator int();

    int get_ID () const;

    void remove_player(int playerID);

    void add_player (const Player* player);

    int get_games_played() const;

    bool is_legal() const;

    bool operator >(const Team* p1) const;





};

class TeamIDOrder
{
public:
    TeamIDOrder();
    ~TeamIDOrder();
    bool operator()(const Team* t1,const Team* t2) const
    {
        return t1->get_ID() > t2->get_ID();
    }
};


#endif //MAIN_CPP_TEAM_H
