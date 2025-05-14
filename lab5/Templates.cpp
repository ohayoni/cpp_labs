#include <iostream>
#include <vector>
#include <string>


template <typename T>
class Queue {
private:
    std::vector<T> items;
    size_t frontIndex = 0;

public:
    void push(const T& item) {
        items.push_back(item);
        std::cout << "Добавлено: " << item << " в очередь.\n";
    }

    T pop() {
        if (empty()) {
            throw std::runtime_error("Очередь пуста! Невозможно удалить элемент.");
        }
        T removedItem = items[frontIndex];
        frontIndex++;

        if (frontIndex > items.size() / 2) {
            items.erase(items.begin(), items.begin() + frontIndex);
            frontIndex = 0;
        }
        return removedItem;
    }

    T front() const {
        if (empty()) {
            throw std::runtime_error("Очередь пуста! Нет первого элемента.");
        }
        return items[frontIndex];
    }

    bool empty() const {
        return frontIndex >= items.size();
    }
};


int main()
{
   std::cout << "\n[~] Инициализация очереди:" << std::endl;
   Queue<std::string> strQueue;

   std::cout << "\n[~] Добавление элементов в очередь:\n" << std::endl;
   strQueue.push("Привет");
   strQueue.push("Мир");
   strQueue.push("!");

   std::cout << "\n[~] Получение элементов из очереди:\n" << std::endl;
   std::cout << "\t- " << strQueue.pop() << std::endl;
   std::cout << "\t- " << strQueue.pop() << std::endl;
   std::cout << "\t- " << strQueue.pop() << std::endl;

   std::cout << std::endl;

   return 0;
}

