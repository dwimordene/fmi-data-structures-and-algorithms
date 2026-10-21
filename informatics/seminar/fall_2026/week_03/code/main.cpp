#include <iostream>
#include <stdexcept>

#include "sorted_array.hpp"

int main() {
    try {
        SortedArray<int> arr;
        arr.add(10);
        arr.add(30);

        // Insert 20 while maintaining sorted order
        arr.add(20);

        for (size_t i = 0; i < arr.getSize(); ++i) {
            std::cout << arr[i] << " ";
        }

        std::cout << "\n";

        // The proxy intercepts the assignment, updates the element's value,
        // and repositions it if necessary to preserve the array's sorted order
        arr[1] = 99;

        for (size_t i = 0; i < arr.getSize(); ++i) {
            std::cout << arr[i] << " ";
        }

        std::cout << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "[Caught Exception]: " << e.what() << std::endl;
    }

    return 0;
}