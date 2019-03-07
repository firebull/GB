/**
 * @copyright Nikita Bulaev 2019
 *
 * @file  task3.c
 * @brief Исполнитель «Калькулятор» преобразует целое число, записанное на экране.
 *        У исполнителя две команды, каждой присвоен номер:
 *            1. Прибавь 1.
 *            2. Умножь на 2.
 *        Первая команда увеличивает число на экране на 1, вторая увеличивает его в 2 раза.
 *        Определить, сколько существует программ, которые преобразуют число 3 в число 20:
 *
 * @note   а. С использованием массива.
 *         b. *С использованием рекурсии.
 *
 */

#include <stdio.h>


/**
 * @brief Рекурсивно ищем итогове число из операций сложения и умножения
 * @param num     Текущее значение числа
 * @param max     Указатель на максимальное значение
 * @param counter Указатель на счётчик при достижении max
 */
void CountNum(unsigned short num, unsigned short * max, unsigned int * counter) {

    if (num == *max) {
        (*counter)++;
        return;
    } else if (num > *max) {
        return;
    }

    CountNum(num + 1, max, counter);

    if (num <= (*max) / 2) {
        CountNum(num *= 2, max, counter);
    }
}


int main (int argc, const char * argv[]) {

    unsigned short max      = 20;  /*!< Максимальное значение числа */
    unsigned int   counter  = 0;   /*!< Количество вариантов для рекурсивной функции */
    unsigned short ways[50] = {0}; /*!< Массив вариантов для подсчета обычным алгоритмом */

    /* Я не буду нумеровать эелементы с 0, т.к. это
       сильно запутает код. Вместо этого текущее число
       и будет номером элемента массива, а значение
       элемента  - это количество вариантов достижения
       этого числа.

       Собственно считается по формуле:
        - Для нечётных значений равно предыдущему варианту
        - Для четных к предыдущему надо плюсовать ways[i/2]

       Т.о. считаем количество вариантов для каждого числа в цепочке,
       пока не достигнем нужного. */

    printf("Counting ways using array:\n");

    ways[3] = 1; // 3
    ways[4] = 1; // 4
    ways[5] = 1; // 5

    for (unsigned short i = 6; i <= max ; ++i) {

        if (i % 2 == 0) {
            ways[i] = ways[i - 1] + ways[i / 2];
        } else {
            ways[i] = ways[i - 1];
        }

        printf("Num %hu => %hu ways,\n", i, ways[i]);
    }

    printf("\nThere are %u variants to get %hu from 3\n\n", ways[max], max);

    printf("Now counting ways with recursive function:\n");

    CountNum(3, &max, &counter);

    printf("There are %u variants to get %hu from 3\n", counter, max);

    return 0;
}
