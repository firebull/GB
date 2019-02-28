/**
 * (c) Nikita Bulaev 2019
 *
 * @file  task12.c
 * @brief Написать функцию нахождения максимального из трех чисел
 *
 */

#include <stdio.h>

/**
 * @brief Поиск максимального значения из трёх чисел
 *
 * @param  a Число 1
 * @param  b Число 2
 * @param  c Число 3
 * @return   Максимальное из трёх
 */
double findMax(double a, double b, double c) {
    double max = a;    /*!< Максимальное значение */

    if (b > a) {
        max = b;
    }

    if (c > max) {
        return c;
    } else {
        return max;
    }
}

int main (int argc, const char* argv[]) {

    double nums[3] = {0.0f}; /*!< Массив вводимых значений */

    printf("Print 3 numbers and I'll print you max of them:\n");

    for (unsigned short i = 0; i < 3; ++i) {
        printf("Print number #%d: ", i + 1);

        // Проверяю входное значение. Если это не число,
        // вываливаюсь с системной ошибкой.
        if (scanf("%lf", &nums[i]) == 0) {
            printf("Invalid value, exitting.\n\n");
            return 1;  // Выходим с системной ошибкой
        }
    }

    // Теперь вывожу среднее
    printf("\nYour max value is: %lf\n\n", findMax(nums[0], nums[1], nums[2]));

    return 0;
}
