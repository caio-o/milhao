#ifndef __MILHAO_H
#define __MILHAO_H
#include "perguntas.h"

typedef enum {
	JOGANDO    =  0,
	FINAL, 
	VENCEU,
	ERROU,
	PAROU
} estados;

typedef struct {
	int premio;
	int acertos;

	estados estado;

	recursos rec;
} jogador;

typedef jogador resultado;


/*
 * Constroi struct <jogador> com os valores fornecidos;
 * retorna o jogador alocado dinamicamente; sai do programa
 * com sinal (1) se houver erro de alocacao.
 */
jogador* constroiJogador (const int pulos,  const int cartas, 
		          const int univ,   const int plateia);


void boasVindas (void);

/* Executa o jogo com os recursos iniciais e o arquivo de perguntas fornecido. */
resultado executa (const recursos rec, FILE *fPerguntas);

/* Mostra resultado do jogo. */
void mostraResultado (resultado res);

void executaEtapa (jogador* pJog, FILE *fPerg);

void mensagemNivel (niveis niv);

#endif

