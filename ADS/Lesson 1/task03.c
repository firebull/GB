/**
 * @copyright Nikita Bulaev 2019
 *
 * @file  task03.c
 * @brief Обмена значениями двух целочисленных переменных
 *
 * @note  a. с использованием третьей переменной;
 *        b. *без использования третьей переменной.
 *
 */

#include <stdio.h>

int main (int argc, const char * argv[]) {

    int a = 0xBADC;
    int b = 0x8DCE;

    printf("I gonna swap a = 0x%X <-> b = 0x%X:\n\n", a, b);

    printf("Classic algoritm with third val:\n");

    int c = a;
    a = b;
    b = c;

    printf("And now a = 0x%X, b = 0x%X\n\n", a, b);

    printf("Now I will swap them back without third val but by XOR:\n");

    a ^= b;
    b ^= a;
    a ^= b;

    printf("And now a = 0x%X, b = 0x%X\n", a, b);

    return 0;
}
