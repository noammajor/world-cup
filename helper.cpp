#include <iostream>
#include "AVL_tree.h"

using namespace std;

int main()
{
    AVL_Tree<int> tree;

    tree.insert_to_tree(5);
    tree.insert_to_tree(7);
    tree.insert_to_tree(2);
    tree.insert_to_tree(6);
    tree.insert_to_tree(9);
    tree.insert_to_tree(1);
    int* to_print = new int[6];
    tree.print_tree(to_print);
    for (int i=0; i<6; i++)
        cout << to_print[i];

    return 0;

}

