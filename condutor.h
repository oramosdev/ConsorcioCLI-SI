#ifndef CONDUTOR_H
#define CONDUTOR_H

// Estrutura de dados para armazenar informações sobre um condutor
typedef struct {
    char nome[80];
    char rg[6];
    int  idade;
    int  sinistros;
    char cnh;          
} Condutor;


void cadastrar_condutor(Condutor *c);
void exibir_condutor(const Condutor *c);

#endif 