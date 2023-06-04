#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó da árvore binária
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Função para criar um novo nó
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Falha na alocação de memória!");
        exit(1);
    }
    newNode->data = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Função para inserir um valor na árvore binária
struct Node* insert(struct Node* node, int value) {
    if (node == NULL) {
        return createNode(value);
    }
    if (value < node->data) {
        node->left = insert(node->left, value);
    } else if (value > node->data) {
        node->right = insert(node->right, value);
    }
    return node;
}

// Função para percorrer e mostrar a árvore em ordem
void inorderTraversal(struct Node* node) {
    if (node != NULL) {
        inorderTraversal(node->left);
        printf("%d ", node->data);
        inorderTraversal(node->right);
    }
}

// Função principal
int main() {
    struct Node* root = NULL;
    
    // Valores a serem inseridos na árvore binária
    int values[] = {7, 6, 22, 14, 40, 63};
    int numValues = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < numValues; i++) {
        root = insert(root, values[i]);
    }

    printf("Arvore binaria resultante:\n");
    printf("   %d\n", root->data);
    printf("  / \\\n");
    printf(" %d   %d\n", root->left->data, root->right->data);
    printf("     / \\\n");
    printf("    %d   %d\n", root->right->left->data, root->right->right->data);
    printf("          \\\n");
    printf("          %d\n", root->right->right->right->data);

    return 0;
}
