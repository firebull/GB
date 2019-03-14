/**
 * @file  math_formula_check.h
 * @brief Header for math_formula_check.c
 * @copyright Nikita Bulaev 2019
 */

#ifndef MATH_FORMULA_CHECK_H_
#define MATH_FORMULA_CHECK_H_ 100

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

#define T char

// В C нет типа Bool, определю его тут
typedef enum {
    false = 0,
    true
} bool;


// @note Для описания структур я использую чисто Си-шный трюк

/**
 * Структура для описания элемента односвязного списка
 */
typedef struct TNode {
    T value;                  /*!< Данные */
    struct TNode *next;       /*!< Указатель на следующий элемент списка */
} Node_t;                     /*!< Элемент односвязного списка */


typedef struct {
    Node_t * head;  /*!< Указатель на верхний элемент стэка*/
    int size;       /*!< Текущий размер стэка */
    int maxSize;    /*!< Максимальный размер стэка */
} Stack_t;          /*!< Структура для описания стэка  */

/** Коды ошибок  */
typedef enum {
    ERROR_BAD_GRAMMAR        = -4, /*!< Некорректное написание формулы */
    ERROR_STACK_MEMORY_ALLOC = -3, /*!< Невозможно выделить память */
    ERROR_STACK_IS_FULL      = -2, /*!< Переполнение стэка */
    ERROR_STACK_IS_EMPTY     = -1, /*!< Стэк пуст */
    NO_ERROR = 0,                  /*!< Нет ошибок */
} ErrorsList_t;

/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif
