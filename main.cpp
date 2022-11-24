#include <iostream>


template<class T>
class AVL_Tree
 {

    struct Node
    {
        Node* father;
        Node* son_smaller;
        Node* son_larger;
        T data;
        int height;
    };

    Node*  root;

public:
    AVL_Tree()
    {
        root = nullptr;
    }

    AVL_Tree<T> &operator=(const AVL_Tree<T> &tree) = delete;

    AVL_Tree<T>(const AVL_Tree<T> &tree) = delete;

    ~AVL_Tree(); //do after

    int height(Node *t)
    {
        if (t == nullptr)
            return -1;
        else {
            int s_height = t->son_smaller->height;
            int l_height = t->son_larger->height;
            return std::max(s_height, l_height) + 1;
        }
    }

    int bf(Node *t)
    {
        return t->son_smaller->height - t->son_larger->height;
    }

    Node* search(const int data)
    {
        if (root == nullptr)
            return nullptr;
        Node* t= root;
        while(t != nullptr)
        {
            if(t->data == data)
            {
                return t;
            }
            if(t->data > data)
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

    Node* rotate_LL(Node* t) {
        Node *temp1 = t;
        Node *temp2 = t->son_smaller;
        temp1->son_smaller = temp2->son_larger;
        temp1->son_smaller->father = temp1;
        temp2->son_larger = temp1;
        temp2->father = temp1->father;
        temp1->father = temp2;
        temp2->height = height(temp2);
        temp1->height = height(temp1);
        return temp2;
    }

    Node* rotate_RR(Node* t) {
        Node *temp1 = t;
        Node *temp2 = t->son_larger;
        temp1->son_larger = temp2->son_smaller;
        temp1->son_larger->father = temp1;
        temp2->son_smaller = temp1;
        temp2->father = temp1->father;
        temp1->father = temp2;
        temp2->height = height(temp2);
        temp1->height = height(temp1);
        return temp2;
    }

    Node* rotate_RL(Node* t)
    {
        Node *temp1 = t;  //points to A
        Node *temp2 = t->son_larger;  //points to B
        Node *temp3 = t->son_larger->son_smaller;  //points to C
        temp1->son_larger = temp3->son_smaller;  //right side of A point to left of C
        temp3->son_smaller->father = temp1;  //right side of C points to new father A
        temp2->son_smaller = temp3->son_larger;  //left side of B points to right side of C
        temp3->son_larger->father = temp2;  //right side of C points to new father B
        temp3->son_smaller = temp1;  //left side C points to A
        temp3->son_larger = temp2;  //right side C points to B
        temp1->father = temp3;  //Apoints to father C
        temp3->father = t->father;  //C points to A's father (C's father pointer)
        temp2->father = temp3;  //B points to father C
        temp1->height = height(temp1);
        temp2->height = height(temp2);
        temp3->height = height(temp3);
        return temp3;  // return new C to be t.
    }

    Node* rotate_LR(Node* t)
    {
        Node *temp1 = t;
        Node *temp2 = t->son_smaller;
        Node *temp3 = t->son_smaller->son_larger;
        temp1->son_smaller = temp3->son_larger;
        temp3->son_larger->father = temp1;
        temp2->son_larger = temp3->son_smaller;
        temp3->son_smaller->father = temp2;
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

    Node* insert(Node* t,const T& data)
    {
        if (t == nullptr)
        {
            try
            {
                Node *base = &new(Node);
                base->data = data;
                base->son_larger = nullptr;
                base->son_smaller = nullptr;
                return base;
            }
            catch (...)
            {
                throw;
            }
        }
        else
        {
            if (t->data < data)
            {
                t->son_larger = insert(t->son_larger, data);
                t->son_larger->father = t;
            }
            else if (t->data > data)
            {
                t->son_smaller = insert(t->son_smaller, data);
                t->son_smaller->father = t;
            }
            else
            {
                return nullptr;
            }
            t->height = height(t);
            t = fix_balance(t);
            return t;
        }
    }

    Node* fix_balance (const Node* t)
    {
        if (bf(t) == 2 && bf(t->son_smaller) >= 0)
        {
            t = rotate_LL(t);
        }
        if (bf(t) == 2 && bf(t->son_smaller) < 0) {
            t = rotate_LR(t);
        }
        if (bf(t) == -2 && bf(t->son_larger) <= 0) {
            t = rotate_RR(t);
        }
        if (bf(t) == -2 && bf(t->son_larger) == 1) {
            t = rotate_RL(t);
        }
        return t;
    }

    bool remove (int num)
    {
        Node *ptr = search(num);
        if (ptr == nullptr)
            return false;
        Node* ptr_father = ptr->father;
        if (isLeaf(ptr))
        {
            remove_leaf(ptr);
        }
        else if (ptr->son_larger == nullptr || ptr->son_smaller == nullptr)
            remove_half_leaf(ptr);
        else
        {
            Node* temp1 = ptr->son_larger;
            Node* temp2 = temp1->son_smaller;
            while (temp2->son_smaller != nullptr)
                temp2 = temp2->son_smaller;
            ptr->son_larger = temp2->son_larger;
            if (temp2->son_larger != nullptr)
                temp2->son_larger->father = ptr;
            temp2->son_larger = temp1;
            temp1->father = temp2;
            temp1 = temp2->father;
            temp2->father = ptr->father;
            if (ptr->father != nullptr && ptr->father->data > ptr->data)
                ptr->father->son_smaller = temp2;
            else if (ptr->father != nullptr)
                ptr->father->son_larger = temp2;
            ptr->father = temp1;
            temp1->son_smaller = ptr;
            if (isLeaf(ptr))
                remove_leaf(ptr);
            else
                remove_half_leaf(ptr);
            while (temp2->father != nullptr)
            {
                temp2->height = height(temp2);
                temp2 = fix_balance(temp2);
                temp2 = temp2->father;
            }
        }
        fix_height(ptr_father);
        return true;
    }

    bool isLeaf (const Node* node)
    {
        if (node->son_larger == nullptr && node->son_smaller == nullptr)
            return true;
        return false;
    }

    void remove_leaf (const Node* ptr)
    {
        if (ptr->father->data > ptr->data)
            ptr->father->son_smaller = nullptr;
        else
            ptr->father->son_larger = nullptr;
    }

    void remove_half_leaf (const Node* ptr)
    {
        if (ptr->son_larger == nullptr)
        {
            if (ptr->father != nullptr && ptr->father->data > ptr->data)
                ptr->father->son_smaller = ptr->son_smaller;
            else if (ptr->father != nullptr)
                ptr->father->son_larger = ptr->son_smaller;
            ptr->son_smaller->father = ptr->father;
        }
        else
        {
            if (ptr->father != nullptr && ptr->father->data > ptr->data)
                ptr->father->son_smaller = ptr->son_larger;
            else  if (ptr->father != nullptr)
                ptr->father->son_larger = ptr->son_larger;
            ptr->son_larger->father = ptr->father;
        }
    }

    void fix_height (const Node* node)
    {
        while (node != nullptr && node->height != height(node))
        {
            node->height = height(node);
            node = fix_balance(node);
            node = node->father;
        }
    }


};
