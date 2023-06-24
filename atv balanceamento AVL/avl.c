/* Pricylia */

#include <stdbool.h>
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

void printTree(struct Node *node) {
  if(node != NULL) {
    printf("<%i", node->data);
    if(node->left != NULL) {
      printTree(node->left);
    } else {
      printf("<>");
    };
    if(node->right != NULL) {
      printTree(node->right);
    } else {
      printf("<>");
    }
  };
  printf(">");
};

int treeHeight(struct Node *node) { 
  if(node == NULL) {
    return -1;
  } else {
    int left_height = treeHeight(node->left);
    int right_height = treeHeight(node->right); 
    if (left_height >= right_height) {
      return left_height + 1;
    } else {
      return right_height + 1;
    };
  };
}

int diffHeight(struct Node *node) {
  if(node == NULL) {
    return 0;
  } else {
    int left_height = treeHeight(node->left);
    int right_height = treeHeight(node->right);
    return left_height - right_height;
  }
}

Node *rotateLeft(Node *node) {
    Node *new_root = node->right;
    node->right = new_root->left;
    new_root->left = node;
    return new_root;
}

Node *rotateRight(Node *node) {
    Node *new_root = node->left;
    node->left = new_root->right;
    new_root->right = node;
    return new_root;
}

Node *rotateLeftRight(Node *node) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
}

Node *rotateRightLeft(Node *node) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
}

Node *insert(Node *node, int data) {
    if (node == NULL) {
        return newNode(data);
    }

    if (data < node->data) {
        node->left = insert(node->left, data);
    } else if (data > node->data) {
        node->right = insert(node->right, data);
    } else {
        return node;
    }

    int balance_factor = diffHeight(node);

    if (balance_factor > 1) {
        if (data < node->left->data) {
            return rotateRight(node);
        } else {
            return rotateLeftRight(node);
        }
    } else if (balance_factor < -1) {
        if (data > node->right->data) {
            return rotateLeft(node);
        } else {
            return rotateRightLeft(node);
        }
    }

    return node;
}

int main() {
    Node *root = NULL;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    printTree(root);
    return 0;
}