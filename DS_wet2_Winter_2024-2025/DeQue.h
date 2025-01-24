//
// Created by Guy Friedman on 24/01/2025.
//

#ifndef DEQUE_H
#define DEQUE_H

#include "DeQueNode.h"
template <typename T>
class DeQue {
protected:
    DeQueNode<T>* head;
    DeQueNode<T>* tail;
    int size;
public:

    DeQue() {
        head = new DeQueNode<T>();
        tail = new DeQueNode<T>();
        size = 0;
        head->addInitial(this->tail);
    }

    ~DeQue() {
        delete head;
    }

    int getSize() {
        return size;
    }

    void append(T* item, int index) {
        auto newNode = new DeQueNode<T>(item,index);
        this->tail->queueAdd(newNode);
        ++this->size;
    }

    void insert(T* item, int index) {
        auto newNode = new DeQueNode<T>(item,index);
        this->head->stackAdd(newNode);
        ++this->size;
    }

    T* pop() {
        auto newNode = this->head->popNext();
        //Pair<T> pair(newNode->getData(), newNode->getKey());
        T* temp = newNode->getData();
        newNode->nullify();
        delete newNode;
        --this->size;
        return temp;
    }

    T* find(T* value) {
        auto node = this->head->find(value);
        return node->getData();
    }

};



#endif //DEQUE_H
