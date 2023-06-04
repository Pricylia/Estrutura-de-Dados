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

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(struct Node* node) {
    if (node == NULL) {
        return 0;
    }
    
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    
    return 1 + max(leftHeight, rightHeight);
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

    printf("Árvore binária em ordem: ");
    inorderTraversal(root);

    int treeHeight = height(root);
    printf("\nAltura da árvore: %d\n", treeHeight);

    return 0;
}
