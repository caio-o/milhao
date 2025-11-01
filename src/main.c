/*********************************************************/
/*                                                       */
/*      FACULDADE DE COMPUTACAO - FACOM UFMS             */
/*      ALGORITMOS E PROGRAMACAO 2                       */
/*      Prof.: Anderson Bessa da Costa                   */
/*      TRABALHO PRÁTICO 2025.2: SHOW DO MILHÃO          */
/*                                                       */
/*      Alunos: Luan Rodolfo dos Santos Leme             */
/*              Henrico Oliveira de Queiroz              */
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
		printAjuda (3, 3, 3, 3);

		resp = lerResposta();
		
		if (resp == pPer->altCorreta) 
			printf ("    A resposta está.... correta!\n");
		else {
			printf ("    A resposta está.... errada!\n\n");
			printf ("    A resposta correta era (%c): %s\n", 
				pPer->altCorreta, 
				pPer->alt [pPer->altCorreta - ALTERNATIVAS[0]]);
		}

		esperaEnter();
	}

	printf("\n\nFim de jogo!\n\n");

	fclose(f);
	if (pPer) free (pPer);

	return 0;
}
