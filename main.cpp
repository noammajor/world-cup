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
class AVL_Tree
 {
Node<T>*  root;
public:
     AVL_Tree()
     {
         root= nullptr;
     }
     AVL_Tree<T>& operator=(const AVL_Tree<T>& tree)=delete;
     AVL_Tree<T>(const AVL_Tree<T>& tree)=delete;
     ~AVL_Tree(); //do after
     AVL_Tree<T>& add(const T& data)
    {
        {
            try
            {
                Node<T>* base = new(Node<T>);
                base->data=data;
            }
            catch (const std::bad_alloc& e)
            {
                throw;
            }


            if(root == nullptr)
            {
                root = base;
                root->son_smaller= nullptr;
                root->son_larger= nullptr;
                root->father= nullptr;
                root->data=data;
                root->balance_factor=0;
            }
    else
    {
        Node<T>* t= root;
        while (t->data<data)
        {
            t=t->son_larger;
        }
    }
        }







};

