#include <stdio.h>
#include <stdlib.h>
#include "arquivo.h"
#include "utils.h"

// salva a quantidade de cotas e o array no binario que estamos usando de db
int salvarcots(const Cotacao *lista, int total, const char *arq) {
    FILE *file = fopen(arq, "wb");
    if (file == NULL) {
        printf("%sNão consegui abrir o arquivo!%s\n", ANSI_COR_VERMELHO, ANSI_COR_RESET);
        return 0;
    }

    // isso aqui so escreve o total de cotações la dentro
    fwrite(&total, sizeof(int), 1, file);

    // escreve o bloco completo de dados
    if (total > 0 && lista != NULL) {
        size_t itens_gravados = fwrite(lista, sizeof(Cotacao), total, file);
        if (itens_gravados != (size_t)total) {
            printf("%sfalha pra salvar%s\n", ANSI_COR_VERMELHO, ANSI_COR_RESET);
            fclose(file);
            return 0;
        }
    }

    fclose(file);
    return 1;
}

// abre o arquivo, aloca memoria e carrega
int carregarcots(Cotacao **lista, int *total, int *cap, const char *arq) {
    FILE *file = fopen(arq, "rb");
    
    // aqui é so uma validação, pra caso n encontrar o arquivo
    if (file == NULL) {
        *lista = NULL;
        *total = 0;
        *cap = 0;
        return 1;
    }

    // le a quantidade salva no arquivo
    int count = 0;
    if (fread(&count, sizeof(int), 1, file) != 1) {
        *lista = NULL;
        *total = 0;
        *cap = 0;
        fclose(file);
        return 1; 
    }

    if (count <= 0) {
        *lista = NULL;
        *total = 0;
        *cap = 0;
        fclose(file);
        return 1;
    }

    // aloca memoria  malloc
    Cotacao *temp = (Cotacao *)malloc(count * sizeof(Cotacao));
    if (temp == NULL) {
        printf("%sFalha de memoria%s\n", ANSI_COR_VERMELHO, ANSI_COR_RESET);
        fclose(file);
        return 0;
    }

    // pega as cotas direto pra nossa memoria
    size_t itens_lidos = fread(temp, sizeof(Cotacao), count, file);
    if (itens_lidos != (size_t)count) {
        printf("%sNão consegui ler os dados, veja se ta tudo ok com o arquivo%s\n", ANSI_COR_VERMELHO, ANSI_COR_RESET);
        free(temp);
        *lista = NULL;
        *total = 0;
        *cap = 0;
        fclose(file);
        return 0;
    }

    // atualiza
    *lista = temp;
    *total = count;
    *cap = count;

    fclose(file);
    return 1;
}
