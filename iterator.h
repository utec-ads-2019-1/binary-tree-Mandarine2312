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
        Node<T> *nullNode;
        bool hasReachedEnd;

    public:
        Iterator(){
            toDo = new stack<Node<T> *>;
            done = new stack<Node<T> *>;
        }

        Iterator(Node<T> *node) {
            current = node;
            toDo = new stack<Node<T> *>;
            done = new stack<Node<T> *>;
            nullNode = new Node<T>(0);
            hasReachedEnd = false;

            while(current->left){
                toDo->push(current);
                current = current->left;
            }
        }

        Iterator<T> operator=(Iterator<T> other) {          
            this->current = other.current;
            *toDo = other.toDo;
            *done = other.done;
            this->hasReachedEnd = other.hasReachedEnd;
        }

        bool operator!=(Iterator<T> other) {
            return this->current != other.current;
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
                }else{
                    hasReachedEnd = true;
                    current = nullNode;
                }
            }
        }

        Iterator<T> operator--() {
            if(done->empty()){
                throw out_of_range("El iterador está en el inicio");
            }else{
                if(hasReachedEnd){
                    hasReachedEnd = false;
                    current = done->top();
                    done->pop();
                }else{
                    toDo->push(current);
                    current = done->top();
                    done->pop();
                }
            }
        }

        T operator*() {
            return current->data;
        }


    template<class>
    friend class Iterator;
};

#endif
