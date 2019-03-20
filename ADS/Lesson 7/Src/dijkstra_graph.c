/**
 * @copyright Nikita Bulaev 2019
 *
 * @file  dijkstra_graph.c
 * @brief Реализация алгоритма Дейкстры для поиска кратчайших пути
 *        от одной из вершин графа до всех остальных
 *
 * @note https://ru.wikipedia.org/wiki/%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC_%D0%94%D0%B5%D0%B9%D0%BA%D1%81%D1%82%D1%80%D1%8B
 *
 */

#include "queue.h"
#include "dijkstra_graph.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main (int argc, char * argv[]) {

    Queue_t queue;
    int startNode = -1;

    if (argc == 1) {
        puts("No file(s) specified in command line");
        puts("Print \"dijkstra_graph.run -h\" for help");
        return 1;
    }

    FILE * file;

    int opt;

    /* Обработка параметров командной строки */
    while ((opt = getopt(argc, argv, "f:n:h")) != -1) {
        switch (opt) {
            case 'h':
                puts("USAGE: dijkstra_graph.run [options] -f <filename>\n");
                puts("-f <filename>\tFilename to parse");
                puts("-s\t\t<start_node>");
                puts("-h\t\tThis help");

                exit(0);
                break;

            case 'f':
                file = fopen(optarg, "r");
                break;

            case 'n':
                // @todo Сделать предварительную проверку, что это число
                startNode = atoi(optarg);
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

    // Считываем количество записей
    if (fscanf(file, "%d %d", &count, &maxWeight) <= 0 ) {
        puts("Incorrect file format");
        exit(1);
    }

    if (count <= 0 || maxWeight <= 0) {
        puts("Incorrect input data");
        exit(1);
    }

    //@fixme: Добавить проверку, чтобы в командной строке был
    //        задан стартовый узел не больше count и > 0

    int matrix[count][count];
    int weight = 0;

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

    for (int i = 0; i < count; ++i) {
        for (int j = 0; j < count; ++j) {
            if (matrix[i][j] == maxWeight) {
                printf("  -\t");
            } else {
                printf("  %d\t", matrix[i][j]);
            }
        }

        puts("\n");
    }

    int pathLen[count];

    for (int i = 0; i < count; ++i) {
        pathLen[i] = maxWeight;
    }

    InitQueue(&queue, count * count); // Размер очереди на размер матрицы

    AddNode(&queue, --startNode);

    pathLen[startNode] = 0;
    int workNode = startNode;
    unsigned int currentLength = 0;

    while (queue.size > 0) {
        if (PopFrontNode(&queue, &workNode) != NO_ERROR) {
            exit(1);
        }

        for (int i = 0; i < count; ++i) {
            if (matrix[workNode][i] < maxWeight) {
                currentLength = pathLen[workNode] + matrix[workNode][i];

                if (pathLen[i] >= currentLength) {

                    AddNode(&queue, i);
                    pathLen[i] = currentLength;
                    printf("node => %02d, it min length => %d\n", i + 1, pathLen[i]);
                }
            }
        }
    }

    ClearQueue(&queue);

    return 0;
}
