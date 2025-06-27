#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct aux {
    int valor;
    struct aux* prox;
} ELEMENTO;

typedef struct{
    ELEMENTO* inicio;
    ELEMENTO* fim;
} Fila;

void inicializarFila(Fila* fila){
    fila->fim = NULL;
    fila->inicio = NULL;
}

int tamanhoFila(Fila* fila){
    ELEMENTO* end = fila->inicio;
    int tam = 0;
    while(end != NULL){
        end = end->prox;
        tam++;
    }
    return tam;
}

int inserirElemento(int valor, Fila* fila){
    
    ELEMENTO* aux = (ELEMENTO*) malloc(sizeof(ELEMENTO));
    aux->valor = valor;
    
    if(fila->inicio == NULL){
        fila->inicio = aux;
        fila->fim = aux;
        return 1;
    }
    
    else{
        fila->fim->prox = aux;
        fila->fim = aux;
        return 1;
    }
    return 0;
}

int exibirFila(Fila* fila){
    if(fila->inicio == NULL) {
        printf("Lista vazia");
        return -1;
    }
    
    int tam = 0;
    ELEMENTO* end = fila->inicio;
    while(end != NULL){
        printf("%d\n", end->valor);
        end = end->prox;
        tam++;
    }
    printf("\n");
    return tam;
}

// A fins do trabalho, queremos apenas remover o último da fila, não algum inteiro específico...

int excluirDaLista(Fila* fila){
    if(fila->fim == NULL){
        printf("A fila não possui elementos...");
        return 0;
    }    
    ELEMENTO* apagar = fila->inicio;
    int excluido = apagar->valor;
    fila->inicio = fila->inicio->prox;
    free(apagar);
    
    if(fila->inicio == NULL) fila->fim == NULL;
    return excluido;
}

void reincializarFila(Fila* fila){
    
    if(fila->inicio == NULL) return;
    
    ELEMENTO* end = fila->inicio;
    while(end != NULL){
        ELEMENTO* apagar = end;
        end = end->prox;
        free(apagar);
    }
    fila->inicio = NULL;
    fila->fim = NULL;
}

ELEMENTO* verificaElemento(int elemento, Fila* fila){
    
    if(fila->inicio == NULL) return NULL;
    ELEMENTO* end = fila->inicio;
    while(end != NULL){
        if(end->valor == elemento){
            return end;
        }
        end = end->prox;
    }
    return NULL;
}

void inserirElementoPosicao(Fila* fila, int elemento, ELEMENTO* posicao){
    if (fila == NULL || posicao == NULL) return;

    ELEMENTO* aux = (ELEMENTO*) malloc(sizeof(ELEMENTO));
    if (aux == NULL) {
        printf("Erro de alocação de memória.\n");
        exit(1);
    }

    aux->valor = elemento;
    aux->prox = posicao->prox;

    posicao->prox = aux;

    if (aux->prox == NULL) {
        fila->fim = aux;
    }
}

int main(){
    
    Fila* filaPrincipal;
    
    int MAX_dequeus = 10;
    int MAX_cenarios = 10;
    
    int num_times = 1;
    int cenarios = 0;
    inicializarFila(filaPrincipal);
    int* listaDequeues = (int*) malloc (MAX_dequeus * sizeof(int));
    int** todosDequeues = (int**) malloc (MAX_cenarios * sizeof(int*));
    int* quantidadeDequeues = (int*) malloc(MAX_cenarios * sizeof(int));
    
    while(num_times != 0){
        scanf("%d", &num_times);
        getchar();
        
        switch(num_times){
            
            case 0:
                break;
            
            default:
                cenarios++;
                int dequeues = 0;
                // Define a quantidade de times e prepara os ponteiros para receber os valores
                int** times = (int**) malloc (num_times * sizeof(int*));
                int tamanhos_times[num_times];
                for(int i = 0; i < num_times; i++){
                    
                    char linha[1024];
                    int tamanho = 0; 
                    int indice = 0;
                    int valor;
                    
                    fgets(linha, sizeof(linha), stdin);
                    char *token = strtok(linha, " \n");
                    
                    sscanf(token, "%d", &tamanho);
                    int* numeros = malloc(tamanho * sizeof(int));
                    times[i] = numeros;
                    
                    for (int j = 0; j < tamanho && (token = strtok(NULL, " \n")); j++) {
                        sscanf(token, "%d", &valor);
                        numeros[j] = valor;
                    }
                    tamanhos_times[i] = tamanho;
                }
                
               /*for(int i = 0; i < num_times; i++){
                    for(int j = 0; j < tamanhos_times[i]; j++){
                        printf("%d ", times[i][j]);
                    }
                    printf("\n");
                }*/
                
                // Lendo uma vez só por enquanto.
                
                // Zera a linha usada acima para preencher os times
                char comandos[64];
                char comando[10] = {"          "};
                
                int n;
                
                while(strcmp(comando, "STOP")){
                    // Passa a ler comando em relação àquele grupo de times
                    fgets(comandos, sizeof(comandos), stdin);
                    
                    sscanf(comandos, "%s", comando);
                
                    if(!strcmp(comando, "ENQUEUE")){
                        sscanf(comandos, "%s %d", comando, &n);
                        
                        // Processo de acrescentar na fila principal
                    
                        // Procurar a linha a qual pertence n
                        int linhaDoTime;
                        
                        int achou = 0;
                        for(int i = 0; i < num_times; i++){
                            for(int j = 0; j < tamanhos_times[i]; j++){
                                if(times[i][j] == n){
                                    linhaDoTime = i;
                                    i = num_times;
                                    j = tamanhos_times[i];
                                    achou = 1;
                                }
                            }
                        }
                        
                        if(achou == 0){
                            printf("Número inválido \n");
                        }
                        else{
                        
                            // Caso da sorte!
                            int furou = 0;
                            ELEMENTO* ultimoDoTime = NULL;
                            
                            // Percorre a fila na ordem, e guarda o último que pertence ao time
                            ELEMENTO* atual = filaPrincipal->inicio;
                            while (atual != NULL) {
                                for (int i = 0; i < tamanhos_times[linhaDoTime]; i++) {
                                    if (atual->valor == times[linhaDoTime][i]) {
                                        ultimoDoTime = atual;
                                        break;  // Achou, não precisa continuar esse for
                                    }
                                }
                                atual = atual->prox;
                            }
                            
                            if (ultimoDoTime != NULL) {
                                inserirElementoPosicao(filaPrincipal, n, ultimoDoTime);
                                furou = 1;
                            }
                            //
                            
                            // Que azar!
                            if(furou == 0){
                                inserirElemento(n, filaPrincipal);
                            }
                            //
                        }
                    }
                    
                    if(!strcmp(comando, "DEQUEUE")){
                        
                        int excluido = excluirDaLista(filaPrincipal);
                        
                        // Ajusta o tamanho da lista de dequeues conforme necessário
                        if(dequeues >= 10){
                            listaDequeues = realloc (listaDequeues, 2 * sizeof(listaDequeues));
                        }
                        
                        listaDequeues[dequeues++] = excluido;
                    }
                }
                
                // Ajusta o tamanho do vetor de contagem das listas conforme necessário
                if(cenarios >= MAX_cenarios){
                    MAX_cenarios *= 2;
                    quantidadeDequeues = realloc (quantidadeDequeues, MAX_cenarios * sizeof(quantidadeDequeues));
                    todosDequeues = realloc(todosDequeues, MAX_cenarios * sizeof(todosDequeues));
                    
                }
                
                quantidadeDequeues[cenarios - 1] = dequeues;
                
                // Aloca espaço para o vetor atual da matriz
                todosDequeues[cenarios - 1] = malloc (dequeues * sizeof(int));
                
                // Preenche a matriz dos dequeues um a um
                for(int i = 0; i < dequeues; i++){
                    todosDequeues[cenarios-1][i] = listaDequeues[i];
                }
        }
    }    

    for(int i = 0; i < cenarios; i++){
        printf("Scenario #%d\n", i+1);
        for(int j = 0; j < quantidadeDequeues[i]; j++){
            printf("%d\n", todosDequeues[i][j]);
        }
        printf("\n");
    }
    return 0;
}
