#include <iostream>
#include "AVL_tree.h"
#include <cstdlib>
#include <set>

using namespace std;


int main() {
    AVL_Tree<int, intBigger> tree;
    set<int> noam;
/*
    AVL_Tree<Player*, Player::PlayerIDOrder> tree;

    Player* p1 = new Player(1,2,3,4,5, true);
    Player* p2 = new Player(5,3,3,4,5, false);
    Player* p3 = new Player(6,2,3,4,5, false);*/
    /*tree.insert_to_tree(7);
    tree.insert_to_tree(1);
    tree.insert_to_tree(5);
    tree.insert_to_tree(4);
    tree.insert_to_tree(4);
    tree.insert_to_tree(3);
    tree.insert_to_tree(2);
    tree.remove(3);
    tree.insert_to_tree(1);*/
    for (int i = 0, k = 0; i < 1000; i++, k++) {
        int j = rand();
        if (i==931 || i==932)
            cout<<j<<'\n';

        tree.insert_to_tree(j);
        noam.insert(j);
        if (k % 10 == 0)
        {
            tree.remove(j);
            noam.erase(j);
        }
    }
        cout << noam.size() << "\n" ;
        cout << tree.height(tree.get_root()) << '\n' << tree.get_size() << '\n';
        /*int* to_print = new int[940];
        tree.array_tree(to_print);
        cout << tree.height(tree.get_root()) << '\n' << tree.get_size() <<'\n';
        for (int i=0; i<940; i++) {
            cout << to_print[i] << '\n';
        }*/
        return 0;


}