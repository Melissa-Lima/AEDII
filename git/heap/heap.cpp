#include "heap.h"
#include "internal.h"

// ATENCAO!!! ATENCAO!!! ATENCAO!!!
// ATENCAO!!! ATENCAO!!! ATENCAO!!!
// ATENCAO!!! ATENCAO!!! ATENCAO!!!
// --- CONSIDERE O INDICE ZERO (A[0]) A QUANTIDADE DE ELEMENTOS
// --- CONSIDERE QUE O VETOR VAI DE 1 ATE N (E NAO DE 0 ATE N-1)
// --- CONSIDERE QUE O VETOOR JA TEM UM TAMANHO SUFICIENTEMENTE GRANDE PARA A INSERCAO

void MaxHeapify (tipoChave A[], int i)
{
    // IMPLEMENTAR
    // OBS.: O indice i vai de 1 ate A[0]
    int e = 2*i;
    int d = 2*i + 1;
    int qtde_nos = A[0];
    int maior;
    int aux;

    if(e <= qtde_nos && A[e] > A[i]) {
        maior = e;
    } else {
        maior = i;
    }

    if(d <= qtde_nos && A[d] > A[maior]) {
        maior = d;
    }

    if(maior != i) {
        aux = A[i];
        A[i] = A[maior];
        A[maior] = aux;
        MaxHeapify(A,maior);
    }
}

void BuildMaxHeap(tipoChave A[])
{
    // IMPLEMENTAR
    // OBS.: Chamar a funcao MaxHeapify
    int n = A[0]/2;
    for(int i = n; i > 0; i--) {
        MaxHeapify(A,i);
    }
}

void HeapSort(tipoChave A[])
{   
    int aux, t;
    // IMPLEMENTAR
    BuildMaxHeap(A);
    t = A[0];

    for(int i = t; i >= 2; i--) {
        aux = A[1];
        A[1] = A[i];
        A[i] = aux;
        A[0]--;
        MaxHeapify(A,1); 
    }
    A[0] = t;

    // DICA: Como a funcao MaxHeapify nao tem o argumento tamanho (como nos slides),
    //       armazene o tamanho atual (t = A[0]), decremente A[0] antes de chamar
    //       MaxHeapify, entao restaure o valor A[0] = t no final.
}

tipoChave HeapMaximum(tipoChave A[])
{
    // IMPLEMENTAR
    // OBS.: Nao esqueca que o primeiro elemento eh o A[1]
    return A[1];
}

tipoChave HeapExtractMax(tipoChave A[])
{
    // IMPLEMENTAR
    // OBS.: Nao precisa tratar o caso do vetor vazio!
    int max = A[1];
    A[1] = A[A[0]];
    A[0]--;
    MaxHeapify(A,1);
	return max;
}

void HeapIncreaseKey(tipoChave A[], int i, tipoChave key)
{
    // IMPLEMENTAR
    // OBS.: Nao precisa tratar o caso da chave alterada for menor que a chave atual!
    int aux;
    int parent = (int)i/2;
    A[i] = key;
    
    while(i > 1 && A[parent] < A[i]) {
        aux = A[i];
        A[i] = A[parent];
        A[parent] = aux;
        i = (int)i/2;
        parent = (int)i/2;
    }
}

void MaxHeapInsert(tipoChave A[], tipoChave key)
{
    // IMPLEMENTAR
    // OBS.: Nao esquecer de aumentar a quantidade de elementos, ou seja, A[0]++
    A[0]++;
    A[A[0]] = -2147483648;
    HeapIncreaseKey(A, A[0], key);
}
