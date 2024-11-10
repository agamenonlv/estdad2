#include <stdio.h>
#include <stdlib.h>

#include "../include/arvorebinaria.h"

//int main(int argc, char const *argv[])
int main(void)
{
    Node* root = NULL;
    Node* node;

    root = insertNode(root, 101, 50, 30);
    root = insertNode(root, 102, 40, 10);
    root = insertNode(root, 103, 60, 25);
    root = insertNode(root, 104, 30, 50);
    root = insertNode(root, 105, 50, 50);
    root = insertNode(root, 106, 60, 20);
    root = insertNode(root, 107, 30, 50);
    root = insertNode(root, 108, 50, 30);
    root = insertNode(root, 109, 10, 20);
    root = insertNode(root, 110, 05, 75);
    root = insertNode(root, 111, 30, 60);
    root = insertNode(root, 112, 60, 10);

    printf("\nLista, em ordem, de usuários cadastrados\n");
    printInOrder(root);

    int id = 103;

    node = searchNode(root, id);

    if (node == NULL)
    {
        if (root == NULL)
        {
            printf("\nÁrvore vazia!\n");
        }
        else
        {
            printf("\nUsuário %d não encontrado\n", id);
        }
    }
    else
    {
        printf("\nUsuário encontrado:\n");
        printf("Id: %d\nCurtidas: %d\nComentários: %d\nTotal de interações: %d\n",node->id, node->curtidas, node->comentarios, node->totalInteracoes);
    }

    id = 104;

    node = deleteUser(root, id, node->totalInteracoes);

    if (node == NULL)
    {
        printf("\nUsuário %d não encontrado\n", id);
    }
    else
    {
        printf("\nLista, em ordem, de usuários, com o usuário %d removido\n", id);
        printInOrder(root);
    }

    id = 107;

    node = updateNode(root, id, 20, 10);

    if (node == NULL)
    {
        printf("\nUsuário %d não encontrado\n", id);
    }
    else
    {
        printf("\nLista, em ordem, de usuários, com o usuário %d atualizado\n", id);
        printInOrder(root);
    }
    
    return 0;
}
