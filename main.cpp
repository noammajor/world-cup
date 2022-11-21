#include <iostream>
template<class T>
struct Node
{
    Node<T>* father;
    Node<T>* son_smaller;
    Node<T>* son_larger;
    T data;
    int balance_factor;
};
template<class T>
class AVL_Tree {
    Node<T> *root;
public:
    AVL_Tree() {
        root = nullptr;
    }

    AVL_Tree<T> &operator=(const AVL_Tree<T> &tree) = delete;

    AVL_Tree<T>(const AVL_Tree<T> &tree) = delete;

    ~AVL_Tree(); //do after
    int add(const T &data) {

        Node<T> *base = new(Node<T>);
        try {
            Node<T> *base = new(Node<T>);
            base->data = data;
            if (base == nullptr) {
                throw;
            }
        }
        catch (const std::bad_alloc &e) {
            throw;
        }
        root->son_smaller = nullptr;
        root->son_larger = nullptr;
        if (root == nullptr) {
            root = base;
            root->father = nullptr;
            root->balance_factor = 0;
        } else {
            Node<T> *t = root;
            while (t != nullptr) {
                if (t->data == data) {
                    return 0;
                }
                if (t->data < data) {
                    t = t->son_larger;
                }
                if (t->data > data) {
                    t = t->son_smaller;
                }
            }
            t = t->father;
            if (t->data < data) {
                t->son_larger = base;
                t->son_larger->father = t;
            } else {
                t->son_smaller = base;
                t->son_smaller->father = t;
            }
            balancefactor(t);
            return 1;
        }
    }

    void balancefactor(Node<T> *t)
    {
        int counterleft = 0;
        int counterright = 0;
        Node<T> left = t;
        Node<T> right = t;
        while (left->son_smaller != nullptr) {
            counterleft += 1;
            left = left->son_smaller;
        }
        while (right->son_larger != nullptr) {
            counterright += 1;
            right = right->son_larger;
        }
        t->balance_factor = counterleft - counterright;
        while ((t->balance_factor > 1 || t->balance_factor < -1))
        {
            if(t->father== nullptr)
            {
                break;
            }
            t = t->father;
            t->balance_factor = t->son_smaller->balance_factor - t->son_larger->balance_factor;

        }
        if(t->balance_factor>1 && t->son_smaller->balance_factor<0)
        {
            rotatelr(t);
        }
        if(t->balance_factor>1 && t->son_smaller->balance_factor>-1)
        {
            rotatell(t);
        }
        if(t->balance_factor<-1 && t->son_smaller->balance_factor<1)
        {
            rotaterr(t);
        }
        if(t->balance_factor<-1 && t->son_smaller->balance_factor>1)
        {
            rotaterl(t);
        }
    }

    Node<T>* search(const T& data)
    {
        Node<T>* t= root;
        while(t!= nullptr)
        {
            if(t->data==data)
            {
                return t;
            }
            if(t->data>data)
            {
                t=t->son_smaller;
            }
            else
            {
                t=t->son_larger;
            }
        }
        return nullptr;
    }

    void rotaterr(Node<T>* t)
    {
        Node<T>* temp=t->son_larger->son_smaller;//forB
        t->son_larger->father=t->father;
        t->father=t->son_larger;
        if (t->father->son_smaller==t)
        {
            t->father->son_smaller=t->son_larger;
        }
        if (t->father->son_larger==t)
        {
            t->father->son_larger=t->son_larger;
        }
        t->son_larger=temp;
    }

//i do rl

}
;