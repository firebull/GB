/**
 * @copyright Nikita Bulaev 2019
 *
 * @file  task13.c
 * @brief Написать функцию, генерирующую случайное число от 1 до 100
 *
 * @note  с использованием стандартной функции rand()
 *        без использования стандартной функции rand()
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static unsigned long tempRand = 0;     /*!< Переменная для хранения промежуточных значений */

/**
 * @brief Вывод случайного числа от 1 до 100 используя стандартную rand()
 *
 * @return  Случайное целое число от 1 до 100
 */
unsigned short StdRand100(void) {

    // Сначала инициализировать стартовое значение
    if (tempRand == 0) {
        tempRand = time(NULL);
        srand(tempRand);  // Инициализация стандартного ГПСЧ текущим временем
    }

    // Вывод остатка от деления от полученного случайного числа
    return (rand() % 100) + 1;
}

/**
 * @brief Вывод псевдо-случайного числа собственной реализации
 *
 * @return  Случайное целое число от 1 до 100
 */
unsigned short OtherRand100(void) {

    // Сначала инициализировать стартовое значение
    if (tempRand == 0) {
        unsigned long long * randAddr = NULL;  /*!< Дополнительный фактор. Адрес переменной даётся случайно при старте */

        tempRand = time(NULL);

        // Для дополнительного случайного фактора наложим
        // XOR на стартовое значение с адресом переменной randAddr,
        // которая инициализируется в неизвестном заранее адресе при старте
        tempRand ^= (unsigned long)&randAddr;
    }

    char * iRand = NULL;  /*!< Дополнительный случайный адрес */

    tempRand = tempRand * 1664525L + (unsigned long)&iRand;

    return (tempRand % 100) + 1;
}

int main (int argc, const char * argv[]) {

    printf("Print Std rand() numbers:\n");

    for (short i = 0; i < 50; i++) {
        printf("%02d - %u\n", i + 1, StdRand100());
    }

    tempRand = 0;

    printf("\n\nPrint own implementation of pseudo-random numbers:\n");

    for (short i = 0; i < 50; i++) {
        printf("%02d - %u\n", i + 1, OtherRand100());
    }

    return 0;
}
