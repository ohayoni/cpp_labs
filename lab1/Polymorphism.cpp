#include <iostream>
#include <string>

class Entity {
protected:
    std::string name;
    int health;
    int attackPower;
    int defense;

public:
    Entity(const std::string& n, int h, int a, int d)
        : name(n), health(h), attackPower(a), defense(d) {}

    virtual void attack(Entity& target) {
        int damage = attackPower - target.defense;
        if (damage > 0) {
            target.health -= damage;
            std::cout << name << " атакует " << target.name << " и наносит " << damage << " урона!\n";
        } else {
            std::cout << name << " атакует " << target.name << ", но безрезультатно!\n";
        }
    }

    virtual void displayInfo() const {
        std::cout << "Имя: " << name << ", Здоровье: " << health
                  << ", Атака: " << attackPower << ", Защита: " << defense << std::endl;
    }

    virtual ~Entity() {}
};


class Character : public Entity {
public:
    Character(const std::string& n, int h, int a, int d)
        : Entity(n, h, a, d) {}

    void attack(Entity& target) override {
        int damage = attackPower - target.defense;
        if (damage > 0) {
            if (rand() % 100 < 20) {
                damage *= 2;
                std::cout << "Критический удар! ";
            }
            target.health -= damage;
            std::cout << name << " атакует " << target.name << " и наносит " << damage << " урона!\n";
        } else {
            std::cout << name << " атакует " << target.name << ", но безрезультатно!\n";
        }
    }

    void displayInfo() const override {
        std::cout << "Персонаж: " << name << ", Здоровье: " << health
                  << ", Атака: " << attackPower << ", Защита: " << defense << std::endl;
    }
};

class Monster : public Entity {
public:
    Monster(const std::string& n, int h, int a, int d)
        : Entity(n, h, a, d) {}

    void attack(Entity& target) override {
        int damage = attackPower - target.defense;
        if (damage > 0) {
            if (rand() % 100 < 30) {
                damage += 5;
                std::cout << "Ядовитая атака! ";
            }
            target.health -= damage;
            std::cout << name << " атакует " << target.name << " и наносит " << damage << " урона!\n";
        } else {
            std::cout << name << " атакует " << target.name << ", но безрезультатно!\n";
        }
    }
    
    void displayInfo() const override {
        std::cout << "Монстр: " << name << ", Здоровье: " << health
                  << ", Атака: " << attackPower << ", Защита: " << defense << std::endl;
    }
};


int main() {
    srand(static_cast<unsigned>(time(0)));

    Character hero("Богатырь", 120, 25, 15);
    Monster goblin("Леший", 70, 18, 8);
    Monster dragon("Змей Горыныч", 200, 35, 25);

    Entity* entities[] = { &hero, &goblin, &dragon };

    std::cout << "\n[~] Информация о существах:\n" << std::endl;
    for (auto& entity : entities) {
        entity->displayInfo();
    }

    std::cout << "\n[~] Битва начинается:\n" << std::endl;
    hero.attack(goblin);
    goblin.attack(hero);
    dragon.attack(hero);

    return 0;
}
