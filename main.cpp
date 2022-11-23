#include <iostream>


template<class T>
struct Node
{
    Node<T>* father;
    Node<T>* son_smaller;
    Node<T>* son_larger;
    T data;
    int height;
};


template<class T>
class AVL_Tree
 {
    Node<T>*  root;
public:
    AVL_Tree()
    {
        root = nullptr;
    }

    AVL_Tree<T> &operator=(const AVL_Tree<T> &tree) = delete;

    AVL_Tree<T>(const AVL_Tree<T> &tree) = delete;

    ~AVL_Tree(); //do after

    int height(Node<T> *t)
    {
        if (t == nullptr)
            return -1;
        else {
            int s_height = t->son_smaller->height;
            int l_height = t->son_larger->height;
            return std::max(s_height, l_height) + 1;
        }
    }

    int bf(Node<T> *t)
    {
        return t->son_smaller->height - t->son_larger->height;
    }

    Node<T>* search(const T& data)
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

     bool isLeaf (const Node<T>* node)
     {
         if (node->son_larger == nullptr && node->son_smaller == nullptr)
             return true;
         return false;
     }

    Node<T>* rotate_LL(Node<T>* t) {
        Node<T> *tmp1 = t;
        Node<T> *tmp2 = t->son_smaller;
        tmp1->son_smaller = tmp2->son_larger;
        tmp1->son_smaller->father = tmp1;
        tmp2->son_larger = tmp1;
        tmp2->father = tmp1->father;
        tmp1->father = tmp2;
        return tmp2;
    }

    Node<T>* rotate_RR(Node<T>* t) {
        Node<T> *temp1 = t;
        Node<T> *temp2 = t->son_larger;
        temp1->son_larger = temp2->son_smaller;
        temp1->son_larger->father = temp1;
        temp2->son_smaller = temp1;
        temp2->father = temp1->father;
        temp1->father = temp2;
        return temp2;
    }

    Node<T>* rotate_RL(Node<T>* t)
    {
        Node<T> *temp1 = t;  //points to A
        Node<T> *temp2 = t->son_larger;  //points to B
        Node<T> *temp3 = t->son_larger->son_smaller;  //points to C
        temp1->son_larger = temp3->son_smaller;  //right side of A point to left of C
        temp3->son_smaller->father = temp1;  //right side of C points to new father A
        temp2->son_smaller = temp3->son_larger;  //left side of B points to right side of C
        temp3->son_larger->father = temp2;  //right side of C points to new father B
        temp3->son_smaller = temp1;  //left side C points to A
        temp3->son_larger = temp2;  //right side C points to B
        temp1->father = temp3;  //Apoints to father C
        temp3->father = t->father;  //C points to A's father (C's father pointer)
        temp2->father = temp3;  //B points to father C
        return temp3;  // return new C to be t.
    }

    Node<T>* rotate_LR(Node<T>* t)
    {
        Node<T> *temp1 = t;
        Node<T> *temp2 = t->son_smaller;
        Node<T> *temp3 = t->son_smaller->son_larger;
        temp1->son_smaller = temp3->son_larger;
        temp3->son_larger->father = temp1;
        temp2->son_larger = temp3->son_smaller;
        temp3->son_smaller->father = temp2;
        temp3->son_larger = temp1;
        temp3->son_smaller = temp2;
        temp1->father = temp3;
        temp3->father = t->father;
        temp2->father = temp3;
        return temp3;
    }

    Node<T>* insert(Node<T>* t,const T& data)
    {
        if (t == nullptr)
        {
            try
            {
                Node<T> *base = &new(Node<T>);
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
                if(t->son_larger->data == data)
                    t->son_larger->father = t;
            }
            else if (t->data > data)
            {
                t->son_smaller = insert(t->son_smaller, data);
                if(t->son_smaller->data == data)
                    t->son_smaller->father = t;
            }
            else
            {
                return nullptr;
            }
            t->height = height(t);
            if (balancefactor(t) == 2 && balancefactor(t->son_smaller) >= 0)
            {
                t = rotate_LL(t);
            }
            if (balancefactor(t) == 2 && balancefactor(t->son_smaller) < 0) {
                t = rotate_LR(t);
            }
            if (balancefactor(t) == -2 && balancefactor(t->son_larger) <= 0) {
                t = rotate_RR(t);
            }
            if (balancefactor(t) == -2 && balancefactor(t->son_larger) == 1) {
                t = rotate_RL(t);
            }
            return t;
        }
    }

};
