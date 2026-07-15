#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "condutor.h"
#include "utils.h"

//leitura de dados do condutor e validação
void cadastrar_condutor(Condutor *c) {
    printf("\n> Perfil de Condutor <\n");

    // Leitura de nome vazio
    do {
        printf("Nome Completo: ");
        ler_string(c->nome, sizeof(c->nome));
        if (strlen(c->nome) == 0) {
            printf("%sO nome nao pode ser vazio!%s\n", ANSI_COR_VERMELHO, ANSI_COR_RESET);
        }
    } while (strlen(c->nome) == 0);


    //Ver os digitos e caracteres do RG, e se o tamanho é 5
    char temp_rg[100];
    int rg_valido = 0;
    do {
        printf("insira seu RG: ");
        ler_string(temp_rg, sizeof(temp_rg));
        
        if (strlen(temp_rg) != 5) {
            printf("%sO RG deve ter exatamente 5 digitos!%s\n", ANSI_COR_VERMELHO, ANSI_COR_RESET);
            continue;
        }
        
        int apenas_digitos = 1;
        for (int i = 0; i < 5; i++) {
            if (!isdigit((unsigned char)temp_rg[i])) {
                apenas_digitos = 0;
                break;
            }
        }
        
        if (!apenas_digitos) {
            printf("%sO RG deve conter apenas numeros!%s\n", ANSI_COR_VERMELHO, ANSI_COR_RESET);
        } else {
            strcpy(c->rg, temp_rg);
            rg_valido = 1;
        }
    } while (!rg_valido);


    // Validação da maioridade do condutor
    do {
        c->idade = ler_inteiro("Idade: ");
        if (c->idade < 18 || c->idade > 120) {
            printf("%so motorista tem que ser de maior de idade%s\n", ANSI_COR_VERMELHO, ANSI_COR_RESET);
        }
    } while (c->idade < 18 || c->idade > 120);


    // sinistros ( as batidas e amassados...)
    do {
        c->sinistros = ler_inteiro("Numero de sinistros nos ultimos 3 anos: ");
        if (c->sinistros < 0) {
            printf("%sO numero de sinistros nao pode ser negativo!%s\n", ANSI_COR_VERMELHO, ANSI_COR_RESET);
        }
    } while (c->sinistros < 0);

    // Cateforias da CNH (A, B ou C) e validação
    do {
        c->cnh = ler_caractere("Categoria da CNH (A / B / C): ");
        if (c->cnh != 'A' && c->cnh != 'B' && c->cnh != 'C') {
            printf("%sCategoria invalida! temos A, B ou C.%s\n", ANSI_COR_VERMELHO, ANSI_COR_RESET);
        }
    } while (c->cnh != 'A' && c->cnh != 'B' && c->cnh != 'C');
}


 //Função de exibição dos dados do condutor 
 void exibir_condutor(const Condutor *c) {
    printf("  %sNome:%s %s\n", ANSI_COR_AZUL, ANSI_COR_RESET, c->nome);
    printf("  %sRG:%s %s\n", ANSI_COR_AZUL, ANSI_COR_RESET, c->rg);
    printf("  %sIdade:%s %d anos\n", ANSI_COR_AZUL, ANSI_COR_RESET, c->idade);
    printf("  %sSinistros nos ultimos 3 anos:%s %d\n", ANSI_COR_AZUL, ANSI_COR_RESET, c->sinistros);
    printf("  %sCNH Categoria:%s %c\n", ANSI_COR_AZUL, ANSI_COR_RESET, c->cnh);
}