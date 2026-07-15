#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "relatorio.h"
#include "utils.h"

static int contem_substring_insensivel(const char *texto, const char *busca) {
    char texto_low[100];
    char busca_low[100];
    int i;
    for (i = 0; texto[i] != '\0' && i < 99; i++) {
        texto_low[i] = (char)tolower((unsigned char)texto[i]);
    }
    texto_low[i] = '\0';

    for (i = 0; busca[i] != '\0' && i < 99; i++) {
        busca_low[i] = (char)tolower((unsigned char)busca[i]);
    }
    busca_low[i] = '\0';

    return strstr(texto_low, busca_low) != NULL;
}

// listar as cotações ( const so le dados ok )
void listarcots(const Cotacao *lista, int total) {
    if (total == 0 || lista == NULL) { // essas barra ai é ou ok
        printf("\n%sNenhuma cotaçao cadastrada no sistema.%s\n", ANSI_COR_AMARELO, ANSI_COR_RESET);
        return;
    }

    printf("\n=== Relatorio das cotações atualizado (%d) ===\n", total);
    for (int i = 0; i < total; i++) {
        printf("\nCotacao #%d:\n", i + 1);
        mostrarcot(&lista[i]);
    }
}

// puxar as cota com o nome do motorista
void filtrarpordriver(const Cotacao *lista, int total) {
    if (total == 0 || lista == NULL) {
        printf("\n%sNenhuma cotaçao cadastrada no sistema.%s\n", ANSI_COR_AMARELO, ANSI_COR_RESET);
        return;
    }

    char busca[80];
    printf("\nDigite o nome para buscar: ");
    lerstr(busca, sizeof(busca));

    if (strlen(busca) == 0) {
        printf("%sBusca vazia. Cancelado.%s\n", ANSI_COR_AMARELO, ANSI_COR_RESET);
        return;
    }

    int encontrados = 0;
    printf("\n=== Resultados da Busca: '%s' ===\n", busca);

    for (int i = 0; i < total; i++) {
        if (contem_substring_insensivel(lista[i].condutor.nome, busca)) {
            printf("\nCotacao #%d (Posicao %d):\n", encontrados + 1, i + 1);
            mostrarcot(&lista[i]);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("%sNenhum condutor encontrado com o nome '%s'.%s\n", ANSI_COR_AMARELO, busca, ANSI_COR_RESET);
    } else {
        printf("\n%sTotal de %d cotacao(oes) encontrada(s).%s\n", ANSI_COR_VERDE, encontrados, ANSI_COR_RESET);
    }
}

// mostra a cotacao com menor valor de premio anual
void menorcot(const Cotacao *lista, int total) {
    if (total == 0 || lista == NULL) {
        printf("\n%sNenhuma cotacao cadastrada no sistema.%s\n", ANSI_COR_AMARELO, ANSI_COR_RESET);
        return;
    }

    int indice_menor = 0;
    float menor_premio = lista[0].premio_anual;

    // pega o menor valor
    for (int i = 1; i < total; i++) {
        if (lista[i].premio_anual < menor_premio) {
            menor_premio = lista[i].premio_anual;
            indice_menor = i;
        }
    }

    printf("\n=== Cotacao de Menor Valor ===\n");
    printf("Posicao na lista: #%d\n", indice_menor + 1);
    mostrarcot(&lista[indice_menor]);
}
