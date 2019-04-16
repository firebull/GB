/**
 * @file    task1.cpp
 * @brief   Создание простейшего класса
 *
 * @note    1. Создать класс Power, который содержит два вещественных числа.
 *             Этот класс должен иметь две переменные-члена для хранения этих
 *             вещественных чисел.
 *          2. Еще создать два метода: один с именем set, который позволит
 *             присваивать значения переменным, второй — calculate, который
 *             будет выводить результат возведения первого числа в степень
 *             второго числа.
 *          3. Задать значения этих двух чисел по умолчанию.
 *
 * @copyright Nikita Bulaev 2019
 *
 */

#include <iostream>

/*!
 * @class Power
 * @brief Быстрое возведение в степень
 */
class Power {
  private:
    long int a;  /*!< Что возводим в степень */
    int b;       /*!< Степень числа */

  public:
    Power() {
        a = 0;
        b = 1;
    }

    /**
     * @brief Присваивание значений переменным a и b
     * @param a Что возводим в степень
     * @param b Степень числа
     */
    void set(long int a, int b) {
        this->a = a;
        this->b = b;
    }

    /**
    * @brief Быстрое возведение в степень целого числа без рекурсии
    *
    * @note Взял свой код из прошлого курса
    *
    * @return   Итоговое число
    */
    long double calculate(void) {
        long long int n = 1;  /*!< Итоговое число */
        int power = b;        /*!< Степень числа, промежуточные значения */

        // Проверка на корректность данных
        if (b == 0) {
            if (a == 0) {
                // 0^0 -> Вернуть ноль, т.к. это неопределённость
                return 0;
            } else {
                // a^0 -> Всегда 1, если a != 0
                return 1;
            }
        } else if (b < 0) {
            // Если степень отрицательная, то сначала считаем с положительной
            power = b * -1;
        } else if (b == 1) {
            // a^1 = a
            return a;
        }

        if (a == 0) {
            return 0;
        }

        while (power) {
            if (power % 2) {
                power--;
                n *= a;
            } else {
                a *= a;
                power /= 2;
            }
        }

        if (b > 0) {
            return static_cast<long double>(n);
        } else {
            // Отрицательная степень
            return 1.0f / n;
        }
    }
};



int main (int argc, char ** args) {

    Power power;

    long int a = 0;  /*!< Что возводим в степень */
    int b = 1;

    std::cout << "Print integer number to get power of: ";
    std::cin >> a;

    std::cout << "Print integer power of number: ";
    std::cin >> b;

    power.set(a, b);

    std::cout << "Result of " << a << "^" << b << " = " << power.calculate() << std::endl;

    return 0;
}
