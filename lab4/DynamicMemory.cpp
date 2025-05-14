#include <iostream>
#include <string>
#include <memory>
#include <list>


class Inventory
{
private:
    std::list<std::unique_ptr<std::string>> items;
public:
    Inventory()
    {
        std::cout << "\n[~] Инвентарь создан" << std::endl;
    }

    ~Inventory()
    {
        std::cout << "\n[~] Инвентарь уничтожен" << std::endl;
    }

    void addItem(const std::string& item)
    {
        items.push_back(std::make_unique<std::string>(item));
        std::cout << "\n[~] Предмет " << item << " добавлен в инвентарь" << std::endl;
    }

    void displayInventory() const
    {
        if (items.empty()) {
            std::cout << "\n[~] Инвентарь пуст." << std::endl;
            return;
        }

        std::cout << "\n[~] В инвентаре находится:" << std::endl;
        for (const auto& item : items) {
            std::cout << "\t- " << *item << "\n";
        }
    }
};

int main() {
    Inventory playerInventory;

    playerInventory.addItem("Меч");
    playerInventory.addItem("Щит");
    playerInventory.addItem("Зелье здоровья");
    playerInventory.addItem("Кольчуга");
    playerInventory.addItem("Свиток телепортации");

    playerInventory.displayInventory();

    return 0;
}
