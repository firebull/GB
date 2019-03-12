/**
 * @copyright Nikita Bulaev 2019
 *
 * @file  hourse_move_task.c
 * @brief Требуется обойти конём шахматную доску размером NxM, пройдя через все поля доски по одному разу.
 *
 * @note Вместо передачи указателя на доску в функции, я использую глобальную
 *       переменную. Просто так код немного более компактен. Делаю это
 *       исключительно для этого ДЗ, в бою, конечно, передача указателя.
 */

#include "hourse_move_task.h"
#include <stdio.h>
#include <stdlib.h>

Board_t board; /*!< Описание доски */

unsigned long long operations = 0; /*!< Количество операций */
unsigned long           moves = 0; /*!< Количество ходов */

/**
 * @brief Инициализация доски произвольных размеров
 *
 * @note Использую трюк с указателями на указатели
 */
void InitBoard(void) {
    board.fields = (short **)malloc(board.N * sizeof(short *));

    for (short i = 0; i < board.N; i++) {
        board.fields[i] = (short *)calloc(board.M, sizeof(short));
    }
}

/**
 * @brief Освободить память, выделенную под доску
 */
void FreeBoard(void) {
    for (short i = 0; i < board.N; ++i) {
        free(board.fields[i]);
    }
}

/**
 * @brief Вывести итоговое заполнение доски
 */
void BoardPrint(void) {
    for (int i = 0; i < board.N; ++i) {
        for (int j = 0; j < board.M; ++j) {
            printf("| %hd ", board.fields[i][j]);
        }

        printf("|\n");
    }
}

/**
 * @brief Проверка, является ли это поле последним незаполненным
 *
 * @param  n Координата по  вертикали
 * @param  m Координата по горизонтали
 * @return   true, если поле последнее
 */
bool CheckIfLastEmpty(int n, int m) {
    unsigned int emptyCount = 0;

    for (int i = 0; i < board.N; ++i) {
        for (int j = 0; j < board.M; ++j) {
            operations++;

            if (board.fields[i][j] == 0) {
                emptyCount++;

                if (emptyCount > 1) {
                    return false;
                }
            }
        }
    }

    if (emptyCount == 1 && board.fields[n][m] == 0) {
        return true;
    }

    return false;
}

/**
 * @brief Проверка на возможность совершить указанный ход
 *
 * @param  n Координата по  вертикали
 * @param  m Координата по горизонтали
 * @param  move Ход из списка доступных
 * @return      Структуру с новыми координатами и флагом, возможен ли ход
 */
MovePoint_t CheckMove(int n, int m, Moves_t move) {
    MovePoint_t newMove;

    newMove.moveIsPossible = false;
    newMove.n = n;
    newMove.m = m;

    operations++;

    switch (move) {
        case MOVE_UP_LEFT:
            newMove.n--;
            newMove.m -= 2;
            break;

        case MOVE_UP_RIGHT:
            newMove.n++;
            newMove.m -= 2;
            break;

        case MOVE_RIGHT_UP:
            newMove.n += 2;
            newMove.m--;
            break;

        case MOVE_RIGHT_DOWN:
            newMove.n += 2;
            newMove.m++;
            break;

        case MOVE_DOWN_RIGHT:
            newMove.n++;
            newMove.m += 2;
            break;

        case MOVE_DOWN_LEFT:
            newMove.n--;
            newMove.m += 2;
            break;

        case MOVE_LEFT_DOWN:
            newMove.n -= 2;
            newMove.m++;
            break;

        case MOVE_LEFT_UP:
            newMove.n -= 2;
            newMove.m--;
            break;

        case MOVES_NUMBER:
        default:
            break;
    }

    if (newMove.n >= 0 && newMove.n < board.N
            && newMove.m >= 0 && newMove.m < board.M) {
        if (board.fields[newMove.n][newMove.m] == 0) {
            newMove.moveIsPossible = true;
        }
    }

    return newMove;
}

/**
 * @brief Совершить ход
 *
 * @param  n Координата по  вертикали
 * @param  m Координата по горизонтали
 * @return   true, если ход был успешен
 */
bool MakeMove(int n, int m) {
    MovePoint_t nextPoint;
    operations++;

    if (CheckIfLastEmpty(n, m) == true) {
        printf("Last move: n = %d, m = %d\n", n, m);
        board.fields[n][m] = 1;
        return true;
    }

    board.fields[n][m] = 1;

    for (int i = 0; i < MOVES_NUMBER; ++i) {
        nextPoint = CheckMove(n, m, i);

        if (nextPoint.moveIsPossible == true) {
            if (MakeMove(nextPoint.n, nextPoint.m) == true) {
                printf(" n = %d, m = %d\n", n, m);
                moves++;
                return true;
            }
        }
    }

    board.fields[n][m] = 0;
    return false;
}

int main (int argc, const char * argv[]) {
    board.N = 0;
    board.M = 0;

    printf("Enter board Height: ");

    // Проверяю входное значение. Если это не целое число,
    // вываливаюсь с системной ошибкой.
    if (scanf("%d", &board.N) == 0 || board.N <= 0) {
        printf("Invalid value, exitting.\n\n");
        return 1;  // Выходим с системной ошибкой
    }

    printf("Enter board Width: ");

    if (scanf("%d", &board.M) == 0 || board.M <= 0) {
        printf("Invalid value, exitting.\n\n");
        return 1;  // Выходим  системной ошибкой
    }

    InitBoard();

    for (int n = 0; n < board.N; n++) {
        for (int m = 0; m < board.M; m++) {
            printf("Move from {%d,%d}\n", n, m);

            if (MakeMove(n, m) == true) {
                break;
            }

            printf("No moves.\n");
        }

        if (moves > 0) {
            break;
        }
    }

    if (moves > 0) {
        printf("Made %lu moves through %llu operations\n\n", moves, operations);
    } else {
        printf("Made %llu operations, but could not find the solution\n\n", operations);
    }

    BoardPrint();

    FreeBoard();
    return 0;
}
