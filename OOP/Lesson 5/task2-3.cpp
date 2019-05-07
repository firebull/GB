/**
 * @file    task2-3.cpp
 * @brief   Реализация шаблона класса
 *
 * @note    1. Реализовать класс Pair, который позволяет
 *             использовать разные типы данных в передаваемых парах.
 *          2. Написать шаблон класса StringValuePair, в котором
 *             первое значение всегда типа string, а второе — любого типа.
 *
 *             Этот шаблон класса должен наследовать частично специализированный
 *             класс Pair, в котором первый параметр — string, а второй — любого
 *             типа данных.
 *
 * @copyright Nikita Bulaev 2019
 *
 */

#include <iostream>

template <typename T1, typename T2>
class Pair {
  protected:
    T1 firstNum;
    T2 secondNum;
  public:
    Pair(): firstNum(0), secondNum(0) {};
    Pair(T1 f, T2 s): firstNum(f), secondNum(s) {};

    T1 first() const {
        return firstNum;
    }

    T2 second() const {
        return secondNum;
    }
};

template <typename T3>
class StringValuePair : public Pair<std::string, T3> {
  public:
    StringValuePair() : Pair<std::string, T3>('\0', 0) {};
    StringValuePair(std::string f, T3 s) : Pair<std::string, T3>(f, s) {};
};

int main (int argc, char ** args) {

    Pair<int, double> p1(6, 7.8);
    std::cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

    const Pair<double, int> p2(3.4, 5);
    std::cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';

    StringValuePair<int> svp("Amazing", 7);
    std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';

    return 0;
}
