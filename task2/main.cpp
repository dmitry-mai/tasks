#include <iostream>
#include <stdexcept>

class DynamicArray {
private:
    int16_t *data;
    size_t size;

public:
    explicit DynamicArray(size_t initialSize) {
        size = initialSize;
        data = new int16_t[size];
    }

    ~DynamicArray() {
        delete[] data;
    }

    [[nodiscard]] int16_t get(size_t index) const {
        if (index >= size)
            throw std::out_of_range("get");

        return data[index];
    }

    void set(size_t index, int16_t value) {
        if (index >= size)
            throw std::out_of_range("set");
        if (value < -100 || value > 100)
            throw std::invalid_argument("set");

        data[index] = value;
    }

    void printElements() const {
        for (size_t i = 0; i < size - 1; i++)
            std::cout << data[i] << " ";
        std::cout << data[size - 1];
        std::cout << std::endl;
    }

    DynamicArray(const DynamicArray &other) {
        size = other.size;
        data = new int16_t[size];
        for (size_t i = 0; i < size; i++)
            data[i] = other.data[i];
    }

    void push_back(int16_t value) {
        if (value < -100 || value > 100)
            throw std::invalid_argument("push_back");

        auto *new_data = new int16_t[size + 1];
        for (size_t i = 0; i < size; i++)
            new_data[i] = data[i];

        new_data[size] = value;
        size++;
        delete[] data;
        data = new_data;
    }

    void addArray(DynamicArray *other) {
        auto s = size > other->size ? other->size : size;

        for (size_t i = 0; i < s; i++)
            data[i] += other->data[i];
    }

    void subtractArray(DynamicArray *other) {
        auto s = size > other->size ? other->size : size;

        for (size_t i = 0; i < s; i++)
            data[i] -= other->data[i];
    }
};

int main() {
    try {
        size_t size1, size2;

        std::cin >> size1;
        DynamicArray first(size1);
        for (size_t i = 0; i < size1; i++) {
            int16_t element;
            std::cin >> element;
            try {
                first.set(i, element);
            } catch (const std::invalid_argument &ex) {
                std::cout << "std:invalid_argument:" << ex.what() << std::endl;
            }
        }

        std::cin >> size2;
        DynamicArray second(size2);
        for (size_t i = 0; i < size2; i++) {
            int16_t element;
            std::cin >> element;
            try {
                second.set(i, element);
            } catch (const std::invalid_argument &ex) {
                std::cout << "std:invalid_argument:" << ex.what() << std::endl;
            }
        }

        size_t numCommands;
        std::cin >> numCommands;

        for (size_t i = 0; i < numCommands; i++) {
            int command, array_num;
            std::cin >> command >> array_num;

            auto [array, other_array] = array_num == 1 ?
                                        std::make_pair(&first, &second) :
                                        std::make_pair(&second, &first);

            try {
                if (command == 1) {
                    size_t index;
                    std::cin >> index;
                    std::cout << array->get(index) << std::endl;
                } else if (command == 2) {
                    size_t index;
                    int16_t value;
                    std::cin >> index >> value;
                    array->set(index, value);
                } else if (command == 3) {
                    int16_t value;
                    std::cin >> value;
                    array->push_back(value);
                } else if (command == 4)
                    array->printElements();
                else if (command == 5)
                    array->addArray(other_array);
                else if (command == 6)
                    array->subtractArray(other_array);
            } catch (const std::out_of_range &ex) {
                std::cout << "std:out_of_range:" << ex.what() << std::endl;
            } catch (const std::invalid_argument &ex) {
                std::cout << "std:invalid_argument:" << ex.what() << std::endl;
            }
        }
    } catch (const std::bad_alloc &ex) {
        std::cout << "std:bad_alloc" << std::endl;
    }
    return 0;
}
