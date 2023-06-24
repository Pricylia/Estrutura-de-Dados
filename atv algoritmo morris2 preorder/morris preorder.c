/* 
1) 10, 5, 3, 7, 20, 15, 24

2)

O algoritmo é mais simples que o percurso em ordem, utilizando com o ponteiro 
para a raiz da árvore como parâmetro e o ponteiro current.

Enquanto root não for nulo, irá verificar se o nó a esquerda é nulo. Caso for,
irá imprimir seu valor e percorrerá na sub-árvore direita. Caso contrário, irá
realizar os seguintes passos:
  - Atribui o ponteiro current para o nó a esquerda de root.
  - Enquanto houver filho a direita de current e ele não for igual a root,
    current percorrerá a sub-árvore a direita.
  - Ao encontrar um nó igual a root, rompe a ligação a direita de current e
    root irá para sua direita.
  - Caso não encontre, imprime o valor de root, interliga a direita de current
    com root e root irá para sua esquerda.
*/

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
    root = insert(root, 10);
    insert(root, 5);
    insert(root, 20);
    insert(root, 7);
    insert(root, 3);
    insert(root, 24);
    insert(root, 15);

    preorderMorrisTraversal(root);
 
    return 0;
}