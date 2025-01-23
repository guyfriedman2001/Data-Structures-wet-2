//
// Created by Guy Friedman on 22/01/2025.
//

#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#define DEFAULT_CAPACITY 32
#include <new>
#include <cassert>


template <typename T>
class DynamicArray {
protected:
    T* data;
    int arr_size;
    int items_held;
public:
    DynamicArray() : data(new T*[DEFAULT_CAPACITY]{nullptr}), arr_size(0), items_held(0) {}

    DynamicArray(int size) : data(new T*[size]{nullptr}), arr_size(size), items_held(0) {}

    ~DynamicArray() {
        delete[] data;
    }

    DynamicArray(const DynamicArray<T>& other, int new_size) :
    data(new T*[new_size]), arr_size(new_size) , items_held(0) {
        try {
            for (T* other : other.data) {
                if (other != nullptr) {
                    this->insert(other);
                }
            }
        } catch (std::bad_alloc& e) {
            delete[] data;
            throw e;
        }
    }

    void insert(T* other) {
        //todo
    }

    DynamicArray* decrease() {
        DynamicArray* other = new DynamicArray(this, ((this->size) / 2));
        //todo
    }

    DynamicArray* increase() {
        DynamicArray* other = new DynamicArray(this, ((this->size) * 2));
        //todo
    }

    template <typename K>
    void swap(K& item_1, K& item_2) {
        K* temp = item_1;
        item_1 = item_2;
        item_2 = temp;
    }

    void SwapInfo(DynamicArray* other) {
        assert(other != nullptr);
        //if (other == nullptr) {throw "Null pointer provided -> Dynamic array -> SwapInfo";}
        swap<T*>(this->data, other->data);
        swap<int>(this->size, other->size);
        swap<int>(this->fill_percent, other->fill_percent);
    }
    DynamicArray& operator=(const DynamicArray& other) {
        DynamicArray other_copy(other);
        this->swap(other_copy);
        return *this;
    }

    inline bool isFull(){
        //todo
        return true;
    }

    inline bool isAlmostEmpty(){
        //todo
        return true;
    }


};



#endif //DYNAMICARRAY_H
