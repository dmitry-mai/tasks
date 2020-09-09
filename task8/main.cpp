#include <iostream>
#include <vector>
#include <map>
#include <string>

// Определяем структуру для представления компонента
struct Component
{
    std::string id;
    std::string type;
    float x, y;          // Центральные координаты
    float width, height; // Размеры
};

// Функция для проверки, выходит ли компонент за границы платы
bool isOutOfBounds(const Component &comp, int boardWidth, int boardHeight)
{
    // Вычисляем края компонента
    float leftEdge = comp.x - comp.width / 2;
    float rightEdge = comp.x + comp.width / 2;
    float topEdge = comp.y - comp.height / 2;
    float bottomEdge = comp.y + comp.height / 2;

    // Проверяем, выходит ли компонент за границы платы
    return leftEdge < 0 || rightEdge > boardWidth || topEdge < 0 || bottomEdge > boardHeight;
}

// Функция для проверки пересечения между двумя компонентами
bool doIntersect(const Component &comp1, const Component &comp2)
{
    // Проверяем перекрытие по оси X
    bool xOverlap = !(comp1.x + comp1.width / 2 < comp2.x - comp2.width / 2 ||
                      comp2.x + comp2.width / 2 < comp1.x - comp1.width / 2);

    // Проверяем перекрытие по оси Y
    bool yOverlap = !(comp1.y + comp1.height / 2 < comp2.y - comp2.height / 2 ||
                      comp2.y + comp2.height / 2 < comp1.y - comp1.height / 2);

    return xOverlap && yOverlap;
}

int main()
{
    int A, B, N;
    std::cin >> A >> B >> N; // Размеры платы и количество компонентов

    std::map<std::string, std::pair<float, float>> componentSizes = {
            {"R01005", {0.4, 0.2}},
            {"R0201", {0.6, 0.3}},
            {"R0402", {1.0, 0.5}},
            {"R0603", {1.6, 0.8}},
            {"R0805", {2.0, 1.25}},
            {"R0808", {2.0, 2.0}},
            {"R1020", {2.5, 1.25}},
            {"R1206", {3.2, 1.6}},
            {"R1210", {3.2, 2.5}},
            {"R1812", {4.5, 3.2}},
            {"R2010", {5.0, 2.5}},
            {"R2512", {6.3, 3.2}},
            {"L2835", {2.8, 3.5}},
            {"L3014", {3.0, 1.4}},
            {"L3528", {3.5, 2.8}},
            {"L5050", {5.0, 5.0}},
            {"L5630", {5.6, 3.0}},
            {"L5730", {5.7, 3.0}},
            {"L5", {5.0, 5.0}}, // Предполагаем, что круглые светодиоды имеют форму квадрата для упрощения
            {"C5", {5.0, 5.0}}, // То же самое для круглых конденсаторов
            {"C8", {8.0, 8.0}},
            {"C10", {10.0, 10.0}},
            {"C16", {16.0, 16.0}},
            {"C18", {18.0, 18.0}},
            {"C20", {20.0, 20.0}},
            {"C22", {22.0, 22.0}},
            {"C25", {25.0, 25.0}}};

    std::vector<Component> components(N);

    // Считываем данные о компонентах
    for (int i = 0; i < N; ++i)
    {
        std::cin >> components[i].id >> components[i].type >> components[i].x >> components[i].y;
        components[i].width = componentSizes[components[i].type].first;
        components[i].height = componentSizes[components[i].type].second;
    }

    bool errorFound = false;

    // Проверяем каждый компонент
    for (int i = 0; i < N; ++i)
    {
        if (isOutOfBounds(components[i], A, B))
        {
            std::cout << "ERROR\nout_of_bounds " << components[i].id << '\n';
            errorFound = true;
        }

        // Проверяем пересечения
        for (int j = i + 1; j < N; ++j)
        {
            if (doIntersect(components[i], components[j]))
            {
                std::cout << "ERROR\nintersection " << components[i].id << " " << components[j].id << '\n';
                errorFound = true;
            }
        }
    }

    if (!errorFound)
    {
        std::cout << "OK\n";
    }

    return 0;
}