/**
 * @copyright Nikita Bulaev 2019
 *
 * @file  barier_move.c
 * @brief Количество маршрутов с препятствиями.
 *        Реализовать чтение массива с препятствием и нахождение
 *        количества маршрутов.
 */

#include <stdio.h>

int main (int argc, const char * argv[]) {

    /** Матрица препятствий (барьеров) */
    unsigned int barierMatrix[8][8] = {
        {1, 1, 1, 1, 1, 1, 1, 1},
        {0, 1, 0, 1, 1, 1, 1, 1},
        {0, 1, 0, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
    };

    unsigned int moveMatrix[8][8]; /*!< Матрица ходов */

    // Очевидно, нулевая клетка ходов равна такой же в барьерной
    moveMatrix[0][0] = barierMatrix[0][0];

    // Сначала заполнить первый ряд матрицы ходов
    for (unsigned short j = 1; j < 8; ++j) {

        if (barierMatrix[0][j] == 0 || moveMatrix[0][j - 1] == 0) {
            moveMatrix[0][j] = 0;
        } else {
            moveMatrix[0][j] = 1;
        }
    }

    for (unsigned short i = 1, j = 0; i < 8; ++i) {

        // Аналогично первой строке надо заполнить первый столбец
        if (barierMatrix[i][0] == 0 || moveMatrix[i - 1][0] == 0) {
            moveMatrix[i][0] = 0;
        } else {
            moveMatrix[i][0] = 1;
        }

        // Считаем ходы, учитывая матрицу препятствий
        for (j = 1; j < 8; j++) {
            if (barierMatrix[i][j] == 0) {
                moveMatrix[i][j] = 0;
            } else {
                moveMatrix[i][j] = moveMatrix[i][j - 1] + moveMatrix[i - 1][j];
            }
        }
    }

    for (unsigned short i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            printf("| %3u\t", moveMatrix[i][j]);
        }

        printf("|\n");
    }

    return 0;
}
