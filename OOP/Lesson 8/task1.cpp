/**
 * @file    task1.cpp
 * @brief   Тестируем исключения
 *
 * @note    1. Написать функцию div, которая должна вычислять
 *             результат деления двух целых чисел и запускать
 *             исключение DivisionByZero, если делитель равен 0.
 *          2. В функции main ввести два целых числа и вывести их
 *             неполное частное, если делитель не равен нулю, и
 *             сообщение об ошибке, если равен.
 *
 * @copyright Nikita Bulaev 2019
 *
 */

#include <iostream>

int Div (int a, int b) {
    if (b == 0) {
        throw ("DivisionByZero");
    } else {
        return a % b;
    }
}

int main (int argc, char ** args) {

    int a = 0, b = 1;

    std::cout << "Enter a: ";
    std::cin >> a;

    std::cout << "Enter b: ";
    std::cin >> b;

    try {
        int c = Div(a, b);

        std::cout << "a % b = " << c << std::endl;
    } catch (const char* exception) {
        std::cout << "Got exception: " << exception << std::endl;
    } catch (...) {
        std::cout << "Got unknown exception" << std::endl;
    }

    return 0;
}
