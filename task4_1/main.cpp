#include <iostream>
#include <map>
#include <sstream>
#include <algorithm>

int main() {
    std::string input;
    std::getline(std::cin, input);

    std::stringstream ss(input);
    std::string word;

    std::map<std::string, int> word_count;

    while (ss >> word) {
        // Используем transform для приведения слов к нижнему регистру (регистронезависимый подсчет)
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        word_count[word]++;
    }

    // Выводим результаты, отсортированные в алфавитном порядке
    for (const auto& pair : word_count) {
        std::cout << pair.first << " " << pair.second << std::endl;
    }

    return 0;
}
