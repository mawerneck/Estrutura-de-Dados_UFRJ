#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b){
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int T[], int size){
    int L = 0;
    int R = size - 1;
    while(L < R){
        if(T[L+1] <= T[L]){
            swap(&T[L+1], &T[L]);
            L++;
        }
        else if(T[L] < T[R]) {R--;}
        else {swap(&T[L+1], &T[R]);}
    }
    return L;
    
}

int qs(int T[], int size, int k){
    
    int p = partition(T, size);
    
    if(p == k) return T[p];
    else if(k < p) return qs(T, p, k);
    else return qs(T + p + 1, size - (p + 1), k - (p + 1));
}

int main(int argc, char *argv[]) {

    if (argc != 3) return -1;
    
    int *arr = malloc(sizeof(int) * 10) ;
    int index = atoi(argv[2]) - 1;
    int i = 0, max = 10;
    int numero;
    
    while(scanf("%d", &numero) == 1){
        if(i >= max){
            max += max/2;
            int *temp = realloc(arr, sizeof(int) * max);
            if(temp == NULL){
                printf("Erro: Alocação de memória mal-sucedida.\n");
                free(arr);
                return 1;
            }
            else arr = temp;
        }
        arr[i] = numero;
        i++;
    }
    printf("%d", qs(arr, i, index));
    free(arr);
    return 0;
}



