#ifndef ITERATOR_H
#define ITERATOR_H

#include "node.h"
#include <stack>

template <typename T> 
class Iterator {
    private:
        Node<T> *current;
        stack<Node<T> * > * toDo;
        stack<Node<T> * > * done;

    public:
        Iterator(){
            toDo = new stack<Node<T> *>;
            done = new stack<Node<T> *>;
        }

        Iterator(Node<T> *node) {
            current = node;
            toDo = new stack<Node<T> *>;
            done = new stack<Node<T> *>;

            while(current->left){
                toDo->push(current);
                current = current->left;
            }
        }

        Iterator<T> operator=(Iterator<T> other) {          
            current = other.current;
        }

        bool operator!=(Iterator<T> other) {
            return current->data != *other;
        }

        Iterator<T> operator++() {
            done->push(current);
            if(current->right){
                current = current->right;
                while(current->left){
                    toDo->push(current);
                    current= current->left;
                }
            }else{
                if(!toDo->empty()) {
                    current = toDo->top();
                    toDo->pop();
                }
            }
        }

        Iterator<T> operator--() {
            if(done->empty()){
                throw out_of_range("El iterador está en el inicio");
            }else{
                current = done->top();
                done->pop();
                toDo->push(current);
            }
        }

        void setCurrent(Node<T> node){
            current = node;
        }

        T operator*() {
            return current->data;
        }
};

#endif
