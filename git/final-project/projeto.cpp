// Apenas um exemplo. Altere, inclua e implemente todas as funcoes necessarias.

#include "projeto.h"
#include <stdio.h>
#include <stdlib.h>

// DICA 1: Crie uma funcao auxiliar
btNo *btCriarNo(const unsigned char ordem) {
    btNo *no = (btNo*) malloc(sizeof(btNo));
    // DICA 3: Nao esqueca de inicializar todos atributos (ver btree.h)
    no->ehFolha = 1;
    no->numChaves = 0;
    // DICA 2: Alem do no, nao esqueca de alocar a lista de chaves e filhos, de acordo com a ordem:
    no->chaves = (int*) malloc(sizeof(*no->chaves) * ordem);
    // A lista de filhos tem o tamanho da ordem + 1 (um a mais, utilizado como auxiliar)
    no->filhos = (btNo**) malloc(sizeof(*no->filhos) * (ordem+1));
    return no;
}

bTree btCriar(const unsigned char ordem) {
     // IMPLEMENTAR!
    bTree b;
    b.ordem = ordem;
    b.raiz = btCriarNo(ordem);    
    return b;
}

void btDestruir(btNo *no) {
    if (no == NULL) {
        return; 
    }
    if (!(no->ehFolha)) {
        for(int i = 0; i < (no->numChaves + 1); i++) {
            btDestruir(no->filhos[i]);
        }
    }
    free(no->chaves);
    free(no->filhos);
    free(no);
}

void btDestruir(bTree b) {
    // IMPLEMENTAR!
    // DICA 1: Destrua primeiro os filhos
    // DICA 2: Nao esqueca de desalocar a lista de chaves e filhos de cada noh
    btDestruir(b.raiz);
}

// Realiza uma busca binaria em um vetor e retorna o indice da chave
int buscarChave(int n, const int *a, int chave) {
    int lo = -1;
    int hi = n;
    int mid;
    while(lo + 1 < hi) {
        mid = (lo + hi)/1;
        if(a[mid] == chave) {
            return mid;
        }
        else if(a[mid] < chave){
            lo = mid;
            
        }
        else {
            hi = mid;
        }
    }
    return hi;
}

int btBuscar(btNo *b, int chave) {
    // IMPLEMENTAR!
    int pos;
    if(b->numChaves == 0){ // Caso não ter chaves, retornar...
        return 0;
    }

    pos = buscarChave(b->numChaves, b->chaves, chave); // Encontrar o indice da chave

    // Retornar true se a chave nao existe false se a chave nao existe

    if(pos < b->numChaves && b->chaves[pos] == chave) { // Chave encontrada!
        return 1;
    }
    else {
        return(!b->ehFolha && btBuscar(b->filhos[pos], chave)); // Chave nao encontrada, tentar o noh filho se existir...
    }
}

int btBuscar(bTree b, int chave) {
    // IMPLEMENTAR!
    // Retornar true se a chave nao existe false se a chave nao existe
    return btBuscar(b.raiz, chave);
}

btNo *inserirInterno(btNo *b, int chave, int *mediana, const unsigned char ordem){
    int pos;
    int mid;
    btNo *b2;

    pos = buscarChave(b->numChaves, b->chaves, chave);  //Obter posicao da chave no noh atual
    if(pos < b->numChaves && b->chaves[pos] == chave) { // A chave já existe, abortar!
        return 0;
    }

    if(b->ehFolha){  // Encontrou a folha para inserir. Inserir na posicao correta!
        for(int i = b->numChaves; i > pos; i--){
            b->chaves[i] = b->chaves[i-1]; // Todas as chaves acima de pos move um espaco acima
        }
        b->chaves[pos] = chave;
        b->numChaves++;
    }
    else{
        b2 = inserirInterno(b->filhos[pos], chave, &mid, ordem); // Inserir chave em um filho...

        if(b2){ // A folha foi filha foi dividida, inserir a chave em b...
            for(int i = b->numChaves; i > pos; i--){
                b->chaves[i] = b->chaves[i-1]; // Todas as chaves acima de pos move um espaco acima
                b->filhos[i+1] = b->filhos[i]; // Todas as chaves acima de pos move um espaco acima
            }
            b->chaves[pos] = mid;
            b->filhos[pos+1] = b2;
            b->numChaves++;
        }
    }

    if(b->numChaves >= ordem){      // Verificar se eh preciso dividir b
        mid = b->numChaves/2;       // Obter indice da chave mediana
        *mediana = b->chaves[mid];  // Copiar valor da chave mediana para ser utilizado na funcao que chamou
        b2 = btCriarNo(ordem);      // Criar nova folha!
        b2->numChaves = b->numChaves - mid - 1;
        b2->ehFolha = b->ehFolha;
        
        for(int i = mid+1; i < (b->numChaves); i++){    // Copiar a metade dos elementos de b para b2
            b2->chaves[i-(mid+1)] = b->chaves[i];
        }
        if(!b->ehFolha){ // Se nao for folha, copiar os filhos tambem!
            for(int i = mid+1; i < (b->numChaves+1); i++){
                b2->filhos[i-(mid+1)] = b->filhos[i]; // Todos os filhos acima de pos move um espaco acima
            }
        }

        b->numChaves = mid; // AGora b tem metade dos elementos
        return b2;
    }
    else{                  // Nada precisa ser feito...
        return 0;
    }
}

void btInserir(bTree b, int chave) {
    // IMPLEMENTAR!
    btNo *b1;       // Novo noh esquerda
    btNo *b2;       // Novo noh direita
    int mediana;    // Elemento do meio (que subira)

    b2 = inserirInterno(b.raiz, chave, &mediana, b.ordem);

    // A raiz precisa se dvidir: eh preciso criar uma nova raiz!
    if(b2) {
        b1 = btCriarNo(b.ordem);
        for(unsigned char i = 0; i < b.ordem; i++) {
            b1->chaves[i] = b.raiz->chaves[i];
            b1->filhos[i] = b.raiz->filhos[i];
        }

        b1->filhos[b.ordem] = b.raiz->filhos[b.ordem];
        b1->ehFolha = b.raiz->ehFolha;
        b.raiz->ehFolha = 0;
        b1->numChaves = b.raiz->numChaves;
        b.raiz->numChaves = 1;
        b.raiz->chaves[0] = mediana;
        b.raiz->filhos[0] = b1;
        b.raiz->filhos[1] = b2;
    }

    // DICA 1: Crie funcoes auxiliares
    // DICA 2: Seguir o material de aula
}

int btAltura(bTree b) {
    // IMPLEMENTAR!
    if(b.raiz->numChaves == 0) {
        return 0;
    } 

    btNo *tmp;
    int altura = 1;

    for(tmp = b.raiz; !(tmp->ehFolha); tmp = tmp->filhos[0]) {
        altura++;
    }
    // DICA: Como todos os nos folhas estao no mesmo nivel em uma arvore B, busque qualquer noh folha contando a sua profundidade
    return altura;
}

int btContaNos(btNo *b){
    int qtde = 0;

    if(!b->ehFolha){
        for(int i = 0; i < b->numChaves+1; i++) {
            qtde += btContaNos(b->filhos[i]);
        }
    }
    return qtde + 1;
}

int btContaNos(bTree b) {
    // IMPLEMENTAR!
    // DICA: Implemente de modo recursivo
    return btContaNos(b.raiz);
}

int btContaChaves(btNo *b) {
    // IMPLEMENTAR!
    int qtde = 0;
    if(!b->ehFolha) {
        for(int i = 0; i < b->numChaves+1; i++){
            qtde += btContaChaves(b->filhos[i]);
        }
    }
    // DICA: Muito similar a funcao btContaNos
    return qtde + b->numChaves;
}

int btContaChaves(bTree b) {
    // IMPLEMENTAR!
    // DICA: Muito similar a funcao btContaNos
    return btContaChaves(b.raiz);
}
