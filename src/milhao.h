#ifndef __MILHAO_H__
#define __MILHAO_H__

#if defined(_WIN32) || defined(WIN32)
#define random(x) rand(x)
#endif

#define N_PERGUNTAS_NIVEL       5
#define N_PERGUNTAS_TOTAL      16
#define N_RECURSO           	3
#define N_PERGUNTAS_NIVEL_ARQ  20
#define N_PERGUNTAS_SUPER_ARQ  10 
#define N_PERGUNTAS_ARQ        70

#define IND_NIVEL(x)            (N_PERGUNTAS_NIVEL_ARQ * (x-1))

#define ALTERNATIVAS           "abcd12345"

/**
 *  DECLARACAO E COMENTARIO DAS FUNCOES DO JOGO DO MILHAO.
 * FUNCOES IMPLEMENTADAS EM "milhao.c".
 */

/* TIPOS, STRUCTS, ENUMS, CONSTANTES */

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

typedef enum {
	MINIMO         = 1,

	FACIL          = 1,
	MEDIO          = 2,
	DIFICIL        = 3,
	SUPER_DIFICIL  = 4,

	MAXIMO         = 4
} niveis;

typedef struct {
	int pulosRest;
	int plateiaRest;
	int univRest;
	int cartasRest;
} recursos;

typedef struct {
	int premio;
	int acertos;
	int errou;
	int venceu;

	recursos rec;
} jogador;


/* FUNÇÕES */

/**
 *  Espera que o usuário termine a linha antes de continuar.
 */
void esperaEnter (void);

/*
 * Constroi struct <jogador> com os valores fornecidos;
 * retorna o jogador alocado dinamicamente; sai do programa
 * com sinal (1) se houver erro de alocacao.
 */
jogador* constroiJogador (const int pulos,  const int cartas, 
		          const int univ,   const int plateia);

/**
 *  Seleciona uma pergunta aleatória do nível dado.
 */
pergunta* pegaPergunta (int nivel, FILE* f);

/**
 *  Imprime pergunta no console. Retorna o numero de caracteres
 * impressos ou numero negativo em caso de erro.
 */
int printPergunta (const pergunta perg, const int num);

char lerResposta(void);
int printAjuda (const recursos rec);

void processaAjuda (recursos* rec, const char escolha, const pergunta perg);

char lerResposta(void);

#endif

