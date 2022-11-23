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
     AVL_Tree<T>& add(const T& data) {
         {
             try {
                 Node<T> *base = new(Node<T>);
                 base->data = data;
             }
             catch (const std::bad_alloc &e) {
                 throw;
             }


             if (root == nullptr) {
                 root = base;
                 root->son_smaller = nullptr;
                 root->son_larger = nullptr;
                 root->father = nullptr;
                 root->data = data;
                 root->balance_factor = 0;
             } else {
                 Node<T> *t = root;
                 while (t->data < data) {
                     t = t->son_larger;
                 }
             }
         }
     }

     bool remove (const int num)
     {
         if (root == nullptr)
             return false;
         Node<T>* ptr = root;
         while (ptr != nullptr)
         {
             if (num > ptr->data && ptr->son_larger != nullptr)
                 ptr = ptr->son_larger;
             else if (num < ptr->data && ptr->son_smaller != nullptr)
                 ptr = ptr->son_smaller;
             else if (ptr->data == num)
             {
                if (isLeaf(ptr))
                {
                    if(ptr->father->data > ptr->data)
                        ptr->father->son_smaller = nullptr;
                    else
                        ptr->father->son_larger = nullptr;
                    delete ptr;
                }
                else if (ptr->son_larger == nullptr)
                {
                    delete ptr->data;
                    ptr->data = ptr->son_smaller->data;
                    delete ptr->son_smaller;
                }
                else
                {
                    Node<T>* temp = ptr;
                    temp = ptr->son_larger;
                    while (temp->son_smaller != nullptr)
                        temp = temp->son_smaller;
                    T tempData = ptr->data;
                    ptr->data = temp->data;
                    temp->data = tempData;
                    if (remove(temp))
                        return true;
                }
                 return true;
             }
             else
                 return false;
         }
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






};

