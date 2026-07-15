#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "relatorio.h"
#include "utils.h"

// Lista todas as cotacoes cadastradas na memoria
void listarcots(const Cotacao *lista, int total) {
    if (total <= 0 || lista == NULL) {
        printf("\n%sNenhuma cotacao cadastrada ate o momento.%s\n\n", ANSI_COR_AMARELO, ANSI_COR_RESET);
        return;
    }

    printf("\n%s=== LISTA DE COTACOES CADASTRADAS (%d) ===%s\n", ANSI_COR_NEGRITO, total, ANSI_COR_RESET);
    for (int i = 0; i < total; i++) {
        printf("\n[Registro #%d]\n", i + 1);
        mostrarcot(&lista[i]);
    }
}

// Filtra as cotacoes buscando pelo nome do condutor
void filtrarpordriver(const Cotacao *lista, int total) {
    if (total <= 0 || lista == NULL) {
        printf("\n%sNao existem cotacoes cadastradas para realizar a busca.%s\n\n", ANSI_COR_AMARELO, ANSI_COR_RESET);
        return;
    }

    char busca[80];
    printf("\nDigite o nome (ou parte dele) do condutor para buscar: ");
    lerstr(busca, sizeof(busca));

    // Converter o termo de busca para minusculo para busca case-insensitive
    char busca_lower[80];
    int len_busca = 0;
    while (busca[len_busca] && len_busca < 79) {
        busca_lower[len_busca] = tolower((unsigned char)busca[len_busca]);
        len_busca++;
    }
    busca_lower[len_busca] = '\0';

    int encontrados = 0;
    printf("\n%s=== RESULTADOS PARA A BUSCA '%s' ===%s\n", ANSI_COR_NEGRITO, busca, ANSI_COR_RESET);

    for (int i = 0; i < total; i++) {
        // Converter o nome do condutor atual para minusculo
        char nome_lower[80];
        int len_nome = 0;
        while (lista[i].condutor.nome[len_nome] && len_nome < 79) {
            nome_lower[len_nome] = tolower((unsigned char)lista[i].condutor.nome[len_nome]);
            len_nome++;
        }
        nome_lower[len_nome] = '\0';

        // Verificar se contem o termo de busca
        if (strstr(nome_lower, busca_lower) != NULL) {
            printf("\n[Registro #%d]\n", i + 1);
            mostrarcot(&lista[i]);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("%sNenhuma cotacao encontrada para o condutor '%s'.%s\n", ANSI_COR_VERMELHO, busca, ANSI_COR_RESET);
    } else {
        printf("%sTotal de registros encontrados: %d%s\n", ANSI_COR_VERDE, encontrados, ANSI_COR_RESET);
    }
    printf("\n");
}

// Exibe a cotacao com o menor valor de premio anual
void menorcot(const Cotacao *lista, int total) {
    if (total <= 0 || lista == NULL) {
        printf("\n%sNenhuma cotacao cadastrada.%s\n\n", ANSI_COR_AMARELO, ANSI_COR_RESET);
        return;
    }

    int indice_menor = 0;
    for (int i = 1; i < total; i++) {
        if (lista[i].premio_anual < lista[indice_menor].premio_anual) {
            indice_menor = i;
        }
    }

    printf("\n%s=== COTACAO COM O MENOR VALOR DO SEGURO ===%s\n", ANSI_COR_NEGRITO, ANSI_COR_RESET);
    printf("[Registro #%d]\n", indice_menor + 1);
    mostrarcot(&lista[indice_menor]);
}
