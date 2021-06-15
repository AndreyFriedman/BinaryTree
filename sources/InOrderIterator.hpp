#pragma once

#include "Node.hpp"
#include <stack>

namespace ariel
{
    template<typename T>
    class inorder_iterator{
        private:
        std::stack<Node<T>*> nStack;
        
        public:
        inorder_iterator(){};
        inorder_iterator(Node<T>* node){
            while(node != nullptr){
                nStack.push(node);
                node = node->left;
            }
        };

        inorder_iterator<T>& operator ++ (){
            Node<T> *current_node = nStack.top()->right;
            nStack.pop();
            while (current_node != nullptr){
                nStack.push(current_node);
                current_node = current_node->left;
            }
            return (*this);
        }

        inorder_iterator<T> operator ++ (int dum){
            inorder_iterator<T> temp = (*this);
            Node<T>* current_node = nStack.top()->right;
            nStack.pop();
            while (current_node != nullptr){
                nStack.push(current_node);
                current_node = current_node->left;
            }
            return temp;
        }

        T& operator * (){
            return nStack.top()->data;
        }

        T* operator -> (){
            return &(nStack.top()->data);
        } 

        bool operator != (const inorder_iterator& other) const{
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

        bool operator == (const inorder_iterator& other) const{
            return *this == other;
        }
        Node<T>* get_node(){
            return nStack.top();
        }
    };
};