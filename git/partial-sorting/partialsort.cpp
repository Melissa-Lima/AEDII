#include "partialsort.h"

void MinHeapify (int A[], int m, int i)
{
    // IMPLEMENTAR
    // OBS.: O indice i vai de 1 ate A[0]
    int e = 2*i;
    int d = 2*i + 1;
    int qtde_nos = A[0];
    int menor;
    int aux;

    if(e <= qtde_nos && A[e] < A[i]) {
        menor = e;
    } else {
        menor = i;
    }

    if(d <= qtde_nos && A[d] < A[menor]) {
        menor = d;
    }

    if(menor != i) {
        aux = A[i];
        A[i] = A[menor];
        A[menor] = aux;
        MinHeapify(A,m,menor);
    }
}

void BuildMinHeap(int A[], int n)
{
    // IMPLEMENTAR
    // DICA: Igual ao BuildMaxHeap, mas chama o MinHeapify
    {
    int n = (int)A[0]/2;
    for(int i = n; i >= 1; i--) {
        MinHeapify(A,A[0],i);
    }
}

}

void PartialHeapSortInverse(int A[], int n, int k)
{
// IMPLEMENTAR
// IMPORTANTE: Considere que o A[0] contem o tamanho da lista, e os elementos estao nas posicoes de 1 ate n (inclusive)
    int aux;
    int m = A[0];
    // DICA: Construa o MinHeap e insira os menores elementos no fim da lista (muito similar ao HeapSort, mas com os menores elementos)
    BuildMinHeap(A, m);
//       Lembre-se de parar com k elementos!
//       A LISTA FICARA INVERTIDA, ou seja, o menor elemento eh o ultimo, depois o penultimo... e assim por diante...
    for(int i = k; i > 0; i--){
        aux = A[1];
        A[1] = A[m];
        A[m] = aux;
        m--;
        MinHeapify(A,m,1);
    }
}

void PartialHeapSort(int A[], int n, int k) {
// IMPLEMENTAR
// IMPORTANTE: Diferente das funcoes anteriores, os elementos comecam na posicao 0, e a saida nao sera invertida
// DICA: 
//  1) Crie um novo array com tamanho n+1
    int B[n+1];
//  2) Copie todos os elementos deslocado em um para o novo array
    for(int i = 0; i <n; i++){
        B[i+1] = A[i];
    }
    B[0] = n;
//  3) Chame o PartialHeapSortInverse
    PartialHeapSortInverse(B, n, k);
//  4) Copie novamente os elementso para o array original, invertendo a ordem e iniciando na posicao 0
    for(int i = 0; i <n; i++){
        A[i] = B[n-i];
    }
}

