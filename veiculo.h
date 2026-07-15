#ifndef VEICULO_H
#define VEICULO_H

// Veiculo , com marca, modelo etc..
typedef struct {
    char  marca[50];
    char  modelo[50];
    int   ano;
    float valor_mercado;
    char  tipo;           /* pra ficar mais tranquilo, vai ser so uma letra beleza pessoal> 'P' (Passeio), 'U' (Utilitario) ou 'E' (Esportivo) */
} Veiculo;


void cadastrarveic(Veiculo *v);
void mostrarveic(const Veiculo *v);

#endif
