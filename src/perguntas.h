#ifndef __PERGUNTAS_H__
#define __PERGUNTAS_H__

#if defined(_WIN32) || defined(WIN32)
#define random(x) rand(x)
#endif

#define N_PERGUNTAS_NIVEL       5
#define N_PERGUNTAS_TOTAL      16
#define N_RECURSO           	3
#define N_PERGUNTAS_NIVEL_ARQ  20
#define N_PERGUNTAS_SUPER_ARQ  10 
#define N_PERGUNTAS_ARQ        70
#define N_PERGUNTAS_MAX        N_PERGUNTAS_ARQ

#define IND_NIVEL(x)            (N_PERGUNTAS_NIVEL_ARQ * (x-1))

#define ALTERNATIVAS           "abcd12345"
#define ALTERNATIVAS_AJUDA     "1234"

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

/* FUNÇÕES */

/* Espera que o usuário termine a linha antes de continuar. */
void esperaEnter (void);

/* Limpa a tela imprimindo novas linhas. */
void limpaTela (void);

/* Retorna uma pergunta aleatória do nível dado. */
pergunta* pegaPergunta (int nivel, FILE* f);

/*  Atualiza "pPerg" para uma nova pergunta do nivel "nivel",
 *  a partir do arquivo "fb". Garante uma pergunta diferente a cada vez.
 *  Caso todas tenham sido usadas, não atualiza. */
void atualizaPergunta (int nivel, FILE* fb, pergunta *pPerg);

/* Imprime pergunta no console. Retorna o numero de caracteres impressos ou 
 * numero negativo em caso de erro. 
 *
 * OBS.: Possui retorno pois se planejava usá-lo no tratamento de erros. */
int printPergunta (const pergunta perg, const int num);

/* Lê a resposta do jogador, garantindo que seja um caracter contido em 
 * "ALTERNATIVAS". Retorna esse caracter. */
char lerResposta(void);

/* Recebe um caracter 'r', e verifica se ele é a resposta da pergunta "perg".
 * Retorna 1 se a resposta é a correta, ou 0 caso contrário. */
int processaResposta (const char r, const pergunta perg);

/* Recebe cópia dos recursos "rec" do jogador, e imprime as opções de ajuda,
 * junto ao número de cada recurso disponível. Retorna o numero de caracteres 
 * impressos ou numero negativo em caso de erro.
 *
 * OBS.: Possui retorno pois se planejava usá-lo no tratamento de erros. */
int printAjuda (const recursos rec);

/* Recebe ponteiro para os recursos "rec" do jogador, a ajuda "escolha" que
 * ele escolheu, e a pergunta "perg" à qual ele estava respondendo.
 *
 * Processa o pedido de ajuda, atualizando os recursos "rec" do jogador, e
 * operando a ajuda pedida (exceto pular a pergunta: TODO : ajeitar). */
void processaAjuda (recursos* rec, const char escolha, const pergunta perg);

#endif

