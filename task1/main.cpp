#include <iostream>
#include <string>
#include <cstring>

int calculateVariant(const std::string &name, unsigned int numVariants) {
    if (name.empty())
        return -1;

    auto firstLetterCode = static_cast<unsigned int>(name[0]);

    return firstLetterCode % numVariants;
}

int main() {
    
    std::string name;
    unsigned int variants;

    std::cout << "Введите ваше имя: ", std::cin >> name;
    std::cout << "Введите количество вариантов: ", std::cin >> variants;
    std::cout << "Ваш номер варивнта: " << calculateVariant(name, variants) << std::endl;
    return 0;
}
