#pragma once

#include "Node.hpp"
#include <stack>

namespace ariel
{
    template<typename T>
    class preorder_iterator{
        private:
        std::stack<Node<T>*> nStack;

        public:
        preorder_iterator(){};
        preorder_iterator(Node<T>* root){
            this->nStack.push(root);
        };
        
        preorder_iterator<T>& operator ++ (){
            Node<T>* current_node = nStack.top();
            nStack.pop();
            if (current_node->right != nullptr){
                nStack.push(current_node->right);
            }
            if (current_node->left != nullptr){
                nStack.push(current_node->left);
            }
            return (*this);
        }

        preorder_iterator<T> operator ++ (int dum){
            preorder_iterator<T> temp = (*this);
            Node<T>* current_node = nStack.top();
            nStack.pop();
            if (current_node-> right != nullptr){
                nStack.push(current_node->right);
            }
            if (current_node-> left != nullptr){
                nStack.push(current_node->left);
            }
            return temp;
        }

        T& operator * (){
            return nStack.top()->data;
        }

        T* operator -> (){
            return &(nStack.top()->data);
        }

        bool operator != (const preorder_iterator &other) const{
            if(this->nStack.empty() && other.nStack.empty()){
                return false;
            }
            if(this->nStack.empty() || other.nStack.empty()){
                return true;
            }
            if(this->nStack.top() != other.nStack.top()){
                return true;
            }
            return false;
        }

        bool operator == (const preorder_iterator& other) const{
            return *this == other;
        }

        Node<T>* get_node(){
            return nStack.top();
        }
    };
};