#ifndef COTACAO_H
#define COTACAO_H

#include "veiculo.h"
#include "condutor.h"

// Estrutura da Cotacao fixa
typedef struct {
    Veiculo  veiculo;
    Condutor condutor;
    float    premio_anual;
    float    premio_mensal;
    char     data[11];    /* aqui so pra vcs n se perderem, é o formato dia/mes/ano */
} Cotacao;

// Funcoes de cotacao , tambem n tem muito oq explicar
void pegardata(char *buf_data);
void calc_cotacao(Cotacao *c);
void cadastrarcot(Cotacao *c);
void mostrarcot(const Cotacao *c);

#endif
