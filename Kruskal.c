#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int vertices[2];
    int peso;
} TAresta;

int find(int x, int pai[]) {
    if (pai[x] != x)
        pai[x] = find(pai[x], pai);
    return pai[x];
}

void BBSortArestas(TAresta* arestas, int tam) {
    for (int i = 0; i < tam - 1; i++) {
        for (int j = 0; j < tam - i - 1; j++) {
            if (arestas[j].peso > arestas[j + 1].peso) {
                TAresta temp = arestas[j];
                arestas[j] = arestas[j + 1];
                arestas[j + 1] = temp;
            }
        }
    }
}

int union_find(TAresta a, int pai[], int rank[]) {
    int root_x = find(a.vertices[0], pai);
    int root_y = find(a.vertices[1], pai);

    if (root_x == root_y)
        return 0; // Não adiciona peso se já estão conectados

    // União por rank
    if (rank[root_x] > rank[root_y]) {
        pai[root_y] = root_x;
        rank[root_x]++;
    } else if (rank[root_x] < rank[root_y]) {
        pai[root_x] = root_y;
        rank[root_y]++;
    } else {
        pai[root_y] = root_x;
        rank[root_x]++;
    }
    return a.peso; // Peso da aresta incluída
}

int kruskal(TAresta* arestas, int* pai, int* rank, int qtdVertices) {
    int peso_arvore_minima = 0;
    int arestas_arvore_minima = 0;
    int i = 0;
    while(i < qtdVertices){
        int peso = union_find(arestas[i], pai, rank);
        if (peso > 0) { // A aresta foi incluída
            peso_arvore_minima += peso;
            arestas_arvore_minima++;
        }
        i++;
    }
    return peso_arvore_minima;
}

int main() {
    int max_aresta = 100;
    TAresta* arestas = malloc(sizeof(TAresta) * max_aresta);
    int cont = 0;

    int vertices = 0;
    int linhas = 0;
    scanf("%d %d", &vertices, &linhas);

    int pai[100] = {0};
    int rank[100] = {0};
    int vertices_unicos[100] = {0};
    int qtdVertices = 0;

    while (cont < linhas) {
        int v1 = 0, v2 = 0, peso = 0;

        if (cont == max_aresta - 2) { // Verifica quantidade limite de arestas
            max_aresta += 10;
            arestas = realloc(arestas, sizeof(TAresta) * max_aresta);
            if (arestas == NULL) {
                printf("Erro de alocação\n");
                exit(1);
            }
        }

        scanf("%d %d %d", &v1, &v2, &peso);
        arestas[cont].vertices[0] = v1;
        arestas[cont].vertices[1] = v2;
        arestas[cont].peso = peso;

        if (pai[v1] == 0) {
            pai[v1] = v1;
            qtdVertices++;
        }
        if (pai[v2] == 0) {
            pai[v2] = v2;
            qtdVertices++;
        }

        cont++;
    }

    BBSortArestas(arestas, cont); // Ordena as arestas por peso

    /*printf("\nArestas ordenadas:\n"); // Imprime as arestas ordenadas por peso
    for (int i = 0; i < cont; i++) {
        printf("%d %d %d\n", arestas[i].vertices[0], arestas[i].vertices[1], arestas[i].peso);
    }*/

    int custo = kruskal(arestas, pai, rank, qtdVertices);
    printf("%d", custo);

    free(arestas);
    return 0;
}
