/**
 * @copyright Nikita Bulaev 2019
 *
 * @file  dijkstra_graph.c
 * @brief Реализация алгоритма Дейкстры для поиска кратчайших пути
 *        от одной из вершин графа до всех остальных
 *
 * @note https://ru.wikipedia.org/wiki/%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC_%D0%94%D0%B5%D0%B9%D0%BA%D1%81%D1%82%D1%80%D1%8B
 *
 * @note Узлы задаются от 1, а хранятся от 0
 *
 * @note Команда для линковки и запуска на Линукс из build: cmake ../ && make && ./dijkstra_graph.exe -f ../matrix.txt -s 5 -e 4
 *
 */

#include "queue.h"
#include "dijkstra_graph.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main (int argc, char * argv[]) {

    Queue_t queue;  /*!< Очередь для хранения списка узлов */

    int startNode = -1;  /*!< Начальный узел, откуда ищем маршрут */
    int endNode   = -1;  /*!< Конечный узел, куда ищем маршрут */

    if (argc == 1) {
        puts("No file(s) specified in command line");
        puts("Print \"dijkstra_graph.exe -h\" for help");
        return 1;
    }

    FILE * file;  /*!< Файл с матрицей смежности */

    int opt;

    /* Обработка параметров командной строки */
    while ((opt = getopt(argc, argv, "f:s:e:h")) != -1) {
        switch (opt) {
            case 'h':
                puts("USAGE: dijkstra_graph.exe [options] -f <filename> -s <start> -e <end>\n");
                puts("-f <filename>\tFilename to parse");
                puts("-s\t\t<start_node>");
                puts("-e\t\t<end_node>");
                puts("-h\t\tThis help");

                exit(0);
                break;

            case 'f':
                file = fopen(optarg, "r");
                break;

            case 's':
                // @todo Сделать предварительную проверку, что это число
                startNode = atoi(optarg);
                break;

            case 'e':
                // @todo Сделать предварительную проверку, что это число
                endNode = atoi(optarg);
                break;

            default:
                exit(1);
                break;
        }
    }

    if (file == NULL) {
        puts("Can't open file!");
        exit(1);
    }

    int count, maxWeight; /*!< Количество записей */

    // Считываем количество записей и максимальный вес из первой строки
    if (fscanf(file, "%d %d", &count, &maxWeight) <= 0 ) {
        puts("Incorrect file format");
        exit(1);
    }

    if (count <= 0 || maxWeight <= 0) {
        puts("Incorrect node count or maxWeight value(s)");
        exit(1);
    }

    // Стартовый и конечный узлы не больше count и > 0
    if (startNode <= 0 || startNode > count || endNode <= 0 || endNode > count) {
        puts("Incorrect vales of startNode or endNode.\nCannot be less then zero and more then nodes count");
        exit(1);
    }

    int matrix[count][count]; /*!< Матрица смежности */
    int weight = 0;           /*!< Вес ребра */

    // Парсинг матрицы смежности из файла
    for (int i = 0; i < count; ++i) {
        for (int j = 0; j < count; ++j) {
            if (fscanf(file, "%d", &weight) <= 0 ) {
                puts("Incorrect file format");
                exit(1);
            }

            if (weight < 0) {
                puts("Can't use weght less then zero");
                exit(1);
            }

            matrix[i][j] = weight;
        }
    }

    fclose(file);

    /* Вывод импортированной матрицы в консоль для проверки на http://graphonline.ru/ */
    puts("\nImported matrix to check at http://graphonline.ru/ is:");

    for (int i = 0; i < count; ++i) {
        for (int j = 0; j < count; ++j) {
            if (matrix[i][j] == maxWeight) {
                printf("0,");
            } else {
                printf("%d,", matrix[i][j]);
            }
        }

        printf("\n");
    }

    /**************************************************************************/
    /* Сначала считаем минимальные длины маршрутов до всех узлов от конечного */

    int pathLen[count]; /*!< Минимальные длины путей до узлов */

    // Инициализировать массив длин максимальными значениями аля +∞
    for (int i = 0; i < count; ++i) {
        pathLen[i] = maxWeight;
    }

    InitQueue(&queue, count * count); // Размер очереди на размер матрицы

    // Добавляем конечный узел в очередь
    if (AddNode(&queue, --endNode) != NO_ERROR) {
        puts("Could not allocate memory!");
        exit(1);
    }

    pathLen[endNode] = 0;

    int workNode = endNode;         /*!< Рабочий узел */
    unsigned int currentLength = 0; /*!< Текущая длина маршрута до узла */

    while (queue.size > 0) {
        if (PopFrontNode(&queue, &workNode) != NO_ERROR) {
            puts("Somehow queue is empty =(");
            exit(1);
        }

        for (int i = 0; i < count; ++i) {
            if (matrix[workNode][i] < maxWeight) {
                currentLength = pathLen[workNode] + matrix[workNode][i];

                // Если маршрут короче, чем текущий, кидаем узел в очередь
                // и обновляем длину в массиве
                if (pathLen[i] >= currentLength) {
                    if (AddNode(&queue, i) != NO_ERROR) {
                        puts("Could not allocate memory!");
                        exit(1);
                    }

                    pathLen[i] = currentLength;
                }
            }
        }
    }

    ClearQueue(&queue);  // Хорошим тоном будет очистить очередь на всякий случай

    /*******************************************************/
    /* Теперь ищем маршрут от начального узла до конечного */

    // Добавить начальный узел в очередь
    if (AddNode(&queue, startNode) != NO_ERROR) {
        puts("Could not allocate memory!");
        exit(1);
    }

    // Выставить рабочий узел на стартовый
    workNode = --startNode;

    int leftPath = pathLen[workNode]; /*!< Оставшееся длина маршрута до конечного узла */
    unsigned int pathNodesCount = 1;  /*!< Количество узлов в маршруте */

    while (leftPath > 0) {
        for (int i = 0; i < count; ++i) {
            if (matrix[workNode][i] == maxWeight) {
                continue;
            }

            if (leftPath - matrix[workNode][i] == pathLen[i]) {
                workNode = i;
                leftPath = pathLen[workNode];
                pathNodesCount++;

                if (AddNode(&queue, i + 1) != NO_ERROR) {
                    puts("Could not allocate memory!");
                    exit(1);
                }

                break;
            }
        }
    }

    printf("\nShortest path from node %d to node %d of %u nodes:\n", startNode + 1, endNode + 1, pathNodesCount);

    PrintQueue(&queue);
    ClearQueue(&queue);

    return 0;
}
