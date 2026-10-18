template <typename T>
inline DynamicArray<T>::DynamicArray(size_t initialCapacity)
    : data(nullptr), capacity(initialCapacity), size(0) {
    if (initialCapacity == 0) {
        throw std::invalid_argument("Initial capacity cannot be zero.");
    }

    data = new T[initialCapacity];
}

template <typename T>
inline DynamicArray<T>::~DynamicArray() noexcept {
    clear();
}

template <typename T>
inline DynamicArray<T>::DynamicArray(DynamicArray&& other) noexcept
    : data(nullptr), capacity(0), size(0) {
    std::swap(data, other.data);

    std::swap(capacity, other.capacity);
    std::swap(size, other.size);
}

template <typename T>
inline DynamicArray<T>::DynamicArray(const DynamicArray& other)
    : data(new T[other.capacity]), capacity(other.capacity), size(0) {
    try {
        for (size_t i = 0; i < other.size; ++i) {
            data[i] = other.data[i];
        }
    }
    catch (...) {
        delete[] data;

        throw;
    }

    size = other.size;
}

template <typename T>
inline DynamicArray<T>& DynamicArray<T>::operator=(DynamicArray<T>&& other) noexcept {
    if (&other != this) {
        std::swap(data, other.data);

        std::swap(capacity, other.capacity);
        std::swap(size, other.size);
    }

    return *this;
}

template <typename T>
inline DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& other) {
    if (&other != this) {
        size_t newCapacity = capacity < other.size ? other.capacity : capacity;

        T* newData = new T[newCapacity];

        try {
            for (size_t i = 0; i < other.size; ++i) {
                newData[i] = other.data[i];
            }
        }
        catch (...) {
            delete[] newData;

            throw;
        }

        delete[] data;

        data = newData;

        capacity = other.capacity;
        size = other.size;
    }

    return *this;
}

template <typename T>
inline bool DynamicArray<T>::contains(const T& element) const {
    for (size_t i = 0; i < size; ++i) {
        if (data[i] == element) return true;
    }

    return false;
}

template <typename T>
inline T& DynamicArray<T>::operator[](size_t position) {
    if (position >= size) {
        throw std::out_of_range("Position exceeds current array size.");
    }

    return data[position];
}

template <typename T>
inline const T& DynamicArray<T>::operator[](size_t position) const {
    if (position >= size) {
        throw std::out_of_range("Position exceeds current array size.");
    }

    return data[position];
}

template <typename T>
inline void DynamicArray<T>::clear() {
    delete[] data;

    data = nullptr;

    capacity = size = 0;
}

template <typename T>
inline void DynamicArray<T>::erase(size_t position) {
    if (position >= size) {
        throw std::out_of_range("Position exceeds current array size.");
    }

    // Shift elements left to fill the gap
    for (size_t i = position; i < size - 1; ++i) {
        data[i] = std::move(data[i + 1]);
    }

    --size;
}

template <typename T>
inline void DynamicArray<T>::insert(T&& element, size_t position) {
    if (position > size) {
        throw std::out_of_range("Position exceeds current array size.");
    }

    checkAndReserve(size + 1);

    // Shift elements right to make room
    for (size_t i = size; i > position; --i) {
        data[i] = std::move(data[i - 1]);
    }

    data[position] = std::move(element);

    ++size;
}

template <typename T>
inline void DynamicArray<T>::insert(const T& element, size_t position) {
    if (position > size) {
        throw std::out_of_range("Position exceeds current array size.");
    }

    checkAndReserve(size + 1);

    // Shift elements right to make room
    for (size_t i = size; i > position; --i) {
        data[i] = std::move(data[i - 1]);
    }

    data[position] = element;

    ++size;
}

template <typename T>
inline void DynamicArray<T>::popBack() {
    if (size == 0) {
        throw std::underflow_error("Cannot remove from an empty array.");
    }

    --size;
}

template <typename T>
inline void DynamicArray<T>::pushBack(T&& element) {
    checkAndReserve(size + 1);
    data[size] = std::move(element);

    ++size;
}

template <typename T>
inline void DynamicArray<T>::pushBack(const T& element) {
    checkAndReserve(size + 1);
    data[size] = element;

    ++size;
}

template <typename T>
inline void DynamicArray<T>::checkAndReserve(size_t targetSize) {
    // Ensure invariant: if data exists, capacity is non-zero
    assert(!data || capacity != 0);

    size_t newCapacity = data ? capacity : 1;

    // Geometric growth (doubling) until target size fits
    while (newCapacity < targetSize) {
        newCapacity *= 2;
    }

    if (capacity != newCapacity) {
        reserve(newCapacity);
    }
}

template <typename T>
inline void DynamicArray<T>::reserve(size_t newCapacity) {
    if (newCapacity == 0) {
        throw std::invalid_argument("New capacity cannot be zero.");
    }

    T* newData = new T[newCapacity];

    try {
        for (size_t i = 0; i < newCapacity && i < size; ++i) {
            newData[i] = data[i];
        }
    }
    catch (...) {
        delete[] newData;

        throw;
    }

    delete[] data;

    data = newData;

    capacity = newCapacity;

    // Clamp size if shrinking
    size = capacity < size ? capacity : size;
}