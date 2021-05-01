#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// NÃO ESQUECER DE INICIALIZAR TAM DIC ATUAL E ALOCAR DICIONARIO NO MAIN

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
            //printf("%c\n", dicionario[posicao][0]);
            //printf("%d", i);
            //fflush(stdout);
            //printf("%d\n", dicionario[posicao][1]);
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