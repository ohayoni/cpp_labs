#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <ctime>
#include <memory>
#include <algorithm>  
#include <utility>   


template <typename T>
class Logger {
private:
    std::string filename;

public:
    Logger(const std::string& fname) : filename(fname) {
        std::ofstream file(filename, std::ios::app);
        if (!file) {
            throw std::runtime_error("Failed to open log file: " + filename);
        }
        file << "Log started at " << std::time(nullptr) << "\n";
    }

    void log(const T& event) {
        std::ofstream file(filename, std::ios::app);
        if (!file) {
            throw std::runtime_error("Failed to append to log file: " + filename);
        }
        file << event << "\n";
    }
};

class Inventory {
private:
    std::vector<std::string> items;

public:
    void addItem(const std::string& item) {
        if (item.empty()) {
            throw std::invalid_argument("Название предмета не может быть пустым.");
        }
        items.push_back(item);
        std::cout << "Добавлено " << item << " в инвентарь.\n";
    }

    void removeItem(const std::string& item) {
        for (auto it = items.begin(); it != items.end(); ++it) {
            if (*it == item) {
                items.erase(it);
                std::cout << "Удалено " << item << " из инвентаря.\n";
                return;
            }
        }
        throw std::invalid_argument("Предмет " + item + " не найден в инвентаре.");
    }

    void displayInventory() const {
        if (items.empty()) {
            std::cout << "Инвентарь пуст.\n";
            return;
        }
        std::cout << "Инвентарь:\n";
        for (const auto& item : items) {
            std::cout << "- " << item << "\n";
        }
    }

    std::string serialize() const {
        std::stringstream ss;
        ss << items.size();
        for (const auto& item : items) {
            ss << " " << item;
        }
        return ss.str();
    }

    void deserialize(const std::string& data) {
        std::istringstream iss(data);
        size_t count;
        iss >> count;
        items.clear();
        std::string item;
        std::getline(iss, item); 
        for (size_t i = 0; i < count; ++i) {
            std::getline(iss, item, ' ');
            if (!item.empty()) {
                items.push_back(item);
            }
        }
    }
};

class Monster {
protected:
    std::string name;
    int health;
    int attack;
    int defense;

public:
    Monster(const std::string& n, int h, int a, int d)
        : name(n), health(h), attack(a), defense(d) {
        validate();
    }

    virtual void displayInfo() const {
        std::cout << "Монстр: " << name << ", Здоровье: " << health
            << ", Атака: " << attack << ", Защита: " << defense << std::endl;
    }

    virtual std::string getType() const = 0;
    virtual std::string serialize() const {
        return getType() + "," + name + "," + std::to_string(health) + "," +
            std::to_string(attack) + "," + std::to_string(defense);
    }

    virtual ~Monster() = default;

    std::string getName() const { return name; }
    int getHealth() const { return health; }
    int getAttack() const { return attack; }
    int getDefense() const { return defense; }

    void takeDamage(int damage, Logger<std::string>& logger) {
        if (damage < 0) {
            throw std::invalid_argument("Урон не может быть отрицательным.");
        }
        health -= damage;
        if (health < 0) {
            health = 0;
            logger.log(name + " был повержен!");
            throw std::runtime_error("Здоровье опустилось ниже 0 у " + name);
        }
        logger.log(name + " получает " + std::to_string(damage) + " урона, здоровье теперь " + std::to_string(health));
    }

protected:
    void validate() const {
        if (health <= 0) throw std::invalid_argument("Здоровье должно быть положительным.");
        if (name.empty()) throw std::invalid_argument("Имя не может быть пустым.");
        if (attack < 0 || defense < 0) throw std::invalid_argument("Атака и защита должны быть неотрицательными.");
    }
};

class Goblin : public Monster {
public:
    Goblin(const std::string& n, int h = 50, int a = 15, int d = 5)
        : Monster(n, h, a, d) {
    }

    std::string getType() const override { return "Goblin"; }
};

class Dragon : public Monster {
public:
    Dragon(const std::string& n, int h = 200, int a = 30, int d = 20)
        : Monster(n, h, a, d) {
    }

    std::string getType() const override { return "Dragon"; }
};

class Zombie : public Monster {
public:
    Zombie(const std::string& n, int h = 40, int a = 10, int d = 15)
        : Monster(n, h, a, d) {
    } 

    std::string getType() const override { return "Zombie"; }
};

class Character {
private:
    std::string name;
    int health;
    int attack;
    int defense;
    int level;
    int experience;
    Inventory inventory;

public:
    Character(const std::string& n, int h, int a, int d)
        : name(n), health(h), attack(a), defense(d), level(1), experience(0) {
        validate();
    }

    void attackEnemy(Monster& enemy, Logger<std::string>& logger) {
        int damage = attack - enemy.getDefense();
        if (damage > 0) {
            enemy.takeDamage(damage, logger);
            logger.log(name + " атакует " + enemy.getName() + " и наносит " + std::to_string(damage) + " урона!");
        }
        else {
            logger.log(name + " атакует " + enemy.getName() + ", но это не приносит эффекта!");
        }
    }

    void takeDamage(int damage, Logger<std::string>& logger) {
        if (damage < 0) {
            throw std::invalid_argument("Урон не может быть отрицательным.");
        }
        health -= damage;
        if (health < 0) {
            health = 0;
            logger.log(name + " был повержен!");
            throw std::runtime_error("Здоровье опустилось ниже 0 у " + name);
        }
        logger.log(name + " получает " + std::to_string(damage) + " урона, здоровье теперь " + std::to_string(health));
    }

    void heal(int amount, Logger<std::string>& logger) {
        if (amount < 0) {
            throw std::invalid_argument("Количество лечения не может быть отрицательным.");
        }
        health += amount;
        if (health > 100) health = 100;
        logger.log(name + " восстановил " + std::to_string(amount) + " здоровья!");
    }

    void gainExperience(int exp, Logger<std::string>& logger) {
        if (exp < 0) {
            throw std::invalid_argument("Опыт не может быть отрицательным.");
        }
        experience += exp;
        logger.log(name + " получает " + std::to_string(exp) + " опыта!");
        while (experience >= 100) {
            level++;
            experience -= 100;
            logger.log(name + " повысил уровень! Теперь уровень " + std::to_string(level) + "!");
        }
    }

    void addItem(const std::string& item, Logger<std::string>& logger) {
        inventory.addItem(item);
        logger.log(name + " добавил " + item + " в инвентарь.");
    }

    void removeItem(const std::string& item, Logger<std::string>& logger) {
        inventory.removeItem(item);
        logger.log(name + " удалил " + item + " из инвентаря.");
    }

    void displayInfo() const {
        std::cout << "Имя: " << name << ", Здоровье: " << health
            << ", Атака: " << attack << ", Защита: " << defense
            << ", Уровень: " << level << ", Опыт: " << experience << std::endl;
        inventory.displayInventory();
    }

    std::string serialize() const {
        return name + "," + std::to_string(health) + "," + std::to_string(attack) + "," +
            std::to_string(defense) + "," + std::to_string(level) + "," +
            std::to_string(experience) + "," + inventory.serialize();
    }

    void deserialize(const std::string& data, Logger<std::string>& logger) {
        std::istringstream iss(data);
        std::string token;
        std::vector<std::string> tokens;
        while (std::getline(iss, token, ',')) {
            tokens.push_back(token);
        }
        if (tokens.size() < 7) {
            throw std::runtime_error("Неверный формат данных персонажа.");
        }
        name = tokens[0];
        try {
            health = std::stoi(tokens[1]);
            attack = std::stoi(tokens[2]);
            defense = std::stoi(tokens[3]);
            level = std::stoi(tokens[4]);
            experience = std::stoi(tokens[5]);
            inventory.deserialize(tokens[6]);
            validate();
        }
        catch (const std::exception& e) {
            throw std::runtime_error("Некорректные числовые данные персонажа: " + std::string(e.what()));
        }
        logger.log("Загружен персонаж: " + name);
    }

    std::string getName() const { return name; }
    int getHealth() const { return health; }
    int getAttack() const { return attack; }
    int getDefense() const { return defense; }

private:
    void validate() const {
        if (health <= 0) throw std::invalid_argument("Здоровье должно быть положительным.");
        if (name.empty()) throw std::invalid_argument("Имя не может быть пустым.");
        if (attack < 0 || defense < 0) throw std::invalid_argument("Атака и защита должны быть неотрицательными.");
        if (level < 1) throw std::invalid_argument("Уровень должен быть не менее 1.");
        if (experience < 0) throw std::invalid_argument("Опыт не может быть отрицательным.");
    }
};

class Game {
private:
    Character player;
    std::vector<std::unique_ptr<Monster>> monsters;
    Logger<std::string> logger;
    bool running;

public:
    Game(const std::string& playerName)
        : player(playerName, 100, 20, 10), logger("game.log"), running(true) {
    }

    void addMonster(std::unique_ptr<Monster> monster) {
        monsters.push_back(std::move(monster));
        logger.log("Добавлен монстр: " + monsters.back()->getName());
    }

    void combat() {
        if (monsters.empty()) {
            std::cout << "Нет монстров для битвы!\n";
            return;
        }
        auto& monster = *monsters.front();
        std::cout << "\nБитва с " << monster.getName() << "!\n";

        try {
            while (player.getHealth() > 0 && monster.getHealth() > 0) {
                player.attackEnemy(monster, logger);
                if (monster.getHealth() > 0) {
                    player.takeDamage(monster.getAttack() - player.getDefense(), logger);
                }
            }
            if (monster.getHealth() <= 0) {
                player.gainExperience(50, logger);
                monsters.erase(monsters.begin());
            }
        }
        catch (const std::runtime_error& e) {
            std::cout << "Битва завершена: " << e.what() << "\n";
            if (player.getHealth() <= 0) {
                running = false;
            }
        }
    }

    void saveProgress(const std::string& filename) {
        std::ofstream file(filename);
        if (!file) {
            throw std::runtime_error("Не удалось открыть файл для записи: " + filename);
        }
        file << player.serialize() << "\n";
        file << monsters.size() << "\n";
        for (const auto& monster : monsters) {
            file << monster->serialize() << "\n";
        }
        logger.log("Прогресс игры сохранён в " + filename);
    }

    void loadProgress(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) {
            throw std::runtime_error("Не удалось открыть файл для чтения: " + filename);
        }

        std::string line;
        std::getline(file, line);
        player.deserialize(line, logger);

        size_t monsterCount;
        file >> monsterCount;
        std::getline(file, line);
        monsters.clear();
        for (size_t i = 0; i < monsterCount; ++i) {
            std::getline(file, line);
            std::istringstream iss(line);
            std::string type, name;
            int health, attack, defense;
            char comma;
            std::getline(iss, type, ',');
            std::getline(iss, name, ',');
            iss >> health >> comma >> attack >> comma >> defense;
            try {
                if (type == "Goblin") {
                    monsters.push_back(std::make_unique<Goblin>(name, health, attack, defense));
                }
                else if (type == "Dragon") {
                    monsters.push_back(std::make_unique<Dragon>(name, health, attack, defense));
                }
                else if (type == "Skeleton") {
                    monsters.push_back(std::make_unique<Zombie>(name, health, attack, defense));
                }
                else {
                    throw std::runtime_error("Неизвестный тип монстра: " + type);
                }
                logger.log("Загружен монстр: " + name);
            }
            catch (const std::exception& e) {
                std::cerr << "Внимание: Не удалось загрузить монстра: " << e.what() << "\n";
            }
        }
        logger.log("Прогресс игры загружен из " + filename);
    }

    void play() {
        while (running) {
            std::cout << "\nИнформация о персонаже:\n";
            player.displayInfo();
            std::cout << "\nМонстры:\n";
            for (const auto& monster : monsters) {
                monster->displayInfo();
            }
            std::cout << "\nОпции: (1) Битва, (2) Лечение, (3) Добавить предмет, (4) Удалить предмет, (5) Сохранить, (6) Загрузить, (7) Выйти\n";
            int choice;
            std::cin >> choice;
            try {
                switch (choice) {
                case 1:
                    combat();
                    break;
                case 2:
                    player.heal(20, logger);
                    break;
                case 3: {
                    std::string item;
                    std::cout << "Введите название предмета: ";
                    std::cin >> item;
                    player.addItem(item, logger);
                    break;
                }
                case 4: {
                    std::string item;
                    std::cout << "Введите название предмета: ";
                    std::cin >> item;
                    player.removeItem(item, logger);
                    break;
                }
                case 5:
                    saveProgress("game_save.txt");
                    break;
                case 6:
                    loadProgress("game_save.txt");
                    break;
                case 7:
                    running = false;
                    break;
                default:
                    std::cout << "Неверная опция.\n";
                }
            }
            catch (const std::exception& e) {
                std::cerr << "Ошибка: " << e.what() << "\n";
            }
        }
        logger.log("Игра завершена.");
    }
};

int main() {
    try {
        Game game("Герой");
        game.addMonster(std::make_unique<Goblin>("Гоблин"));
        game.addMonster(std::make_unique<Dragon>("Дракон"));
        game.addMonster(std::make_unique<Zombie>("Зомби"));
        game.play();
    }
    catch (const std::exception& e) {
        std::cerr << "Фатальная ошибка: " << e.what() << "\n";
        return 1;
    }
    return 0;
}