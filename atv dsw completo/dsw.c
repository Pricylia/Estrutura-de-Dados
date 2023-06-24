/* Pricylia */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

typedef struct ArvoreNo {
    int el;
    struct ArvoreNo *left;
    struct ArvoreNo *right;
} ArvoreNo;

typedef struct Arvore {
    ArvoreNo *root;
} Arvore;

ArvoreNo* novoNo(int e, ArvoreNo *l, ArvoreNo *r) {
    ArvoreNo *no = (ArvoreNo*)malloc(sizeof(ArvoreNo));
    no->el = e;
    no->left = l;
    no->right = r;
    return no;
}

void clear(Arvore *arvore) {
    ArvoreNo *no = arvore->root;
    if (no != NULL) {
        clear(&(Arvore){.root = no->left});
        clear(&(Arvore){.root = no->right});
        free(no);
    }
}

bool isEmpty(Arvore *arvore) {
    return arvore->root == NULL;
}

void visit(ArvoreNo *p) {
    printf("%d ", p->el);
}

int search(Arvore *arvore, int el) {
    ArvoreNo *p = arvore->root;
    while (p != NULL) {
        if (el == p->el)
            return p->el;
        else {
            if (el < p->el)
                p = p->left;
            else
                p = p->right;
        }
    }
    return 0;
}

void insert(Arvore *arvore, int el) {
    ArvoreNo *p = arvore->root, *prev = NULL;
    while (p != NULL) {
        prev = p;
        if (el < p->el)
            p = p->left;
        else
            p = p->right;
    }
    if (arvore->root == NULL)
        arvore->root = novoNo(el, NULL, NULL);
    else if (el < prev->el)
        prev->left = novoNo(el, NULL, NULL);
    else
        prev->right = novoNo(el, NULL, NULL);
}

void percursoExtensao(Arvore *arvore) {
    ArvoreNo *p = arvore->root;
    if (p != NULL) {
        ArvoreNo *fila[100];
        int frente = 0, tras = 0;
        fila[tras++] = p;
        while (frente != tras) {
            p = fila[frente++];
            visit(p);
            if (p->left != NULL)
                fila[tras++] = p->left;
            if (p->right != NULL)
                fila[tras++] = p->right;
        }
    }
}

int treeHeight(ArvoreNo *node) {
    if (node == NULL) {
        return -1;
    } else {
        int left_height = treeHeight(node->left);
        int right_height = treeHeight(node->right);
        if (left_height >= right_height) {
            return left_height + 1;
        } else {
            return right_height + 1;
        }
    }
}

void printTree(ArvoreNo *node) {
    if (node != NULL) {
        printf("<%d", node->el);
        if (node->left != NULL) {
            printTree(node->left);
        } else {
            printf("<>");
        }
        if (node->right != NULL) {
            printTree(node->right);
        } else {
            printf("<>");
        }
    }
    printf(">");
}

void preorder(ArvoreNo *p) {
    if (p != NULL) {
        visit(p);
        preorder(p->left);
        preorder(p->right);
    }
}

void rotateLeft(ArvoreNo *p) {
    if (p == NULL || p->right == NULL) {
        return;
    }

    int tmp_value = p->el;
    p->el = p->right->el;
    p->right->el = tmp_value;

    ArvoreNo *oR = p->right; // originalRight
    p->right = oR->right;
    oR->right = oR->left;
    oR->left = p->left;
    p->left = oR;
}

void rotateRight(ArvoreNo *p) {
    if (p == NULL || p->left == NULL) {
        return;
    }

    int tmp_value = p->el;
    p->el = p->left->el;
    p->left->el = tmp_value;

    ArvoreNo *oL = p->left; // originalLeft
    p->left = oL->left;
    oL->left = oL->right;
    oL->right = p->right;
    p->right = oL;
}

void balanceTree(ArvoreNo *p) {
    ArvoreNo *current = p;
    int nodecount = 0;

    while (current != NULL) {
        while (current->left != NULL) {
            rotateRight(current);
        }
        current = current->right;
        nodecount++;
    }

    int expected = ceil(log2(nodecount) - nodecount);
    ArvoreNo *current1 = p;

    for(int i = 0; i < expected; i++) {
        if(i == 0) {
            rotateLeft(current1);
            current1 = p;
        } else {
            rotateLeft(current1->right);
            current1 = current1->right;
        }
    }

    int times = nodecount;
    while(times > 1) {
        times /= 2;

        rotateLeft(p);
        ArvoreNo *current2 = p;

        for(int i = 0; i < times - 1; i++) {
            rotateLeft(current2->right);
            current2 = current2->right;
        }
    }
}

int main() {
    Arvore *a = (Arvore*)malloc(sizeof(Arvore));
    a->root = NULL;

    insert(a, 7);
    insert(a, 22);
    insert(a, 14);
    insert(a, 40);
    insert(a, 30);
    insert(a, 63);
    insert(a, 80);

    printf("Altura da arvore: %d\n", treeHeight(a->root));
    printTree(a->root);
    printf("\n");
    preorder(a->root);

    balanceTree(a->root);

    printf("\n--- Apos as rotacoes ---\n");
    printTree(a->root);
    printf("\n");
    preorder(a->root);

    clear(a);
    free(a);

    return 0;
}
