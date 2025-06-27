#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int value;
    int altura;
    int regulagem;
    int prod;
    struct Node* pai;
    struct Node* esq;
    struct Node* dir;
} Node;

#define MAX(a,b) ((a > b) ? a : b)

Node* BinSearch(Node* root, int value){
    Node* aux = root;
    
    if(aux == NULL) return NULL;
    
    if(value == aux->value) return aux;
    
    if(value < aux->value) return BinSearch(aux->esq, value);
    
    return BinSearch(aux->dir, value);
}

int InsereNode(Node** root, int value) {
    
    Node* inserido = malloc(sizeof(Node));
    if (!inserido) return -1; // falha de alocação
    
    inserido->value = value;
    inserido->esq = inserido->dir = inserido->pai = NULL;
    
    /*if(root->esq == NULL && root->dir == NULL && root->pai == NULL && root->value == 0){
        root = inserido;
        return 1;
    }*/
    
    if (*root == NULL ) { // Árvore vazia
        *root = inserido;
        return 1;
    }

    Node* aux = *root;
    
    while (1) {
        if (value == aux->value) {
            printf("Valor já inserido!\n");
            free(inserido); // evita vazamento
            return -1;
        }

        if (value < aux->value) {
            if (aux->esq == NULL) {
                aux->esq = inserido;
                inserido->pai = aux;
                return 1;
            }
            aux = aux->esq;
        } 
        
        else { // value > aux->value
            if (aux->dir == NULL) {
                aux->dir = inserido;
                inserido->pai = aux;
                return 1;
            }
            aux = aux->dir;
        }
    }
}

int visitar(Node* No){
    return printf("%d %d\n", No->value, No->prod);
}

void PreOrdem(Node* root){
    
    if(root == NULL) return;
    
    visitar(root);
    PreOrdem(root->esq);
    PreOrdem(root->dir);
}

void PosOrdem(Node* root){
    
    if(root == NULL) return;
    
    PosOrdem(root->esq);
    PosOrdem(root->dir);
    visitar(root);
}

void InOrder(Node* root){
    if(root == NULL) return;
    InOrder(root->esq);
    visitar(root);
    InOrder(root->dir);
}

int setarAltura(Node* root){
    if(root == NULL) return 0;
    
    if(root->esq == NULL && root->dir == NULL) return 1;
    root->altura = MAX(setarAltura(root->dir) , setarAltura(root->esq)) + 1;
    return root->altura;
    
}

int verificaAVL(Node* root){
    if(root == NULL) return 1;
    
    int regulagem = setarAltura(root->esq) - setarAltura(root->dir);
    
    if(regulagem > 1 || regulagem < -1){
        return 0;        
    }
    
    return verificaAVL(root->esq) && verificaAVL(root->dir);
    
}

int produtoMenores(Node* root){
    if(root == NULL) return 1;
    root->prod = root->value * produtoMenores(root->esq);
    return root->prod * produtoMenores(root->dir);
}

int buscaNivel(Node* root, int chave){
    if(root == NULL || root->value == chave) return 1;
    if(root->value > chave) return 1 + buscaNivel(root->esq, chave);
    return 1 + buscaNivel(root->dir, chave);
}
    
int main(){
    Node* root = NULL;
    InsereNode(&root, 5);
    InsereNode(&root, 4);
    InsereNode(&root, 11);
    InsereNode(&root, 10);
    InsereNode(&root, 8);
    InsereNode(&root, 12);
    InsereNode(&root, 1);
    InsereNode(&root, 2);
    produtoMenores(root);
    InOrder(root);
    
    printf("%d\n", buscaNivel(root, 10));
    printf("%d\n", buscaNivel(root, 11));
    printf("%d\n", buscaNivel(root, 30));
    
    return 0;
}