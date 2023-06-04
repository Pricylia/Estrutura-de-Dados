#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó da árvore
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Função para criar um novo nó
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Função para inserir um valor na árvore
struct Node* insert(struct Node* node, int data) {
    if (node == NULL) {
        return createNode(data);
    }
    
    if (data < node->data) {
        node->left = insert(node->left, data);
    } else if (data > node->data) {
        node->right = insert(node->right, data);
    }
    
    return node;
}

// Função para percorrer a árvore em ordem (esquerda, raiz, direita)
void inorderTraversal(struct Node* node) {
    if (node == NULL) {
        return;
    }
    
    inorderTraversal(node->left);
    printf("%d ", node->data);
    inorderTraversal(node->right);
}

int main() {
    struct Node* root = NULL;

    // Inserindo os valores na árvore
    root = insert(root, 7);
    root = insert(root, 22);
    root = insert(root, 14);
    root = insert(root, 40);
    root = insert(root, 30);
    root = insert(root, 63);
    root = insert(root, 80);

    // Percorrendo a árvore em ordem
    printf("Árvore binária em ordem: ");
    inorderTraversal(root);

    return 0;
}
