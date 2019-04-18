/**
 * @copyright Nikita Bulaev 2019
 *
 * @file  stack.cpp
 * @brief Простая реализация стэка на массиве
 *
 *
 */

#include <iostream>
#include "stack.hpp"

/**
 * @brief Закинуть в стэк
 *
 * @param  value Значение эелемента стэка
 * @return       false, если превышен размер стэка
 */
bool Stack::push(T value) {
    if (this->size >= STACK_MAX_SIZE) {
        return false;
    }

    this->data[this->size++] = value;

    return true;
}

/**
 * @brief Взять верхний элемент стэка
 *
 * @return       Предупреждение и 0, если стэк пуст
 * @return       Верхний элемент стэка, если стэк не пустой
 */
T Stack::pop() {
    if (this->size == 0) {
        std::cout << "Warning: Stack is empty" << std::endl;
        return 0;
    }

    // Возвращаем значение, которое было в «голове»
    return this->data[this->size--];
}

/**
 * @brief Возвращает текущий размер стэка
 * @return Размер стэка
 */
unsigned int Stack::getSize() {
    return this->size;
}

/**
 * @brief Выводит все элементы стэка начиная с нижнего.
 *        Стэк не обнуляется.
 */
void Stack::print() {

    std::cout << "(";

    for (int i = 0; i < this->size; ++i) {
        std::cout << this->data[i];

        if (i < this->size - 1) {
            std::cout << ",";
        }
    }

    std::cout << ")" << std::endl;
}

/**
 * @brief Очищает стэк
 */
void Stack::reset() {
    for (int i = 0; i < this->size; ++i) {
        this->data[i] = 0;
    }

    this->size = 0;
}
