#include "projeto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Funcao hash. Retorna o indice de uma chave na tabela. Nao alterar!
int hash(char chave[STR_SIZE], int tamanho, int tentativa) {
    int h = chave[0];
    for (int i = 1; chave[i] != '\0'; i++)
        h = (h * 251 * chave[i]) % tamanho;
    return (h + tentativa) % tamanho;
}

tipoHash criar(modoHash m, int t) {
    tipoHash h;
    h.tamanho = t;
        h.tabela.encadeada = (hashEncadeada*) malloc(sizeof(hashEncadeada) * t);
        for (int i = 0; i < t; i++){
            h.tabela.encadeada[i].primeiro = NULL;
        }
    return h;
}

void destruirEncadeadaInterno(listaEncadeada *l){
    if(l->proximo != NULL){
        destruirEncadeadaInterno(l->proximo);
        free(l->proximo);
    }
}

void destruir(tipoHash h) {
  switch (h.modo) {
    case semColisao:
        free(h.tabela.aberto);
        h.tabela.aberto = NULL;
        break;
    case encadeamento: {
       for(int i = 0; i<h.tamanho; i++) {
            if(h.tabela.encadeada[i].primeiro != NULL) {
                destruirEncadeadaInterno(h.tabela.encadeada[i].primeiro);
                free(h.tabela.encadeada[i].primeiro);
            }
        }
        free(h.tabela.encadeada);
        break;
    }
    case aberto:
        free(h.tabela.aberto);
        h.tabela.aberto = NULL;
        break;
    }
}

void inserir(tipoHash h, char c[STR_SIZE], char v[STR_SIZE]) {
    int idx = hash(c, h.tamanho);
    switch (h.modo) {
    case semColisao:
        strcpy(h.tabela.aberto[idx].chave, c);
        strcpy(h.tabela.aberto[idx].valor, v);
        break;

    case encadeamento: {
        // IMPLEMENTAR!!!
        // Sugiro incluir no final da lista, mas pode ser inserido em qualquer ponto.
        // Eh preciso alocar a estrutura listaEncadeada para cada elemento inserido.
        listaEncadeada *newElem = (listaEncadeada *)malloc(sizeof(listaEncadeada));
        listaEncadeada *temp = h.tabela.encadeada[idx].primeiro;

        // Criando o novo nó
        strcpy(newElem->chave, c);
        strcpy(newElem->valor, v);
        newElem->proximo = NULL;

        // Colocando o novo nó no primeiro lugar que ele achar
        if(h.tabela.encadeada[idx].primeiro == NULL) { 
            h.tabela.encadeada[idx].primeiro = newElem;
        }else {
            while(temp->proximo != NULL) {
                temp = temp->proximo;
            }
            temp->proximo = newElem;
        }
        break;
    } 
    
    case aberto:
        // IMPLEMENTAR!!!
        // DICA: Eh utilizado encadeamento aberto linear. Utilize as tentativas conforme mostrado abaixo.
        for (int tentativa = 0; tentativa < h.tamanho; tentativa++) {
            // DICA: Use uma verificacao como h.tabela.aberto[idx].chave[0] == '\0' para saber se a celula esta vazia
            idx = hash(c, h.tamanho, tentativa);
            if(h.tabela.aberto[idx].chave[0] == '\0') {
                strcpy(h.tabela.aberto[idx].chave, c);
                strcpy(h.tabela.aberto[idx].valor, v);
                // DICA: Nao esquecer de atualizar o atributo excluido
                h.tabela.aberto[idx].excluido = false;
                break;
            }
        }
        break;
    }
}

char *buscar(tipoHash h, char c[STR_SIZE]) {
    int idx = hash(c, h.tamanho);
    switch (h.modo) {
    case semColisao:
        return strcmp(h.tabela.aberto[idx].chave, c) == 0 ? h.tabela.aberto[idx].valor : NULL;

    case encadeamento:{
        listaEncadeada *temp = h.tabela.encadeada[idx].primeiro;

        while(temp != NULL && strcmp(temp->chave, c) != 0) {
            temp = temp->proximo;
        }
        if(temp == NULL) {
            return NULL;
        }
        return temp->valor;
    }

    case aberto:
        for(int tentativa = 0; tentativa < h.tamanho; tentativa++) {
            idx = hash(c, h.tamanho, tentativa);

            if(strcmp(h.tabela.aberto[idx].chave, c) == 0) {
                return h.tabela.aberto[idx].valor;
            }else if(h.tabela.aberto[idx].chave[0] == '\0' && !h.tabela.aberto[idx].excluido) {
                break;
            }
        }
        return NULL;
    }
    return NULL;
}

void apagar(tipoHash h, char c[STR_SIZE]) {
    int idx = hash(c, h.tamanho);
    switch (h.modo) {
    case semColisao:
        if (strcmp(h.tabela.aberto[idx].chave, c) == 0)
            h.tabela.aberto[idx].chave[0] = h.tabela.aberto[idx].valor[0] = '\0';
        break;

     case encadeamento:{
        // IMPLEMENTAR!!!
        if(h.tabela.encadeada[idx].primeiro == NULL) break;

        listaEncadeada *aux = h.tabela.encadeada[idx].primeiro;
        listaEncadeada *remover;

        if(strcmp(h.tabela.encadeada[idx].primeiro->chave, c) == 0) {
            remover = h.tabela.encadeada[idx].primeiro;
            h.tabela.encadeada[idx].primeiro = h.tabela.encadeada[idx].primeiro->proximo;
            free(remover);
        }else {
            while(aux->proximo != NULL && strcmp(aux->proximo->chave, c) != 0) {
                aux = aux->proximo;
            }

            if(aux->proximo != NULL) {
                remover = aux->proximo; 
                aux->proximo = aux->proximo->proximo;
                free(remover);
            }
        }
        break;
    }
        case aberto:
        for (int tentativa = 0; tentativa < h.tamanho; tentativa++) {
            idx = hash(c, h.tamanho, tentativa);
            if(strcmp(h.tabela.aberto[idx].chave, c) == 0){
                h.tabela.aberto[idx].excluido = true;
                h.tabela.aberto[idx].chave[0] = '\0';
                break;
            }
        }
        break;
    }
}

int qtdEncadeadaInterno(listaEncadeada *l) {
    if(l->proximo == NULL){
        return 1;
    }
    return 1 + (qtdEncadeadaInterno(l->proximo));
}

int quantidade(tipoHash h) {
    int qtd = 0;
    switch (h.modo) {
    case semColisao:
    case aberto: // Igual ao semColisao, portanto, jah implementado!!!
        for (int i = 0; i < h.tamanho; i++) {
            if (h.tabela.aberto[i].chave[0] != '\0') {
                qtd++;
            }
        }

        break;

    case encadeamento:
        for(int i = 0; i< h.tamanho; i++) {
            if(h.tabela.encadeada[i].primeiro != NULL) {
                qtd += qtdEncadeadaInterno(h.tabela.encadeada[i].primeiro);
            }
        }
        break;
    }
    return qtd;
}

/*
Printa o dicionario inteiro
Entrada: dicionario e tamanho atual do dicionario
Saida: void */
void printa_dici(char **dicionario, int tam_dic_atual) {
    for(int i = 0; i < tam_dic_atual; i++) {
        printf("%s",dicionario[i]);
    }
    printf("\n");
}

/*
Printa a compressao inteira
Entrada: dicionario e tamanho atual da compressao
Saida: void */
void printa_codigo(int codigo[], int tam_cod) {
    printf("Compressao ate o momento:");
    for(int i=0; i<tam_cod; i++) {
        printf("%d ", codigo[i]);
    }
    printf("\n");
}

/* 
Retorna o indice da silaba a ser procurada.
Entrada: silaba a ser procurada, dicionario e tamanho atual do dicionario.
Saida: indice de onde a silaba se encontra ou -1 se não existir no dicionario. */
int index_silaba(char silaba[], char **dicionario, int *tam_dic_atual) {
    for(int i = 0; i < *tam_dic_atual; i++) {
        if(strcmp(dicionario[i],silaba) == 0) { //ver como verifica o conteudo do conteudo do dicionario '-'
            return i;
        }
    }
    return -1;
}

/* 
Insere uma nova silaba no dicionario
Entrada: silaba a ser inserida, dicionario e tamanho atual do dicionario.
Saida: void (apenas altera o dicionario)*/
void insere_silaba(char silaba[], char **dicionario, int *tam_dic_atual) {
    strncpy(dicionario[*tam_dic_atual], silaba, strlen(silaba));
    (*tam_dic_atual)++;
}

/* Insere cada caractere (sem repetição) no dicionario
Entrada: Dicionario e palavara. 
Saida: void (dicionario e alterado)*/
void copia_chars(char **dicionario, char *palavra, int *tam_dic_atual) {
    int posicao = 0;
    int caracteres[256] = {0};

    // laco para verificar quais caracteres estao presentes na palavra
    for(int i = 0; i < strlen(palavra); i++) {
        caracteres[palavra[i]]++;
    }

    // laco para copiar para o dicionario cada caractere presente na palavra, sem repeticoes
     for(int i = 0; i < 256; i++) {
        if(caracteres[i] != 0) {
            //colocando o caractere no dicionario
            dicionario[posicao][0] = (char)i;
            // coloca o caractere nulo no final (pois o dicionario contem palavra, não caracteres)
            dicionario[posicao][1] = '\0';
            posicao++;
            (*tam_dic_atual)++;
        }
    }
}

/* 
Funcao LZW: 
Entrada: dicionario, palavra a ser comprimida, quantas letras foram analisadas ate o momento (0 inicialmente no main) 
e tamanho da palavra.  
Saida: endereco do vetor com codigo de saida no formato array de int ([1,2,3,0,1])*/
int *lzw(char **dicionario, char *palavra, int *tam_dic_atual)  {
    int tam_palavra = strlen(palavra);
    if (tam_palavra < 1) return NULL;

    char p[5], c[5], p_plus_c[5];
    //char *p, *c, *p_plus_c;
    int indice_silaba;
    // codigo = vetor de saida (compressao), ex: [0 3 1 3 4 5]
    // tam_cod = tamanho inicial do codigo = 0
    int *codigo = (int*) malloc(35 * sizeof(int));
    int tam_cod = 0;
    
    //Iniciando c, p e p+c com caractere nulo.
    c[0] = '\0';
    p[0] = '\0';
    p_plus_c[0] = '\0';
    /*strcpy(p, "");
    strcpy(c, "");
    strcpy(p_plus_c, "");*/
    
    for(int i = 0; i < tam_palavra; i++) {
        // copiando char da palavra[i] no c
        strncpy(c, &palavra[i], 1);
        // p+c = concatenacao do p e c
        strncpy(p_plus_c, p, strlen(p)+1);
        strncat(p_plus_c, c, strlen(c));
        printf("p = %s, c = %s, p+c = %s\n",p,c,p_plus_c);

        indice_silaba = index_silaba(p_plus_c, dicionario, tam_dic_atual);

        if(indice_silaba != -1) {
            strncpy(p, p_plus_c, strlen(p_plus_c)+1);
            printf("%s ja existe no dicionario\n", p_plus_c);
        } else { 
            printf("%s nao existe no dicionario\n", p_plus_c);
            codigo[tam_cod] = index_silaba(p, dicionario, tam_dic_atual);
            insere_silaba(p_plus_c, dicionario, tam_dic_atual);
            strncpy(p, c, strlen(c)+1);
            tam_cod++;
            printa_codigo(codigo, tam_cod);
            //printa_dici(dicionario, *tam_dic_atual);
            (*tam_dic_atual)++;
        }
    }
    // retornar endereço pro vetor com o codigo final...
    
    return codigo;
    // lembrar de dar free nos aux.
}