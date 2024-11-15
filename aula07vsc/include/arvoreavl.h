#ifdef _ARVOREAVL_H
    #define _ARVOREAVL_H

    // Estrutura de um nó da árvore AVL
    typedef struct Node
    {
        int id;               // ID do cliente (chave de busca)
        char name[50];        // Nome do cliente
        struct Node *left;
        struct Node *right;
        int height;
    } Node;

    // Função para criar um novo nó
    Node* newNode(int id, char name[]);
    // Função para obter a altura de um nó
    int height(Node *N);
    // Função para obter o valor máximo entre dois inteiros
    int max(int a, int b);
    // Rotação à direita
    Node *rightRotate(Node *y);
    // Rotação à esquerda
    Node *leftRotate(Node *x);
    // Obter o fator de balanceamento do nó
    int getBalance(Node *N);
    // Insere um novo nó
    Node* insert(Node* node, int id, char name[]);
    // Função para exibir a árvore AVL em ordem
    void inOrder(Node *root);
#endif