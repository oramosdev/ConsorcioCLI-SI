#ifndef RELATORIO_H
#define RELATORIO_H

#include "cotacao.h"

// Funções dos relatorios, aqui n tem muito o que explicar
void listarcots(const Cotacao *lista, int total);
void filtrarpordriver(const Cotacao *lista, int total);
void menorcot(const Cotacao *lista, int total);

#endif
