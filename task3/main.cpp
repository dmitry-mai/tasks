#include <iostream>
#include <fstream>
#include <string>


int main() {
    std::ifstream input("input.txt");
    std::ofstream output("output.gift");

    std::cout << "what" << std::endl;
    bool question = false;
    std::string line;

    while (getline(input, line)) {
        if (isdigit(line[0])) {
            if (question) // cover previous line if it was a question
                output << "}" << std::endl;
            output << line.substr(0, line.length() - 1) << " {" << std::endl;
            question = true;
        } else if (line[0] == '+' || line[0] == '-')
            output << (line[0] == '+' ? '=' : '~') << ' ' << line.substr(2) << std::endl;
    }

    if (question)
        output << "}" << "\n";
    return 0;
}