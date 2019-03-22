/**
 * @copyright Nikita Bulaev 2019
 *
 * @file  lesson8.c
 * @brief Тестирование различных алгоритмов сортировок и бинарного поиска
 *
 * @note 1. Реализовать сортировку подсчётом.
 *       2. Реализовать быструю сортировку.
 *       3. *Реализовать сортировку слиянием.
 *       4. **Реализовать алгоритм сортировки со списком.
 *       5. Проанализировать время работы каждого из вида сортировок для 100, 10000, 1000000 элементов. Заполнить таблицу.

 *
 * @note По логике, хотелось бы считать каждую операцию SWAP за три.
 *       Но сравниваем с O(n^2) и O(n*log(n)), поэтому, для относительного сравнивания
 *       алгоритмов между собой, считаю, как и в методичке, SWAP за одну операцию.
 *
 * @note Надо помнить, что компилировать с ключом -lm
 *
 * @note В Wolfram получился график для пузырьковых и шейкерной сортировок:
 *       Show[
 *           Plot[x^2, {x, 0, 10000}, PlotStyle -> {Blue},
 *                PlotLegends -> LineLegend[{Red, Green, Orange, Blue},
 *                                          {"Simple Bubble Sort", "Shaker Sort", "Optimised Bubble Sort","O(x^2)"}]],
 *           ListLinePlot[{{10, 110}, {100, 1200}, {1000, 1250000}, {5000, 31000000}, {10000, 125000000}}, PlotStyle -> {Red}, InterpolationOrder -> 2],
 *           ListLinePlot[{{10, 100}, {100, 9500}, {1000, 1000000}, {5000, 25000000}, {10000, 100000000}}, PlotStyle -> {Orange}, InterpolationOrder -> 2],
 *           ListLinePlot[{{10, 80},  {100, 7600}, {1000, 830000},  {5000, 21000000}, {10000, 84000000}}, PlotStyle -> {Green}, InterpolationOrder -> 2]]
 *
 *       Для Быстрой, слиянием и сортировки подсчётом:
 *
 *       Show[
 *           ListLinePlot[{{10, 46}, {100, 1000}, {1000, 15000}, {5000, 94500}, {10000, 221000}, {500000, 14670000}, {1000000, 30648000}}, PlotStyle -> {Red}, InterpolationOrder -> 2,
 *                   PlotLegends -> LineLegend[{Red, Green, Orange, Blue},
 *                                             {"Quick Sort", "Merge Sort", "Counting Sort", "O(x*log(x))"}]],
 *           ListLinePlot[{{10, 138}, {100, 2400}, {1000, 34000}, {5000, 205000}, {10000, 440000}, {500000, 30500000}, {1000000, 63850000}}, PlotStyle -> {Green}, InterpolationOrder -> 2],
 *           ListLinePlot[{{10, 131090}, {100, 131270}, {1000, 133070}, {5000, 141070}, {10000, 151000}, {500000, 1131000}, {1000000, 2131000}}, PlotStyle -> {Orange}, InterpolationOrder -> 2],
 *           Plot[x*Log[x], {x, 0, 10000}, PlotStyle -> {Blue}]]
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define SWAP(A, B) { unsigned int t = A; A = B; B = t; }

unsigned long recurCounter = 0; /*!< Счётчик для рекурсивных функций */

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
 * @brief Сортировка подсчётом
 *
 * @param  arr    Массив данных
 * @param  length Длина массива
 * @return        Количество совершённых операций
 */
unsigned long SimpleCountingSort(unsigned int * arr, size_t length, unsigned int maxVal) {
    unsigned long counter = maxVal; // calloc делает maxVal операций обнуления

    unsigned int * cArray = (unsigned int*)calloc(maxVal, sizeof(unsigned int));

    if (cArray == NULL) {
        puts("Could not allocate memory!");
        exit(1);
    }

    for (unsigned int i = 0; i < length; i++) {
        cArray[arr[i]]++;
        counter++;
    }

    unsigned int b = 0;

    for (unsigned int j = 0; j < maxVal; j++) {
        counter++;

        if (cArray[j] == 0) {
            continue;
        }

        for (unsigned int i = 0; i < cArray[j]; i++) {
            arr[b++] = j;
            counter++;
        }
    }

    free(cArray);

    return counter;
}

/**
 * @brief Быстрая сортировка
 *
 * @param arr   Массив данных
 * @param first Номер стартового элемента
 * @param last  Номер конечного элемента
 */
void QuickSort(unsigned int * arr, long first, long last) {

    if (first < last) {
        long left   = first,
             right  = last,
             medium = arr[(left + right) / 2];

        do {
            while (arr[left] < medium) {
                left++;
                recurCounter++;
            };

            while (arr[right] > medium) {
                right--;
                recurCounter++;
            };

            if (left <= right) {
                SWAP(arr[left], arr[right]);
                left++;
                right--;
                recurCounter += 3;
            }
        } while (left <= right);

        QuickSort(arr, first, right);
        QuickSort(arr, left, last);
    }
}

/**
 * @brief Слияние массивов для сортировки слиянием
 *
 * @param arr    Сортируемый массив
 * @param left   Левый индекс
 * @param right  Правый индекс
 * @param medium Среднее значение
 */
void Merge(unsigned int * arr, int left, int right, long medium) {
    int j = left;
    int k = medium + 1;
    long count = right - left + 1;

    if (count <= 1) { return; }

    unsigned int * tmpArr = (unsigned int*)calloc(count, sizeof(unsigned int));

    if (tmpArr == NULL) {
        puts("Could not allocate memory!");
        exit(1);
    }

    recurCounter += count; // calloc делает count операций обнуления

    for (long i = 0; i < count; ++i) {
        if (j <= medium && k <= right) {
            if (arr[j] < arr[k]) {
                tmpArr[i] = arr[j++];
            } else {
                tmpArr[i] = arr[k++];
            }
        } else {
            if (j <= medium) {
                tmpArr[i] = arr[j++];
            } else {
                tmpArr[i] = arr[k++];
            }
        }

        recurCounter++;
    }

    j = 0;

    for (long i = left; i <= right; ++i) {
        arr[i] = tmpArr[j++];
        recurCounter++;
    }

    free(tmpArr);
}

/**
 * @brief Сортировка слиянием
 *
 * @param arr   Массив данных
 * @param first Номер стартового элемента
 * @param last  Номер конечного элемента
 */
void MergeSort(unsigned int * arr, int left, int right) {
    long middle;

    if (left >= right) { return; }

    middle = left + (right - left) / 2;

    // Рекурсивная сортировка полученных массивов
    MergeSort(arr, left, middle);
    MergeSort(arr, middle + 1, right);
    Merge(arr, left, right, middle);

    recurCounter += 4;
}


int main (int argc, const char * argv[]) {

    short        error       = 0;  /*!< Возвращаемая системная ошибка */
    unsigned int arrayLength = 0;  /*!< Длина массива */
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

    if (basicArray == NULL || sortingArray == NULL) {
        puts("Could not allocate memory!");
        exit(1);
    }

    // Заполнить базовый массив случайными числами
    srand(time(NULL));

    // Для экономии памяти в сортировке подсчётом ограничу
    // числа от 0 до 65535
    for (unsigned i = 0; i < arrayLength; i++) {
        *(basicArray + i) = rand() % 0xFFFF;
    }

    /* Проверка обычной Пузырьковой сортировки */
    // Перед началом инициализирую рабочий массив из базового
    //memcpy(sortingArray, basicArray, arraySize);

    //printf("Simple bubble sort of %u-length array: %lu operations\n", arrayLength, SimpleBubbleSort(sortingArray, (size_t)arrayLength));

    /* Проверка оптимизированной пузырьковой сортировки */
    //memcpy(sortingArray, basicArray, arraySize);

    //printf("Optimized bubble sort of %u-length array: %lu operations\n", arrayLength, OptBubbleSort(sortingArray, (size_t)arrayLength));

    /* Проверка шейкерной сортировки */
   // memcpy(sortingArray, basicArray, arraySize);

    //printf("Shake sort of %u-length array: %lu operations\n", arrayLength, ShakeSort(sortingArray, (size_t)arrayLength));

    /* Проверка сортировки подсчётом */
    memcpy(sortingArray, basicArray, arraySize);

    printf("Counting sort of %u-length array: %lu operations\n", arrayLength, SimpleCountingSort(sortingArray, (size_t)arrayLength, 0xFFFF));

    /* Проверка быстрой сортировки */
    memcpy(sortingArray, basicArray, arraySize);

    QuickSort(sortingArray, 0, arrayLength - 1);

    printf("Quick sort of %u-length array: %lu operations\n", arrayLength, recurCounter);

    /* Проверка сортировки слиянием */
    memcpy(sortingArray, basicArray, arraySize);

    recurCounter = 0;

    MergeSort(sortingArray, 0, arrayLength - 1);

    printf("Merge sort of %u-length array: %lu operations\n", arrayLength, recurCounter);

    // Дебаг результата
    /*for (int i = 0; i < arrayLength; ++i) {
        printf("%u\n", sortingArray[i]);
    }*/

    free(basicArray);
    free(sortingArray);

    return error;

}
