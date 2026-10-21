#pragma once

#include <cassert>
#include <cstdint>
#include <stdexcept>
#include <utility>

template <typename T>
class DynamicArray {
public:
    // === OBJECT LIFE-CYCLE MEMBERS ===

    explicit DynamicArray(size_t initialCapacity = 16);
    ~DynamicArray() noexcept;

    DynamicArray(DynamicArray&& other) noexcept;
    DynamicArray(const DynamicArray& other);

    DynamicArray& operator=(DynamicArray&& other) noexcept;
    DynamicArray& operator=(const DynamicArray& other);

    // === INFORMATION METHODS ===

    bool contains(const T& elem) const;

    bool isEmpty() const {
        return size == 0;
    }

    size_t getCapacity() const {
        return capacity;
    }

    size_t getSize() const {
        return size;
    }

    // === ACCESS OPERATORS ===

    T& operator[](size_t pos);
    const T& operator[](size_t pos) const;

    // === MODIFIERS ===

    void clear();
    void erase(size_t pos);
    void insert(T&& elem, size_t pos);
    void insert(const T& elem, size_t pos);
    void popBack();
    void pushBack(T&& elem);
    void pushBack(const T& elem);

    // === ITERATORS ===

#include "dynamic_array_iterator.inl"

    DynamicArrayIterator begin() {
        return DynamicArrayIterator(data);
    }

    DynamicArrayIterator end() {
        return DynamicArrayIterator(data + size);
    }

protected:
    T* data;
    size_t capacity, size;

private:
    // === HELPER METHODS ===

    // Checks if geometric growth is needed and triggers reserve
    void checkAndReserve(size_t targetSize);

    // Reallocates buffer to a new capacity with exception safety
    void reserve(size_t newCapacity);
};

#include "dynamic_array.inl"