class DynamicArrayIterator {
    friend class DynamicArray;

public:
    // === POSTFIX INCREMENT & DECREMENT ===

    DynamicArrayIterator operator++(int) {
        DynamicArrayIterator copy(*this);

        ++(*this);

        return copy;
    }

    DynamicArrayIterator operator--(int) {
        DynamicArrayIterator copy(*this);

        --(*this);

        return copy;
    }

    // === ARRAY SUBSCRIPTING ===

    T& operator[](int offset) {
        return *(ptr + offset);
    }

    const T& operator[](int offset) const {
        return *(ptr + offset);
    }

    // === MEMBER ACCESS THROUGH POINTER ===

    T* operator->() {
        return ptr;
    }

    const T* operator->() const {
        return ptr;
    }

    // === PREFIX INCREMENT & DECREMENT ===

    DynamicArrayIterator& operator++() {
        ++ptr;

        return *this;
    }

    DynamicArrayIterator& operator--() {
        --ptr;

        return *this;
    }

    // === INDIRECTION (DEREFERENCE) ===

    T& operator*() {
        return *ptr;
    }

    const T& operator*() const {
        return *ptr;
    }

    // === ADDITION ===

    DynamicArrayIterator operator+(int offset) const {
        DynamicArrayIterator copy(*this);
        copy += offset;

        return copy;
    }

    // === COMPARISON OPERATORS ===

    bool operator<(const DynamicArrayIterator& other) const {
        return ptr < other.ptr;
    }

    bool operator<=(const DynamicArrayIterator& other) const {
        return !(*this > other);
    }

    bool operator>(const DynamicArrayIterator& other) const {
        return other < *this;
    }

    bool operator>=(const DynamicArrayIterator& other) const {
        return !(*this < other);
    }

    // === EQUALITY ===

    bool operator==(const DynamicArrayIterator& other) const {
        return other.ptr == ptr;
    }

    // === INEQUALITY ===

    bool operator!=(const DynamicArrayIterator& other) const {
        return !(*this == other);
    }

    // === ASSIGNMENT BY SUM ===

    DynamicArrayIterator& operator+=(int offset) {
        ptr += offset;

        return *this;
    }

private:
    DynamicArrayIterator(T* ptr)
        : ptr(ptr) {
    }

    T* ptr;
};