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

    bool contains(const T& element) const;

    inline bool isEmpty() const {
        return size == 0;
    }

    inline size_t getCapacity() const {
        return capacity;
    }

    inline size_t getSize() const {
        return size;
    }

    // === ACCESS OPERATORS ===

    T& operator[](size_t position);
    const T& operator[](size_t position) const;

    // === MODIFIERS ===

    void clear();
    void erase(size_t position);
    void insert(T&& element, size_t position);
    void insert(const T& element, size_t position);
    void popBack();
    void pushBack(T&& element);
    void pushBack(const T& element);

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