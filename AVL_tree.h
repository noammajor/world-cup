#ifndef AVL_TREE
#define AVL_TREE

#include "Team.h"
#include <stdio.h>
#include <math.h>

using namespace std;


template<class T, class Cond>
struct Node
{
    Node* father;
    Node* son_smaller;
    Node* son_larger;
    T data;
    int height;
    T& get_data_Node();
};


template<class T, class Cond>
class AVL_Tree
{

    Node<T, Cond>* root;
    Node<T, Cond>* higher_data;
    int size;

public:
    AVL_Tree(): root(nullptr), higher_data(nullptr), size(0) {}

    AVL_Tree(Node<T, Cond>*  root, Node<T, Cond>* higher_data, int size): root(root), higher_data(higher_data), size(size){}

    AVL_Tree<T, Cond> &operator=(const AVL_Tree<T, Cond> &tree) = delete;

    AVL_Tree<T, Cond>(const AVL_Tree<T, Cond> &tree) = delete;

    ~AVL_Tree();//do after

    AVL_Tree<T, Cond>* unite(AVL_Tree<T, Cond>* t2);

    void postorderDelete(Node<T,Cond>* p);

    int height(Node<T, Cond> *t);

    int bf(Node<T, Cond> *t);

    template<class S>
    Node<T, Cond>* search(const S& data);

    Node<T, Cond>* rotate_LL(Node<T, Cond>* t);

    Node<T, Cond>* rotate_RR(Node<T, Cond>* t);

    Node<T, Cond>* rotate_RL(Node<T, Cond>* t);

    Node<T, Cond>* rotate_LR(Node<T, Cond>* t);

    bool insert_to_tree(const T& data);

    Node<T, Cond>* insert(Node<T, Cond>* t,const T& data);

    Node<T, Cond>* fix_balance (Node<T, Cond>* t);

    template<class S>
    bool remove (S num);

    bool isLeaf (Node<T, Cond>* node);

    void remove_leaf (Node<T, Cond>* ptr);

    void remove_half_leaf (Node<T, Cond>* ptr);

    void fix_height (Node<T, Cond>* node);

    //void print_tree (int* const output);

    void array_tree (T* const output);

    //void inorder_print (Node<T, Cond>* node, int* const output);

    void inorder_array (Node<T, Cond>* node, T* const output);

    int knockout_tree (int min, int max);

    void inorder_knockout (Node<T, Cond>* node, int* output, int min, int max);

    void inorder_change (Node<T, Cond>* node, T* t);

    T& get_data(Node<T, Cond>* node) const;

    Node<T, Cond>* get_root() const;

    T& get_higher() const;

    bool isSmallest(const Node<T,Cond>* t) const;

    Node<T,Cond>* set_closests_small(Node<T,Cond>* player) const;

    void merge (T* united, T* t1, int t1_size, T* t2, int t2_size);

    Node<T, Cond>* create_tree(int height);

    int get_size() const;

};

template<class T, class Cond>
T& Node<T, Cond>::get_data_Node()
{
    return data;
}

template<class T, class Cond>
int AVL_Tree<T, Cond>::get_size() const
{
    return size;
}

template<class T, class Cond>
int AVL_Tree<T, Cond>::height(Node<T, Cond>* t)
{
    if (t == nullptr)
        return -1;
    else
    {
        int s_height = (t->son_smaller == nullptr ? -1 : t->son_smaller->height);
        int l_height = (t->son_larger == nullptr ? -1 : t->son_larger->height);
        return s_height > l_height ? s_height + 1 : l_height + 1;
    }
}

template<class T, class Cond>
int AVL_Tree<T, Cond>::bf(Node<T, Cond> *t)
{
    int s_height = (t->son_smaller == nullptr ? -1 : t->son_smaller->height);
    int l_height = (t->son_larger == nullptr ? -1 : t->son_larger->height);
    return s_height - l_height;
}

template<class T, class Cond>
template<class S>
Node<T, Cond>* AVL_Tree<T, Cond>::search(const S& data)
{
    Cond is_bigger;
    if (root == nullptr)
        return nullptr;
    Node<T, Cond>* t= root;
    while(t != nullptr)
    {
        if(is_bigger(data, t->data))
        {
            t = t->son_larger;
        }
        else if(is_bigger(t->data, data))
        {
            t = t->son_smaller;
        }
        else
        {
            return t;
        }
    }
    return nullptr;
}

template<class T, class Cond>
Node<T, Cond>* AVL_Tree<T, Cond>::rotate_LL(Node<T, Cond>* t)
{
    Node<T, Cond> *temp1 = t;
    Node<T, Cond> *temp2 = t->son_smaller;
    temp1->son_smaller = temp2->son_larger;
    if (temp1->son_smaller)
        temp1->son_smaller->father = temp1;
    temp2->son_larger = temp1;
    temp2->father = temp1->father;
    temp1->father = temp2;
    temp2->height = height(temp2);
    temp1->height = height(temp1);
    return temp2;
}

template<class T, class Cond>
Node<T, Cond>* AVL_Tree<T, Cond>::rotate_RR(Node<T, Cond>* t)
{
    Node<T, Cond> *temp1 = t;
    Node<T, Cond> *temp2 = t->son_larger;
    temp1->son_larger = temp2->son_smaller;
    if (temp1->son_larger)
        temp1->son_larger->father = temp1;
    temp2->son_smaller = temp1;
    temp2->father = temp1->father;
    temp1->father = temp2;
    temp2->height = height(temp2);
    temp1->height = height(temp1);
    return temp2;
}

template<class T, class Cond>
Node<T, Cond>* AVL_Tree<T, Cond>::rotate_RL(Node<T, Cond>* t)
{
    Node<T, Cond> *temp1 = t;  //points to A
    Node<T, Cond> *temp2 = t->son_larger;  //points to B
    Node<T, Cond> *temp3 = t->son_larger->son_smaller;  //points to C
    temp1->son_larger = temp3->son_smaller;  //right side of A point to left of C
    if (temp3->son_smaller)
        temp3->son_smaller->father = temp1;  //right side of C points to new father A
    temp2->son_smaller = temp3->son_larger;  //left side of B points to right side of C
    if (temp2->son_smaller)
        temp2->son_smaller->father = temp2;  //right side of C points to new father B
    temp3->son_smaller = temp1;  //left side C points to A
    temp3->son_larger = temp2;  //right side C points to B
    temp1->father = temp3;  //A points to father C
    temp3->father = t->father;  //C points to A's father (C's father pointer)
    temp2->father = temp3;  //B points to father C
    temp1->height = height(temp1);
    temp2->height = height(temp2);
    temp3->height = height(temp3);
    return temp3;  // return new C to be t.
}

template<class T, class Cond>
Node<T, Cond>* AVL_Tree<T, Cond>::rotate_LR(Node<T, Cond>* t)
{
    Node<T, Cond> *temp1 = t;
    Node<T, Cond> *temp2 = t->son_smaller;
    Node<T, Cond> *temp3 = t->son_smaller->son_larger;
    temp1->son_smaller = temp3->son_larger;
    if (temp3->son_larger)
        temp3->son_larger->father = temp1;
    temp2->son_larger = temp3->son_smaller;
    if (temp2->son_larger)
        temp2->son_larger->father = temp2;
    temp3->son_larger = temp1;
    temp3->son_smaller = temp2;
    temp1->father = temp3;
    temp3->father = t->father;
    temp2->father = temp3;
    temp1->height = height(temp1);
    temp2->height = height(temp2);
    temp3->height = height(temp3);
    return temp3;
}

template<class T, class Cond>
bool AVL_Tree<T, Cond>::insert_to_tree(const T& data)
{
    Node<T, Cond>* ptr = insert(root, data);
    if (ptr != nullptr)
    {
        root = ptr;
        size++;
        return true;
    }
    return false;
}

template<class T, class Cond>
Node<T, Cond>* AVL_Tree<T, Cond>::insert(Node<T, Cond>* t,const T& data)
{
    Cond is_bigger;
    if (t == nullptr)
    {
        try
        {
            Node<T, Cond>* base = new(Node<T, Cond>);
            base->data = data;
            base->son_larger = nullptr;
            base->son_smaller = nullptr;
            base->father = nullptr;
            base->height = 0;
            if (!root)
                higher_data = base;
            return base;
        }
        catch (...)
        {
            throw;
        }
    }
    else
    {
        if (is_bigger(data, t->data))
        {
            Node<T, Cond>* temp = insert(t->son_larger, data);
            if (temp == nullptr)
                return nullptr;
            t->son_larger = temp;
            temp->father = t;
            if (higher_data == t)
                higher_data = temp;
        }
        else if (is_bigger(t->data, data))
        {
            Node<T, Cond>* temp = insert(t->son_smaller, data);
            if (temp == nullptr)
                return nullptr;
            t->son_smaller = temp;
            temp->father = t;
        }
        else
        {
            return nullptr;
        }
        t = fix_balance(t);
        return t;
    }
}

template<class T, class Cond>
Node<T, Cond>* AVL_Tree<T, Cond>::fix_balance (Node<T, Cond>* t)
{
    if (bf(t) == 2 && bf(t->son_smaller) >= 0)
    {
        t = rotate_LL(t);
    }
    else if (bf(t) == 2 && bf(t->son_smaller) < 0) {
        t = rotate_LR(t);
    }
    else if (bf(t) == -2 && bf(t->son_larger) <= 0) {
        t = rotate_RR(t);
    }
    else if (bf(t) == -2 && bf(t->son_larger) == 1) {
        t = rotate_RL(t);
    }
    else
        t->height = height(t);
    return t;
}

template<class T, class Cond>
template<class S>
bool AVL_Tree<T, Cond>::remove (S num)
{
    Cond is_bigger;
    Node<T, Cond> *ptr = search(num);
    if (ptr == nullptr)
        return false;
    Node<T, Cond>* ptr_father = ptr->father;
    if (isLeaf(ptr))
    {
        remove_leaf(ptr);
    }
    else if (!ptr->son_larger || !ptr->son_smaller)
    {
        remove_half_leaf(ptr);
    }
    else
    {
        Node<T, Cond> *temp1 = ptr->son_larger;
        Node<T, Cond> *temp2 = temp1->son_smaller;
        if (!temp1->son_smaller)
        {
            if (ptr->father && is_bigger(ptr->father->data, ptr->data))
                ptr->father->son_smaller = temp1;
            else if (ptr->father)
                ptr->father->son_larger = temp1;
            temp1->father = ptr->father;
            temp1->son_smaller = ptr->son_smaller;
            ptr->son_smaller->father = temp1;
            delete ptr;
        }
        else
        {
            while (temp2->son_smaller)
                temp2 = temp2->son_smaller;
            temp2->father->son_smaller = temp2->son_larger;
            if (temp2->son_larger)
                temp2->son_larger->father = temp2->father;
            temp2->son_larger = temp1;
            temp1->father = temp2;
            temp1 = temp2->father; //using the  same pointer for bf
            temp2->father = ptr->father;
            if (ptr->father && is_bigger(ptr->father->data, ptr->data))
                ptr->father->son_smaller = temp2;
            else if (ptr->father)
                ptr->father->son_larger = temp2;
            if (ptr->son_smaller)
            {
                temp2->son_smaller = ptr->son_smaller;
                ptr->son_smaller->father = temp2;
            }
            while (temp1->father)
            {
                temp1 = fix_balance(temp1);
                temp1 = temp1->father;
            }
        }
    }
    fix_height(ptr_father);
    size--;
    return true;
}

template<class T, class Cond>
bool AVL_Tree<T, Cond>::isLeaf (Node<T, Cond>* node)
{
    if (!node->son_larger && !node->son_smaller)
        return true;
    return false;
}

template<class T, class Cond>
void AVL_Tree<T, Cond>::remove_leaf (Node<T, Cond>* ptr) {
    Cond is_bigger;
    if (ptr->father)
    {
        if (is_bigger(ptr->father->data, ptr->data))
            ptr->father->son_smaller = nullptr;
        else
            ptr->father->son_larger = nullptr;
    }
    else
    {
       root = nullptr;
    }
    delete ptr;
}

template<class T, class Cond>
void AVL_Tree<T, Cond>::remove_half_leaf (Node<T, Cond>* ptr)
{
    Cond is_bigger;
    if (!ptr->son_larger)
    {
        if (ptr->father && is_bigger(ptr->father->data, ptr->data))
            ptr->father->son_smaller = ptr->son_smaller;
        else if (ptr->father)
            ptr->father->son_larger = ptr->son_smaller;
        ptr->son_smaller->father = ptr->father;
        if (!ptr->son_smaller->father)
            root = ptr->son_smaller->father;
    }
    else
    {
        if (ptr->father && is_bigger(ptr->father->data, ptr->data))
            ptr->father->son_smaller = ptr->son_larger;
        else  if (ptr->father)
            ptr->father->son_larger = ptr->son_larger;
        ptr->son_larger->father = ptr->father;
        if (!ptr->son_larger->father)
            root = ptr->son_larger->father;
    }
    delete ptr;
}

template<class T, class Cond>
void AVL_Tree<T, Cond>::fix_height (Node<T, Cond>* node)
{
    while (node && node->height != height(node))
    {
        node->height = height(node);
        node = fix_balance(node);
        node = node->father;
    }
}
/*
template<class T, class Cond>
void AVL_Tree<T, Cond>::print_tree (int* const output)
{
    inorder_print(root, output);
}*/

template<class T, class Cond>
void AVL_Tree<T, Cond>::array_tree (T* const output)
{
    inorder_array(root, output);
}
/*
template<class T, class Cond>
void AVL_Tree<T, Cond>::inorder_print (Node<T, Cond>* node,  int* const output)
{
    static int i = 0;
    if (!node)
        return;
    inorder_print(node->son_smaller, output);
    output[i++] = node->data->get_playerID();
    inorder_print(node->son_larger, output);
}*/

template<class T, class Cond>
void AVL_Tree<T, Cond>::inorder_array (Node<T, Cond>* node,  T* const output)
{
    static int i = 0;
    if (!node)
        return;
    inorder_array(node->son_smaller, output);
    output[i++] = node->data;
    inorder_array(node->son_larger, output);
}

template<class T, class Cond>
int AVL_Tree<T, Cond>::knockout_tree (int min, int max)
{
    int* table = new int[2];
    table[0] = 0;
    inorder_knockout(root, table, min, max);
    return table[0];
}

template<class T, class Cond>
void AVL_Tree<T, Cond>::inorder_knockout (Node<T, Cond>* node, int* output, int min, int max)
{
    Cond is_bigger;
    if (!node)
        return;
    if (is_bigger(node->data, min))
        inorder_knockout(node->son_smaller, output, min, max);
    if (is_bigger(node->data, min) && is_bigger(max, node->data))
    {
        if (is_bigger(node->data, output[0]))
        {
            node->data->match(output);
        }
    }
    if(is_bigger(max, node->data))
        inorder_knockout(node->son_larger, output, min, max);
}

template<class T, class Cond>
void AVL_Tree<T, Cond>::inorder_change (Node<T, Cond>* node, T* t)
{
    if (!node)
        return;
    inorder_change(node->son_smaller, t);
    node->data->change_team(t);
    inorder_change(node->son_larger, t);
}

template<class T, class Cond>
T& AVL_Tree<T, Cond>::get_data(Node<T, Cond>* node) const
{
    return node->data;
}

template<class T, class Cond>
Node<T, Cond>* AVL_Tree<T, Cond>::get_root() const
{
    return root;
}

template<class T, class Cond>
T& AVL_Tree<T, Cond>::get_higher() const
{
    return higher_data->data;
}

template<class T, class Cond>
bool AVL_Tree<T, Cond>::isSmallest(const Node<T,Cond>* t) const
{
    Node<T,Cond>* temp = root;
    while(temp!= nullptr)
        temp=temp->son_smaller;
    if(t==temp)
        return true;
    return false;
}

template<class T, class Cond>
Node<T,Cond>* AVL_Tree<T, Cond>::set_closests_small(Node<T,Cond>* player) const
{
    if(isSmallest(player))
        return nullptr;
    Node<T, Cond>* temp = player;
    if(temp->son_smaller == nullptr)
    {
        if(temp == temp->father->son_smaller)
        {
            while(temp==temp->father->son_smaller)
            {
                temp=temp->father;
            }
            temp=temp->father;
            return temp;
        }
        if(temp == temp->father->son_larger)
        {
                return temp->father;
        }
    }
    return temp->son_smaller;
}

template<class T, class Cond>
void AVL_Tree<T,Cond>::postorderDelete(Node<T,Cond>* p)
{
    if (p== nullptr)
        return;
    postorderDelete(p->son_smaller);
    postorderDelete(p->son_larger);
    delete p;
}

template<class T, class Cond>
AVL_Tree<T,Cond>::~AVL_Tree()
{
    postorderDelete(root);
}

/*
template<class T, class Cond>
Node<T,Cond> AVL_Tree<T, Cond>::set_closests_large(int data)
{
    Node<T, Cond>* temp = search(data);
    if(isLargest(temp))
        return nullptr;
    if(temp->son_larger== nullptr)
    {
        if(temp==temp->father->son_smaller)
            return temp->father;
        if(temp==temp->father->son_larger)
        {
            while(temp==temp->father->son_larger)
            {
                temp=temp->father;
            }
            temp=temp->father;
            return temp;
        }
    }
    if(temp->son_larger!= nullptr && temp->son_smaller!= nullptr)
    {
        return temp->son_larger;
    }
}
*/








template<class T, class Cond>
AVL_Tree<T, Cond>* AVL_Tree<T, Cond>::unite(AVL_Tree<T, Cond>* t2)
{
    Cond is_bigger;
    T* t1_data = new T[this->size];
    T* t2_data = new  T[t2->size];
    this->array_tree(t1_data);
    t2->array_tree(t2_data);
    T* united_data = new T[this->size + t2->size];
    merge(united_data, t1_data, this->size, t2_data, t2->size);
    Node<T, Cond>* higher = (is_bigger(this->higher_data->data, t2->higher_data->data)? this->higher_data : t2->higher_data);
    AVL_Tree<T, Cond>* tree = new AVL_Tree<T, Cond>(create_tree(log(this->size + t2->size)), higher,this->size + t2->size);
    delete[] t1_data;
    delete[] t2_data;
    delete[] united_data;
    return tree;
}

template<class T, class Cond>
void AVL_Tree<T, Cond>::merge (T* united, T* t1, int t1_size, T* t2, int t2_size)
{
    Cond is_bigger;
    int i = 0;
    int j = 0;
    int k = 0;
    while (i < t1_size && j < t2_size)
        is_bigger(t1[i], t2[j]) ? united[k++] = t1[i++] : united[k++] = t2[j++];
    while (i  < t1_size)
        united[k++] =t1[i++];
    while (j < t2_size)
        united[k++] =  t2[j++];
}

template<class T, class Cond>
Node<T, Cond>* AVL_Tree<T, Cond>::create_tree(int height)
{
    if (height == 0)
        return nullptr;
    Node<T, Cond>* node = new Node<T, Cond>;
    node->son_larger = create_tree(height - 1);
    node->son_smaller = create_tree(height - 1);
    return node;
}


class intBigger
{
public:
    intBigger()= default;

    ~intBigger()= default;

    bool operator()(const int &p1, const int &p2) const
    {
        return p1 > p2;
    }
};

#endif //AVL_TREE