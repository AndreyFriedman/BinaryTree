#pragma once

#include "Node.hpp"
#include <list>

namespace ariel
{
    template <typename T>
    class postorder_iterator{
        private:
        std::list<Node<T>*> nStack;
        void postorder(Node<T>* current_node){
            if (current_node != nullptr){
                if (current_node->left != nullptr){
                    postorder(current_node->left);
                }
                if (current_node->right != nullptr){
                    postorder(current_node->right);
                }
                nStack.push_back(current_node);
            }
        }

        public:
        postorder_iterator(){};
        postorder_iterator(Node<T>* node){
            postorder(node);
        };

        postorder_iterator<T>& operator ++ (){
            nStack.pop_front();
            return (*this);
        }

        postorder_iterator<T> operator ++ (int dum){
            postorder_iterator<T> temp = (*this);
            nStack.pop_front();
            return temp;
        }

        T& operator * (){
            return nStack.front()->data;
        }

        T* operator -> (){
            return &(nStack.front()->data);
        }

        bool operator != (const postorder_iterator &other) const{
            if(this->nStack.empty() && other.nStack.empty()){
                return false;
            }
            if(this->nStack.empty() || other.nStack.empty()){
                return true;
            }
            if(this->nStack.front() != other.nStack.front()){
                return true;
            }
            return false;
        }

        bool operator == (const postorder_iterator& other) const{
            return *this == other;
        }

        Node<T>* get_node(){
            return nStack.front();
        }
    };
};