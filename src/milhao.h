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
	char altCorreta;
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

/**
 * Abre o arquivo encontrado em <caminho>, e carrega todos os dados
 * como perguntas, até o fim do arquivo, armazenando em um vetor.
 * Retorna o vetor de perguntas.
 * 
 */
pergunta* carregaPerguntas (const char* caminho);

/**
 *  Imprime pergunta no console. Retorna o numero de caracteres
 * impressos ou numero negativo em caso de erro.
 */
int printPergunta (const pergunta perg, const int num);

#endif
