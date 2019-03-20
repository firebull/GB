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
    int startNode;

    InitQueue(&queue, 100);  // FIXME

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


    fclose(file);
    return 0;
}
