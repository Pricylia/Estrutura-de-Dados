#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

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

void printTree(struct Node* node, int level) {
    if (node == NULL) {
        return;
    }
    
    printTree(node->right, level + 1);
    
    for (int i = 0; i < level; i++) {
        printf("    ");
    }
    
    printf("%d\n", node->data);
    
    printTree(node->left, level + 1);
}

int main() {
    struct Node* root = NULL;

    root = insert(root, 7);
    root = insert(root, 22);
    root = insert(root, 14);
    root = insert(root, 40);
    root = insert(root, 30);
    root = insert(root, 63);
    root = insert(root, 80);

    printf("Árvore binária resultante:\n");
    printTree(root, 0);

    return 0;
}
