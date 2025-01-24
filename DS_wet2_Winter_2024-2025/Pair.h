//
// Created by Guy Friedman on 24/01/2025.
//

#ifndef PAIR_H
#define PAIR_H

constexpr int DEFAULT_KEY = 0;

template <typename T>
class Pair {
public:
    int key;
    T* value;

    Pair(int key, T* value) {
        this->key = key;
        this->value = value;
    }

    Pair() {
        this->key = DEFAULT_KEY;
        this->value = nullptr;
    }

};



#endif //PAIR_H
