/**
 * @copyright Nikita Bulaev 2019
 *
 * @file  math_formula_check.c
 * @brief 3. Написать программу, которая определяет, является ли введенная
 *           скобочная последовательность правильной. Примеры правильных
 *           скобочных выражений: (), ([])(), {}(), ([{}]),
 *           неправильных — )(, ())({), (, ])}), ([(]) для скобок [,(,{.
 *        5. **Реализовать алгоритм перевода из инфиксной записи арифметического
 *           выражения в постфиксную.
 *
 * @note Также тут частично реализовал задание №2 в функции Push()
 *
 */

#include "math_formula_check.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
 * @brief Взять верхний элемент стэка
 *
 * @param  stack Указатель на структуру с описанием стэка
 * @return       Значение эелемента стэка
 * @return       Код ошибки из списка ErrorsList_t, если возникнет ошибка
 */
T Pop(Stack_t * stack) {
    if (stack->size == 0) {
        return ERROR_STACK_IS_EMPTY;
    }

    // Временный указатель
    Node_t * next = NULL;

    // Значение «наверху» списка
    T value;
    value = stack->head->value;
    next  = stack->head;

    stack->head = stack->head->next;

    // Запись, на которую указывала «голова», удаляем, освобождая память
    free(next);

    // Возвращаем значение, которое было в «голове»
    stack->size--;
    return value;
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
 * @brief Проверка правильности скобочной последовательности
 *
 * @param  buff   Строка с формулой или скобочной последовательности
 * @param  length Длина строки
 * @return        Код ошибки из списка ErrorsList_t
 */
ErrorsList_t CheckParenthesisGrammar(char * buff, unsigned int length) {
    Stack_t grammarStack = { NULL, 0, 256 };
    ErrorsList_t error = NO_ERROR;
    unsigned int brackPairs = 0;

    for (unsigned int i = 0; i < length; ++i) {
        if (buff[i] == '\0') {
            break;
        }

        if (strchr("{[(", buff[i]) != NULL) {
            //printf("%c", buff[i]);  // Debug brackets
            error = Push(&grammarStack, buff[i]);

            if (error != NO_ERROR) {
                break;
            }

        } else if (strchr(")]}", buff[i]) != NULL) {
            char lastSymb = Pop(&grammarStack);
            //printf("%c", buff[i]);  // Debug brackets

            switch (lastSymb) {
                case '(':
                    if (buff[i] != ')') {
                        error = ERROR_BAD_GRAMMAR;
                    }

                    brackPairs++;
                    break;

                case '[':
                    if (buff[i] != ']') {
                        error = ERROR_BAD_GRAMMAR;
                    }

                    brackPairs++;
                    break;

                case '{':
                    if (buff[i] != '}') {
                        error = ERROR_BAD_GRAMMAR;
                    }

                    brackPairs++;
                    break;


                case ERROR_STACK_IS_EMPTY:
                default:
                    error = ERROR_BAD_GRAMMAR;
                    break;
            }

            if (error != NO_ERROR) {
                break;
            }
        } else {
            continue;
        }
    }

    // Если стэк не пустой, значит остались открывающие скобки - ошибка
    // Если пар скобок не обнаружено - также ошибка
    if (grammarStack.size > 0 || brackPairs == 0) {
        error = ERROR_BAD_GRAMMAR;
    }

    ClearStack(&grammarStack);

    return error;
}

/**
 * @brief Перевод из инфиксной записи арифметического выражения в постфиксную
 *
 * @note  Тут нет обработки степеней, корней и т.д.
 *
 * @param  infixBuffer   Строка с инфиксной записью
 * @param  length        Длина строки инфиксной записи
 * @param  postfixBuffer Строка с постфиксной записью
 * @return               Код ошибки из списка ErrorsList_t
 */
ErrorsList_t ToPostfixNotation(char * infixBuffer, unsigned int length, char * postfixBuffer) {
    ErrorsList_t error = NO_ERROR;
    Stack_t postfixStack = { NULL, 0, 256 };

    for (unsigned int i = 0; i < length; ++i) {
        if (infixBuffer[i] == '\0') {
            break;
        }

        // Цифры сразу писать в выходной буфер
        if (infixBuffer[i] >= '0' && infixBuffer[i] <= '9') {
            while (infixBuffer[i] >= '0' && infixBuffer[i] <= '9') {
                *(postfixBuffer++) = infixBuffer[i++];
            }

            *(postfixBuffer++) = ' ';

            i--;
        } else {
            char algOper = 0;

            switch (infixBuffer[i]) {
                case '+':
                case '-':
                case '*':
                case '/':
                case '\\':
                    error = Push(&postfixStack, infixBuffer[i]);
                    break;

                case ')':
                case ']':
                case '}':
                    algOper = Pop(&postfixStack);

                    if (algOper > NO_ERROR) {
                        *(postfixBuffer++) = algOper;
                        *(postfixBuffer++) = ' ';
                    }

                    break;

                default:
                    break;
            }
        }

        if (error != NO_ERROR) {
            break;
        }
    }

    *(postfixBuffer++) = '\0';

    ClearStack(&postfixStack);

    return error;
}

int main (int argc, const char * argv[]) {

    char buff[101] = {'\0'};

    // Для проверки, например:
    // (((2+3)*[(5-7)/4])-45)
    // [((56-6)+(6*2)) + 24]
    printf("Enter arithmetic expression (100 symbols max): ");
    fgets(buff, sizeof(buff), stdin);

    ErrorsList_t grammarCheck = CheckParenthesisGrammar(buff, strlen(buff));

    // Подробно выведу описание ошибок. Хотя для боевой задачи,
    // надо это выводить в отдельную функцию. Сейчас я упрощаю код.
    switch (grammarCheck) {
        case ERROR_STACK_IS_EMPTY:
        case ERROR_BAD_GRAMMAR:
            printf("ERROR: Bad Parenthesis Grammar\n");
            return 1;

        case ERROR_STACK_IS_FULL:
            printf("ERROR: While Parenthesis Grammar check got stack overload\n");
            return 1;

        case ERROR_STACK_MEMORY_ALLOC:
            printf("ERROR: Could not allocate memory\n");
            return 1;

        case NO_ERROR:
        default:
            printf("Parenthesis Grammar check OK!\n\n");
            break;
    }

    char postfixBuffer[100];

    // Я не буду тут повторно выводить описание подробных ошибок
    if (ToPostfixNotation(buff, strlen(buff), postfixBuffer) != NO_ERROR) {
        printf("Some errors occured. Check formula notation!\n");
        return 1;
    }

    printf("Resulted formula: %s\n", postfixBuffer);

    return 0;
}
