/*********************************************************/
/*                                                       */
/*      FACULDADE DE COMPUTACAO - FACOM UFMS             */
/*      ALGORITMOS E PROGRAMACAO 2                       */
/*      Prof.: Anderson Bessa da Costa                   */
/*      TRABALHO PRÁTICO 2025.2: SHOW DO MILHÃO          */
/*                                                       */
/*      Alunos: Luan Rodolfo dos Santos Leme             */
/*              Henrico ?? Queiroz                       */
/*              Caio e Silva Barbieri                    */
/*                                                       */
/*                                                       */
/*********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "milhao.h"

int main (void)
{
	FILE *f = fopen("assets/perguntas.dat", "r");
	pergunta* pPer = NULL;
	int pergAtual = 1;
	
	/* Variaveis do loop */
	niveis niv;
	char resp;

	srand (time(NULL));

	printf("\n\nOla, bem-vindo ao Show do Milhao!\n\n");

	for (niv = MINIMO, resp = ','; niv <= MAXIMO; niv++)
	{
		pPer = pegaPergunta (niv, f);
		printPergunta (*pPer, pergAtual++);
		resp = esperaResposta ("abcd");
		
		printf ("    Voce escolheu: (%c): %s\n", 
				resp, 
				pPer->alt [resp - (int)'a']);
		
		if (resp == pPer->altCorreta) 
			printf ("    A resposta está.... correta!\n");
		else {
			printf ("    A resposta está.... errada!\n\n");
			printf ("    A resposta correta era (%c): %s\n", 
				pPer->altCorreta, 
				pPer->alt [pPer->altCorreta - (int)'a']);
		}
	}

	printf("\n\nFim de jogo!\n\n");

	fclose(f);
	if (pPer) free (pPer);

	// comentário teste
	return 0;
}
