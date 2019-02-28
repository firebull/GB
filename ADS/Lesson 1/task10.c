/**
 * (c) Nikita Bulaev 2019
 *
 * @file  task10.c
 * @brief Дано целое число N (> 0). С помощью операций деления нацело и взятия
 * остатка от деления определить, имеются ли в записи числа N нечетные цифры.
 * Если имеются, то вывести True, если нет — вывести False.
 *
 * @note При переполнении числа даёт некорректный ответ
 */

#include <stdio.h>

int main (int argc, const char* argv[]) {

    long long int n = 0;

    printf("Enter integer number: ");

    // Проверяю входное значение. Если это не число,
    // вываливаюсь с системной ошибкой.
    if (scanf("%lld", &n) == 0) {
        printf("Invalid value, exitting.\n\n");
        return 1;  // Выходим с системной ошибкой
    }

    if (n < 0) {
        n *= -1;
    }

    while (n) {
        if ((n % 10) % 2 == 1 ) {
            printf("true\n");
            return 0;
        }

        n /= 10;
    }


    printf("false\n");
    return 0;
}
