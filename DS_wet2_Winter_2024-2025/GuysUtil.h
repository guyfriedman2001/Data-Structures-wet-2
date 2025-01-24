//
// Created by Guy Friedman on 24/01/2025.
//

#ifndef GUYSUTIL_H
#define GUYSUTIL_H
namespace GuysUtil {
    template <typename K>
    void swap(K& item_1, K& item_2) {
        K* temp = item_1;
        item_1 = item_2;
        item_2 = temp;
    }
}

#endif //GUYSUTIL_H
