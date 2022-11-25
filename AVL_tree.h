#ifndef AVL_TREE_H
#define AVL_TREE_H

using namespace std;

bool func(int a,  int b)
{
    return a>b;
}

template<class T>
struct Node
{
    Node* father;
    Node* son_smaller;
    Node* son_larger;
    T data;
    int height;
};


template<class T>
class AVL_Tree
{

    Node<T>*  root;
    bool (*is_bigger)(T a, T b);

public:
    explicit AVL_Tree(bool (*func)(T a, T b)): root(nullptr), is_bigger(func){}

    AVL_Tree<T> &operator=(const AVL_Tree<T> &tree) = delete;

    AVL_Tree<T>(const AVL_Tree<T> &tree) = delete;

    ~AVL_Tree() = default; //do after

    int height(Node<T> *t);

    int bf(Node<T> *t);

    Node<T>* search(int data);

    Node<T>* rotate_LL(Node<T>* t);

    Node<T>* rotate_RR(Node<T>* t);

    Node<T>* rotate_RL(Node<T>* t);

    Node<T>* rotate_LR(Node<T>* t);

    bool insert_to_tree(const T& data);

    Node<T>* insert(Node<T>* t,const T& data);

    Node<T>* fix_balance (Node<T>* t);

    bool remove (int num);

    bool isLeaf (Node<T>* node);

    void remove_leaf (Node<T>* ptr);

    void remove_half_leaf (Node<T>* ptr);

    void fix_height (Node<T>* node);

    void print_tree (int* const output);

    void inorder_print (Node<T>* node, int* const output);

};


template<class T>
int AVL_Tree<T>::height(Node<T>* t)
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

template<class T>
int AVL_Tree<T>::bf(Node<T> *t)
{
    int s_height = (t->son_smaller == nullptr ? -1 : t->son_smaller->height);
    int l_height = (t->son_larger == nullptr ? -1 : t->son_larger->height);
    return s_height - l_height;
}

template<class T>
Node<T>* AVL_Tree<T>::search(const int data)
{
    if (root == nullptr)
        return nullptr;
    Node<T>* t= root;
    while(t != nullptr)
    {
        if(t->data == data)
        {
            return t;
        }
        if(is_bigger(t->data, data))
        {
            t = t->son_smaller;
        }
        else
        {
            t = t->son_larger;
        }
    }
    return nullptr;
}

template<class T>
Node<T>* AVL_Tree<T>::rotate_LL(Node<T>* t)
{
    Node<T> *temp1 = t;
    Node<T> *temp2 = t->son_smaller;
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

template<class T>
Node<T>* AVL_Tree<T>::rotate_RR(Node<T>* t)
{
    Node<T> *temp1 = t;
    Node<T> *temp2 = t->son_larger;
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

template<class T>
Node<T>* AVL_Tree<T>::rotate_RL(Node<T>* t)
{
    Node<T> *temp1 = t;  //points to A
    Node<T> *temp2 = t->son_larger;  //points to B
    Node<T> *temp3 = t->son_larger->son_smaller;  //points to C
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

template<class T>
Node<T>* AVL_Tree<T>::rotate_LR(Node<T>* t)
{
    Node<T> *temp1 = t;
    Node<T> *temp2 = t->son_smaller;
    Node<T> *temp3 = t->son_smaller->son_larger;
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

template<class T>
bool AVL_Tree<T>::insert_to_tree(const T& data)
{
    Node<T>* ptr = insert(root, data);
    if (ptr != nullptr)
    {
        root = ptr;
        return true;
    }
    return false;
}

template<class T>
Node<T>* AVL_Tree<T>::insert(Node<T>* t,const T& data)
{
    if (t == nullptr)
    {
        try
        {
            Node<T>* base = new(Node<T>);
            base->data = data;
            base->son_larger = nullptr;
            base->son_smaller = nullptr;
            base->height = 0;
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
            Node<T>* temp = insert(t->son_larger, data);
            if (temp == nullptr)
                return nullptr;
            t->son_larger = temp;
            temp->father = t;
        }
        else if (is_bigger(t->data, data))
        {
            Node<T>* temp = insert(t->son_smaller, data);
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

template<class T>
Node<T>* AVL_Tree<T>::fix_balance (Node<T>* t)
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

template<class T>
bool AVL_Tree<T>::remove (int num)
{
    Node<T> *ptr = search(num);
    if (ptr == nullptr)
        return false;
    Node<T>* ptr_father = ptr->father;
    if (isLeaf(ptr))
    {
        remove_leaf(ptr);
    }
    else if (ptr->son_larger == nullptr || ptr->son_smaller == nullptr) {
        remove_half_leaf(ptr);
    }
    else
    {
        Node<T> *temp1 = ptr->son_larger;
        Node<T> *temp2 = temp1->son_smaller;
        if (temp1->son_smaller == nullptr) {
            if (ptr->father != nullptr && is_bigger(ptr->father->data, ptr->data))
                ptr->father->son_smaller = temp1;
            else if (ptr->father != nullptr)
                ptr->father->son_larger = temp1;
            temp1->father = ptr->father;
            ptr->father = temp1;
            ptr->son_larger = temp1->son_larger;
        } else {
            while (temp2->son_smaller != nullptr)
                temp2 = temp2->son_smaller;
            ptr->son_larger = temp2->son_larger;
            if (temp2->son_larger != nullptr)
                temp2->son_larger->father = ptr;
            temp2->son_larger = temp1;
            temp1->father = temp2;
            temp1 = temp2->father;
            temp2->father = ptr->father;
            if (ptr->father != nullptr && is_bigger(ptr->father->data, ptr->data))
                ptr->father->son_smaller = temp2;
            else if (ptr->father != nullptr)
                ptr->father->son_larger = temp2;
            ptr->father = temp1;
            temp1->son_smaller = ptr;
            if (isLeaf(ptr))
                remove_leaf(ptr);
            else
                remove_half_leaf(ptr);
            while (temp2->father != nullptr) {
                temp2 = fix_balance(temp2);
                temp2 = temp2->father;
            }
        }
    }
    fix_height(ptr_father);
    return true;
}

template<class T>
bool AVL_Tree<T>::isLeaf (Node<T>* node)
{
    if (node->son_larger == nullptr && node->son_smaller == nullptr)
        return true;
    return false;
}

template<class T>
void AVL_Tree<T>::remove_leaf (Node<T>* ptr) {
    if (is_bigger(ptr->father->data, ptr->data))
        ptr->father->son_smaller = nullptr;
    else
        ptr->father->son_larger = nullptr;
}

template<class T>
void AVL_Tree<T>::remove_half_leaf (Node<T>* ptr)
{
    if (ptr->son_larger == nullptr)
    {
        if (ptr->father != nullptr && is_bigger(ptr->father->data, ptr->data))
            ptr->father->son_smaller = ptr->son_smaller;
        else if (ptr->father != nullptr)
            ptr->father->son_larger = ptr->son_smaller;
        ptr->son_smaller->father = ptr->father;
    }
    else
    {
        if (ptr->father != nullptr && is_bigger(ptr->father->data, ptr->data))
            ptr->father->son_smaller = ptr->son_larger;
        else  if (ptr->father != nullptr)
            ptr->father->son_larger = ptr->son_larger;
        ptr->son_larger->father = ptr->father;
    }
}

template<class T>
void AVL_Tree<T>::fix_height (Node<T>* node)
{
    while (node != nullptr && node->height != height(node))
    {
        node->height = height(node);
        node = fix_balance(node);
        node = node->father;
    }
}

template<class T>
void AVL_Tree<T>::print_tree (int* const output)
{
    inorder_print(root, output);
}

template<class T>
void AVL_Tree<T>::inorder_print (Node<T>* node, int* const output)
{
    static int i = 0;
    if (node == nullptr)
        return;
    inorder_print(node->son_smaller, output);
    output[i++] = node->data;
    inorder_print(node->son_larger, output);
}

#endif //AVL_TREE_H
