#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

struct Object {
    std::string name;
    int length;
    int width;
    int height;
    float weight;
};

bool isObjectMatch(const Object &obj, int param, char op, float value) {
    std::function<bool(float, float)> func;
    switch (op) {
        case '>':
            func = [](float r, float l) { return r > l; };
            break;
        case '<':
            func = [](float r, float l) { return r < l; };
            break;
        case '=':
            func = [](float r, float l) { return r == l; };
            break;
        default:
            return false;
    }

    switch (param) {
        case 2:
            return func(obj.length, value);
        case 3:
            return func(obj.width, value);
        case 4:
            return func(obj.height, value);
        case 5:
            return func(obj.weight, value);
        default:
            return false;
    }
}

int main() {
    int n;
    std::cin >> n;

    std::vector<Object> objects(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> objects[i].name >> objects[i].length >> objects[i].width >> objects[i].height >> objects[i].weight;
    }

    int numCommands;
    std::cin >> numCommands;

    std::vector<Object> currentList = objects;

    for (int i = 0; i < numCommands; ++i) {
        int command, param;
        char op;
        float value;

        std::cin >> command;

        if (command == 1) {
            std::cin >> param >> op >> value;

            auto it = std::remove_if(currentList.begin(), currentList.end(), [&](const Object &obj) {
                return !isObjectMatch(obj, param, op, value);
            });

            currentList.erase(it, currentList.end());
        } else if (command == 2) {
            if (currentList.empty()) {
                std::cout << "empty" << std::endl;
            } else {
                for (const auto &obj: currentList) {
                    std::cout << obj.name << " " << obj.length << " " << obj.width << " " << obj.height << " "
                              << obj.weight << std::endl;
                }
            }
        } else if (command == 3) {
            currentList = objects;
        }
    }

    return 0;
}
