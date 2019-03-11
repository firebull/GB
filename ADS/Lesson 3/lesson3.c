/**
 * @copyright Nikita Bulaev 2019
 *
 * @file  lesson3.c
 * @brief Тестирование различных алгоритмов сортировок и бинарного поиска
 *
 * @note 1. Попробовать оптимизировать пузырьковую сортировку.
 *          Сравнить количество операций сравнения оптимизированной
 *          и не оптимизированной программы. Написать функции сортировки,
 *          которые возвращают количество операций.
 *       2. *Реализовать шейкерную сортировку.
 *       3. Реализовать бинарный алгоритм поиска в виде функции, которой
 *          передается отсортированный массив. Функция возвращает индекс
 *          найденного элемента или -1, если элемент не найден.
 *       4. *Подсчитать количество операций для каждой из сортировок и
 *          сравнить его с асимптотической сложностью алгоритма
 *
 * @note По логике, хотелось бы считать каждую операцию SWAP за три.
 *       Но сравниваем с O(n^2), поэтому, для относительного сравнивания
 *       алгоритмов между собой, считаю, как и в методичке, SWAP за одну операцию.
 *
 * @note Надо помнить, что компилировать с ключом -lm
 *
 * @note В Wolfram получился график:
 *       Show[
 *           Plot[x^2, {x, 0, 10000}, PlotStyle -> {Blue},
 *                PlotLegends -> LineLegend[{Red, Green, Orange, Blue},
 *                                          {"Simple Bubble Sort", "Shaker Sort", "Optimised Bubble Sort","O(x^2)"}]],
 *           ListLinePlot[{{10, 110}, {100, 1200}, {1000, 1250000}, {5000, 31000000}, {10000, 125000000}}, PlotStyle -> {Red}, InterpolationOrder -> 2],
 *           ListLinePlot[{{10, 100}, {100, 9500}, {1000, 1000000}, {5000, 25000000}, {10000, 100000000}}, PlotStyle -> {Orange}, InterpolationOrder -> 2],
 *           ListLinePlot[{{10, 80},  {100, 7600}, {1000, 830000},  {5000, 21000000}, {10000, 84000000}}, PlotStyle -> {Green}, InterpolationOrder -> 2]]
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define SWAP(A, B) { unsigned int t = A; A = B; B = t; }

#define NOT_FOUND -1

/**
 * @brief Простая пузырьковая сортировка
 *
 * @param  arr    Массив данных
 * @param  length Длина массива
 * @return        Количество совершённых операций
 */
unsigned long SimpleBubbleSort(unsigned int * arr, size_t length) {
    unsigned long counter = 0;

    long i, j;

    for (i = 0; i < length; i++) {
        for (j = 0; j < length - 1; j++) {
            counter++;

            if (arr[j] > arr[j + 1]) {
                counter ++;
                SWAP(arr[j], arr[j + 1]);
            }
        }
    }

    return counter;
}


/**
 * @brief Оптимизированная пузырьковая сортировка
 *
 * @param  arr    Массив данных
 * @param  length Длина массива
 * @return        Количество совершённых операций
 */
unsigned long OptBubbleSort(unsigned int * arr, size_t length) {
    unsigned long counter = 0;

    long j, n;

    for (long i = length - 1; i >= 0; i--) {
        n = 0;

        for (j = 0; j < i; j++) {
            counter++;;

            if (arr[j] > arr[j + 1]) {
                counter += 2;  // Плюс одна операция присваивания
                SWAP(arr[j], arr[j + 1]);
                n = j;
            }
        }

        counter += 3; // Проверка условия и 2 операции присваивания

        // Выход, если проход пустой
        if (n == 0) {
            break;
        }

        j = n;
    }

    return counter;
}


/**
 * @brief Шейкерная сортировка
 *
 * @param  arr    Массив данных
 * @param  length Длина массива
 * @return        Количество совершённых операций
 */
unsigned long ShakeSort(unsigned int * arr, size_t length) {
    unsigned long counter = 0;
    long j, n;

    for (long leftInd = 0, rightInd = length - 1; leftInd < rightInd;) {
        n = 0;

        // Проход вправо
        for (j = leftInd; j < rightInd; j++) {
            counter++;

            if (arr[j + 1] < arr[j]) {
                counter += 2;
                SWAP(arr[j], arr[j + 1]);
                n = j;
            }
        }

        if (n > 0) {
            rightInd = n;
        }

        // Проход влево
        for (j = rightInd; j > leftInd; j--) {
            counter++;

            if (arr[j - 1] >  arr[j]) {
                counter += 2;
                SWAP(arr[j - 1], arr[j]);
                n = j;
            }
        }

        // Необязательно делать лишнюю проверку на левый индекс
        // В худшем случае будет лишний полный проход вправо в
        // следующем цикле, зато сэкономим кучу проверок на
        // предыдущих проходах. Особенно заметно будет на больших массивах.
        leftInd = n;

        // Выход, если проходы уже пустые
        if (n == 0) {
            break;
        }

        counter += 4;
    }

    return counter;
}

/**
 * @brief Двоичный поиск в отсортированном массиве
 *
 * @note  Как вариант, его ещё называют "Поиск методом половинного деления"
 *
 * @param  arr    Массив отсортированных данных по возрастанию
 * @param  length Длина массива
 * @param  x      Искомое значение
 * @return        Позицию найденного значения в массиве
 * @return -1     Если ничего не найдено
 */
long BinarySearch(unsigned int * arr, size_t length, unsigned int x) {
    /* Начальная проверка:
        - Нулевая длина массива
        - искомый элемент меньше всех в массиве
        - искомый элемент больше всех в массиве
    */
    if (length == 0 || arr[0] > x || arr[length - 1] < x) {
        /* искомый элемент меньше всех в массиве */
        return NOT_FOUND;
    }

    unsigned int first = 0;       /*!< Первый элемент в искомом интервале */
    unsigned int last  = length;  /*!< Последний элемент в искомом интервале */

    unsigned int mid = first + (last - first) / 2; /*!< Средняя точка */

    while (first < last && arr[mid] != x) {
        if (x <= arr[mid]) {
            last = mid;
        } else {
            first = mid + 1;
        }

        mid = first + (last - first) / 2;
    }

    if (arr[mid] == x) {
        return mid;
    } else {
        return NOT_FOUND;
    }
}

int main (int argc, const char * argv[]) {

    short        error       = 0;  /*!< Возвращаемая системная ошибка */
    unsigned int arrayLength = 0;  /*!< Длина массива */
    unsigned int search      = 0;  /*!< Искомое значение */
    size_t       arraySize   = 0;  /*!< Размер массива, байт */

    unsigned int * basicArray;    /*!< Базовый массив, из него копируются данные для каждого алгоритма */
    unsigned int * sortingArray;  /*!< Сортируемый массив */

    printf("Enter a number of array elements: ");

    // Проверяю входное значение. Если это не целое число,
    // вываливаюсь с системной ошибкой.
    if (scanf("%u", &arrayLength) == 0 || arrayLength == 0) {
        printf("Invalid value, exitting.\n\n");
        return 1;  // Выходим с системной ошибкой
    }

    // Сначала выделить память под массивы
    arraySize    = sizeof(unsigned int) * arrayLength;
    basicArray   = malloc(arraySize);
    sortingArray = malloc(arraySize);

    // Заполнить базовый массив случайными числами
    srand(time(NULL));

    for (unsigned i = 0; i < arrayLength; i++) {
        *(basicArray + i) = rand();
    }

    /* Проверка обычной Пузырьковой сортировки */
    // Перед началом инициализирую рабочий массив из базового
    memcpy(sortingArray, basicArray, arraySize);

    printf("Simple bubble sort of %u-length array: %lu operations\n", arrayLength, SimpleBubbleSort(sortingArray, (size_t)arrayLength));

    /* Проверка оптимизированной пузырьковой сортировки */
    memcpy(sortingArray, basicArray, arraySize);

    printf("Optimized bubble sort of %u-length array: %lu operations\n", arrayLength, OptBubbleSort(sortingArray, (size_t)arrayLength));

    /* Проверка шейкерной сортировки */
    memcpy(sortingArray, basicArray, arraySize);

    printf("Shake sort of %u-length array: %lu operations\n", arrayLength, ShakeSort(sortingArray, (size_t)arrayLength));

    /* Проверка бинарного поиска */
    printf("\n\nNow you can search something like: %u, %u, %u: ",
           sortingArray[rand() % arrayLength],
           sortingArray[rand() % arrayLength],
           sortingArray[rand() % arrayLength]);

    if (scanf("%u", &search) == 0) {
        printf("Invalid value, exitting.\n\n");
        error = 1;  // Выходим с системной ошибкой
    } else {
        long position = BinarySearch(sortingArray, (size_t)arrayLength, search);

        if ( position >= 0) {
            printf("Found at %ld\n", position);
        } else {
            printf("Not found\n");
        }

    }

    free(basicArray);
    free(sortingArray);

    return error;

}
