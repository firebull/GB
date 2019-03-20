/**
 * @copyright Nikita Bulaev 2019
 *
 * @file  binary_tree.c
 * @brief 2. Переписать программу, реализующее двоичное дерево поиска.
 *
 * @note  а) Добавить в него обход дерева различными способами;
 *        б) Реализовать поиск в двоичном дереве поиска;
 *        в) *Добавить в программу обработку командной строки, с помощью
 *           которой можно указывать из какого файла считывать данные,
 *           каким образом обходить дерево.
 *
 * @note Для проверки  можно использовать параметры строки: -f bintree.txt -3 -s 65
 *
 */

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <unistd.h>

typedef int T;

typedef struct Node {
    T data;
    struct Node * left;
    struct Node * right;
    struct Node * parent;
} Node;

/** Список способов вывода дерева */
typedef enum {
    BIN_TREE_PRINT_UNKNOWN = 0,
    BIN_TREE_PRINT_PREORDER,
    BIN_TREE_PRINT_LROOTR,
    BIN_TREE_PRINT_LRROOT
} BinPrintWay_t;


/**
 * @brief Вывод двоичного дерева в виде скобочной записи
 * @param root Указатель на корень дерева
 */
void PrintTree(Node *root) {
    if (root) {
        printf("%d", root->data);

        if (root->left || root->right) {
            printf("(");

            if (root->left) {
                PrintTree(root->left);
            } else {
                printf("NULL");
            }

            printf(",");

            if (root->right) {
                PrintTree(root->right);
            } else {
                printf("NULL");
            }

            printf(")");
        }
    }
}

/**
 * @brief Создание нового узла
 *
 * @param  value  Значение узла
 * @param  parent Указатель на родительский кзел
 * @return        Указатель на созданный узел
 */
Node * CreateFreeNode(T value, Node *parent) {
    Node* tmp = (Node*) malloc(sizeof(Node));
    tmp->left = tmp->right = NULL;
    tmp->data = value;
    tmp->parent = parent;
    return tmp;
}

/**
 * @brief Вставка узла
 * @param head  Указатель на указатель корня дерева
 * @param value Значение, которое необходимо вставить
 */
void InsertNode(Node ** head, int value) {
    Node *tmp = NULL;

    if (*head == NULL) {
        *head = CreateFreeNode(value, NULL);
        return;
    }

    tmp = *head;

    while (tmp) {
        if (value > tmp->data) {
            if (tmp->right) {
                tmp = tmp->right;
                continue;
            } else {
                tmp->right = CreateFreeNode(value, tmp);
                return;
            }
        } else if (value < tmp->data) {
            if (tmp->left) {
                tmp = tmp->left;
                continue;
            } else {
                tmp->left = CreateFreeNode(value, tmp);
                return;
            }
        } else {
            exit(2);                     // Дерево построено неправильно
        }
    }
}

/**
 * @brief Вывод дерева от корня, потом Лево - Право
 *
 * @param root Указатель на корень дерева
 */
void PreOrderTravers(Node * root) {
    if (root) {
        printf("%d ", root->data);
        PreOrderTravers(root->left);
        PreOrderTravers(root->right);
    }
}

/**
 * @brief Вывод дерева в виде Лево - Корень - Право
 *
 * @param root Указатель на корень дерева
 */
void LeftRootRight(Node * root) {
    if (root) {
        LeftRootRight(root->left);
        printf("%d ", root->data);
        LeftRootRight(root->right);
    }
}

/**
 * @brief Вывод дерева в виде Лево - Право - Корень
 *
 * @param root Указатель на корень дерева
 */
void LeftRightRoot(Node * root) {
    if (root) {
        LeftRootRight(root->left);
        LeftRootRight(root->right);
        printf("%d ", root->data);
    }
}

/**
 * @brief Поиск по бинарному дереву
 *
 * @note  Поиск рекурсивный, хотя код может быть
 *        довольно простым и обычным проходом
 *
 * @param  root  Указатель на корень дерева
 * @param  value Искомое значение
 * @return       1 в случае успеха
 */
int SearchTree(Node * root, int value){

    if (root->data == value){
        printf("%d ", root->data);
        return 1;
    } else if (root->data > value && root->left != NULL){
        if (SearchTree(root->left, value) == 1){
            printf(" <- %d ", root->data);
            return 1;
        }
    } else if (root->data < value && root->right != NULL) {
        if (SearchTree(root->right, value) == 1){
            printf(" <- %d ", root->data);
            return 1;
        }
    }

    return 0;
}


int main(int argc, char * argv[]) {
    Node * Tree = NULL;
    BinPrintWay_t printWay = BIN_TREE_PRINT_UNKNOWN;
    int searchNum = -1;

    if (argc == 1) {
        puts("No file(s) specified in command line");
        puts("Print \"binary_tree.run -h\" for help");
        return 1;
    }

    FILE * file;

    int opt;

    /* Обработка параметров командной строки */
    while ((opt = getopt(argc, argv, "f:s:h123")) != -1) {
        switch (opt) {
            case 'h':
                puts("USAGE: binary_tree.run [options] -f <filename>\n");
                puts("-f <filename>\t\tFilename to parse");
                puts("-s\t\t\t<search_number>");
                puts("-1\t\t\tPrint in PreOrder style");
                puts("-2\t\t\tPrint in Left-Root-Right style");
                puts("-3\t\t\tPrint in Left-Right-Root style");

                exit(0);
                break;

            case 'f':
                file = fopen(optarg, "r");
                break;

            case 's':
                // @todo Сделать предварительную проверку, что это число
                searchNum = atoi(optarg);
                break;

            case '1':
                printWay = BIN_TREE_PRINT_PREORDER;
                break;

            case '2':
                printWay = BIN_TREE_PRINT_LROOTR;
                break;

            case '3':
                printWay = BIN_TREE_PRINT_LRROOT;
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


    int count; /*!< Количество записей */

    // Считываем количество записей
    fscanf(file, "%d", &count);

    if (count <= 0) {
        puts("Incorrect input data!");
        exit(1);
    }

    for (int i = 0; i < count; i++) {
        int value;
        fscanf(file, "%d", &value);
        InsertNode(&Tree, value);
    }

    fclose(file);
    PrintTree(Tree);

    switch (printWay) {
        case BIN_TREE_PRINT_PREORDER:
            printf("\nPreOrder:");
            PreOrderTravers(Tree);
            break;

        case BIN_TREE_PRINT_LROOTR:
            printf("\nLeftRootRight:");
            LeftRootRight(Tree);
            break;

        case BIN_TREE_PRINT_LRROOT:
            printf("\nLeftRightRoot:");
            LeftRightRoot(Tree);
            break;

        case BIN_TREE_PRINT_UNKNOWN:
        default:
            puts("\nIncorrect print style option");
            break;
    }

    puts("\n");

    printf("Searching number %d in parsed tree:\n", searchNum);

    if (SearchTree(Tree, searchNum)){
        puts("\nSuccess!");
    } else {
        puts("Nothing found...");
    }

    puts("\n");

    return 0;
}

