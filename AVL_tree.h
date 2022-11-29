#ifndef AVL_TREE_H
#define AVL_TREE_H

using namespace std;


template<class T, class Cond>
struct Node
{
    Node* father;
    Node* son_smaller;
    Node* son_larger;
    T data;
    int height;
};


template<class T, class Cond>
class AVL_Tree
{

    Node<T, Cond>*  root;
    Cond is_bigger;
    Node<T, Cond>* higher_data;

public:
    AVL_Tree(): root(nullptr), higher_data(nullptr) {}

    AVL_Tree<T, Cond> &operator=(const AVL_Tree<T, Cond> &tree) = delete;

    AVL_Tree<T, Cond>(const AVL_Tree<T, Cond> &tree) = delete;

    ~AVL_Tree();//do after

    void inorderDelete(Node<T, Cond>*);

    int height(Node<T, Cond> *t);

    int bf(Node<T, Cond> *t);

    Node<T, Cond>* search(int data);

    Node<T, Cond>* rotate_LL(Node<T, Cond>* t);

    Node<T, Cond>* rotate_RR(Node<T, Cond>* t);

    Node<T, Cond>* rotate_RL(Node<T, Cond>* t);

    Node<T, Cond>* rotate_LR(Node<T, Cond>* t);

    bool insert_to_tree(const T& data);

    Node<T, Cond>* insert(Node<T, Cond>* t,const T& data);

    Node<T, Cond>* fix_balance (Node<T, Cond>* t);

    bool remove (int num);

    bool isLeaf (Node<T, Cond>* node);

    void remove_leaf (Node<T, Cond>* ptr);

    void remove_half_leaf (Node<T, Cond>* ptr);

    void fix_height (Node<T, Cond>* node);

    void print_tree (int* const output);

    void inorder_print (Node<T, Cond>* node, int* const output);

    int knockout_tree (int min, int max);

    void inorder_knockout (Node<T, Cond>* node, int* output, int min, int max);

    T& get_data(Node<T, Cond>* node) const;

    Node<T, Cond>* get_root() const;

    T& get_higher() const;

};


template<class T, class Cond>
int AVL_Tree<T, Cond>::height(Node<T, Cond>* t)
{
    if (t == nullptr)
        return -1;
    else
    {
        int s_height = (t->son_smaller == nullptr ? -1 : t->son_smaller->height);
        int l_height = (t->son_larger == nullptr ? -1 : t->son_larger->height);
        return max(s_height, l_height) + 1;
    }
}

template<class T, class Cond>
int AVL_Tree<T, Cond>::bf(Node<T, Cond> *t)
{
    int s_height = (t->son_smaller == nullptr ? -1 : t->son_smaller->height);
    int l_height = (t->son_larger == nullptr ? -1 : t->son_larger->height);
    return s_height - l_height;
}

template<class T, class Cond, class S>
Node<T, Cond>* AVL_Tree<T, Cond>::search(const S& data)
{
    if (root == nullptr)
        return nullptr;
    Node<T, Cond>* t= root;
    while(t != nullptr)
    {
        if(is_bigger(data, t->data))
        {
            t = t->son_larger;
        }
        if(is_bigger(t->data, data))
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
        return true;
    }
    return false;
}

template<class T, class Cond>
Node<T, Cond>* AVL_Tree<T, Cond>::insert(Node<T, Cond>* t,const T& data)
{
    if (t == nullptr)
    {
        try
        {
            Node<T, Cond>* base = new(Node<T, Cond>);
            base->data = data;
            base->son_larger = nullptr;
            base->son_smaller = nullptr;
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
bool AVL_Tree<T, Cond>::remove (int num)
{
    Node<T, Cond> *ptr = search(num);
    if (ptr == nullptr)
        return false;
    Node<T, Cond>* ptr_father = ptr->father;
    if (isLeaf(ptr))
    {
        remove_leaf(ptr);
    }
    else if (!ptr->son_larger || !ptr->son_smaller) {
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
            ptr->father = temp1;
            ptr->son_larger = temp1->son_larger;
        }
        else
        {
            while (temp2->son_smaller)
                temp2 = temp2->son_smaller;
            ptr->son_larger = temp2->son_larger;
            if (temp2->son_larger)
                temp2->son_larger->father = ptr;
            temp2->son_larger = temp1;
            temp1->father = temp2;
            temp1 = temp2->father;
            temp2->father = ptr->father;
            if (ptr->father && is_bigger(ptr->father->data, ptr->data))
                ptr->father->son_smaller = temp2;
            else if (ptr->father)
                ptr->father->son_larger = temp2;
            ptr->father = temp1;
            temp1->son_smaller = ptr;
            if (isLeaf(ptr))
                remove_leaf(ptr);
            else
                remove_half_leaf(ptr);
            while (temp2->father)
            {
                temp2 = fix_balance(temp2);
                temp2 = temp2->father;
            }
        }
    }
    fix_height(ptr_father);
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
    if (is_bigger(ptr->father->data, ptr->data))
        ptr->father->son_smaller = nullptr;
    else
        ptr->father->son_larger = nullptr;
}

template<class T, class Cond>
void AVL_Tree<T, Cond>::remove_half_leaf (Node<T, Cond>* ptr)
{
    if (!ptr->son_larger)
    {
        if (ptr->father && is_bigger(ptr->father->data, ptr->data))
            ptr->father->son_smaller = ptr->son_smaller;
        else if (ptr->father)
            ptr->father->son_larger = ptr->son_smaller;
        ptr->son_smaller->father = ptr->father;
    }
    else
    {
        if (ptr->father && is_bigger(ptr->father->data, ptr->data))
            ptr->father->son_smaller = ptr->son_larger;
        else  if (ptr->father)
            ptr->father->son_larger = ptr->son_larger;
        ptr->son_larger->father = ptr->father;
    }
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

template<class T, class Cond>
void AVL_Tree<T, Cond>::print_tree (int* const output)
{
    inorder_print(root, output);
}

template<class T, class Cond>
void AVL_Tree<T, Cond>::inorder_print (Node<T, Cond>* node, int* const output)
{
    static int i = 0;
    if (!node)
        return;
    inorder_print(node->son_smaller, output);
    output[i++] = node->data;
    inorder_print(node->son_larger, output);
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
    static int i = 0;
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
bool AVL_Tree<T, Cond>::isSmallest(const Node<T,Cond>* t)
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
    Node<T, Cond>* temp = player;
    if(isSmallest(temp))
        return nullptr;
    if(temp->son_smaller== nullptr)
    {
        if(temp==temp->father->son_smaller)
        {
            while(temp==temp->father->son_smaller)
            {
                temp=temp->father;
            }
            temp=temp->father;
            return temp;
        }
        if(temp==temp->father->son_larger)
        {
                return temp->father;

        }
    }
    if(temp->son_smaller!= nullptr && temp->son_larger!= nullptr)
    {
        return temp->son_smaller;
    }
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

#endif //AVL_TREE_H