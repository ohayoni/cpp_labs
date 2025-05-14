#include <iostream>
#include <string>

class Person {
private:
    std::string name;
    int age;
    std::string email;
    std::string address;

public:
    std::string getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

    std::string getEmail() const {
        return email;
    }

    std::string getAddress() const {
        return address;
    }

    void setName(const std::string& newName) {
        if (!newName.empty()) {
            name = newName;
        }
        else {
            std::cerr << "Ошибка: Имя не может быть пустым!" << std::endl;
        }
    }

    void setAge(int newAge) {
        if (newAge >= 0 && newAge <= 120) {
            age = newAge;
        }
        else {
            std::cerr << "Ошибка: Возраст должен быть в диапазоне от 0 до 120!" << std::endl;
        }
    }

    void setEmail(const std::string& newEmail) {
        if (newEmail.find('@') != std::string::npos) {
            email = newEmail;
        }
        else {
            std::cerr << "Ошибка: Неверный формат электронной почты!" << std::endl;
        }
    }

    void setAddress(const std::string& newAddress)
    {
        if (!newAddress.empty()) {
            address = newAddress;
        }
        else {
            std::cerr << "Ошибка: Адрес не может быть пустым!" << std::endl;
        }
    }

    void displayInfo() const {
        std::cout << "Имя: " << name << ", Возраст: " << age << ", Электронная почта: "
            << email << ", Адрес: " << address << std::endl;
    }
};

int main() {
   Person person;

   person.setName("Иван Иванов");
   person.setAge(30);
   person.setEmail("ivan.ivanov@example.com");
   person.setAddress("ул. Пушкина, д. 10");

   std::cout << "Имя: " << person.getName() << std::endl;
   std::cout << "Возраст: " << person.getAge() << std::endl;
   std::cout << "Электронная почта: " << person.getEmail() << std::endl;
   std::cout << "Адрес: " << person.getAddress() << std::endl;

   person.setName("");
   person.setAge(140);
   person.setEmail("неверный-формат");
   person.setAddress("");

   person.displayInfo();

   return 0;
}
