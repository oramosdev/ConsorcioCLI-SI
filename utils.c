#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

// funcao para ignorar aquele caractere invisivel do windows 
static const char* ignorar_bom(const char *str) {
    if (strncmp(str, "\xef\xbb\xbf", 3) == 0) {
        return str + 3;
    }
    return str;
}

// funcao para limpa o buffer do teclado
void limparbuf(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// funcao que le uma string do teclado de forma segura e tira o enter do final
void lerstr(char *dest, int tam) {
    char buf_temp[1000];
    if (fgets(buf_temp, sizeof(buf_temp), stdin) != NULL) {
        const char *ptr = ignorar_bom(buf_temp);
        size_t len = strlen(ptr);
        
        char *copia_temp = (char *)malloc(len + 1);
        if (copia_temp != NULL) {
            strcpy(copia_temp, ptr);
            if (len > 0 && copia_temp[len - 1] == '\n') {
                copia_temp[len - 1] = '\0';
            }
            strncpy(dest, copia_temp, tam - 1);
            dest[tam - 1] = '\0';
            free(copia_temp);
        } else {
            strncpy(dest, ptr, tam - 1);
            dest[tam - 1] = '\0';
        }
    } else {
        dest[0] = '\0';
    }
}

// funcao que verifica  se o usuario nao digitou uma letra em vez de um numero
int lerint(const char *msg) {
    char buf[100];
    int valor;
    int ok = 0;

    while (!ok) {
        printf("%s", msg);
        if (fgets(buf, sizeof(buf), stdin) != NULL) {
            const char *ptr = ignorar_bom(buf);
            if (sscanf(ptr, "%d", &valor) == 1) {
                ok = 1;
            } else {
                printf("%sDigite um numero inteiro valido!%s\n", ANSI_COR_VERMELHO, ANSI_COR_RESET);
            }
        }
    }
    return valor;
}

//funcao que le um float e valida se digitou errado
float lerfloat(const char *msg) {
    char buf[100];
    float valor;
    int ok = 0;

    while (!ok) {
        printf("%s", msg);
        if (fgets(buf, sizeof(buf), stdin) != NULL) {
            const char *ptr = ignorar_bom(buf);
            if (sscanf(ptr, "%f", &valor) == 1) {
                ok = 1;
            } else {
                printf("%sDigite um numero decimal valido!%s\n", ANSI_COR_VERMELHO, ANSI_COR_RESET);
            }
        }
    }
    return valor;
}

// funcao que le apenas um caractere e transforma em maiusculo
char lerchar(const char *msg) {
    char buf[100];
    char caractere = '\0';
    int ok = 0;

    while (!ok) {
        printf("%s", msg);
        if (fgets(buf, sizeof(buf), stdin) != NULL) {
            const char *ptr = ignorar_bom(buf);
            while (*ptr && isspace((unsigned char)*ptr)) {
                ptr++;
            }
            if (*ptr != '\0' && *ptr != '\n') {
                caractere = toupper((unsigned char)*ptr);
                ok = 1;
            } else {
                printf("%sDigite pelo menos um caractere!%s\n", ANSI_COR_VERMELHO, ANSI_COR_RESET);
            }
        }
    }
    return caractere;
}
