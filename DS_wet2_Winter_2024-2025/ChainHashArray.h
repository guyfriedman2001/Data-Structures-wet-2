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
#define QUARTER_OF(a) (a*0.25)
#define EMPTY (0)


//todo remove for mivnei
#include <fstream>
#include <iostream>
using std::cout;
using std::ostream;
using std::endl;

//todo remove for mivnei



template<class T>
class ChainHashArray {
private:
    DeQue<Pair<T>>* data_arr;
    int arr_size;
    int amount_of_items;
    int capacity;

public:

    ChainHashArray() : capacity(EMPTY) {
        this->data_arr = nullptr;
        this->arr_size = INITIAL_SIZE;
        this->amount_of_items = EMPTY;
        this->updateCapacity();
        this->initializeArray();
    }

    ~ChainHashArray() {
        delete[] data_arr;
    }

    void insert(int key, T* value) { //fixme new mode
        this->insert(key, value, true);
    }

    T* find(int key) {
        int index = this->calcIndex(key);
        Pair<T> temp = Pair<T>(key);//new Pair<T>(key);
        Pair<T>* toFind = this->data_arr[index].find(temp);
        //delete temp;
        return toFind == nullptr ? nullptr : toFind->value;
    }

    T* remove(int key) {
        return this->remove(key,true);
    }

    void deleteItem(int key) {
        delete this->remove(key);
    }

protected:

    void insert(int key, T* value, bool checkForUpdateSize) {
        int insertionIndex = this->calcIndex(key);
        DeQue<Pair<T>>& desiredSlot = this->data_arr[insertionIndex];
        Pair<T>* newItem = new Pair<T>(key, value);
        desiredSlot.append(newItem);
        ++this->amount_of_items;
        if (checkForUpdateSize) {
            this->checkUpdateArr();
        }
    }

    /**
     *the same functionality as regular insert, but without
     *checking for size updates, for inside methods and usages
     *
     * @param key
     * @return
     */
    void insertImmediate(int key, T* value) {
        this->insert(key, value, false);
    }

    T* remove(int key, bool checkForUpdateSize) {
        int index = this->calcIndex(key);
        DeQue<Pair<T>>* toRemove = &(this->data_arr[index]);
        Pair<T> toRemovePair = Pair<T>(key);

        Pair<T>* toFind = (toRemove->remove(toRemovePair)); //fixme
        //delete toRemovePair;
        if (toFind == nullptr) {
            return nullptr;
        }
        T* value = toFind->extract();
        delete toFind;
        --this->amount_of_items;
        if (checkForUpdateSize) {
            this->checkUpdateArr();
        }
        return value;
    }

    /**
     *the same functionality as regular remove, but without
     *checking for size updates, for inside methods and usages
     *
     * @param key
     * @return
     */
    T* removeImmediate(int key) {
        return this->remove(key, false);
    }


    void initializeArray() {
        this->data_arr = new DeQue<Pair<T>>[this->arr_size];
        for (int i = 0; i < this->arr_size; ++i) {
            //this->data_arr[i] = *(new DeQue<Pair<T>>()); //fixme
            DeQue<Pair<T>>& desiredSlot = this->data_arr[i];
            desiredSlot.verifyInitialisation();
        }
    }

    ChainHashArray(int size)  : capacity(EMPTY) {
        this->data_arr = nullptr;
        this->arr_size = MAX(INITIAL_SIZE,size);
        this->amount_of_items = EMPTY;
        this->updateCapacity();
        this->initializeArray();
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
            return;
        }
        if (this->amount_of_items <= QUARTER_OF(this->capacity)) {
            this->makeSmaller();
        }
    }

    void resize(int new_capacity) {
        ChainHashArray<T>* other = new ChainHashArray(new_capacity);
        for (int i = 0; i < this->arr_size; i++) {
            DeQue<Pair<T>>& temp = (this->data_arr)[i];
            int tempSize = temp.getSize(); //fixme move from pointer to reference
            for (int j = 0; j < tempSize; j++) { //fixme problem
                Pair<T>* tempItem = temp.pop();
                other->insertImmediate(tempItem->key, tempItem->extract()); //fixme todo fix
                delete tempItem;
            }
        }
        this->swapData(other);
        delete other;
    }

    void makeBigger() {
        this->resize(MAKE_DOUBLE(this->arr_size));
    }

    void makeSmaller() {
        if(this->arr_size <= INITIAL_SIZE) {
            return;
        }
        this->resize(HALF_OF(this->arr_size));
    }

    template <typename K>
    void swap(K& item_1, K& item_2) {
        K temp = item_1; //fixme might be problematic
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

    /*
    ChainHashArray& operator =(ChainHashArray other) {
        if (this == &other) {
            return *this; //fixme
        }
        return *this;

    }
    */



    //todo remove for mivnei

    void printHelper(ostream& os) const {
        cout << "ChainHashArray of size " << this->arr_size;
        cout << ", with " << this->amount_of_items << " items";
        cout << " and a capacity of " << this->capacity;
        cout << ":" << endl;
        for (int i = 0; i < this->arr_size; i++) {
            if (i != 0) {
                cout << "," << endl;
            }
            DeQue<Pair<T>>& temp = this->data_arr[i];
            os << "at index " << i << ": " << endl;
            os << '{' << temp << '}';
        }
    }

    // Overloaded ostream operator
    friend ostream& operator<<(ostream& os, const ChainHashArray<T>& deque) {
        deque.printHelper(os);
        return os;
    }




    //todo remove for mivnei


};



#endif //CHAINHASHARRAY_H
