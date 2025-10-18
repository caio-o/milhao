#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "milhao.h"

/**
 *  Implementacao das funcoes declaradas em "milhao.h".
 *
 */

void esperaEnter (void)
{
	printf (
"\n\
#####################################\n\
#  Pressione ENTER para continuar.  #\n\
#####################################\n");
	
	fgetc  (stdin);
}

int printPergunta (const pergunta perg, const int num)
{
	return printf("\
\n\
Pergunta %d: %s\n\
    [a] %s\n\
    [b] %s\n\
    [c] %s\n\
    [d] %s\n\n", 

    num, perg.descricao, perg.alt[0], perg.alt[1], perg.alt[2], perg.alt[3]);
}

size_t indiceAleatorio (int nivel)
{	
	return nivel == (int) SUPER_DIFICIL ?
		IND_NIVEL (nivel) + random() % N_PERGUNTAS_SUPER_ARQ :
		IND_NIVEL (nivel) + random() % N_PERGUNTAS_NIVEL_ARQ;
}

pergunta* pegaPergunta (int nivel, FILE* fb) {
	pergunta *perg = (pergunta*) malloc (sizeof (pergunta));

	if (nivel > (int) MAXIMO)
		nivel = MAXIMO;
	if (nivel < (int) MINIMO)
		nivel = (int) MINIMO;

	if (perg) {			
		fseek (fb, indiceAleatorio (nivel) * sizeof(pergunta), SEEK_SET);
		fread (perg, sizeof (pergunta), 1, fb);
	}

	else {
		perror ("pegaPergunta: erro de alocacao");
		exit (1);
	}	
	
	return perg;
}

char ajudas[4][100] = {
    "Pular pergunta",
    "Pedir ajuda a plateia",
    "Pedir ajuda aos universitarios",
    "Pedir ajuda as cartas"
};

void printAjuda(int q1, int q2, int q3, int q4) {
	printf("-- Ajuda --\n");
	if (q1) printf("[1] %s (%dx)\n", ajudas[0], q1);
	if (q2) printf("[2] %s (%dx)\n", ajudas[1], q2);
	if (q3) printf("[3] %s (%dx)\n", ajudas[2], q3);
	if (q4) printf("[4] %s (%dx)\n", ajudas[3], q4);
	printf("[5] Parar\n");
	printf("-----------\n");
}

char lerResposta(void) {
	char resp = '\0';
	while(1){
		printf("Digite sua resposta: ");
		scanf(" %c", &resp);
		if((resp >= 'a' && resp <= 'd') || (resp >= '1' && resp <= '5'))
			break;
		printf("Resposta invalida! Tente novamente.\n");
	}

	
	return resp;
}