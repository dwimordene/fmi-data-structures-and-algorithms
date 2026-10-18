#include <iostream>
#include <string>

#include "dynamic_array.hpp"

template <typename T>
void display(const DynamicArray<T>& arr, const std::string& label) {
    std::cout << "--- " << label << " ---\n";
    std::cout << "Capacity: " << arr.getCapacity() << "\n";
    std::cout << "Size:     " << arr.getSize() << "\n";

    std::cout << "Elements: ";

    for (size_t i = 0; i < arr.getSize(); ++i) {
        std::cout << arr[i] << (i + 1 < arr.getSize() ? ", " : " ");
    }

    std::cout << "\n\n";
}

int main() {
    try {
        // === BASIC CONSTRUCTION ===

        DynamicArray<int> numbers(2);
        display(numbers, "Initial (Empty) Array");

        // === GEOMETRIC GROWTH TEST ===

        std::cout << "Pushing back elements...\n\n";

        numbers.pushBack(10);
        numbers.pushBack(20);
        numbers.pushBack(30);
        numbers.pushBack(40);

        display(numbers, "After Pushing");

        // === ELEMENT MODIFICATION & ACCESS ===

        numbers[1] = 99;

        std::cout
            << "Modified element at index 1. Current value: "
            << numbers[1] << ".\n\n";

        // === INSERT ===

        std::cout << "Inserting element at index 1...\n\n";

        numbers.insert(50, 1);

        display(numbers, "After Insert");

        // === ERASE ===

        std::cout << "Erasing element at index 3...\n\n";

        numbers.erase(3);

        display(numbers, "After Erase");

        // === COPY SEMANTICS ===

        DynamicArray<int> copy = numbers;
        copy.pushBack(500);
        display(copy, "Copy (With 500 Pushed)");
        display(numbers, "Original (Unchanged)");

        // === MOVE SEMANTICS ===

        DynamicArray<int> temp(std::move(copy));
        display(copy, "Moved-From Array");
        display(temp, "Moved-To Array");

        // === OUT-OF-BOUNDS ACCESS ===

        std::cout << "Testing out-of-bounds access...\n\n";
        std::cout << numbers[100] << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "[Caught Exception]: " << e.what() << std::endl;
    }

    return 0;
}