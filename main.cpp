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
    int add(const T &data) {

        root->son_smaller = nullptr;
        root->son_larger = nullptr;
        if (root == nullptr) {
            root = base;
            root->father = nullptr;
            root->height = 0;
        } else
        {
            Node<T> *t = root;
            while (t != nullptr) {
                if (t->data == data) {
                    return 0;
                }
                if (t->data < data) {
                    t = t->son_larger;
                }
                if (t->data > data)
                {
                    t = t->son_smaller;
                }
            }
            t = t->father;
            if (t->data < data)
            {
                t->son_larger = base;
                t->son_larger->father = t;
            }
            else
            {
                t->son_smaller = base;
                t->son_smaller->father = t;
            }
            height(t);
            balancefactor(t);
            return 1;
        }
    }//not to use
    int height(Node<T> *t)
    {
        if(t->son_smaller!= nullptr && t->son_larger!= nullptr)
        {
            if(t->son_smaller->height>t->son_larger->height)
            {
                return t->son_smaller->height+1 ;
            }
            else
            {
                return t->son_larger->height+1;
            }
        }
        if (t->son_smaller== nullptr && t->son_larger!= nullptr)
        {
            return t->son_larger->height+1;
        }
        if (t->son_smaller!= nullptr && t->son_larger== nullptr)
        {
            return t->son_smaller->height+1;
        }
        if(t->son_smaller== nullptr && t->son_larger== nullptr)
        {
            return 0;
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
        while ((t->balance_factor == 1 || t->balance_factor == -1))
        {
            if(t->father== nullptr)
            {
                break;
            }
            if (t->father->son_smaller==t)
            {
                t->father->balance_factor= t->father->balance_factor+1;
            }
            if (t->father->son_larger==t)
            {
                t->father->balance_factor= t->father->balance_factor-1;
            }
            t=t->father;
        }
        if (t->balance_factor>1 || t->balance_factor<-1)
        {
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
            //t->balance_factor=0;
        }

    }
    int bf(Node<T> *t)
    {
        if(t->son_smaller!= nullptr && t->son_larger!= nullptr)
        {
            return (t->son_smaller->height-t->son_larger->height);
        }
        if(t->son_smaller!= nullptr && t->son_larger== nullptr)
        {
            return t->son_smaller->height;
        }
        if(t->son_smaller== nullptr && t->son_larger!= nullptr)
        {
            return t->son_larger->height;
        }
        if(t->son_smaller== nullptr && t->son_larger== nullptr)
        {
            return 0;
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

     bool isLeaf (const Node<T>* node)
     {
         if (node->son_larger == nullptr && node->son_smaller == nullptr)
             return true;
         return false;
     }

     void rotate_LL (Node<T>* node)
     {
         //Node<T>* temp = node;
         if(node->father > node)
             node->father->son_smaller = node->son_smaller;
         else
             node->father->son_larger = node->son_smaller;
         node->son_smaller = node->son_smaller->son_larger; //B->Ar
         node->son_smaller->son_larger = node; //A->B

     }





    Node<T>* rotaterr(Node<T>* t)
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
        return t;
    }
    int insert(Node<T>* t,const T &data)
    {
        if (t == nullptr)
        {
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
          t=base;
            t->son_larger= nullptr;
            t->son_smaller= nullptr;
        }
        else
        {
            if (t->data < data)
            {
                insert(t->son_larger, data);
                if(t->son_larger->data==data)
                {
                    t->son_larger->father=t;
                }
            }
            if (t->data > data)
            {
                insert(t->son_smaller, data);
                if(t->son_smaller->data==data)
                {
                    t->son_smaller->father=t;
                }
            }
            t->height = height(t);
            if (balancefactor(t) == 2 && balancefactor(t->son_smaller) =>0)
            {
                t = rotatell(t);
            }
            if (balancefactor(t) == 2 && balancefactor(t->son_smaller) < 0) {
                t = rotatelr(t);
            }
            if (balancefactor(t) == -2 && balancefactor(t->son_larger) <= 0) {
                t = rotaterr(t);
            }
            if (balancefactor(t) == -2 && balancefactor(t->son_larger) == 1) {
                t = rotaterr(t);
            }
            return ;
        }
    }
    Node<T>* rotaterl(Node<T>* t)
    {
        Node<T> *temp1 = t;
        Node<T> *temp2 = t->son_larger;
        Node<T> *temp3 = t->son_larger->son_smaller;
        temp1->

    }


        temp1->son_larger=t->son_larger->son_smaller->son_smaller;
        t->son_larger->son_smaller->son_smaller=t;
        temp2->son_smaller=temp2->son_smaller->son_larger;

    }

};