#include "projeto.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    

    char *palavra = (char*) malloc(sizeof(char) * 35);
    int tam_dic_atual, qtde;
    int chave;
    int i;

    printf("Quantas palavras deseja adicionar na tabela hash e comprimi-las?\n");
    scanf("%d", &qtde);
    tipoHash tabelaHash = criar(encadeamento, qtde);
    if(qtde < 1){
        printf("Bye...\n");
        return 0;
    }

    for(i = 0; i<qtde; i++){
        printf("Digite a palavra %d\n",i);
        scanf("%s", palavra);
        
        if(strlen(palavra) > 35){
            i--;
            printf("A palavra pode ter no máximo 35 caracteres.");
        }else{
            tam_dic_atual = 0;
            chave = hash(palavra, STR_SIZE);
            inserir(tabelaHash, palavra, palavra);
            printf("Palavra inserida na tabela hash. Chave = %d\n", chave);

            char **dicionario = (char**) malloc(sizeof(char*) * 256);

            for(int i = 0; i < 256; i++) {
                dicionario[i] = (char*) malloc(sizeof(char) * 35);
            }
            printf("Dicionario inicial:\n");
            printa_dici(dicionario, tam_dic_atual);
            printf("Iniciando compressão...\n");
            copia_chars(dicionario, palavra, &tam_dic_atual);
            lzw(dicionario, palavra, &tam_dic_atual);
            for(int i = 0; i < 256; i++) {
                free(dicionario[i]);
            }
            free(dicionario);
            free(palavra);
        }
    }
    return 0;
}

/*int main(int argc, char *argv[]) {
    
    char *palavra = (char*) malloc(sizeof(char) * 35);
    int tam_dic_atual;
    //int codigo[5];
    printf("Digite a palavra e/ou frase que deseja adicionar na tabela hash.\n");
    //fgets(palavra, 35, stdin);
    scanf("%s", palavra);
    printf("%s\n", palavra);
        //printf("Digite a palavra e/ou frase que deseja comprimir e digite enter para inicializar a compressão.\n");
    tam_dic_atual = 0;
    char **dicionario = (char**) malloc(sizeof(char*) * 256);
    for(int i = 0; i < 256; i++) {
        dicionario[i] = (char*) malloc(sizeof(char) * 35);
    }        
        //printf("%s",palavra);
        copia_chars(dicionario, palavra, &tam_dic_atual);
        printf("Dicionario inicial:\n");
        printa_dici(dicionario, tam_dic_atual);
        //printa_dici(dicionario, tam_dic_atual);
        lzw(dicionario, palavra, &tam_dic_atual);
        printa_dici(dicionario, tam_dic_atual);
        for(int i = 0; i < 256; i++) {
            free(dicionario[i]);
        }
        free(dicionario);
        free(palavra);
        // adiciona o codigo na tabela hash
    return 0;
}
*/