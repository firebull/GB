/**
 * @file  hourse_move_task.h
 * @brief Header for hourse_move_task.c
 * @copyright Nikita Bulaev 2019
 */

#ifndef HOURSE_MOVE_TASK_H_
#define HOURSE_MOVE_TASK_H_ 100

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

// В C нет типа Bool, определю его тут
typedef enum {
    false = 0,
    true
} bool;

typedef struct{
    int N;            /*!< Высота доски */
    int M;            /*!< Ширина строки */
    short ** fields;  /*!< Доска, размер массива задается в функции */
} Board_t;

typedef enum {
    MOVE_UP_LEFT = 0, /*!< Ход вверх влево */
    MOVE_UP_RIGHT,    /*!< Ход вверх вправо */
    MOVE_RIGHT_UP,    /*!< Ход направо вверх */
    MOVE_RIGHT_DOWN,  /*!< Ход направо вниз */
    MOVE_DOWN_RIGHT,  /*!< Ход вниз направо */
    MOVE_DOWN_LEFT,   /*!< Ход вниз влево */
    MOVE_LEFT_DOWN,   /*!< Ход налево вниз */
    MOVE_LEFT_UP,     /*!< Ход налево вверх */

    MOVES_NUMBER      /*!< Всего доступных ходов */
} Moves_t;

typedef struct {
    bool moveIsPossible;  /*!< Возможен ли ход */
    int n;                /*!< Координата по высоте */
    int m;                /*!< Координата по ширине */
} MovePoint_t;

/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif
