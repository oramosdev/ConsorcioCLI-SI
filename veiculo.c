#include <stdio.h>
#include <string.h>
#include <time.h>
#include "veiculo.h"
#include "utils.h"

// ver as info do veiculo e ver se ta bala
void cadastrarveic(Veiculo *v) {
    printf("\n--- Cadastro de Veiculo ---\n");

    // aqui a gente ver se a marca não ta vazia
    do {
        printf("Marca: ");
        lerstr(v->marca, sizeof(v->marca));
        if (strlen(v->marca) == 0) {
            printf("%s A marca nao pode ser vazia!%s\n", ANSI_COR_VERMELHO, ANSI_COR_RESET);
        }
    } while (strlen(v->marca) == 0);

    // mesma coisa, so que com o modelo
    do {
        printf("Modelo: ");
        lerstr(v->modelo, sizeof(v->modelo));
        if (strlen(v->modelo) == 0) {
            printf("%sO modelo nao pode ser vazio!%s\n", ANSI_COR_VERMELHO, ANSI_COR_RESET);
        }
    } while (strlen(v->modelo) == 0);

    // valida o ano de fabricacao pegando o ano do sistema
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int ano_limite = tm.tm_year + 1900 + 1;
    
    do {
        v->ano = lerint("Ano de fabricacao: ");
        if (v->ano < 1900 || v->ano > ano_limite) {
            printf("%sErro: Digite um ano entre 1900 e %d.%s\n", ANSI_COR_VERMELHO, ano_limite, ANSI_COR_RESET);
        }
    } while (v->ano < 1900 || v->ano > ano_limite);

    // vendo se o valor do carro é 0 ou menor
    do {
        v->valor_mercado = lerfloat("Valor de mercado (R$): ");
        if (v->valor_mercado <= 0) {
            printf("%sO valor deve ser maior que zero!%s\n", ANSI_COR_VERMELHO, ANSI_COR_RESET);
        }
    } while (v->valor_mercado <= 0);

    // aqui é o tipo, como falei ali em cima : P, U ou E
    do {
        v->tipo = lerchar("Tipo ((P) Passeio / (U) Utilitario / (E) Esportivo): ");
        if (v->tipo != 'P' && v->tipo != 'U' && v->tipo != 'E') {
            printf("%sTipo invalido! Digite P, U ou E.%s\n", ANSI_COR_VERMELHO, ANSI_COR_RESET);
        }
    } while (v->tipo != 'P' && v->tipo != 'U' && v->tipo != 'E');
}

// printa na tela os dados do carro bonitinho fofo
void mostrarveic(const Veiculo *v) {
    const char *tipo_extenso = "Desconhecido";
    if (v->tipo == 'P') tipo_extenso = "Passeio";
    else if (v->tipo == 'U') tipo_extenso = "Utilitario";
    else if (v->tipo == 'E') tipo_extenso = "Esportivo";

    printf("  %sMarca/Modelo:%s %s %s\n", ANSI_COR_AZUL, ANSI_COR_RESET, v->marca, v->modelo);
    printf("  %sAno:%s %d\n", ANSI_COR_AZUL, ANSI_COR_RESET, v->ano);
    printf("  %sValor de mercado:%s R$ %.2f\n", ANSI_COR_AZUL, ANSI_COR_RESET, v->valor_mercado);
    printf("  %sTipo de veiculo:%s %s (%c)\n", ANSI_COR_AZUL, ANSI_COR_RESET, tipo_extenso, v->tipo);
}
