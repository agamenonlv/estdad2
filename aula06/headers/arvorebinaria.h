#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó da árvore
typedef struct Node {
    int Id;
    int idade;
    struct Node* esquerda;  // left
    struct Node* direita;   // right
} Node;

// Função para criar um novo nó
Node* createNode(int Id, int idade);

// Função para inserir um nó na árvore usando o Id como critério
Node* insertNode(Node* root, int Id, int idade);
// Função para buscar um usuário pelo ID
Node* buscarID(Node* root, int Id);
// Função para encontrar o menor nó (usado na remoção)
Node* minNode(Node* node);
// Função para remover um usuário pelo ID
Node* deleteUser(Node* root, int Id);
// Função para exibir a árvore em ordem crescente de idade
void exibirEmOrdem(Node* root);
// Função para exibir a árvore no percurso pré-ordem
void exibirPreOrdem(Node* root);
// Função para exibir a árvore no percurso pós-ordem
void exibirPosOrdem(Node* root);
