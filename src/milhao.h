#ifndef __MILHAO_H__
#define __MILHAO_H__

/**
 *  DECLARACAO E COMENTARIO DAS FUNCOES DO JOGO DO MILHAO.
 * FUNCOES IMPLEMENTADAS EM "milhao.c".
 */

/**
 *  Pergunta que pode ser feita ao jogador.
 *
 *  nivel:        dificuldade da questão. 
 *  descricicao:  enunciado de tamanho maximo 200 ( termina em '\0' ).
 *  alt:          vetor de strings correspondedo as possiveis respostas.
 *  alt_correta:  alternativa correta dentre as <alt>
 */
typedef struct
{
	char nivel;
	char descricao[200];
	char alt[4][30];
	char alt_correta;
} pergunta;

/**
 *  Espera que o usuário termine a linha antes de continuar.
 *
 */
void esperaEnter ();

/**
 *  Seleciona uma pergunta aleatória do nível dado.
 *
 */
pergunta* pegaPergunta (char nivel);

#endif
