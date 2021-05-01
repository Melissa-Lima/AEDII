#ifndef PROJETO_H
#define PROJETO_H
#include <stdlib.h>
#include <string.h>


#define STR_SIZE 35 // Tamanho maximo da chave e do valor (que eh do tipo string)

// Tres tipos de hash, o primeiro jah esta implementado
typedef enum
{
    semColisao,
    encadeamento,
    aberto
} modoHash;

// Estrutura utilizada no hash semColisao e aberto
struct hashAberto
{
    char chave[STR_SIZE];
    char valor[STR_SIZE];
    bool excluido; // Utilizado para encontrar uma chave em hash com encadeamento aberto
};

// Estrutura da lista ligada
struct listaEncadeada
{
    char chave[STR_SIZE];
    char valor[STR_SIZE];
    listaEncadeada *proximo;
};

// Estrutura utilizada no hash com encadeamento externo
struct hashEncadeada
{
    listaEncadeada *primeiro;
};

// Estrutura principal do hash
struct tipoHash
{
    union
    { // A estrutura union permite 'selecionar' a estrutura da tabela que sera utilizada
        hashEncadeada *encadeada;
        hashAberto *aberto;
    } tabela;
    int tamanho;   // Tamanho da tabela hash
    modoHash modo; // Modo de operacao da tabela hash: semColisao, encadeamento, aberto
};

// Funcao que transforma a chave em um indice da tabela
int hash(char chave[STR_SIZE], int tamanho, int tentativa = 0);

tipoHash criar(modoHash modo, int tamanho); // Inicializa uma tabela hash
void destruir(tipoHash hash);               // Libera da memoria toda a tabela

void inserir(tipoHash hash, char chave[STR_SIZE], char valor[STR_SIZE]);
char *buscar(tipoHash hash, char chave[STR_SIZE]);
void apagar(tipoHash hash, char chave[STR_SIZE]);
int quantidade(tipoHash hash); // Retorna a quantidade de elementos

void printa_dici(char **dicionario, int tam_dic_atual);
void printa_codigo(int codigo[], int tam_cod);
int index_silaba(char silaba[], char **dicionario, int *tam_dic_atual);
void insere_silaba(char silaba[], char **dicionario, int *tam_dic_atual);
void copia_chars(char **dicionario, char *palavra, int *tam_dic_atual);
int *lzw(char **dicionario, char *palavra, int *tam_dic_atual);

#endif