/**
 * (c) Nikita Bulaev 2019
 *
 * @file  task07.c
 * @brief С клавиатуры вводятся числовые координаты двух полей шахматной
 *        доски (x1,y1,x2,y2). Требуется определить, относятся ли к поля
 *        к одному цвету или нет
 *
 * @note Я реализую через табличные данные. Так всегда быстрее.
 */

#include <stdio.h>

/** Цвета полей шахматной доски */
typedef enum {
    w, /*!< White */
    b  /*!< Black */
} Colors;

/** Структура для хранения координат точки */
typedef struct {
    short x;
    short y;
} Coordinates_t;

/** Расположение цветов на шахматной доске 8х8 */
Colors chessDesk[8][8] = {
    {b, w, b, w, b, w, b, w},
    {w, b, w, b, w, b, w, b},
    {b, w, b, w, b, w, b, w},
    {w, b, w, b, w, b, w, b},
    {b, w, b, w, b, w, b, w},
    {w, b, w, b, w, b, w, b},
    {b, w, b, w, b, w, b, w},
    {w, b, w, b, w, b, w, b},
};

int main (int argc, const char* argv[]) {

    Coordinates_t p1, p2; /*!< Вводимые координаты точек */

    printf("Print coordinates. Must be > 0 and <= 8:\n\n");

    printf("Print X1: ");

    // Проверяю входное значение. Если это не число,
    // вываливаюсь с системной ошибкой.
    if (scanf("%hd", &p1.x) == 0) {
        printf("Invalid value, exitting.\n\n");
        return 1;  // Выходим с системной ошибкой
    }

    printf("Print Y1: ");

    // Проверяю входное значение. Если это не число,
    // вываливаюсь с системной ошибкой.
    if (scanf("%hd", &p1.y) == 0) {
        printf("Invalid value, exitting.\n\n");
        return 1;  // Выходим с системной ошибкой
    }

    printf("Print X2: ");

    // Проверяю входное значение. Если это не число,
    // вываливаюсь с системной ошибкой.
    if (scanf("%hd", &p2.x) == 0) {
        printf("Invalid value, exitting.\n\n");
        return 1;  // Выходим с системной ошибкой
    }

    printf("Print Y2: ");

    // Проверяю входное значение. Если это не число,
    // вываливаюсь с системной ошибкой.
    if (scanf("%hd", &p2.y) == 0) {
        printf("Invalid value, exitting.\n\n");
        return 1;  // Выходим с системной ошибкой
    }

    if (p1.x <= 0 || p1.y <= 0 || p2.x <= 0 || p2.y <= 0
            || p1.x > 8 || p1.y > 8 || p2.x > 8 || p2.y > 8) {
        printf("Invalid value, must be > 0 and <= 8, exitting.\n\n");
        return 1;  // Выходим с системной ошибкой
    }

    if (chessDesk[p1.x - 1][p1.y - 1] == chessDesk[p2.x - 1][p2.y - 1]) {
        printf("Colors are the same\n");
    } else {
        printf("Colors are different\n");
    }

    return 0;
}
