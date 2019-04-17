
#include <iostream>
#include "stack.hpp"

bool Stack::push(T value) {
    if (this->size >= STACK_MAX_SIZE) {
        return false;
    }

    this->data[this->size++] = value;

    return true;
}

T Stack::pop() {
    if (this->size == 0) {
        std::cout << "Warning: Stack is empty" << std::endl;
        return 0;
    }

    // Значение «наверху» списка
    T value = this->data[this->size--];

    // Возвращаем значение, которое было в «голове»
    return value;
}

unsigned int Stack::getSize() {
    return this->size;
}

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

void Stack::reset() {
    for (int i = 0; i < this->size; ++i) {
        this->data[i] = 0;
    }

    this->size = 0;
}
