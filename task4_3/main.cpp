#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

int main() {
    // Чтение количества вершин в графе
    int N;
    cin >> N;

    // Очистка буфера ввода после чтения числа (для дальнейшего использования sstream)
    cin.ignore();

    vector<vector<int>> rm(N, vector<int>(N, 0));

    for (int i = 0; i < N; ++i) {
        // Установка значения 1 для каждой вершины, так как вершина достижима сама из себя
        rm[i][i] = 1;

        // Чтение строки ввода для текущей вершины
        string line;
        getline(cin, line);

        // Преобразование строки в поток для чтения чисел
        stringstream ss(line);

        int to;
        // Чтение каждого числа из потока
        while (ss >> to) {
            // Если число не равно 0, устанавливаем значение 1 в матрице достижимости
            if (to != 0)
                rm[i][to - 1] = 1;
        }
    }

    // Построение матрицы достижимости
    for (int k = 0; k < N; ++k)
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                // Если вершина i достижима из вершины k и вершина j достижима из вершины k,
                // то вершина j достижима из вершины i
                rm[i][j] = rm[i][j] || (rm[i][k] && rm[k][j]);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j)
            cout << rm[i][j] << " ";
        cout << endl;
    }

    return 0;
}
