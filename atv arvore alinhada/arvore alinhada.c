#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
    int isThreaded;
} Node;

Node *createNode(int data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->isThreaded = 1;
    return newNode;
}

Node *insertNode(Node *root, int data) {
    Node *newNode = createNode(data);

    if (root == NULL) {
        root = newNode;
        return root;
    }

    Node *current = root;

    while (1) {
        if (data < current->data) {
            if (current->left == NULL) {
                current->left = newNode;
                newNode->right = current;
                newNode->isThreaded = 1;
                return root;
            }
            current = current->left;
        } else {
            if (current->isThreaded == 0) {
                current = current->right;
                if (current == root) {
                    break;
                }
            }
            else {
                newNode->right = current->right;
                newNode->isThreaded = 1;
                current->right = newNode;
                current->isThreaded = 0;
                break;
            }
        }
    }

    return root;
}

void inorderTraversal(Node *root) {
    if (root == NULL) {
        return;
    }

    Node *current = root;

    while (current->left != NULL) {
        current = current->left;
    }

    while (current != NULL) {
        printf("%d ", current->data);

        if (current->isThreaded) {
            current = current->right;
        } else {
            current = current->right;
            while (current != NULL && current->left != NULL) {
                current = current->left;
            }
        }
    }
}

void preorderTraversal(Node *root) {
    if (root == NULL) {
        return;
    }

    Node *current = root;

    printf("%d ", current->data);

    while (current != NULL) {
        if (current->left != NULL) {
            current = current->left;
            printf("%d ", current->data);
            continue;
        }
        if (current->isThreaded) {
            current = current->right;
        }
        if (current != NULL && !current->isThreaded) {
            current = current->right;
            printf("%d ", current->data);
        }
    }
}

int main() {
    Node *root = NULL;

    root = insertNode(root, 4);
    root = insertNode(root, 2);
    root = insertNode(root, 6);
    root = insertNode(root, 1);
    root = insertNode(root, 3);
    root = insertNode(root, 5);
    root = insertNode(root, 7);

    printf("Percorrendo a arvore em ordem: ");
    inorderTraversal(root);
    printf("\n");

    printf("Percorrendo a arvore em pre-ordem: ");
    preorderTraversal(root);
    printf("\n");

    return 0;
}