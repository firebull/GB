/**
 * @copyright Nikita Bulaev 2019
 *
 * @file  stack.hpp
 * @brief Заголовочный файл к stack.cpp
 *
 *
 */

#define T int              /*!< Тип данных, используемый в стэке*/
#define STACK_MAX_SIZE 10  /*!< Максимальная длина стэка */

class Stack {
  private:
    unsigned int size    = 0; /*!< Текущий размер стэка */
    T data[STACK_MAX_SIZE];   /*!< Сам стэк */

  public:
    bool push(T value);
    T pop();
    unsigned int getSize();
    void print();
    void reset();
};
