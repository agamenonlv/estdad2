#include <stdio.h>

#include "../headers/arvorebinaria.h"

// Função principal
int main() {
    Node* root = NULL;
    
    // Inserindo usuários
    root = insertNode(root, 101, 50);
    root = insertNode(root, 102, 40);
    root = insertNode(root, 103, 20);
    root = insertNode(root, 104, 30);
    root = insertNode(root, 105, 70);

    // Exibindo usuários em ordem
    printf("Usuários em ordem de idade:\n");
    exibirEmOrdem(root);

    //Exbindo usuários em pré-ordem
    printf("\nUsuários em pré-ordem de idade:\n");
    exibirPreOrdem(root);

    //Exibindo usuário em pós-ordem
    printf("\nUsuários em pós-ordem de idade:\n");
    exibirPosOrdem(root);

    // Removendo um usuário
    root = deleteUser(root, 105);
    printf("\nApós remoção do usuário:\n");
    printf("Em ordem:\n");
    exibirEmOrdem(root);
    printf("Pré-ordem:\n");
    exibirPreOrdem(root);
    printf("Pós-ordem:\n");
    exibirPosOrdem(root);

