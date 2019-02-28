/**
 * (c) Nikita Bulaev 2019
 *
 * @file  task08.c
 * @brief Ввести a и b и вывести квадраты и кубы чисел от a до b
 *
 */

#include <stdio.h>
#include <stdlib.h>


/**
 * @brief Быстрое возведение в степень целого числа
 *
 * @note  Степень тоже целое число
 *
 * @param  a Что возводим в степень
 * @param  b Степень числа
 * @return   Итоговое число
 */
double quickPow(int a, int b) {
    int n = 1;
    int power = b;

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
        power = abs(b);
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
        return n;
    } else {
        // Отрицательная степень
        return 1.0f / n;
    }
}

int main (int argc, const char* argv[]) {

    int a = 0, b = 0;

    printf("Print number to count power of. Must be integer. a=");

    // Проверяю входное значение. Если это не число,
    // вываливаюсь с системной ошибкой.
    if (scanf("%d", &a) == 0) {
        printf("Invalid value, exitting.\n\n");
        return 1;  // Выходим с системной ошибкой
    }

    printf("Print power of number. Must be integer. b=");

    if (scanf("%d", &b) == 0) {
        printf("Invalid value, exitting.\n\n");
        return 1;  // Выходим с системной ошибкой
    }

    // a должно быть меньше b:
    if (a > b) {
        printf("a must be less then b.\n\n");
        return 1;  // Выходим с системной ошибкой
    }

    while (a <= b) {
        printf("%d^2 = %.0lf, %d^3 = %.0lf\n", a, quickPow(a, 2), a, quickPow(a, 3));
        a++;
    }

    return 0;
}
