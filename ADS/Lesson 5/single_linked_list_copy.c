/**
 * @copyright Nikita Bulaev 2019
 *
 * @file  single_linked_list_copy.c
 * @brief Создать функцию, копирующую односвязный список (то есть создает
 *        в памяти копию односвязного списка, без удаления первого списка).
 */

#include "math_formula_check.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * @brief Закинуть в стэк
 *
 * @param  stack Указатель на структуру с описанием стэка
 * @param  value Значение эелемента стэка
 * @return       Код ошибки из списка ErrorsList_t
 */
ErrorsList_t Push(Stack_t * stack, T value) {

    if (stack->size >= stack->maxSize) {
        return ERROR_STACK_IS_FULL;
    }

    Node_t * tmp = (Node_t*) malloc(sizeof(Node_t));

    if (tmp == NULL) {
        return ERROR_STACK_MEMORY_ALLOC;
    }

    tmp->value = value;
    tmp->next  = stack->head;

    stack->head = tmp;
    stack->size++;

    return NO_ERROR;
}


/**
 * @brief Очистить стэк
 *
 * @param stack Указатель на структуру с описанием стэка
 */
void ClearStack(Stack_t * stack) {
    while (stack->head != NULL) {
        Node_t * temp = stack->head;
        stack->head = stack->head->next;
        free(temp);
    }

    stack->size = 0;
}

/**
 * @brief Создание копии стэка
 *
 * @note  Копию делаю от первого элемента к последнему
 *
 * @param  stackIn  Указатель на стэк, который надо скопировать
 * @param  stackOut Указатель на стэк, в который надо сделать копию
 * @return          Ошибку из списка ErrorsList_t
 */
ErrorsList_t CopyStack(Stack_t * stackIn, Stack_t * stackOut) {
    ErrorsList_t error = NO_ERROR;
    Node_t * nodeIn = stackIn->head;
    Node_t * pastNodeOut = (Node_t*) malloc(sizeof(Node_t));

    if (pastNodeOut == NULL) {
        return ERROR_STACK_MEMORY_ALLOC;
    }

    pastNodeOut->value = nodeIn->value;
    stackOut->head = pastNodeOut;

    nodeIn = stackIn->head->next;

    int i = 0;

    for (i = 1; i < stackIn->size; ++i) {
        Node_t * tmp = (Node_t*) malloc(sizeof(Node_t));

        if (tmp == NULL) {
            error = ERROR_STACK_MEMORY_ALLOC;
            break;
        }

        tmp->value = nodeIn->value;
        nodeIn = nodeIn->next;
        pastNodeOut->next = tmp;
        pastNodeOut = tmp;
    }

    stackOut->size = i;
    stackOut->maxSize = stackIn->maxSize;

    return error;
}

/**
 * @brief Вывод в консоль содержимого стэка БЕЗ его очистки
 *
 * @param stack Указатель на стэк
 */
void PrintStack(Stack_t * stack) {
    Node_t * tmp = stack->head;

    for (int i = 0; i < stack->size; ++i) {
        printf("0x%02X\n", tmp->value);
        tmp = tmp->next;
    }
}

int main (int argc, const char * argv[]) {
    Stack_t mainStack = { NULL, 0, 256 };
    Stack_t copyStack = { NULL, 0, 256 };

    srand(time(NULL));  // Инициализация стандартного ГПСЧ текущим временем

    // Создам стэк со случайными числами от 0 до 127
    for (int i = 0; i < 10; ++i) {
        ErrorsList_t error = Push(&mainStack, (char)(rand() % 0x0F));

        if (error != NO_ERROR) {
            ClearStack(&mainStack);

            switch (error) {
                case ERROR_STACK_IS_FULL:
                    printf("ERROR: Got stack overload\n");
                    return 1;

                case ERROR_STACK_MEMORY_ALLOC:
                    printf("ERROR: Could not allocate memory\n");
                    return 1;

                default:
                    printf("Unknown error occured\n");
                    return 1;
            }
        }
    }

    printf("Initial stack is:\n");

    PrintStack(&mainStack);

    if (CopyStack(&mainStack, &copyStack) == NO_ERROR) {
        printf("\nNew stack is:\n");
        PrintStack(&copyStack);
    } else {
        printf("ERROR: Could not allocate memory\n");
        ClearStack(&copyStack);
        return 1;
    }

    ClearStack(&mainStack);
    ClearStack(&copyStack);

    return 0;
}
