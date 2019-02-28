/**
 * (c) Nikita Bulaev 2019
 *
 * @file  task11.c
 * @brief С клавиатуры вводятся числа, пока не будет введен 0.
 *        Подсчитать среднее арифметическое всех положительных
 *        четных чисел, оканчивающихся на 8.
 */

#include <stdio.h>

int main (int argc, const char* argv[]) {

    int inputNo = -1;
    double sum = 0;
    unsigned int count = 0;

    printf("Enter numbers. To exit print 0.\n\n");

    for (;;) {
        printf("Enter integer number: ");

        // Проверяю входное значение. Если это не число,
        // вываливаюсь с системной ошибкой.
        if (scanf("%d", &inputNo) == 0) {
            printf("Invalid value, exitting.\n\n");
            return 1;  // Выходим с системной ошибкой
        }

        if (inputNo == 0) {
            break;
        } else {
            if ((inputNo % 10) == 8) {
                sum += inputNo;
                count++;
            }
        }
    }

    if (count > 0) {
        printf("Medium of positive numbers ending with 8 is: %.03lf\n", sum / (float)count);
    } else {
        printf("Got no positive numbers with 8 at the end\n");
    }

    return 0;
}
