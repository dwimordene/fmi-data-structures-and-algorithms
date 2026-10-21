class SortedArrayProxy {
    friend class SortedArray;

public:
    SortedArrayProxy& operator=(const SortedArrayProxy& other) {
        return operator=((const T&)other);
    }

    SortedArrayProxy& operator=(const T& value) {
        if (owner.data[index] < value) {
            owner.data[index] = value;
            owner.moveTowardEnd(index);
        }
        else if (value < owner.data[index]) {
            owner.data[index] = value;
            owner.moveTowardBeginning(index);
        }
        else {
            owner.data[index] = value;
        }

        return *this;
    }

    operator const T& () const {
        return owner.data[index];
    }

private:
    SortedArrayProxy(SortedArray& owner, size_t index)
        : owner(owner), index(index) {
    }

    SortedArray& owner;
    size_t index;
};