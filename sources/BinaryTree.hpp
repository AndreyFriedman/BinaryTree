#pragma once

#include <iostream>

#include <vector>
#include "Node.hpp"

#include "InOrderIterator.hpp"
#include "PreOrderIterator.hpp"
#include "PostOrderIterator.hpp"

namespace ariel
{
    template <typename T>
    class BinaryTree{
        private:
        Node<T>* root;
        Node<T>* find_value(T value){
            if(this->root == nullptr){
                return nullptr;
            }
            for(auto iter = begin_preorder(); iter != end_preorder();++iter){
                if(*iter == value){
                    return iter.get_node();
                }
            }
            return nullptr;
        }
        
        void del_tree(){
            if(this->root == nullptr){
                return;
            }
            for (auto iter = begin_preorder(); iter != end_preorder();){
                Node<T>* current_node = iter.get_node();
                ++iter;
                delete current_node;
            }
        }
        void copySons(Node<T>* dest,Node<T>* start){
            if (start-> left != nullptr){
                dest->left = new Node<T>{start-> left-> data};
                copySons(dest-> left, start-> left);
            }
            if (start-> right != nullptr){
                dest-> right = new Node<T>{start-> right-> data};
                copySons(dest-> right, start-> right);
            }
        }
        void copy(const BinaryTree& other){
            if(other.root != nullptr){
                this-> root = new Node<T>{other.root-> data};
            }
        }
        public:
        BinaryTree(){
            this->root = nullptr;
        }
        BinaryTree(const BinaryTree& other){
            this->copy(other);
        }
        BinaryTree(BinaryTree && other) noexcept{
            this->root = other.root;
            other.root = nullptr;
        }
        ~BinaryTree(){
            this->del_tree();
        }

        BinaryTree& add_root(T value){
            if(this-> root == nullptr){
                this-> root = new Node<T>{value};
            }
            else{
                this-> root-> data = value;
            }
            return (*this);
        } 

        BinaryTree& add_left(T parent_value, T left_value){
            Node<T>* parent_node = this->find_value(parent_value);

            if(parent_node == nullptr){
                throw std::invalid_argument("There is no value at parent");
            }
            if(parent_node-> left == nullptr){
                parent_node-> left = new Node<T>{left_value};
            }
            else{
                parent_node-> left->data = left_value;
            }
            return (*this);
        }

        BinaryTree& add_right(T parent_value, T right_value){
            Node<T>* parent_node = this->find_value(parent_value);
            if(parent_node == nullptr){
                throw std::invalid_argument("There is no value at parent");
            }
            if(parent_node->right == nullptr){
                parent_node->right = new Node<T>{right_value};
            }
            else{
                parent_node->right->data = right_value;
            }
            return (*this);
        } 
    
        preorder_iterator<T> begin_preorder() {return preorder_iterator<T>{root};}
        preorder_iterator<T> end_preorder() {return preorder_iterator<T>{};}

        inorder_iterator<T> begin_inorder() {return inorder_iterator<T>{root};}
        inorder_iterator<T> end_inorder() {return inorder_iterator<T>{};}

        postorder_iterator<T> begin_postorder() {return postorder_iterator<T>{root};}
        postorder_iterator<T> end_postorder() {return postorder_iterator<T>{};}

        inorder_iterator<T> begin() {return this->begin_inorder();}
        inorder_iterator<T> end() {return this->end_inorder();}

        BinaryTree& operator = (const BinaryTree& other){
            if (this != &other){
                this-> del_tree();
                this-> copy(other);
            }
            return (*this);
        }
        BinaryTree& operator = (BinaryTree && other) noexcept{
            this-> root = other.root;
            other.root = nullptr;
            return (*this);
        }

        friend std::ostream& operator << (std::ostream& os,const BinaryTree<T>& tree);

        Node<T>* get_root(){
            if(this-> root != nullptr){
                return this->root;
            }
            throw std::invalid_argument("no root");
        }
    };
    template <typename T>
    std::ostream& operator << (std::ostream& os, BinaryTree<T>& tree){
        os << "\nthe values are:" << std::endl;
        for (auto element : tree){
            os << element << " ";
        }
        os << std::endl;
        return os;
    }
};