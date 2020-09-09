#include <iostream>

class DynamicArray {
private:
    int8_t *data;
    size_t size;

public:
    explicit DynamicArray(size_t initialSize) {
        size = initialSize;
        data = new int8_t[size];
    }

    ~DynamicArray() {
        delete[] data;
    }

    [[nodiscard]] int8_t get(size_t index) const {
        if (index >= size) {
            std::cerr << "Error: Index out of bounds." << std::endl;
            return 0;
        }
        return data[index];
    }

    void set(size_t index, int8_t value) {
        if (index >= size) {
            std::cerr << "Error: Index out of bounds." << std::endl;
            return;
        }
        if (value < -100 || value > 100) {
            std::cerr << "Error: Value out of range [-100, 100]." << std::endl;
            return;
        }
        data[index] = value;
    }

    void printElements() const {
        for (size_t i = 0; i < size; ++i)
            std::cout << static_cast<int>(data[i]) << " ";
        std::cout << std::endl;
    }

    DynamicArray(const DynamicArray &other) {
        size = other.size;
        data = new int8_t[size];
        for (size_t i = 0; i < size; ++i)
            data[i] = other.data[i];
    }

    void append(int8_t value) {
        if (size == 0) {
            data = new int8_t[1];
            data[0] = value;
            size = 1;
            return;
        }

        auto *newData = new int8_t[size + 1];
        for (size_t i = 0; i < size; ++i)
            newData[i] = data[i];

        newData[size] = value;
        delete[] data;
        data = newData;
        ++size;
    }

    void addArray(const DynamicArray &other) {
        if (size != other.size) {
            std::cerr << "Error: Arrays must be of the same size for addition." << std::endl;
            return;
        }

        for (size_t i = 0; i < size; ++i)
            data[i] += other.data[i];
    }

    void subtractArray(const DynamicArray &other) {
        if (size != other.size) {
            std::cerr << "Error: Arrays must be of the same size for subtraction." << std::endl;
            return;
        }

        for (size_t i = 0; i < size; ++i)
            data[i] -= other.data[i];
    }
};

int main() {
    size_t size1, size2;

    std::cin >> size1;
    DynamicArray first(size1);
    for (size_t i = 0; i < size1; ++i) {
        int element;
        std::cin >> element;
        first.set(i, (int8_t) element);
    }

    std::cin >> size2;
    DynamicArray second(size2);
    for (size_t i = 0; i < size2; ++i) {
        int element;
        std::cin >> element;
        second.set(i, (int8_t) element);
    }

    size_t numCommands;
    std::cin >> numCommands;

    for (size_t i = 0; i < numCommands; ++i) {
        int command;
        std::cin >> command;

        size_t arrayNum;
        std::cin >> arrayNum;

        if (command == 1) {
            size_t index;
            std::cin >> index;
            std::cout << (arrayNum == 1 ? first : second).get(index) << std::endl;
        } else if (command == 2) {
            size_t index;
            int value;
            std::cin >> index >> value;
            (arrayNum == 1 ? first : second)
                    .set(index, (int8_t) value);
        } else if (command == 3) {
            int value;
            std::cin >> value;

            (arrayNum == 1 ? first : second).append((int8_t) value);
        } else if (command == 4) {
            (arrayNum == 1 ? first : second).printElements();
        } else if (command == 5) {
            (arrayNum == 1 ? first : second)
                    .addArray(arrayNum != 1 ? first : second);
        } else if (command == 6) {
            (arrayNum == 1 ? first : second)
                    .subtractArray(arrayNum != 1 ? first : second);
        }
    }

    return 0;
}