/**
 * @file    task1.cpp
 * @brief   Реализация шаблона класса
 *
 * @note    Реализовать шаблон класса Pair1, который позволяет
 *          пользователю передавать данные одного типа парами.
 *
 * @copyright Nikita Bulaev 2019
 *
 */

#include <iostream>

template <class T>
class Pair1 {
  private:
    T firstNum;
    T secondNum;
  public:
    Pair1(): firstNum(0), secondNum(0) {};
    Pair1(T f, T s): firstNum(f), secondNum(s) {};

    T first() const {
        return firstNum;
    }

    T second() const {
        return secondNum;
    }
};

int main (int argc, char ** args) {

    Pair1<int> p1(6, 9);
    std::cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

    const Pair1<double> p2(3.4, 7.8);
    std::cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';

    return 0;
}
