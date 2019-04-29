/**
 * @file    task2.cpp
 * @brief   Реализация контйнерного класса с моделью очереди
 *
 * @note    1. Создайте контейнерный класс, реализующий модель очереди.
 *
 * @copyright Nikita Bulaev 2019
 *
 */

#include <iostream>
#include <cassert>

class QueueInt {
  private:
    int qLength;
  public:
    QueueInt() : qLength(0) {};

    ~QueueInt() {

    }

    /**
     * @brief Добавить элемент в конец очереди
     *
     * @param x Новый элемент
     */
    void push(int x) {

    }
    /** Возвращает количество элементов в очереди */
    int size() {
        return qLength;
    }

    /** Возвращает первый элемент в очереди */
    int front() {

    }

    /** Возвращает последний элемент в очереди */
    int back() {

    }

    /** Удаляет первый элемент в очереди */
    void pop() {

    }
};


int main (int argc, char ** args) {

    QueueInt myQueue; // создаем пустую очередь

    // добавили в очередь несколько элементов
    myQueue.push(1);
    myQueue.push(2);
    myQueue.push(3);

    std::cout << "Количество элементов в очереди: " << myQueue.size();
    std::cout << "\nВот первый: " << myQueue.front() << "\nВот последний: " << myQueue.back();

    myQueue.pop();     // удаляем один элемент в очереди
    std::cout << "\nКоличество элементов в очереди: " << myQueue.size();
    std::cout << "\nВот первый: " << myQueue.front() << "\nВот последний: " << myQueue.back();
    return 0;

    return 0;
}
