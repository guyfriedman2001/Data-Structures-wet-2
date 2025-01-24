//
// Created by Guy Friedman on 24/01/2025.
//

#ifndef CHAINHASHARRAY_H
#define CHAINHASHARRAY_H
#include "DeQue.h"
#include "Pair.h"
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
    DeQue<Pair<T>>* data_arr;
    int arr_size;
    int amount_of_items;
    int capacity;
public:

    ChainHashArray() {
        data_arr = new DeQue<Pair<T>>[INITIAL_SIZE];
        arr_size = INITIAL_SIZE;
        amount_of_items = EMPTY;
        this->updateCapacity();
    }



    ~ChainHashArray() {
        delete[] data_arr;
    }

    void insert(int key, T* value) {
        int insertionIndex = this->calcIndex(key);
        auto newPair = new Pair<T>(key, value);
        auto requieredDeQue = this->data_arr[insertionIndex];
        requieredDeQue.append(newPair);
        ++this->amount_of_items;
    }



    T* find(int key) {
        int index = this->calcIndex(key);
        auto toFind = this->data_arr[index].find(key);
        return toFind == nullptr ? nullptr : toFind->value;
    }

    T* remove(int key) {
        int index = this->calcIndex(key);
        Pair<T>* toFind = (this->data_arr[index])->remove(key);
        if (toFind == nullptr) {
            return nullptr;
        }
        T* value = toFind->extract();
        --this->amount_of_items;
        return value;
    }

protected:

    ChainHashArray(int size) {
        data_arr = new DeQue<Pair<T>>[MAX(INITIAL_SIZE,size)];
        arr_size = MAX(INITIAL_SIZE,size);
        amount_of_items = EMPTY;
        this->updateCapacity();
    }



    void updateCapacity() {
        capacity = this->arr_size * MAX_FILL_RATIO;
    }



    int calcIndex(int key) {
        return key % this->arr_size;
    }

    void checkUpdateArr() {
        if (this->amount_of_items == this->capacity) {
            this->makeBigger();
        }
        if (this->amount_of_items <= QUARTER_OF(this->capacity)) {
            this->makeSmaller();
        }
    }

    void resize(int new_capacity) {
        auto other = new ChainHashArray(new_capacity);
        for (int i = 0; i < this->arr_size; i++) {
            DeQue<Pair<T>>* temp = (this->data_arr)[i];
            int tempSize = temp->getSize();
            for (int j = 0; j < tempSize; j++) {
                Pair<T>* tempItem = temp->pop();
                other->append(tempItem->key, tempItem);
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
        swap<int>(other->arr_size, this->arr_size);
        swap<int>(other->amount_of_items, this->amount_of_items);
        swap<int>(other->capacity, this->capacity);
        swap<DeQue<Pair<T>>*>(other->data_arr, this->data_arr);
    }

    ChainHashArray& operator =(ChainHashArray other) {
        if (this == &other) {
            return *this; //fixme
        }
        return *this;

    }

    //todo - copy constructor? resize func
};



#endif //CHAINHASHARRAY_H
