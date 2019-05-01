#ifndef BSTREE_H
#define BSTREE_H

#include "node.h"
#include "iterator.h"

template <typename T> 
class BSTree {
    private:
        Node<T> *root;

    public:
        BSTree() : root(nullptr) {};

        bool find(T data) {
            if(root == nullptr){
                return false;
            }else{
                auto tempNode = root;
                while(tempNode->data != data){
                    if(data > tempNode->data){
                        if(tempNode->right != nullptr){
                            tempNode = tempNode->right;
                        }else{
                            return false;
                        }
                    }else{
                        if(tempNode->left != nullptr){
                            tempNode = tempNode->left;
                        }else{
                            return false;
                        }
                    }
                }
                return true;
            }
        } 

        bool insert(T data) {
            if(find(data)){
                return false;
            }else{
                auto newNode = new Node<T>(data);
                if(root == nullptr){
                    root = newNode;
                    return true;
                }else{
                    auto tempNode = root;
                    do{
                        if(data > tempNode->data){
                            if(tempNode->right){
                                tempNode = tempNode->right;
                            }else{
                                tempNode->right = newNode;
                                return true;
                            }
                        }else {
                            if (tempNode->left) {
                                tempNode = tempNode->left;
                            } else {
                                tempNode->left = newNode;
                                return true;
                            }
                        }
                    }while(true); //dislike
                }
            }
        }

        bool remove(T data) {
            if(find(data)){
                auto currentNode = &root;
                while((*currentNode)->data != data) {
                    if (data > (*currentNode)->data & (*currentNode)->right != nullptr) {
                        currentNode = &((*currentNode)->right);
                    }else if ((*currentNode)->left != nullptr) {
                        currentNode = &((*currentNode)->left);
                    }
                }
                return removeNode(currentNode);
            }else return false;
        }

        bool removeNode(Node<T> ** currentNode){
            if(isLeaf(currentNode)){
                deleteLeaf(currentNode);
                return true;
            }else{
                auto temp = (*currentNode);

                if(hasTwoChildren(currentNode)){
                    if((*currentNode)->right){
                        currentNode = &((*currentNode)->right);
                    }
                    while((*currentNode)->left){
                        currentNode = &((*currentNode)->left);
                    }
                    swapNodeValues(temp, (*currentNode));
                    removeNode(currentNode);
                }else if(hasLeftChild(currentNode)){
                    (*currentNode) = (*currentNode)->left;
                    delete temp;
                    return true;
                }else if(hasRightChild(currentNode)){
                    (*currentNode) = (*currentNode)->right;
                    delete temp;
                    return true;

                /*if(hasLeftChild(currentNode)){
                    (*currentNode) = (*currentNode)->left;
                    delete temp;
                    return true;
                }else if(hasRightChild(currentNode)){
                    (*currentNode) = (*currentNode)->right;
                    delete temp;
                    return true;
                }else{
                    if((*currentNode)->right){
                        currentNode = &((*currentNode)->right);
                    }
                    while((*currentNode)->left){
                        currentNode = &((*currentNode)->left);
                    }
                    swapNodeValues(temp, (*currentNode));
                    removeNode(currentNode);*/
                }
            }
        }

        void swapNodeValues(Node<T> * node1, Node<T> * node2){
            auto temp = node1->data;
            node1->data = node2->data;
            node2->data = temp;
        }

        void deleteLeaf(Node<T> ** currentNode){
            auto temp = (*currentNode);
            (*currentNode) = nullptr;
            delete temp;
        }

        bool hasTwoChildren(Node<T> ** currentNode){
            if((*currentNode)-> left != nullptr & (*currentNode)->right != nullptr) return true;
            else return false;
        }

        /*bool hasLeftChild(Node<T> ** currentNode){
            if((*currentNode)-> left != nullptr & (*currentNode)->right == nullptr) return true;
            else return false;
        }

        bool hasRightChild(Node<T> ** currentNode){
            if((*currentNode)-> right != nullptr & (*currentNode)->left == nullptr) return true;
            else return false;
        }*/

        bool hasLeftChild(Node<T> ** currentNode){
            if((*currentNode)-> left) return true;
            else return false;
        }

        bool hasRightChild(Node<T> ** currentNode) {
            if ((*currentNode)->right) return true;
            else return false;
        }

        bool isLeaf(Node<T> ** currentNode) {
            if (!((*currentNode)->left) & !((*currentNode)->right)) return true;
            else return false;
        }

        unsigned int size() {
            if(root == nullptr){
                return 0;
            }else {
                int size = countBranches(root);
                return size;
            }
        }

        unsigned int countBranches(Node<T> * localRoot){
            unsigned int counter = 1;
            if(hasLeftChild(&localRoot)){
                counter += countBranches(localRoot->left);
            }
            if(hasRightChild(&localRoot)){
                counter += countBranches(localRoot->right);
            }

            return counter;
        };

        void traversePreOrder() {
            if(root != nullptr){
                traversePreOrderHelper(root);
            }
        }

        void traversePreOrderHelper(Node<T> * localRoot){
            cout << localRoot->data << " ";
            if(hasLeftChild(&localRoot)){
                traversePreOrderHelper(localRoot->left);
            }
            if(hasRightChild(&localRoot)){
                traversePreOrderHelper(localRoot->right);
            }
        }

        void traverseInOrder() {
            if(root != nullptr){
                traverseInOrderHelper(root);
            }
        }

        void traverseInOrderHelper(Node<T> * localRoot){
            if(hasLeftChild(&localRoot)){
                traverseInOrderHelper(localRoot->left);
            }
            cout << localRoot->data << " ";
            if(hasRightChild(&localRoot)){
                traverseInOrderHelper(localRoot->right);
            }
        }

        void traversePostOrder() {
            if(root != nullptr){
                traversePostOrderHelper(root);
            }
        }

        void traversePostOrderHelper(Node<T> * localRoot){
            if(hasLeftChild(&localRoot)){
                traversePostOrderHelper(localRoot->left);
            }
            if(hasRightChild(&localRoot)){
                traversePostOrderHelper(localRoot->right);
            }
            cout << localRoot->data << " ";
        }

        Iterator<T> begin() {
            if(root){
                return Iterator<T>(root);
            }else{
                throw out_of_range("El árbol binario no tiene elementos");
            }
        }

        Iterator<T> end() {
            //TODO
        }

        ~BSTree() {
            // TODO
        }
};

#endif
