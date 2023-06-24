#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

Node *newNode(int data) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
 
    return node;
}

struct Node* insert(struct Node *node, int data) {
    if (node == NULL)
        return newNode(data);

    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);

    return node;
}

void inorderMorrisTraversal(Node *root) {
    Node *current, *previous;
 
    if (root == NULL) {
        return;
    }

    current = root;
    while (current != NULL) {
        if (current->left == NULL) {
            printf("%d ", current->data);
            current = current->right;
        }
        else {
            previous = current->left;
            while (previous->right != NULL && previous->right != current) {
              previous = previous->right;
            } 
 
            if (previous->right == NULL) {
                previous->right = current;
                current = current->left;
            } else {
                previous->right = NULL;
                printf("%d ", current->data);
                current = current->right;
            }
        }
    }
}

void preorderMorrisTraversal(struct Node *root)
{   
    while (root) {
        if (root->left == NULL) {
            printf("%d ", root->data);
            root = root->right;
        }
        else {
            struct Node *current = root->left;
            while (current->right && current->right != root) {
                current = current->right;
            }
            if (current->right == root) {
                current->right = NULL;
                root = root->right;
            } else {
                printf("%d ", root->data);
                current->right = root;
                root = root->left;
            }
        }
    }
}

int main() {
    Node *root = NULL;
    root = insert(root, 90);
    insert(root, 45);
    insert(root, 70);
    insert(root, 25);
    insert(root, 30);

    inorderMorrisTraversal(root);
    printf("\n");
    preorderMorrisTraversal(root);
 
    return 0;
}