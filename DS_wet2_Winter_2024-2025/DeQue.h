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

    void append(T* item) {
        auto newNode = new DeQueNode<T>(item);
        this->tail->queueAdd(newNode);
        ++this->size;
    }

    void insert(T* item) {
        auto newNode = new DeQueNode<T>(item);
        this->head->stackAdd(newNode);
        ++this->size;
    }

    T* pop() {
        assert(this->head->hasNext());
        auto newNode = this->head->popNext();
        T* tempVal = newNode->getData();
        newNode->nullify();
        delete newNode;
        --this->size;
        return tempVal;
    }

    T* find(T* value) {
        auto node = this->head->find(value);
        return node->getData();
    }

    T* remove(T* item) {
        DeQueNode<T>* temp = this->head->remove(item);
        if (temp == nullptr) {
            return nullptr;
        }
        T* newTemp = temp->getData();
        temp->nullify();
        delete temp;
        --this->size;
        return newTemp;
    }

};



#endif //DEQUE_H
