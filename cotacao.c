#include <stdio.h>
#include <time.h>
#include "cotacao.h"
#include "utils.h"

// issoa qui é importante, são as regras, talvez ele vai perguntar 

// pega a data do PC no formato dia/mes/ano
void pegardata(char *buf_data) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(buf_data, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

// faz a conta do seguro aplicando as regras
void calc_cotacao(Cotacao *c) {
    float taxa_base = 0.04f; // 4.0%
    float acrescimos = 0.0f;
    float descontos = 0.0f;

    // se o carro tiver ate 3 anos de uso soma +1.5%
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int ano_atual = tm.tm_year + 1900;
    int idade_veiculo = ano_atual - c->veiculo.ano;
    if (idade_veiculo <= 3) {
        acrescimos += 0.015f;
    }

    // se for jovem (tiver menos q 25 ) soma +2%, se for idoso (mais q 65 anos ) soma +1%
    if (c->condutor.idade < 25) {
        acrescimos += 0.02f;
    } else if (c->condutor.idade >= 65) {
        acrescimos += 0.01f;
    }

    // soma +1.5% por sinistro ate o maximo de 3 ( sinistro é tipo batida essas coisas )
    int sinistros_considerados = c->condutor.sinistros;
    if (sinistros_considerados > 3) {
        sinistros_considerados = 3;
    }
    acrescimos += (sinistros_considerados * 0.015f);

    // CNH C ganha -0.5% de desconto
    if (c->condutor.cnh == 'C') {
        descontos += 0.005f;
    }

    // calcula a taxa total e o premio base do seguro
    float taxa_total = taxa_base + acrescimos - descontos;
    float premio_base = c->veiculo.valor_mercado * taxa_total;

    // se o carro for esportivo multiplica o valor final por 1.4
    if (c->veiculo.tipo == 'E') {
        c->premio_anual = premio_base * 1.4f;
    } else {
        c->premio_anual = premio_base;
    }

    // divide por 12 pra ver o valor por mes
    c->premio_mensal = c->premio_anual / 12.0f;
}

// junta o cadastro do carro, motorista e calcula a cotacao
void cadastrarcot(Cotacao *c) {
    cadastrarveic(&(c->veiculo));
    cadastrarcond(&(c->condutor));

    calc_cotacao(c);
    pegardata(c->data);
    
    printf("\n%sCotacao calculada em %s!%s\n", ANSI_COR_VERDE, c->data, ANSI_COR_RESET);
}

// mostra na tela
void mostrarcot(const Cotacao *c) {
    printf("-------------------------------------------\n");
    printf("%sCOTACAO - DATA: %s%s\n", ANSI_COR_NEGRITO, c->data, ANSI_COR_RESET);
    printf("--------------------------------------------------\n");
    printf("%sDADOS DO VEICULO:%s\n", ANSI_COR_NEGRITO, ANSI_COR_RESET);
    mostrarveic(&(c->veiculo));
    
    printf("--------------------------------------------------\n");
    printf("%sPERFIL DO CONDUTOR:%s\n", ANSI_COR_NEGRITO, ANSI_COR_RESET);
    mostrarcond(&(c->condutor));
    
    printf("--------------------------------------------------\n");
    printf("%sVALORES DO SEGURO:%s\n", ANSI_COR_NEGRITO, ANSI_COR_RESET);
    printf("  %sPremio Anual: %s R$ %.2f\n", ANSI_COR_VERDE, ANSI_COR_RESET, c->premio_anual);
    printf("  %sPremio Mensal:%s R$ %.2f\n", ANSI_COR_VERDE, ANSI_COR_RESET, c->premio_mensal);
    printf("-------------------------------------------\n");
}
