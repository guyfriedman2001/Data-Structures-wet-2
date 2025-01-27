//
// Created by Guy Friedman on 27/01/2025.
//

#ifndef TEAMUNIONFIND_H
#define TEAMUNIONFIND_H
#include "UnionFindTwo.h"
#include "uptree_jockeys.h"


class TeamUnionFind : public UnionFind<TeamNode> {
public:

    TeamUnionFind() : UnionFind<TeamNode>() {}

    ~TeamUnionFind() = default;

};



#endif //TEAMUNIONFIND_H
