/**
 * @file    task1.cpp
 * @brief   Создание простейшего класса
 *
 * @note    Написать класс, который реализует функциональность стека.
 *          Класс Stack должен иметь:
 *           - private-массив целых чисел длиной 10;
 *           - private целочисленное значение для отслеживания длины стека;
 *           - public-метод с именем reset(), который будет сбрасывать длину
 *             и все значения элементов на 0;
 *           - public-метод с именем push(), который будет добавлять значение
 *             в стек. push() должен возвращать значение false, если массив уже
 *             заполнен, и true в противном случае;
 *           - public-метод с именем pop() для вытягивания и возврата значения из
 *             стека. Если в стеке нет значений, то должно выводиться предупреждение;
 *           - public-метод с именем print(), который будет выводить все значения стека.
 *
 * @copyright Nikita Bulaev 2019
 *
 */

#include <iostream>
#include "stack.hpp"

int main (int argc, char ** args) {
    Stack stack;
    stack.reset();
    stack.print();

    stack.push(3);
    stack.push(7);
    stack.push(5);
    stack.print();

    stack.pop();
    stack.print();

    stack.pop();
    stack.pop();
    stack.print();

    stack.reset();

    return 0;
}
