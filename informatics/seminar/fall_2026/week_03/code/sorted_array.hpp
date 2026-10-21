#pragma once

#include "dynamic_array.hpp"

template <typename T>
class SortedArray {
public:
    // === INFORMATION METHODS ===

    bool isEmpty() const {
        return data.isEmpty();
    }

    int find(const T& elem) const;

    size_t getSize() const {
        return data.getSize();
    }

    // === ACCESS OPERATORS ===

#include "sorted_array_proxy.inl"

    SortedArrayProxy operator[](size_t pos) {
        return SortedArrayProxy(*this, pos);
    }

    const T& operator[](size_t pos) const {
        return data[pos];
    }

    // === MODIFIERS ===

    void add(const T& elem);

    void clear() {
        data.clear();
    }

    void remove(size_t pos) {
        data.erase(pos);
    }

private:
    // Used when an element is too small for its current position,
    // such as inserting a new element at the end
    // or decreasing an existing element's value
    void moveTowardBeginning(size_t pos);

    // Used when an element is too large for its current position,
    // such as increasing an existing element's value
    void moveTowardEnd(size_t pos);

    DynamicArray<T> data;
};

#include "sorted_array.inl"