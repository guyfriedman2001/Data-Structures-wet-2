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

    Pair(int key) {
        this->key = key;
        this->value = nullptr;
    }

    Pair() {
        this->key = DEFAULT_KEY;
        this->value = nullptr;
    }

    ~Pair() {
        delete this->value;
    }

    T* extract() {
        auto value = this->value;
        this->value = nullptr;
        return value;
    }

    void nullify() {
        this->key = DEFAULT_KEY;
        this->value = nullptr;
    }

    bool operator ==(const Pair& other) {
        return this->key == other.key;
    }

};



#endif //PAIR_H
