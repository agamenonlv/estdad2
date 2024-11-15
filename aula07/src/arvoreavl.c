/*
 * arvoreavl.c
 *
 *  Created on: 14 de nov. de 2024
 *      Author: agamenon
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/arvoreavl.h"

// Função para criar um novo nó
Node* newNode(int id, char name[]) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->id = id;
    strcpy(node->name, name);
    node->left = NULL;
    node->right = NULL;
    node->height = 1;  // novo nó é inicialmente uma folha
    return node;
}

// Função para obter a altura de um nó
int height(Node *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

// Função para obter o valor máximo entre dois inteiros
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Rotação à direita
Node *rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Rotação à esquerda
Node *leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Obter o fator de balanceamento do nó
int getBalance(Node *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

Node* insert(Node* node, int id, char name[]) {
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
void inOrder(Node *root) {
    if(root != NULL) {
        inOrder(root->left);
        printf("ID: %d, Nome: %s, Altura: %d\n", root->id, root->name, root->height);
        inOrder(root->right);
    }
}

// Função para pesquisar um ID específico na árvore
 Node* search(Node* node, int id)
{
   if (node == NULL)
      return node;

   if (id == node->id)
      return node;
   else if (id < node->id)
      return search(node->left, id);
   else
      return search(node->right, id);
}

 // Função para encontrar o menor nó (usado na remoção)
 Node* minNode(Node* node) {
     struct Node* current = node;
     while (current && current->left != NULL) {
         current = current->left;
     }
     return current;
 }

 // Função para remover um cliente pelo ID
 Node* removeUser(Node* node, int id)
 {
     if (node == NULL)
         return node; // Se o nó é NULL, retorna NULL (não há nada a remover)

     // 1. Encontre o nó a ser removido
     if (id < node->id) // Se o id a ser removido for menor, vai para a esquerda
         node->left = removeUser(node->left, id);
     else if (id > node->id) // Se o id for maior, vai para a direita
         node->right = removeUser(node->right, id);
     else // Se o id for encontrado, esse é o nó a ser removido
     {
         // Caso 1: nó com um único filho ou nenhum filho
         if (node->left == NULL)
         {
             Node* temp = node->right;
             free(node);
             return temp;
         }
         else if (node->right == NULL)
         {
             Node* temp = node->left;
             free(node);
             return temp;
         }

         // Caso 2: nó com dois filhos
         // Encontre o menor nó da subárvore direita (sucessor em ordem)
         Node* temp = minNode(node->right);

         // Copia o valor do sucessor para este nó
         node->id = temp->id;
         strcpy(node->name, temp->name);

         // Remove o sucessor
         node->right = removeUser(node->right, temp->id);
     }

     // Se a árvore tiver apenas um nó, retorna NULL
     if (node == NULL)
         return node;

     // 2. Atualize a altura do nó
     node->height = 1 + max(height(node->left), height(node->right));

     // 3. Verifique o fator de balanceamento e balanceie a árvore
     int balance = getBalance(node);

     // Caso 1: Rotação à esquerda
     if (balance > 1 && getBalance(node->left) >= 0)
         return rightRotate(node);

     // Caso 2: Rotação à direita
     if (balance < -1 && getBalance(node->right) <= 0)
         return leftRotate(node);

     // Caso 3: Rotação dupla à esquerda
     if (balance > 1 && getBalance(node->left) < 0)
     {
         node->left = leftRotate(node->left);
         return rightRotate(node);
     }

     // Caso 4: Rotação dupla à direita
     if (balance < -1 && getBalance(node->right) > 0)
     {
         node->right = rightRotate(node->right);
         return leftRotate(node);
     }

     return node; // Retorna o nó (possivelmente balanceado)
}
