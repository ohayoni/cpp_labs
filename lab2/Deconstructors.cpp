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
        : name(n), health(h), attack(a), defense(d) {
        std::cout << "Персонаж " << name << " создан!\n";
    }

    ~Character() {
        std::cout << "Персонаж " << name << " уничтожен!\n";
    }

    void displayInfo() const {
        std::cout << "Имя: " << name << ", Здоровье: " << health
                  << ", Атака: " << attack << ", Защита: " << defense << std::endl;
    }
};

class Weapon {
private:
    std::string name; 
    int damage;  
    float weight;

public:
    Weapon(const std::string& n, int d, float w)
        : name(n), damage(d), weight(w) {
        std::cout << "Оружие " << name << " создано!\n";
    }

    ~Weapon() {
        std::cout << "Оружие " << name << " уничтожено!\n";
    }

    void displayInfo() const {
        std::cout << "Оружие: " << name << ", Урон: " << damage
        << ", Вес: " << weight << " кг\n";
    }
};


class Monster {
private:
    std::string name;
    int health;
    int attack;
    int defense;

public:
    Monster(const std::string& n, int h, int a, int d)
        : name(n), health(h), attack(a), defense(d) {
        std::cout << "Монстр " << name << " создан!\n";
    }

    ~Monster() {
        std::cout << "Монстр " << name << " уничтожен!\n";
    }

    void displayInfo() const {
        std::cout << "Имя: " << name << ", Здоровье: " << health
                  << ", Атака: " << attack << ", Защита: " << defense << std::endl;
    }
};

int main() {
    Weapon luk("Длинный лук", 25, 1.5f);
    Weapon topor("Боевой топор", 40, 4.8f);
    
    std::cout << "\nИнформация об оружии:\n";
    luk.displayInfo();
    topor.displayInfo();
    
    return 0;
}
