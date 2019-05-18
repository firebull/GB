/**
 * @file    task2.cpp
 * @brief   Тестируем исключения
 *
 * @note    1. Написать класс Ex, хранящий вещественное число x
 *             и имеющий конструктор по вещественному числу,
 *             инициализирующий x значением параметра.
 *          2. Написать класс Bar, хранящий вещественное число y
 *             (конструктор по умолчанию инициализирует его нулем) и
 *             имеющий метод set с единственным вещественным параметром a.
 *          3. Если y + a > 100, возбуждается исключение типа Ex с
 *             данными ay, иначе в y заносится значение a.
 *          4. В функции main завести переменную класса Bar и в
 *             цикле в блоке try вводить с клавиатуры целое n.
 *             Использовать его в качестве параметра метода set
 *             до тех пор, пока не будет введено 0.
 *          5. В обработчике исключения выводить сообщение об ошибке,
 *             содержащее данные объекта исключения.
 *
 * @copyright Nikita Bulaev 2019
 *
 */

#include <iostream>

class Ex {
  private:
    int x;
  public:
    Ex() : x(0) {};
    Ex(int a): x(a) {};

    int get() const {
        return x;
    }

    friend std::ostream &operator<<(std::ostream &os, const Ex &ex);
};

std::ostream &operator<<(std::ostream &os, const Ex &ex) {
    os << ex.x;
    return os;
}

class Bar {
  private:
    int y;
    Ex ex;

  public:
    Bar() : y(0) {};
    Bar(int a) {
        set(a);
    };

    void set(int a) {
        if ((y + a) > 100) {
            throw (Ex(y * a));
        }

        y = a;
    }
};

int main (int argc, char ** args) {
    Bar bar;

    for (;;) {
        try {
            int a = 0;

            std::cout << "Enter number or 0 to exit: ";
            std::cin >> a;

            if (a == 0) { break; }

            bar.set(a);

        } catch (Ex &ex) {
            std::cout << "Got Exception: " << ex << std::endl;
        } catch (...) {
            std::cout << "Got unknown exception" << std::endl;
        }
    }


    return 0;
}
