#ifndef _ARVOREBINARIA_H

    #define _ARVOREBINARIA_H

    //Estrutura do nó da árvore
    typedef struct Node
    {
        int id;
        int curtidas;
        int comentarios;
        int totalInteracoes;
        struct Node* esquerda;
        struct Node* direita;        
    } Node;
    
    /*
    Protótipos das funções
    */
    
    //Função para criar um novo nó.
    Node *createNode(int id, int curtidas, int comentarios);
    //Função para inserir um novo nó na árvore.
    Node *insertNode(Node* root, int id, int curtidas, int comentarios);
    //Função de busca para encontrar e exibir a quantidade de interações de um usuário pelo ID.
    Node *searchNode(Node* root, int id);
    //Função de exibição para listar os usuários em ordem decrescente de engajamento.
    void printInOrder(Node* root);
    //Função para remover um usuário.
    Node *deleteUser(Node* root, int id, int key);
    //Função para atualizar os dados de interações de um usuário específico.
    Node *updateNode(Node* root, int id, int curtidas, int comentarios);
    // Função para encontrar o menor nó (usado na remoção)
    Node *minNode(Node* root);

#endif