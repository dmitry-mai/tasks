#include <iostream>
#include <list>

template<typename T>
struct ListItem {
    int id;
    T data;
    int accessCount = 0;

    ListItem(int id, T data) : id(id), data(data) {}
};

template<typename T>
class SortingList {
private:
    std::list<ListItem<T>> items;

    typename std::list<ListItem<T>>::iterator findIterator(int id) {
        for (auto it = items.begin(); it != items.end(); ++it)
            if (it->id == id)
                return it;

        return items.end();
    }

    void updatePosition(typename std::list<ListItem<T>>::iterator it) {
        while (it != items.begin()) {
            auto prevIt = std::prev(it);
            if (prevIt->accessCount >= it->accessCount)
                break;

            std::iter_swap(it, prevIt);
            --it;
        }
    }

public:
    void add(int id, T data) {
        items.push_back(ListItem<T>(id, data));
    }

    void update(int id, T newData) {
        auto it = findIterator(id);
        if (it != items.end())
            it->data = newData;
    }

    ListItem<T> *find(int id) {
        auto it = findIterator(id);
        if (it != items.end()) {
            it->accessCount++;
            updatePosition(it);
            return &(*findIterator(id));
        }
        return nullptr;
    }

    void print() {
        items.sort([](const auto &a, const auto &b) {
            return a.accessCount > b.accessCount;
        });

        for (const auto &item: items) {
            std::cout << "{" << item.id << " " << item.accessCount << " " << item.data << "} ";
        }
        std::cout << std::endl;
    }
};

int main() {
    SortingList<int> list;
    int N;

    std::cin >> N;
    for (int i = 0; i < N; ++i) {
        int id, data;
        std::cin >> id >> data;
        list.add(id, data);
    }

    std::cin >> N;
    for (int i = 0; i < N; ++i) {
        int cmd, id, data;

        std::cin >> cmd;
        switch (cmd) {
            case 1:
                std::cin >> id >> data;
                list.update(id, data);
                break;
            case 2:
                std::cin >> id;
                if (auto item = list.find(id)) {
                    std::cout << "{" << item->id << " " << item->accessCount << " " << item->data << "}" << std::endl;
                }
                break;
            case 3:
                std::cin >> data;
                std::cout << (list.find(data) ? "YES" : "NO") << std::endl;
                break;
            case 4:
                list.print();
                break;
        }
    }

    return 0;
}
