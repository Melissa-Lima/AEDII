#ifndef LZW_H
#define LZW_H
#include <stdlib.h>
#include <string.h>

void printa_dici(char **dicionario, int tam_dic_atual);
void printa_codigo(int codigo[], int tam_cod);
int index_silaba(char silaba[], char **dicionario, int *tam_dic_atual);
void insere_silaba(char silaba[], char **dicionario, int *tam_dic_atual);
void copia_chars(char **dicionario, char *palavra, int *tam_dic_atual);
int *lzw(char **dicionario, char *palavra, int *tam_dic_atual);

#endif