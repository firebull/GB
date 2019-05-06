/**
 * @file    task3.cpp
 * @brief   Создание простейшего класса с наследованием
 *
 * @note    1. Создать классы Apple (яблоко) и Banana (банан),
 *             которые наследуют класс Fruit (фрукт).
 *          2. У Fruit есть две переменные-члена: name (имя)
 *             и color (цвет).
 *          3. Добавить новый класс GrannySmith, который наследует
 *             класс Apple.
 *
 * @copyright Nikita Bulaev 2019
 *
 */

#include <iostream>

class Fruit {
  protected:
    std::string name;
    std::string color;
  public:
    Fruit() {
        name  = "unknown";
        color = "undefined";
    };

    Fruit(std::string n = "", std::string c = ""): name(n), color(c) {
    };

    void setName(std::string n) {
        name = n;
    }

    void setColor(std::string c) {
        color = c;
    }

    std::string getName() const {
        return name;
    }

    std::string getColor() const {
        return color;
    }
};

class Apple : public Fruit {
  public:
    Apple(): Fruit("apple", "undefined") {};
    Apple(std::string c = ""): Fruit("apple", c) {};

};

class Banana : public Fruit {
  public:
    Banana(): Fruit("banana", "yellow") {};

};

class GrannySmith : public Apple {
  public:
    GrannySmith(): Apple("green") {
        name = "Granny Smith apple";
    };
};

int main (int argc, char * * args) {
    Apple a("red");
    Banana b;
    GrannySmith c;

    std::cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
    std::cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
    std::cout << "My " << c.getName() << " is " << c.getColor() << ".\n";
    return 0;
}
