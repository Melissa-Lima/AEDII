#include "trie.h"

// DICA: Estude o arquivo trie.h antes de iniciar a sua implementacao!

no *criarNo(void) {
    int i;
    no *novo = (no *)malloc(sizeof(no));

    if(novo != NULL){
        novo->tipo = 'I';
        for(i = 0; i < TAMANHO_ALFABETO; i++){
            novo->filho[i] = NULL;
        }
    }
    return novo;
}

void apagarArvore(no *raiz) {
    if(raiz != NULL){
        for(int i = 0; i < TAMANHO_ALFABETO; i++){
            if(raiz->filho[i] != NULL){
                apagarArvore(raiz->filho[i]);
            }
        }
        free(raiz);
    }
}

void adicionarPalavra(char *palavra, no *raiz) {
    int nivel, indice;
    no *tmp = raiz;

    for(nivel = 0; nivel < strlen(palavra); nivel++){
        indice = CHAR_TO_INDEX(palavra[nivel]);
        if(tmp->filho[indice] == NULL){
            tmp->filho[indice] = criarNo();
        }
        tmp = tmp->filho[indice];
    }
    tmp->tipo = 'P';
}

int buscaPalavra(char *palavra, no *raiz) {
    int i, indice;
    no *tmp = raiz;

    for(i = 0; i < strlen(palavra); i++){
        indice = CHAR_TO_INDEX(palavra[i]);

        if(tmp->filho[indice] != NULL){
            tmp = tmp->filho[indice];
        }else{
            break;
        }
    }
    if (palavra[i] == '\0' && tmp->tipo == 'P'){
        return 1;
    }
    return 0;
}

int numeroDeNos(no *r) {
    if(r != NULL){
        int tmp = 0;
        for(int i = 0; i < TAMANHO_ALFABETO; i++){
            if(r->filho[i] != NULL){
                tmp += numeroDeNos(r->filho[i]);
            }
        }
        return 1 + tmp;
    }
    return 0;
}

int numeroDePalavras(no *r) {
    if(r != NULL){
        int tmp = 0;
        for(int i = 0; i < TAMANHO_ALFABETO; i++){
            if(r->filho[i] != NULL){
                tmp += numeroDePalavras(r->filho[i]);
            }
        }
        return r->tipo == 'P' ? 1 + tmp: tmp;
    }
    return 0;
}

int altura(no *r) {
    int maiorAltura = 0;
    int filhoFlag = 0;
    if(r != NULL){
        for(int i = 0; i < TAMANHO_ALFABETO; i++){
            if(r->filho[i] != NULL) {
                filhoFlag = 1;
                int tmp = altura(r->filho[i]);
                maiorAltura = maiorAltura < tmp ? tmp: maiorAltura;
            }
        }
        return maiorAltura + filhoFlag;
    }
    return 0;
}

int quantidadeFilhos(no *r){
    int f = 0;
    for(int i = 0; i < TAMANHO_ALFABETO; i++){
        if(r->filho[i] != NULL){
            f++;
        }
    }
    return f;
}

int removerPalavra_i(int indice_palavra, char *palavra, no* r){
    if(r == NULL) return -2; 

    int status = 0;
    if(indice_palavra < strlen(palavra) -1){ // Checa se chegou ao fim da palavra
        no *prox = r->filho[CHAR_TO_INDEX(palavra[indice_palavra + 1])];
        if(prox != NULL){
            status = removerPalavra_i(indice_palavra + 1, palavra, prox); // Chamada recursiva para a próxima letra da palavra
            if(status == 1){
                free(prox);
                r->filho[CHAR_TO_INDEX(palavra[indice_palavra + 1])] = NULL;
            }
        }else{
            return -1;
        }
    }

    if(status == -1){
        return -1;  
    }


   if(quantidadeFilhos(r) > 1){ 
        if(indice_palavra == strlen(palavra) -1) r->tipo = 'I';  // caso onde a palavra é prefixo de outra
        return -1;                                               // indica que as remoções acabaram
   }else{
        return 1;                                                // indica que o a remoção deve ser feita
   }
    return 0;
}

void removerPalavra(char *palavra, no *raiz) {
    if(strcmp(palavra, "") == 0 || palavra == NULL || raiz == NULL || raiz->filho[CHAR_TO_INDEX(palavra[0])] == NULL){
        return;
    }
    
    if(removerPalavra_i(0, palavra, raiz->filho[CHAR_TO_INDEX(palavra[0])]) == 1){
        free(raiz->filho[CHAR_TO_INDEX(palavra[0])]);
        raiz->filho[CHAR_TO_INDEX(palavra[0])] = NULL;
    }
}




/* MEU CODGIO AAAAAAAAAAAA*/




#include "trie.h"

// DICA: Estude o arquivo trie.h antes de iniciar a sua implementacao!

no *criarNo(void) {
    // IMPLEMENTAR !!!
    // Dica: Aloca um no, atribua o tipo como 'I' e todos os filhos como NULL.
    int i;
    no *novo = (no *)malloc(sizeof(no));
    if (novo != NULL) {
        novo->tipo = 'I';

        for (i=0; i<TAMANHO_ALFABETO; i++){
            novo->filho[i] = NULL;
        }
     }
    return novo;
}

void apagarArvore(no *raiz) {
     // IMPLEMENTAR !!!
    if(raiz != NULL){
        // Dica 1: Desaloque todos os nos filhos e depois desaloca o no atual.
        // Dica 2: Usar recursao facilita!
        for(int i = 0; i < TAMANHO_ALFABETO; i++){
            if(raiz->filho[i] != NULL){
                apagarArvore(raiz->filho[i]);
            }
        }
        free(raiz);
    }
}


void adicionarPalavra(char *palavra, no *raiz) {
    // IMPLEMENTAR !!!
    int nivel, indice;
    no *tmp = raiz;
    // Dica 1: Use um laco iterativo de 0 ate strlen(palavra)
    for(nivel = 0; nivel < strlen(palavra); nivel++) {
    // Dica 3: Utilize a macro CHAR_TO_INDEX (ver trie.h) para converter o caractere para o indice filho
        indice = CHAR_TO_INDEX(palavra[nivel]);
    // Dica 2: Criar o no com a funcao criarNo (caso nao existir)
        if(tmp->filho[indice]==NULL) {
            tmp->filho[indice] = criarNo();
        }
        tmp = tmp->filho[indice];
    }
    tmp->tipo = 'P';
    // Dica 4: Nao esqueca de mudar o tipo para 'P' no ultimo noh que representa o ultimo caractere
}

int buscaPalavra(char *palavra, no *raiz) {
    // IMPLEMENTAR !!!
    int i, indice;
    no *tmp = raiz;
    // Dica 1: Funcao similar ao adicionarPalavra
    for(i=0; i<strlen(palavra); i++) {
        indice = CHAR_TO_INDEX(palavra[i]);

        if (tmp->filho[indice] != NULL) {
            tmp = tmp->filho[indice];
        }else {
            break;
        }
    }
     // Dica 2: Se o ultimo noh que representa o ultimo caractere for do tipo 'I', a palavra nao existe
    // IMPORTANTE:
    //   retorne 0 se a palavra nao exite
    //   retorne 1 se a palavra existir
     if(palavra[i] =='\0' && tmp->tipo == 'P') {
            return 1;
        }else {
            return 0;
    }
    return 0;
}

int numeroDeNos(no *r) {
    // IMPLEMENTAR !!!
    int qtde_no = 0;
    int i;
    // Dica: A funcao pode ser muito simples se utilizar recursao

    if(r != NULL){
        for(i = 0; i<TAMANHO_ALFABETO; i++){
            qtde_no += numeroDeNos(r->filho[i]);
        }
        qtde_no++;
    }
    return qtde_no;
}

int numeroDePalavras(no *r) {
    // IMPLEMENTAR !!!
    int i;
    int qtde_pal = 0;
    // Dica: Similar a funcao numeroDeNos, mas contabilize apenas os tipos 'P', que representa as palavras
    if(r != NULL){
        if(r->tipo == 'P'){
                qtde_pal++;
        }
        for(i=0; i<TAMANHO_ALFABETO; i++){
            qtde_pal += numeroDePalavras(r->filho[i]);
        }
    }
    return qtde_pal;
}

int altura(no *r) {
    // IMPLEMENTAR !!!
    int i;
    int aux = 0;
    int alt = 0;
    int maior_altura = 0;
    // Dica: A funcao pode ser muito simples se utilizar recursao
    if(r != NULL){
        for(i=0; i<TAMANHO_ALFABETO; i++) {
            if(r->filho[i] != NULL) {
                alt = 1;
                aux += altura(r->filho[i]);

                if(maior_altura < aux) {
                    maior_altura = aux;
                }
            }
        }
    }
    return maior_altura + alt;
}

void removerPalavra(char *palavra, no *raiz) {
    // IMPLEMENTAR !!!
    // Nota: Esta funcao eh a mais elaborada. Recomendo criar funcoes auxiliares e utilizar recursao
}
