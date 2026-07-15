#ifndef ARQUIVO_H
#define ARQUIVO_H

#include "cotacao.h"

// Funcoes para salvar e ler os dados na database
int salvarcots(const Cotacao *lista, int total, const char *arq);
int carregarcots(Cotacao **lista, int *total, int *cap, const char *arq);

#endif
