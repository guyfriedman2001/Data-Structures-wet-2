//
// Created by Guy Friedman on 24/01/2025.
//

#ifndef CHAINHASHARRAY_H
#define CHAINHASHARRAY_H
#include "DeQue.h"
#include <cassert>
constexpr int MAX_FILL_RATIO = 10;
constexpr int INITIAL_SIZE = 16;
#define MAX(a,b) (a>b)?a:b
#define MIN(a,b) (a<b)?a:b
#define MAKE_DOUBLE(a) (a*2)
#define HALF_OF(a) (a*0.5)
#define QUARTER_OF(a) (a*0.5)
#define EMPTY (0)

template<class T>
class ChainHashArray {
private:
    DeQue<T>* data_arr;
    int arr_size;
    int ammount_of_items;
    int capacity;
public:

    ChainHashArray() {
        data_arr = new DeQue<T>[INITIAL_SIZE];
        arr_size = INITIAL_SIZE;
        ammount_of_items = EMPTY;
        this->updateCapacity();
    }

    ChainHashArray(int size) {
        data_arr = new DeQue<T>[MAX(INITIAL_SIZE,size)];
        arr_size = MAX(INITIAL_SIZE,size);
        ammount_of_items = EMPTY;
        this->updateCapacity();
    }

    ~ChainHashArray() {
        delete[] data_arr;
    }

    void updateCapacity() {
        capacity = this->arr_size * MAX_FILL_RATIO;
    }

    void insert(T item, int index) {
        int insertionIndex = this->calcIndex(index);
        this->data_arr[insertionIndex].insert(item);
        ++this->ammount_of_items;
    }

    int calcIndex(int index) {
        return index % this->arr_size;
    }

    void checkUpdateArr() {
        if (this->ammount_of_items == this->capacity) {
            this->makeBigger();
        }
        if (this->ammount_of_items <= QUARTER_OF(this->capacity)) {
            this->makeSmaller();
        }
    }

    void resize(int new_capacity) {
        auto other = new ChainHashArray(new_capacity);
        for (int i = 0; i < this->arr_size; i++) {
            DeQue<T>* temp = (this->data_arr)[i];
            int tempSize = temp->getSize();
            for (int j = 0; j < tempSize; j++) {
                T* tempItem = temp->pop(j);
                other->insert(tempItem); //todo - refactor code to work with DeQue<Pair<T>>
            }
        }
        this->swapData(other);
        delete other;
    }

    void makeBigger() {
        this->resize(MAKE_DOUBLE(this->arr_size));
    }

    void makeSmaller() {
        if(this->arr_size == INITIAL_SIZE) {
            return;
        }
        this->resize(HALF_OF(this->arr_size));
    }

    template <typename K>
    void swap(K& item_1, K& item_2) {
        K* temp = item_1;
        item_1 = item_2;
        item_2 = temp;
    }

    void swapData(ChainHashArray* other) {
        assert(other != nullptr);
        //todo
    }

    ChainHashArray& operator =(ChainHashArray other) {
        if (this == &other) {
            return *this;
        }
        return *this;

    }

    //todo - copy constructor? resize func
};



#endif //CHAINHASHARRAY_H
