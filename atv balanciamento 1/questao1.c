#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó da árvore
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Função para criar um novo nó da árvore
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Função para inserir um nó na árvore
struct Node* insertNode(struct Node* node, int value) {
    if (node == NULL)
        return createNode(value);

    if (value < node->data)
        node->left = insertNode(node->left, value);
    else if (value > node->data)
        node->right = insertNode(node->right, value);

    return node;
}

// Função para percorrer a árvore em ordem (in-order traversal)
void inOrderTraversal(struct Node* node) {
    if (node == NULL)
        return;

    inOrderTraversal(node->left);
    printf("%d ", node->data);
    inOrderTraversal(node->right);
}

int main() {
    struct Node* root = NULL;

    // Inserindo os valores na árvore
    root = insertNode(root, 7);
    insertNode(root, 22);
    insertNode(root, 14);
    insertNode(root, 40);
    insertNode(root, 30);
    insertNode(root, 63);
    insertNode(root, 80);

    // Percorrendo a árvore em ordem
    printf("Árvore binária em ordem: ");
    inOrderTraversal(root);
    printf("\n");

    return 0;
}
