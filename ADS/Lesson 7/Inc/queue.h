/**
 * @file  queue.h
 * @brief Header for queue.c
 * @copyright Nikita Bulaev 2019
 */

#ifndef QUEUE_H_
#define QUEUE_H_ 100

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

typedef struct Node_t {
    int    field;
    struct Node_t *next;
} Node_t;

typedef struct {
    unsigned int   size;
    unsigned int   maxSize;
    struct Node_t *front;
    struct Node_t *rear;
} Queue_t;

/** Коды ошибок  */
typedef enum {
    ERROR_QUEUE_MEMORY_ALLOC = -3, /*!< Невозможно выделить память */
    ERROR_QUEUE_IS_FULL      = -2, /*!< Переполнение очереди */
    ERROR_QUEUE_IS_EMPTY     = -1, /*!< Очередь пуста */
    NO_ERROR                 = 0,  /*!< Нет ошибок */
} QueueErrorsList_t;


void InitQueue(Queue_t * q, unsigned int maxSize);
QueueErrorsList_t AddNode(Queue_t * q, int x);
void PrintQueue(Queue_t * q);
QueueErrorsList_t DeleteFrontNode(Queue_t * q);
QueueErrorsList_t PopFrontNode(Queue_t * q, int * value);
void ClearQueue(Queue_t * q);
int ViewFront(Queue_t * q);

/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif
