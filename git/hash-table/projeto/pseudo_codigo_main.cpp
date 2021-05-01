#include <projeto.h>
//scanf quantas palavras
//cria tabela tamanho = qtde de palavras
//for com scanf para receber as palavras
//for para colocar cada palavra na tabela hash e dentro dese mesmo for fazer a compressão de cada uma e printa

int main(int argc, char *argv[]) {

    char *palavra = (char*) malloc(sizeof(char) * STR_SIZE);
    char *chave = (char*) malloc(sizeof(char) * STR_SIZE);
    int tam_dic_atual, qtde;
    struct tipoHash tabelaHash;

    printf("Quantas palavras deseja adicioanr na tabela hash e comprimi-las?\n");
    scanf("%d", &qtde);
    tabelaHash = criar(encadeamento, qtde);
    (if(qtde < 1)){
        printf("Bye...\n");
        return 0;
    }

    for(int i = 0; i<qtde; i++){
        scanf("%c", palavra);
        
        if(strlen(palavra > STR_SIZE) {
            (if i > 0){
            i--;
            printf("A palavra deve ter no máximo 35 caracteres.\n");
        }else {
            tam_dic_atual = 0;
            inserir(encadeamento, chave, palavra);
            printf("Palavra inserida na tabela hash.\n");
            char **dicionario = (char**) malloc(sizeof(char*) * 256);
            for(int i = 0; i < 256; i++) {
                dicionario[i] = (char*) malloc(sizeof(char) * STR_SIZE);
            }
            printf("Iniciando compressão...\n");
            copia_chars(dicionario, palavra, &tam_dic_atual);
            printf("Dicionario inicial:\n");
            printa_dici(dicionario, tam_dic_atual);
            lzw(dicionario, palavra, &tam_dic_atual);
            printa_dici(dicionario, tam_dic_atual);
            for(int i = 0; i < 256; i++) {
                free(dicionario[i]);
            }
            free(dicionario);
            free(palavra);
            free(chave);
        }
    }
    return 0;
}