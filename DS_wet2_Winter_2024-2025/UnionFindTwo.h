//
// Created by Guy Friedman on 27/01/2025.
//

#ifndef UNIONFIND_H
#define UNIONFIND_H
#include "UnionFindtwoNode.h"
#include "ChainHashArray.h"
#define EMPTY (0)

template<class T>
class UnionFind {
protected:
    ChainHashArray<UnionFindNode<T>>* nodes;
    int size;

public:

    UnionFind() : nodes(new ChainHashArray<UnionFindNode<T>>()), size(EMPTY) {}

    ~UnionFind() {
        delete this->nodes;
    }

    void insert(int id) {
        UnionFindNode<T>* node = new UnionFindNode<T>(id);
        this->nodes->insert(id,node);
        ++this->size;
    }

    T* find(int key) {
        return this->nodes->find(key);
    }

    bool connected(int id1, int id2) {
        UnionFindNode<T>* node1 = this->find(id1);
        UnionFindNode<T>* node2 = this->find(id2);
        UnionFindNode<T>* groupOne = node1->getGroup();
        UnionFindNode<T>* groupTwo = node2->getGroup();
        return groupOne == groupTwo;
    }

    bool uniteGroup(int id1, int id2) {
        UnionFindNode<T>* node1 = this->find(id1);
        UnionFindNode<T>* node2 = this->find(id2);
        UnionFindNode<T>* groupOne = node1->getGroup();
        UnionFindNode<T>* groupTwo = node2->getGroup();
        if (groupOne == nullptr || groupTwo == nullptr) {
            return false;
        }
        return groupOne->unite(groupTwo);
    }

    T* remove(int key) {
        T* result = this->remove(key);
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




};



#endif //UNIONFIND_H
