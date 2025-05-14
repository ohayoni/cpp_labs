#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>
#include <string>

class Entity {
private:
    std::string name;
    int health;
    int attack;
    int defense;

public:
    Entity(const std::string& name, int health, int attack, int defense)
        : name(name), health(health), attack(attack), defense(defense) {}

    std::string getName() const { return name; }
    int getHealth() const { return health; }
    int getAttack() const { return attack; }
    int getDefense() const { return defense; }

    virtual void displayInfo() const {
        std::cout << "Имя: " << name << ", Здоровье: " << health
            << ", Атака: " << attack << ", Защита: " << defense << std::endl;
    }
};

template <typename T>
class GameManager {
private:
    std::vector<T> entities;

public:
    void addEntity(T entity) {
        entities.push_back(std::move(entity));
    }

    void displayAll() const {
        for (const auto& entity : entities) {
            entity->displayInfo();
        }
    }

    auto begin() { return entities.begin(); }
    auto end() { return entities.end(); }
    auto begin() const { return entities.begin(); }
    auto end() const { return entities.end(); }
};


void saveToFile(const GameManager<std::unique_ptr<Entity>>& manager, const std::string& filename) {
    std::ofstream file("save_data.txt");
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл для записи.");
    }

    for (const auto& entity : manager) {
        file << entity->getName() << "," << entity->getHealth() << ","
            << entity->getAttack() << "," << entity->getDefense() << "\n";
    }
}

GameManager<std::unique_ptr<Entity>> loadFromFile(const std::string& filename) {
    std::ifstream file("save_data.txt");
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл для чтения.");
    }

    GameManager<std::unique_ptr<Entity>> manager;
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string name;
        int health, attack, defense;

        if (std::getline(ss, name, ',') &&
            ss >> health && ss.ignore() &&
            ss >> attack && ss.ignore() &&
            ss >> defense) {
            manager.addEntity(std::make_unique<Entity>(name, health, attack, defense));
        }
    }

    return manager;
}

int main() {
   std::cout << "\n[~] Создание менеджера игры:\n" << std::endl;
   GameManager<std::unique_ptr<Entity>> manager;
   manager.addEntity(std::make_unique<Entity>("Герой", 100, 10, 5));
   manager.addEntity(std::make_unique<Entity>("Гоблин", 50, 7, 3));
   manager.displayAll();

   std::cout << "\n[~] Сохранение в файл:\n" << std::endl;
   saveToFile(manager, ".\\save_data.txt");

   std::cout << "\n[~] Загрузка из файла:\n" << std::endl;
   auto loadedManager = loadFromFile(".\\save_data.txt");
   loadedManager.displayAll();

   std::cout << std::endl;

   return 0;
}
