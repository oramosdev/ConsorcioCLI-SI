#ifndef UTILS_H
#define UTILS_H

// Cores ANSI para deixar o menu colorido , vamos usar o %s , pra usar eles la beleza
#define ANSI_COR_RESET   "\x1b[0m"
#define ANSI_COR_VERMELHO "\x1b[31m"
#define ANSI_COR_VERDE    "\x1b[32m"
#define ANSI_COR_AMARELO  "\x1b[33m"
#define ANSI_COR_AZUL     "\x1b[34m"
#define ANSI_COR_NEGRITO  "\x1b[1m"

// Funcoes para melhora a leitura 
void limparbuf(void);
void lerstr(char *dest, int tam);
int lerint(const char *msg);
float lerfloat(const char *msg);
char lerchar(const char *msg);

#endif
