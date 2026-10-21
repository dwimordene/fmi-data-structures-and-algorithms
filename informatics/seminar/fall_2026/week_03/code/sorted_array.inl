template <typename T>
int SortedArray<T>::find(const T& elem) const {
    size_t left = 0, right = data.getSize();

    while (left < right) {
        size_t middle = left + (right - left) / 2;

        const T& current = data[middle];

        if (current < elem) left = middle + 1;
        else if (elem < current) right = middle;
        else return (int)middle;
    }

    return -1;
}

template <typename T>
void SortedArray<T>::add(const T& elem) {
    data.pushBack(elem);
    moveTowardBeginning(data.getSize() - 1);
}

template <typename T>
void SortedArray<T>::moveTowardBeginning(size_t pos) {
    if (pos == 0 || data[pos - 1] < data[pos]) {
        return;
    }

    T elem = std::move(data[pos]);

    while (pos && elem < data[pos - 1]) {
        data[pos] = std::move(data[pos - 1]);

        --pos;
    }

    data[pos] = std::move(elem);
}

template <typename T>
void SortedArray<T>::moveTowardEnd(size_t pos) {
    if (pos == data.getSize() - 1 || data[pos] < data[pos + 1]) {
        return;
    }

    T elem = std::move(data[pos]);

    while (pos < data.getSize() - 1 && data[pos + 1] < elem) {
        data[pos] = std::move(data[pos + 1]);

        ++pos;
    }

    data[pos] = std::move(elem);
}