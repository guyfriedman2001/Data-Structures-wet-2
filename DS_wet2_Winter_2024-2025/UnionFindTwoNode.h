//
// Created by Guy Friedman on 27/01/2025.
//

#ifndef UNIONFINDNODE_H
#define UNIONFINDNODE_H


template <typename T>
class UnionFindNode {
protected:
    T* data;
    int size;
    UnionFindNode* group;
public:

    UnionFindNode() = delete;

    UnionFindNode(T* data) : data(data), size(1) {}

    ~UnionFindNode() {
        delete data;
    }

    T* extract() {
        T* temp = this->data;
        this->data = nullptr;
        return temp;
    }

    UnionFindNode* getGroup() {
        if (this->group == nullptr) {
            return this;
        }
        UnionFindNode* actuallGroup = this->group->getGroup();
        this->group = actuallGroup;
        return actuallGroup;
    }

    T* getData() {
        return this->data;
    }

    void swapData(UnionFindNode* other) {
        T* temp = other->data;
        other->data = this->data;
        this->data = temp;
    }

    bool unite(UnionFindNode* node) {
        if (node == nullptr) {
            return false;
        }
        UnionFindNode* thisGroup = this->getGroup();
        UnionFindNode* otherGroup = node->getGroup();
        if (thisGroup == otherGroup) {
            return false;
        }
        if (thisGroup->size < otherGroup->size) {
            thisGroup->group = otherGroup;
        } else {
            otherGroup->group = thisGroup;
        }
        return true;
    }




};



#endif //UNIONFINDNODE_H
