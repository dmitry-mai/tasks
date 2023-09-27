#include <iostream>
#include <cstring>
#include <vector>
#include <cassert>

class String {
private:
    const char *buf = nullptr;
public:
    explicit String(const char *buf) {
        this->buf = buf;
    }

    ~String() {
        delete[] this->buf;
    }

    void show() {
        std::cout << this->buf;
    }

    int length() {
        return std::strlen(this->buf) + 1;
    }
};


int main() {
    std::vector<std::pair<std::string, int>> truth{
            {"",    1},
            {"a",   2},
            {"ab",  3},
            {"abc", 4},
    };

    for (auto [str, length]: truth) {
        auto foo = new String(str.c_str());
        std::cout << "Testing: \"", foo->show(), std::cout << "\"\t(" << length << ") | ";
        std::cout << " Output: " << foo->length() << std::endl;
        assert(foo->length() == length);
    }

    std::cout << "All tests have succeeded";
    return 0;
}