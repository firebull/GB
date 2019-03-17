/**
 * @copyright Nikita Bulaev 2019
 *
 * @file  simple_hash.c
 * @brief 1. Реализовать простейшую хэш-функцию.
 *           На вход функции подается строка, на выходе сумма кодов символов.
 *
 * @note Простейшая реализация, где вычисление хэша каждого текущего
 *       символа зависит от текущего вычесленного хэша
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * @brief Простейшая HASH-функция, основанная на регистровом сдвиге и XOR
 * @param  str    Строка для вычисления HASH
 * @param  length Длина строки
 * @return        HASH длиной 32 бита
 */
unsigned long int GetHash(char * str, unsigned long length) {
    unsigned long int hash = 0xFFFFFFFFFFFFFFFF^(length << 15);
    unsigned int i    = 0;

    for (i = 0; i < length; ++str, ++i) {
        hash = ((hash << 15) ^ (hash >> 27)) ^ (*str);
    }

    return hash;
}

int main (int argc, const char * argv[]) {

    char buff[101] = {'\0'};

    printf("Enter a string to get hash of (100 symbols max): ");
    fgets(buff, sizeof(buff), stdin);

    printf("Hash of your string is: %016lX\n", GetHash(buff, strlen(buff)));
    return 0;
}
