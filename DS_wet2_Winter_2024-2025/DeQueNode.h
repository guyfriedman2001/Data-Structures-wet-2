//
// Created by Guy Friedman on 24/01/2025.
//

#ifndef DEQUENODE_H
#define DEQUENODE_H


#include <cassert>

constexpr int DEFAULT_KEY = 0;

template <typename T>
class DeQueNode {
private:

    inline bool initialNode() const {
        return (this->next == nullptr) && (this->prev == nullptr);
    }

    inline bool noData() const {
        return this->data == nullptr;
    }

    inline bool canBecomeHead() {
        return (this->initialNode()) && (this->noData());
    }

    inline bool canBecomeTail() {
        return (this->initialNode()) && (this->noData());
    }

protected:

    T* data;
    DeQueNode<T>* next;
    DeQueNode<T>* prev;

public:

    DeQueNode() : data(nullptr), next(nullptr), prev(nullptr) {}

    DeQueNode(T* data) : data(data), next(nullptr), prev(nullptr) {}

    ~DeQueNode() {
        delete next;
        delete data;
    }

    void nullify() {
        this->next = nullptr;
        this->prev = nullptr;
        this->data = nullptr;
    }

    void deCouple() {
        this->next->prev = this->prev;
        this->prev->next = this->next;
        this->next = this->prev = nullptr;
    }

    inline bool hasNext() const {
        return !((this->next != nullptr) && (this->next->isTail()));
    }

    inline bool isTail() const {
        return (this->prev != nullptr) && (this->data == nullptr) && (this->next == nullptr);
    }

    inline bool isHead() const {
        return (this->next != nullptr) && (this->data == nullptr) && (this->prev == nullptr);
    }

    DeQueNode<T>* popNext() {
        assert(this->hasNext());
        assert(this->next != nullptr && this->next->next != nullptr);
        DeQueNode<T>* temp = this->next;
        temp->deCouple();
        return temp;
    }

    void queueAdd(DeQueNode<T>* node) {
        assert(node != nullptr);
        assert(!this->isHead());
        this->prev->next = node;
        node->prev = this->prev;
        node->next = this;
        this->prev = node;
    }

    void stackAdd(DeQueNode<T>* node) {
        assert(node != nullptr);
        assert(!this->isTail());
        this->next->prev = node;
        node->next = this->next;
        node->prev = this;
        this->next = node;
    }

    void addInitial(DeQueNode<T>* node) {
        assert(node != nullptr);
        //make sure that 'this' node is in a state required to become head
        assert(this->canBecomeHead());
        //make sure that 'node' node is in a state required to become tail
        assert(node->canBecomeTail());
        this->next = node;
        node->prev = this;
    }

    T* getData() const {
        return this->data;
    }

    DeQueNode<T>* find(T* toFind) {
        if(this->isTail()) {
            return nullptr;
        }
        if (this->data == toFind) {
            return this;
        }
        return this->next->find(toFind);
    }

    DeQueNode<T>* remove(T* toFind) {
        if(this->isTail()) {
            return nullptr;
        }
        if (this->data == toFind) {
            this->deCouple();
            return this;
        }
        return this->next->find(toFind);
    }

    //int getKey() {return this->key;}



};



#endif //DEQUENODE_H
