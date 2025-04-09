#include <iostream>
#include <string>

class Character {
private:
    std::string name;
    int health;
    int attack;
    int defense;

public:
    Character(const std::string& n, int h, int a, int d)
        : name(n), health(h), attack(a), defense(d) {}

    bool operator==(const Character& other) const {
        return name == other.name && health == other.health;
    }

    friend std::ostream& operator<<(std::ostream& os, const Character& character) {
        os << "Персонаж: " << character.name << ", Здоровье: " << character.health
           << ", Атака: " << character.attack << ", Защита: " << character.defense;
        return os;
    }
};

class Weapon {
private:
    std::string name;
    int damage;
    float weight;

public:
    Weapon(const std::string& n, int d, float w)
        : name(n), damage(d), weight(w) {}

    Weapon operator+(const Weapon& other) const {
        std::string newName = name + "+" + other.name;
        int newDamage = damage + other.damage;
        float newWeight = weight + other.weight;
        return Weapon(newName, newDamage, newWeight);
    }

    bool operator>(const Weapon& other) const {
        return damage > other.damage;
    }

    void displayInfo() const {
        std::cout << "Оружие: " << name << ", Урон: " <<
        damage << ", Вес: " << weight << " кг\n";
    }
};

int main() {
    Character герой1("Илья Муромец", 200, 35, 20);
    Character герой2("Илья Муромец", 200, 35, 20);
    Character герой3("Добрыня Никитич", 180, 40, 15);

    if (герой1 == герой2) {
        std::cout << "Илья Муромец и его двойник одинаковые!\n";
    }
    if (!(герой1 == герой3)) {
        std::cout << "Илья Муромец и Добрыня Никитич разные!\n";
    }

    std::cout << герой1 << std::endl;
    
    Weapon меч("Меч-кладенец", 50, 5.0f);
    Weapon копьё("Копьё-булатное", 35, 2.5f);
    
    Weapon объединённое = меч + копьё;
    объединённое.displayInfo();
    
    if (меч > копьё) {
        std::cout << "\nМеч-кладенец сильнее чем копьё\n";
    } else {
        std::cout << "\nКопьё-булатное сильнее чем меч\n";
    }
    
    return 0;
}

