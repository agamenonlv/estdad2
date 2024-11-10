#include <stdio.h>
#include <stdlib.h>

#include "../include/arvorebinaria.h"

//Função para criar um novo nó.
Node *createNode(int id, int curtidas, int comentarios)
{
    Node* newNode = (Node*)malloc(sizeof(Node));

    if (newNode == NULL)
    {
        printf("\nErro Crítico! Sem memória para criar no nó!\n");
    }
    else
    {
        newNode->id = id;
        newNode->curtidas = curtidas;
        newNode->comentarios = comentarios;
        newNode->totalInteracoes = curtidas + comentarios;
        newNode->esquerda = NULL;
        newNode->direita = NULL;
    }

    return newNode;
}

//Função para inserir um novo nó na árvore.
Node *insertNode(Node* root, int id, int curtidas, int comentarios)
{
    if (root == NULL) // Se a árvore não existir
    {
        return createNode(id, curtidas, comentarios);
    }

    if ((curtidas + comentarios) < root->totalInteracoes) // Se o total de interações for menor do que o total de interações do nó anterior
    {
        root->esquerda = insertNode(root->esquerda, id, curtidas, comentarios);
    }
    else if ((curtidas + comentarios) > root->totalInteracoes) // Se o total de interações for maior do que o total de interações do nó anterior
    {
        root->direita = insertNode(root->direita, id, curtidas, comentarios);
    }
    else // Se o total de interações for igual ao total de interações do nó anterior
    {
        if (curtidas < root->curtidas)
        {
            root->esquerda = insertNode(root->esquerda, id, curtidas, comentarios);
        }
        else if (curtidas > root->curtidas)
        {
            root->direita = insertNode(root->direita, id, curtidas, comentarios);
        }
        else
        {
            if (id < root->id)
            {
                root->esquerda = insertNode(root->esquerda, id, curtidas, comentarios);
            }
            else if (id > root->id)
            {
                root->direita = insertNode(root->direita, id, curtidas, comentarios);
            }
            else
            {
                printf("\nUsuário %d já cadastrado!\n", id);
            }
        }
    }

    return root;

}

//Função de busca para encontrar e exibir a quantidade de interações de um usuário pelo ID.
Node *searchNode(Node* root, int id)
{
    if (root == NULL)
    {
        return root;
    }

    // Se o nó corrente for o nó procurado
    if (id == root->id)
    {
        return root;
    }

    //Realiza a busca recursiva nos dois lados
    Node* foundNode = searchNode(root->esquerda, id);

    // Se encontrou no lado esquerdo
    if (foundNode != NULL)
    {
        return foundNode;
    }
    
    // Se não encontrou no lado esquerdo, procura no lado direito
    return searchNode(root->direita, id);
}

//Função de exibição para listar os usuários em ordem decrescente de engajamento.
void printInOrder(Node* root)
{
    if (root != NULL)
    {
        printInOrder(root->direita);
        printf("O usuário %d tem %d curtidas, %d comentários, com um total de %d interações.\n", root->id, root->curtidas, root->comentarios, root->totalInteracoes);
        printInOrder(root->esquerda);
    }
}

//Função para remover um usuário.
Node* deleteUser(Node* root, int id, int key)
{
    if (root == NULL)
    {
        return root; // Caso base: árvore vazia ou usuário não encontrado
    }

    if (key < root->totalInteracoes)
    {
        root->esquerda = deleteUser(root->esquerda, id, key);
    }
    else if (key > root->totalInteracoes)
    {
        root->direita = deleteUser(root->direita, id, key);
    }
    else
    {
        if (id == root->id)
        {
            //Caso 1: Nó sem filhos (nó folha)
            if (root->esquerda == NULL && root->direita == NULL)
            {
                free(root);
                return NULL;
            }
            // Caso 2: Nó com apenas um filho
            else if (root->esquerda == NULL)  // Tem apenas filho direito
            {
                Node* temp = root->direita;
                free(root);
                return temp;
            }
            else if (root->direita == NULL) // Tem apenas filho esquerdo
            {
                Node* temp = root->esquerda;
                free(root);
                return temp;
            }
            else
            {
                // Encontrando o sucessor em ordem (menor nó da subárvore direita)
                Node* temp = minNode(root->direita);
            
                // Copiando os dados do sucessor para o nó atual
                root->id = temp->id;
                root->curtidas = temp->curtidas;
                root->comentarios = temp->comentarios;
                root->totalInteracoes = temp->totalInteracoes;
                
                // Removendo o sucessor da subárvore direita
                root->direita = deleteUser(root->direita, temp->id, key);
            }
        }
        else
        {
            root->esquerda = deleteUser(root->esquerda, id, key);
            root->direita = deleteUser(root->direita, id, key);
        }
    }

    return root;
}

//Função para atualizar os dados de interações de um usuário específico.
Node* updateNode(Node* root, int id, int curtidas, int comentarios)
{
    if (root == NULL)
    {
        return root;
    }
    
    Node* temp = searchNode(root, id);

    if (temp == NULL)
    {
        return NULL;
    }

    int tempCurtidas = temp->curtidas + curtidas;
    int tempComentarios = temp->comentarios + comentarios;

    printf("\nId: %d\n", id);
    printf("Curtidas: %d + %d\n", curtidas, temp->curtidas);
    printf("Comentarios: %d + %d\n", comentarios, temp->comentarios);
    printf("Total de interações: %d\n", temp->totalInteracoes);

    deleteUser(root, id, temp->totalInteracoes);
    insertNode(root, id, tempCurtidas, tempComentarios);

    return root;
}

// Função para encontrar o menor nó (usado na remoção)
Node* minNode(Node* node) {
    Node* current = node;
    while (current && current->esquerda != NULL) {
        current = current->esquerda;
    }
    return current;
}