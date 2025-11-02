#ifndef __EXECUTA_H
#define __EXECUTA_H
#include "milhao.h"

typedef jogador resultado;

/* Executa o jogo com os recursos iniciais e o arquivo de perguntas fornecido. */
resultado executa (const recursos rec, FILE *fPerguntas);

/* Mostra resultado do jogo. */
void mostraResultado (resultado res);

#endif
