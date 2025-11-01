#ifndef __MILHAO_H__
#define __MILHAO_H__

#if defined(_WIN32) || defined(WIN32)
#define random(x) rand(x)
#endif

#define N_PERGUNTAS_NIVEL       5
#define N_PERGUNTAS_TOTAL      16
#define N_RECURSO_PULAR         3
#define N_PERGUNTAS_NIVEL_ARQ  20
#define N_PERGUNTAS_SUPER_ARQ  10 
#define N_PERGUNTAS_ARQ        70

#define IND_NIVEL(x)            (N_PERGUNTAS_NIVEL_ARQ * (x-1))

#define ALTERNATIVAS           "abcd12345"

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
 *  altcorreta:  alternativa correta dentre as <alt>
 */
typedef struct
{
	char nivel;
	char descricao[200];
	char alt[4][30];
	char altCorreta;
} pergunta;

typedef struct {
	int premio;
	int acertos;
	int nPular;
	int nAjudaCartas;
	int nAjudaUni;
	int nAjudaPlateia;
} jogador;

typedef enum {
	MINIMO         = 1,

	FACIL          = 1,
	MEDIO          = 2,
	DIFICIL        = 3,
	SUPER_DIFICIL  = 4,

	MAXIMO         = 4
} niveis;

/**
 *  Espera que o usuário termine a linha antes de continuar.
 */
void esperaEnter (void);

/*
 * Constroi struct <jogador> com os valores fornecidos;
 * retorna o jogador alocado dinamicamente; sai do programa
 * com sinal (1) se houver erro de alocacao.
 */
jogador* constroiJogador (const int pular, 
		          const int ajCartas, 
		          const int ajUni, 
                          const int ajPlat);

/**
 *  Seleciona uma pergunta aleatória do nível dado.
 */
pergunta* pegaPergunta (int nivel, FILE* f);

/**
 *  Imprime pergunta no console. Retorna o numero de caracteres
 * impressos ou numero negativo em caso de erro.
 */
int printPergunta (const pergunta perg, const int num);

//char esperaResposta (const char* alternativas);

void printAjuda(int q1, int q2, int q3, int q4);

char lerResposta(void);

#endif

