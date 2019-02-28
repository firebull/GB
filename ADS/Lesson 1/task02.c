/**
 * (c) Nikita Bulaev 2019
 *
 * @file  task02.c
 * @brief Найти максимальное из четырех чисел. Массивы не использовать
 *
 */

#include <stdio.h>

unsigned short num = 4;   /*!< Количество вводимых значений */
double inputNo = 0.0f;    /*!< Вводимое значение */
double max     = 0.0f;    /*!< Максимальное значение */

int main (int argc, const char* argv[]) {
    printf("Print %u numbers and I'll print you max of them:\n", num);

    for (unsigned short i = 0; i < num; ++i) {
        printf("Print number #%d: ", i + 1);

        // Проверяю входное значение. Если это не число,
        // вываливаюсь с системной ошибкой.
        if (scanf("%lf", &inputNo) == 0) {
            printf("Invalid value, exitting.\n\n");
            return 1;  // Выходим с системной ошибкой
        }

        if (inputNo > max){
            max = inputNo;
        }
    }

    // Теперь вывожу среднее
    printf("\nYour max value is: %.3lf\n\n", max);

    return 0;
}
