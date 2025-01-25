#ifndef UNIONFIND_H
#define UNIONFIND_H

#include <cassert>
#include "ChainHashArray.h"

template<class T>
class UnionFind {
protected:
    typedef int set_id_t;
    ChainHashArray<T> m_sets;           // Maps roots to set descriptions
    ChainHashArray<size_t> m_sizes;     // Maps roots to sizes of their trees
    ChainHashArray<set_id_t> m_parents; // Maps each set to its parent in the trees

public:
    UnionFind() = default;

    virtual ~UnionFind() = default;

    UnionFind(const UnionFind& other) = default;

    UnionFind(UnionFind&& other) noexcept = default;

    UnionFind& operator=(const UnionFind& other) = default;

    UnionFind& operator=(UnionFind&& other) noexcept = default;

    void makeSet(set_id_t setId, const T& set);

    virtual T& unionSets(set_id_t root1, set_id_t root2);

    T& getRootSet(set_id_t root); // Get the set description of the root

    set_id_t findRoot(set_id_t setId); // Find the root of the tree containing setId

    T& findSet(set_id_t setId); // = findRoot + getRootSet

    bool hasEverExisted(set_id_t member) const;
};


template<class T>
void UnionFind<T>::makeSet(set_id_t setId, const T& set) {
    if (!hasEverExisted(setId)) {
        m_parents.insert(setId, setId);
        m_sets.insert(setId, set);
        m_sizes.insert(setId, 1);
    }
}

template<class T>
T& UnionFind<T>::unionSets(set_id_t root1, set_id_t root2) {
    assert(m_sizes.find(root1) != nullptr && m_sizes.find(root2) != nullptr);

    if (*m_sizes.find(root1) < *m_sizes.find(root2)) {
        std::swap(root1, root2);
    }
    m_parents.insert(root2, root1);
    *m_sizes.find(root1) += *m_sizes.find(root2);
    m_sets.remove(root2);
    m_sizes.remove(root2);
    return getRootSet(root1);
}

template<class T>
T& UnionFind<T>::getRootSet(set_id_t root) {
    assert(m_sets.find(root) != nullptr);
    return *m_sets.find(root);
}

template<class T>
typename UnionFind<T>::set_id_t UnionFind<T>::findRoot(set_id_t setId) {
    if (*m_parents.find(setId) != setId) {
        m_parents.insert(setId, findRoot(*m_parents.find(setId)));
    }
    return *m_parents.find(setId);
}

template<class T>
T& UnionFind<T>::findSet(set_id_t setId) {
    return getRootSet(findRoot(setId));
}

template<class T>
bool UnionFind<T>::hasEverExisted(set_id_t member) const {
    return m_parents.find(member) != nullptr;
}

#endif // UNIONFIND_H
