/**
 * @copyright Nikita Bulaev 2019
 *
 * @file  task2.c
 * @brief Реализовать функцию возведения числа a в степень b:
 *        a. без рекурсии;
 *        b. рекурсивно;
 *        c. *рекурсивно, используя свойство чётности степени.
 *
 * @note Значение итогового числа ограниченно типом long long int
 *
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Быстрое возведение в степень целого числа без рекурсии
 *
 * @note  Степень тоже целое число
 *
 * @param  a Что возводим в степень
 * @param  b Степень числа
 * @return   Итоговое число
 */
long double QuickPow(long long a, int b) {
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
        return (long double)n;
    } else {
        // Отрицательная степень
        return 1.0f / n;
    }
}


/**
 * @brief Возведение в степень целого числа без рекурсии
 *
 * @note  Равенство a = 0 я проверяю внутри других условий,
 *        дабы не тормозить рекурсию на длинных цепочках
 *
 * @param  a Указатель на число, которое возводим в степень
 * @param  b Указатель на степень числа
 * @return   Итоговое число
 */
long double PowRecur(long long * a, int * b) {
    if (*b == 0) {
        if (*a == 0) {
            return 0;
        } else {
            return 1;
        }
    } else if (*b > 0) {
        (*b)--;
        return *a * PowRecur(a, b);
    } else {
        if (*a == 0) {
            return 0;
        }

        (*b)++;
        return (1.0f / (*a)) * PowRecur(a, b);
    }
}

/**
 * @brief Возведение в степень целого числа с рекурсией и
 *        без проверок на входные данные
 *
 * @param a Указатель на число, которое возводим в степень
 * @param b Указатель на степень числа
 * @param n Указатель на итоговое число
 */
static void QuickPowRecurOnly(long long * a, unsigned int * b, long long * n) {
    if (*b == 0) {
        return;
    }

    if (*b % 2) {
        (*b)--;
        *n *= *a;
    } else {
        *b /= 2;
        (*a) *= (*a);
    }

    QuickPowRecurOnly(a, b, n);
}


/**
 * @brief Быстрое возведение в степень целого числа с рекурсией
 *
 * @note  Степень тоже целое число
 *
 * @param  a Что возводим в степень
 * @param  b Степень числа
 * @return   Итоговое число
 */
long double QuickPowRecur(long long a, int b) {
    if (a == 0) {
        return 0;
    }

    long long n = 1;        /*!< Итоговое число */
    unsigned int power = b; /*!< Степень числа, промежуточные значения */

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

    QuickPowRecurOnly(&a, &power, &n);

    if (b > 0) {
        return (long double)n;
    } else {
        // Отрицательная степень
        return 1.0f / n;
    }
}

int main (int argc, const char * argv[]) {

    long long a = 0;  /*!< Что возводим в степень */
    int b = 0;  /*!< Степень числа */


    printf("Print number to count power of. Must be integer. a=");

    // Проверяю входное значение. Если это не число,
    // вываливаюсь с системной ошибкой.
    if (scanf("%lld", &a) == 0) {
        printf("Invalid value, exitting.\n\n");
        return 1;  // Выходим с системной ошибкой
    }

    printf("Print power of number. Must be integer. b=");

    if (scanf("%d", &b) == 0) {
        printf("Invalid value, exitting.\n\n");
        return 1;  // Выходим с системной ошибкой
    }

    printf("Quick Power of number without recursion: %lld^%d = %.04Lf\n", a, b, QuickPow(a, b));
    printf("Quick Power of number with recursion: %lld^%d = %.04Lf\n", a, b, QuickPowRecur(a, b));
    printf("Simple Power of number with recursion: %lld^%d = %.04Lf\n", a, b, PowRecur(&a, &b));

    return 0;
}
