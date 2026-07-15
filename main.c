#include <stdio.h>
#include <stdlib.h>
#include "funcoes/utils.h"
#include "funcoes/veiculo.h"
#include "funcoes/condutor.h"
#include "funcoes/cotacao.h"
#include "funcoes/arquivo.h"
#include "funcoes/relatorio.h"

#define ARQUIVO_DADOS "cotacoes.bin"

int main(void) {
    Cotacao *lista_cotacoes = NULL;
    int total_cotacoes = 0;
    int capacidade = 0;

    // carrega os dados da nossa database , o cotacoes.bin
    if (!carregarcots(&lista_cotacoes, &total_cotacoes, &capacidade, ARQUIVO_DADOS)) {
        printf("%sNao foi possivel carregar as cotacoes anteriores.%s\n", 
               ANSI_COR_AMARELO, ANSI_COR_RESET);
    } else {
        if (total_cotacoes > 0) {
            printf("%s%d cotacao(oes) carregada(s) do arquivo.%s\n", 
                   ANSI_COR_VERDE, total_cotacoes, ANSI_COR_RESET);
        } else {
            printf("%sNenhum arquivo anterior encontrado. Iniciando banco de dados.%s\n", 
                   ANSI_COR_AZUL, ANSI_COR_RESET);
        }
    }

    int opcao = 0;
    do {
        printf("    %sSistema De Cotacao - SI.LAB%s\n", ANSI_COR_NEGRITO, ANSI_COR_RESET);
        printf("                       ____________________                              \n");
        printf("                     //|           |        \\                            \n");
        printf("                   //  |           |          \\                          \n");
        printf("      ___________//____|___________|__________()\\__________________      \n");
        printf("    /__________________|_=_________|_=___________|_________________{}    \n");
        printf("    [           ______ |           | .           | ==  ______      { }   \n");
        printf("  __[__        /##  ##\\|           |             |    /##  ##\\    _{# }_ \n");
        printf(" {_____)______|##    ##|___________|_____________|___|##    ##|__(______}\n");
        printf("             /  ##__##                              /  ##__##        \\   \n");
        printf("--------------------------------------------------\n");
        printf("  %s[1]%s - Cadastrar Nova Cotacao\n", ANSI_COR_AZUL, ANSI_COR_RESET);
        printf("  %s[2]%s - Listar Todas as Cotacoes Salvas\n", ANSI_COR_AZUL, ANSI_COR_RESET);
        printf("  %s[3]%s - Filtrar Cotacoes por Condutor\n", ANSI_COR_AZUL, ANSI_COR_RESET);
        printf("  %s[4]%s - Exibir Cotacao de Menor Valor\n", ANSI_COR_AZUL, ANSI_COR_RESET);
        printf("  %s[99]%s - Sair\n", ANSI_COR_VERMELHO, ANSI_COR_RESET);
        printf("--------------------------------------------------\n");
        
        opcao = lerint(">> : ");

        switch (opcao) {
            case 1: {
                // Alocacao e realocacao da lista de cotacoes
                if (total_cotacoes >= capacidade) {
                    capacidade = (capacidade == 0) ? 4 : capacidade * 2;
                    Cotacao *temp = (Cotacao *)realloc(lista_cotacoes, capacidade * sizeof(Cotacao));
                    if (temp == NULL) {
                        printf("%sErro: Falha de memoria ao alocar cotacao!%s\n", 
                               ANSI_COR_VERMELHO, ANSI_COR_RESET);
                        break;
                    }
                    lista_cotacoes = temp;
                }

                // bota a cotacao na memoria e incrementa total
                cadastrarcot(&lista_cotacoes[total_cotacoes]);
                total_cotacoes++;

                // salva a lista atualizada 2026 no .bin
                if (salvarcots(lista_cotacoes, total_cotacoes, ARQUIVO_DADOS)) {
                    printf("%sDados salvos na database!%s\n", 
                           ANSI_COR_VERDE, ANSI_COR_RESET);
                }
                break;
            }
            case 2:
                listarcots(lista_cotacoes, total_cotacoes);
                break;
            case 3:
                filtrarpordriver(lista_cotacoes, total_cotacoes);
                break;
            case 4:
                menorcot(lista_cotacoes, total_cotacoes);
                break;
            case 99:
                printf("\n%sSaindo do programa. Ate mais!%s\n", ANSI_COR_VERDE, ANSI_COR_RESET);
                break;
            default:
                printf("%sErro: Opcao invalida! Digite uma opcao de 1 a 4 ou 99.%s\n", 
                       ANSI_COR_VERMELHO, ANSI_COR_RESET);
                break;
        }
    } while (opcao != 99);

    // liberar a memoria antes de fechar pra evitar bug ( vazamento de memoria )
    if (lista_cotacoes != NULL) {
        free(lista_cotacoes);
        lista_cotacoes = NULL;
    }

    return 0;
}
