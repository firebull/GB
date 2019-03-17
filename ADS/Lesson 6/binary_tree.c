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
 *
 */

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef int T;

typedef struct Node {
    T data;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
} Node;

// Распечатка двоичного дерева в виде скобочной записи
void printTree(Node *root) {
    if (root) {
        printf("%d", root->data);

        if (root->left || root->right) {
            printf("(");

            if (root->left) {
                printTree(root->left);
            } else {
                printf("NULL");
            }

            printf(",");

            if (root->right) {
                printTree(root->right);
            } else {
                printf("NULL");
            }

            printf(")");
        }
    }
}

// Создание нового узла
Node* getFreeNode(T value, Node *parent) {
    Node* tmp = (Node*) malloc(sizeof(Node));
    tmp->left = tmp->right = NULL;
    tmp->data = value;
    tmp->parent = parent;
    return tmp;
}

// Вставка узла
void insert(Node **head, int value) {
    Node *tmp = NULL;

    if (*head == NULL) {
        *head = getFreeNode(value, NULL);
        return;
    }

    tmp = *head;

    while (tmp) {
        if (value > tmp->data) {
            if (tmp->right) {
                tmp = tmp->right;
                continue;
            } else {
                tmp->right = getFreeNode(value, tmp);
                return;
            }
        } else if (value < tmp->data) {
            if (tmp->left) {
                tmp = tmp->left;
                continue;
            } else {
                tmp->left = getFreeNode(value, tmp);
                return;
            }
        } else {
            exit(2);                     // Дерево построено неправильно
        }
    }
}

void preOrderTravers(Node* root) {
    if (root) {
        printf("%d ", root->data);
        preOrderTravers(root->left);
        preOrderTravers(root->right);
    }
}


int main(int argc, const char * argv[]) {
    Node *Tree = NULL;

    if (argc == 1) {
        puts("No file(s) specified in command line");
        return 1;
    }

    FILE* file = fopen("data.txt", "r");

    for (int i = 1; i < argc; ++i) {

    }

    if (file == NULL) {
        puts("Can't open file!");
        exit(1);
    }

    int count;
    fscanf(file, "%d", &count);          // Считываем количество записей
    int i;

    for (i = 0; i < count; i++) {
        int value;
        fscanf(file, "%d", &value);
        insert(&Tree, value);
    }

    fclose(file);
    printTree(Tree);
    printf("\nPreOrderTravers:");
    preOrderTravers(Tree);
    return 0;
}

