//
// Created by Guy Friedman on 27/01/2025.
//

#ifndef UNIONFIND_H
#define UNIONFIND_H
#include "UnionFindTwoNode.h"
#include "ChainHashArray.h"
#define EMPTY (0)

template<class T>
class UnionFind {
protected:
    ChainHashArray<UnionFindNode<T>>* nodes;
    int size;

    UnionFindNode<T>* findNode(int key) {
        return this->nodes->find(key);
    }

public:

    UnionFind() : nodes(nullptr), size(EMPTY) {
        this->nodes = new ChainHashArray<UnionFindNode<T>>();
    }

    ~UnionFind() {
        delete this->nodes;
    }

    void insert(int id, T* value) {
        UnionFindNode<T>* node = new UnionFindNode<T>(value);
        this->nodes->insert(id,node);
        ++this->size;
    }

    T* find(int key) { //todo
        UnionFindNode<T>* tempNode = this->findNode(key);
        return (tempNode==nullptr)?nullptr:tempNode->getData();
    }

    bool connected(int id1, int id2) {
        UnionFindNode<T>* node1 = this->findNode(id1);
        UnionFindNode<T>* node2 = this->findNode(id2);
        UnionFindNode<T>* groupOne = node1->getGroup();
        UnionFindNode<T>* groupTwo = node2->getGroup();
        return groupOne == groupTwo;
    }

    virtual bool uniteGroup(int id1, int id2) {
        UnionFindNode<T>* node1 = this->findNode(id1);
        UnionFindNode<T>* node2 = this->findNode(id2);
        UnionFindNode<T>* groupOne = node1->getGroup();
        UnionFindNode<T>* groupTwo = node2->getGroup();
        if (groupOne == nullptr || groupTwo == nullptr) {
            return false;
        }
        return groupOne->unite(groupTwo);
    }

    T* remove(int key) {
        /*
        T* toRemove = this->find(key);
        if (toRemove == nullptr) {
            return nullptr;
        }
        */
        //T* result = this->nodes->remove(key);
        UnionFindNode<T>* tempNode = this->nodes->remove(key);
        if (tempNode == nullptr) {
            return nullptr;
        }
        T* result = tempNode->extract();
        delete tempNode;
        if (result != nullptr) {
            --this->size;
        }
        return result;
    }

    void deleteItem(int key) {
        T* result = this->remove(key);
        if (result != nullptr) {
            --this->size;
        }
        delete result;
    }

    T* getGroupLeader(int id) {
        UnionFindNode<T>* groupOne = this->findNode(id);
        UnionFindNode<T>* groupTwo = groupOne->grouLeaderNode();
        return groupTwo->getGroupLeader();
    }




};



#endif //UNIONFIND_H
