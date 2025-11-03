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

/* Usado em "mostraResultado(resultado)". */
typedef jogador resultado;


/* Constroi struct <jogador> com os valores fornecidos;
 * retorna o jogador alocado dinamicamente; sai do programa
 * com sinal (1) se houver erro de alocacao. */
jogador* constroiJogador (const int pulos,  const int cartas, 
		          const int univ,   const int plateia);

/* Imprime a mensagem de boas vindas, explicando o jogo, 
 * aguardando o ENTER do usuário. */
void boasVindas (void);

/* Executa o jogo com os recursos iniciais e o arquivo de perguntas fornecido. */
resultado executa (const recursos rec, FILE *fPerguntas);

/* Recebe os dados de um jogador "res", e mostra a respectiva mensagem final. 
 * Aguarda ENTER do usuário.*/
void mostraResultado (resultado res);

/* Recebe ponteiro para o jogador, e o arquivo que contém as perguntas. 
 * 
 * Executa uma iteração do jogo: faz uma nova pergunta ao usuário, lê e 
 * procecssa sua resposta, atualiza o nível das perguntas, o premio do jogador
 * e o estado do jogo. */
void executaEtapa (jogador* pJog, FILE *fPerg);

/* Notifica ao jogador que ele passou para o dado nível "niv". */
void mensagemNivel (niveis niv);

#endif

