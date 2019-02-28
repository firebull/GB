/**
 * @copyright Nikita Bulaev 2019
 *
 * @file  task04.c
 *
 * @brief Написать программу нахождения корней заданного квадратного уравнения
 *
 * @note Надо помнить, что компилировать с ключом -lm
 */

#include <stdio.h>
#include <math.h>

/**
 * @brief Решение квадратного уравнения с помощью дискриминанта
 *
 * @param  a  Первый коэффициент
 * @param  b  Второй коэффициент
 * @param  c  Свободный член
 * @param  x1 Первый корень
 * @param  x2 Второй корень
 * @return    -1, если уравнение не имеет корней
 *             0, если у уравнения есть один корень
 *             1, если у уравнения два корня
 */
int calculateSquareEquality(int a, int b, int c, float* x1, float* x2) {
    // Проверка деления на ноль
    if (a == 0) {
        return -1;
    }

    double d;  // Тип double, т.к. sqrt принимает double

    // Рассчитываем дискриминант
    d = b * b - 4 * a * c;

    // Если дискриминант < 0, уравнение не имеет решения
    if (d < 0) {
        return -1;
    } else if (d > 0) { // Если больше нуля, имеем два корня

        // Хорошим тоном будет привести все int к float
        *x1 = ((float)(-b) + sqrt(d)) / (2.0f * (float)a);
        *x2 = ((float)(-b) - sqrt(d)) / (2.0f * (float)a);

        return 1;
    } else {
        *x1 = *x2 = -((float)b / (2.0f * (float)a));
        return 0;
    }
}

int main (int argc, const char* argv[]) {

    // Определяю переменные локально в функции

    int a, /*!< Первый коэффициент */
        b, /*!< Второй коэффициент */
        c; /*!< Свободный член */

    float x1, /*!< Первый корень */
          x2; /*!< Второй корень */

    /*
        Я не буду переспрашивать данные, если введены неправильно.
        Не хочу усложнять программу, это за пределами задания.
        Просто выход с системной ошибкой.
     */

    printf("Print numerical coefficient (integer)\"a\": ");
    if (scanf("%d", &a) == 0) { return 1; }

    printf("Print numerical coefficient (integer)\"b\": ");
    if (scanf("%d", &b) == 0) { return 1; }

    printf("Print numerical coefficient (integer)\"c\": ");
    if (scanf("%d", &c) == 0) { return 1; }

    /* Я предпочитаю использовать switch для таких случаев */
    switch (calculateSquareEquality(a, b, c, &x1, &x2)) {
        case -1:
            printf("Current Quadric equation have no solution\n\n");
            break;

        case 0:
            printf("Current quadric equation have one solution x=%.4f\n\n", x1);
            break;

        case 1:
            printf("Current quadric equation have two solutions x1=%.4f, x2=%.4f\n\n", x1, x2);
            break;

        default:
            return 1; // не должны попасть сюда. Если дошли, выход с ошибкой.
            break;
    }

    return 0;
}
