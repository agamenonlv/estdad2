#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arvoreavl.h"

// Função para criar um novo nó
Node* newNode(int id, char name[]) {
    Node* node = (struct Node*)malloc(sizeof(Node));
    node->id = id;
    strcpy(node->name, name);
    node->left = NULL;
    node->right = NULL;
    node->height = 1;  // novo nó é inicialmente uma folha
    return node;
}

// Função para obter a altura de um nó
int height(struct Node *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

// Função para obter o valor máximo entre dois inteiros
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Rotação à direita
struct Node *rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Rotação à esquerda
struct Node *leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Obter o fator de balanceamento do nó
int getBalance(struct Node *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

struct Node* insert(struct Node* node, int id, char name[]) {
    if (node == NULL)
        return newNode(id, name);

    // Comparação com o ID do nó para decidir a posição na árvore
    if (id < node->id)
        node->left = insert(node->left, id, name);
    else if (id > node->id)
        node->right = insert(node->right, id, name);
    else  // IDs duplicados não são permitidos na árvore AVL
        return node;

    // Atualizar altura do nó ancestral
    node->height = 1 + max(height(node->left), height(node->right));

    // Obter fator de balanceamento
    int balance = getBalance(node);

    // Casos de rotação para balanceamento
    // Caso Esquerda-Esquerda
    if (balance > 1 && id < node->left->id)
        return rightRotate(node);

    // Caso Direita-Direita
    if (balance < -1 && id > node->right->id)
        return leftRotate(node);

    // Caso Esquerda-Direita
    if (balance > 1 && id > node->left->id) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Caso Direita-Esquerda
    if (balance < -1 && id < node->right->id) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Função para exibir a árvore AVL em ordem
void inOrder(struct Node *root) {
    if(root != NULL) {
        inOrder(root->left);
        printf("ID: %d, Nome: %s\n", root->id, root->name);
        inOrder(root->right);
    }
}
