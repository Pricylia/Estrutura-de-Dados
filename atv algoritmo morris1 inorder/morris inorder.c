/* 
1) 3, 5, 7, 10, 15, 20, 24

2)
A função recebe um nó raiz como parâmetro e dois ponteiros chamados current e previous,
para marcação do nó atual e nó predecessor do atual.

O ponteiro current receberá o nó raiz como valor. Caso o nó raiz for nulo, a função encerra.

Enquanto o current não for nulo, um loop será feito da seguinte forma:

- Se current->left for nulo, imprime current e caminha para current->right.
- Caso current->left não for nulo, previous receberá current->left e iniciará a procura pelo 
  último nó a direita da sub-árvore esquerda ou que iguale ao valor de current, para definir
  o predecessor de current no percurso em ordem:
  - Enquanto o nó a direita de previous não for nulo e não for igual ao current, previous
    caminhará nos nós a sua direita.
  - Ao finalizar o loop do previous, checará se o nó a direita de previous está nulo e caso
    sim previous->right receberá current como valor, depois current caminha para o nó 
    a sua esquerda.
  - Caso não for nulo, previous->right ficará nulo, removendo sua interligação feita antes,
    imprime current e current caminha pra sub-árvore direita.
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

int main() {
    Node *root = NULL;
    root = insert(root, 10);
    insert(root, 5);
    insert(root, 20);
    insert(root, 7);
    insert(root, 3);
    insert(root, 24);
    insert(root, 15);

    inorderMorrisTraversal(root);
 
    return 0;
}