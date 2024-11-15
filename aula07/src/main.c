/*
 * main.c
 *
 *  Created on: 14 de nov. de 2024
 *      Author: agamenon
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/arvoreavl.h"

int main() {

    Node *root = NULL;

    // Inserção de nós como exemplo
    root = insert(root, 10, "Alice");
    root = insert(root, 70, "Grace");
    root = insert(root, 20, "Bob");
    root = insert(root, 50, "Eve");
    root = insert(root, 30, "Charlie");
    root = insert(root, 40, "Diana");
    root = insert(root, 60, "Frank");


    printf("Árvore AVL em ordem:\n");
    inOrder(root);

    int id = 100;
    struct Node *aux = search(root, id);
    printf("\nPesquisando o cliente %d\n", id);
    if (aux != NULL)
       printf("ID: %d, Nome: %s\n", aux->id, aux->name);
    else
       printf("Cliente com ID: %d não encontrado\n", id);

    root = removeUser(root, id);
    printf("\nRemovendo o cliente %d\n", id);

    printf("\nÁrvore AVL em ordem:\n");
    inOrder(root);

    return 0;
}
