/**
 * @copyright Nikita Bulaev 2019
 *
 * @file  queue.c
 * @brief Реализация очереди на основе односвязного списка
 *
 */

#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Инициализация очереди
 *
 * @param q       Указатель на очередь
 * @param maxSize Максимальная длина очереди
 */
void InitQueue(Queue_t * q, unsigned int maxSize) {
    q->front   = NULL;
    q->rear    = NULL;
    q->size    = 0;
    q->maxSize = maxSize;
}

/**
 * @brief Добавление элемента в очередь
 *
 * @param q   Указатель на очередь
 * @param val Добавляемое значение
 * @return    Состояние или ошибку из списка QueueErrorsList_t
 */
QueueErrorsList_t AddNode(Queue_t * q, int val) {
    if (q->size == q->maxSize) {
        return ERROR_QUEUE_IS_FULL;
    }

    Node_t * tmp = (Node_t*) malloc(sizeof(Node_t));

    if (tmp == NULL) {
        return ERROR_QUEUE_MEMORY_ALLOC;
    }

    tmp->field = val;
    tmp->next  = NULL;

    if ((q->rear == NULL) && (q->front == NULL)) {
        q->rear  = tmp;
        q->front = q->rear;
    } else {
        q->rear->next = tmp;
        q->rear = tmp;
    }

    q->size++;

    return NO_ERROR;
}

/**
 * @brief Забрать первый элемент очереди
 * @param  q     Указатель на очередь
 * @param  value Указатель на переменную, куда
 *               положить значение  извлекаемого узла
 * @return       Состояние или ошибку из списка QueueErrorsList_t
 */
QueueErrorsList_t PopFrontNode(Queue_t * q, int * value) {

    if (q->size == 0) {
        return ERROR_QUEUE_IS_EMPTY;
    }

    *value = q->front->field;

    return DeleteFrontNode(q);
}

/**
 * @brief Вывод элементов очереди
 *
 * @param q Указатель на очередь
 */
void PrintQueue(Queue_t * q) {
    struct Node_t * node;

    if (q->size == 0) {
        return;
    }

    for (node = q->front; node != NULL; node = node->next) {
        printf("%d", node->field);

        if (node->next != NULL) {
            printf(" => ");
        } else {
            printf("\n");
        }
    }
}

/**
 * @brief Удаление элемента из очереди
 *
 * @param  q Указатель на очередь
 * @return   Состояние или ошибку из списка QueueErrorsList_t
 */
QueueErrorsList_t DeleteFrontNode(Queue_t * q) {
    Node_t * tmp;

    if (q->size == 0) {
        return ERROR_QUEUE_IS_EMPTY;
    }

    tmp = q->front;

    if (tmp != NULL) {
        q->front = q->front->next;
        free(tmp);
        q->size--;
    }

    if (q->size == 0) {
        q->rear = NULL;
    }

    return NO_ERROR;
}


/**
 * @brief Очистка всей очереди
 *
 * @param q Указатель на очередь
 */
void ClearQueue(Queue_t * q) {
    while (q->front != NULL) {
        Node_t * temp = q->front;

        q->front = q->front->next;
        free(temp);
    }

    q->size = 0;
}

/**
 * @brief Получение первого элемента в очереди без его удаления
 *
 * @param  q Указатель на очередь
 * @return   Значение узла
 */
int ViewFront(Queue_t * q) {
    return q->front->field;
}
