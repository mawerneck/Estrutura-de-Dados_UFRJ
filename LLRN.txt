#include <stdio.h>
#include <stdlib.h>

#define RED 1
#define BLACK 0

typedef struct Node {
    int key;
    int color;
    struct Node* left;
    struct Node* right;
} Node;

int isRed(Node* node) {
    if (node == NULL) return 0;
    return node->color == RED;
}

Node* rotateLeft(Node* h) {
    Node* x = h->right;
    h->right = x->left;
    x->left = h;
    x->color = h->color;
    h->color = RED;
    return x;
}

Node* rotateRight(Node* h) {
    Node* x = h->left;
    h->left = x->right;
    x->right = h;
    x->color = h->color;
    h->color = RED;
    return x;
}

void flipColors(Node* h) {
    h->color = RED;
    if (h->left) h->left->color = BLACK;
    if (h->right) h->right->color = BLACK;
}

Node* createNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->color = RED;  // Novo nó sempre inicia vermelho
    node->left = node->right = NULL;
    return node;
}

Node* insert(Node* h, int key) {
    if (h == NULL) return createNode(key);

    if (key < h->key)
        h->left = insert(h->left, key);
    else if (key > h->key)
        h->right = insert(h->right, key);
    else
        ; // já existe, não insere duplicatas

    // Correções LLRN
    if (isRed(h->right) && !isRed(h->left)) h = rotateLeft(h);
    if (isRed(h->left) && isRed(h->left->left)) h = rotateRight(h);
    if (isRed(h->left) && isRed(h->right)) flipColors(h);

    return h;
}

void printPreOrder(Node* root) {
    if (root == NULL) return;
    printf("%d%s ", root->key, root->color == RED ? "R" : "N");
    printPreOrder(root->left);
    printPreOrder(root->right);
}

int main() {
    Node* root = NULL;
    int capacity = 10;
    int* keys = malloc(capacity * sizeof(int));
    int i = 0;
    
    while (scanf("%d", &keys[i]) == 1) {
        root = insert(root, keys[i]);
        root->color = BLACK;  // A raiz deve sempre ser preta
        i++;

        if (i == capacity) {
            capacity *= 2;
            keys = realloc(keys, capacity * sizeof(int));
            if (!keys) {
                fprintf(stderr, "Erro de realocação de memória.\n");
                return 1;
            }
        }
    }

    printPreOrder(root);

    free(keys);
    return 0;
}
