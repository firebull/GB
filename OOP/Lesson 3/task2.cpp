/**
 * @file    task2.cpp
 * @brief   Тестируем "Алмаз смерти"
 *
 * @note    1. Создать класс Car (автомобиль) с полями company (компания)
 *             и model (модель).
 *          2. Классы-наследники: PassengerCar (легковой автомобиль) и Bus (автобус).
 *          3. От этих классов наследует класс Minivan (минивэн).
 *          4. Создать конструкторы для каждого из классов, чтобы они выводили данные
 *             о классах.
 *          5. Создать объекты для каждого из классов и посмотреть, в какой
 *             последовательности выполняются конструкторы.
 *          6. Обратить внимание на проблему «алмаз смерти».
 *
 * @copyright Nikita Bulaev 2019
 *
 */

#include <iostream>

class Car {
  protected:
    std::string company;
    std::string model;
    std::string carClass;
  public:
    Car() {
        std::cout << "Default Car constructor" << std::endl;
    }

    Car(std::string c, std::string m, std::string t) : company(c), model(m), carClass(t) {
        std::cout << "Main Car constructor" << std::endl;
    }

    ~Car() {
        std::cout << "Car destructor" << std::endl;
    }

    void print() {
        std::cout << "\n*************************" << std::endl;
        std::cout << carClass << " " << company << " " << model << std::endl;
        std::cout << "*************************" << std::endl << std::endl;
    }
};

class PassengerCar : virtual public Car {
  public:
    PassengerCar() {
        std::cout << "Default PassengerCar constructor" << std::endl;
    }

    PassengerCar(std::string c, std::string m) : Car(c, m, "Passenger Car") {
        std::cout << "Main PassengerCar constructor" << std::endl;
    }

    ~PassengerCar() {
        std::cout << "PassengerCar destructor" << std::endl;
    }
};

class Bus : virtual public Car {
  public:
    Bus() {
        std::cout << "Default Bus constructor" << std::endl;
    }

    Bus(std::string c, std::string m) : Car(c, m, "Bus") {
        std::cout << "Main Bus constructor" << std::endl;
    }

    ~Bus() {
        std::cout << "Bus destructor" << std::endl;
    }
};

class Minivan : public PassengerCar, public Bus {
  public:
    Minivan() {
        std::cout << "Default Minivan constructor" << std::endl;
    }

    Minivan(std::string c, std::string m) {
        company  = c;
        model    = m;
        carClass = "Minivan";

        std::cout << "Main Minivan constructor" << std::endl;
    }

    ~Minivan() {
        std::cout << "Minivan destructor" << std::endl;
    }
};

int main (int argc, char ** args) {
    Minivan car;

    /*
        Если не использовать виртуальные классы, то получаем:

        =====================
        Default Car constructor
        Default PassengerCar constructor
        Default Car constructor
        Default Bus constructor
        Default Minivan constructor
        Minivan destructor
        Bus destructor
        Car destructor
        PassengerCar destructor
        Car destructor
        =====================

        Тут базовый класс вызывается дважды. Если я правильно
        понимаю логику процесса, то сначала он вызывается для
        Minivan и PassengerCar, а потом для Bus.


        Иначе получаем:

        =====================
        Default Car constructor
        Default PassengerCar constructor
        Default Bus constructor
        Default Minivan constructor
        Minivan destructor
        Bus destructor
        PassengerCar destructor
        Car destructor
        =====================

        Видно, что сначала вызывается базовый для всех класс, потом
        опускается по потомкам до последнего. Как и должно быть.
     */

    std::cout << std::endl << std::endl << "Now lets check constructor with init: " << std::endl;

    Minivan minivan("Honda", "Odyssey");

    minivan.print();

    return 0;
}
