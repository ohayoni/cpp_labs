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

    int getHealth() const {
        return health;
    }

    void heal(int amount) {
        health += amount;
        if (health > 100) {
            health = 100;
        }
        std::cout << name << " исцелился, теперь его здоровье " << health << std::endl;
    }

    void takeDamage(int amount) {
        health -= amount;
        if (health < 0) {
            health = 0;
        }
        std::cout << name << " получил урон, теперь его здоровье " << health << std::endl;
    }

    void displayInfo() const {
        std::cout << "Имя: " << name << ", Здоровье: " << health
                  << ", Атака: " << attack << ", Защита: " << defense << std::endl;
    }
    
    void attackEnemy(Character& enemy) {
        int damage = attack - enemy.defense;
        if (damage > 0) {
            enemy.health -= damage;
            std::cout << name << " атакует " << enemy.name << " и наносит " << damage << " урона!" << std::endl;
        } else {
            std::cout << name << " атакует " << enemy.name << ", но безрезультатно!" << std::endl;
        }
    }
};


int main() {
    Character monster("Дракон", 80, 25, 8);
    Character hero("Богатырь", 100, 30, 12);

    hero.displayInfo();
    monster.displayInfo();

    hero.attackEnemy(monster);
    monster.displayInfo();

    hero.heal(20);
    hero.takeDamage(25);
    hero.displayInfo();
    
    return 0;
}
