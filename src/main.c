/*********************************************************/
/*                                                       */
/*      FACULDA DE COMPUTACAO - FACOM UFMS               */
/*      ALGORITMOS E PROGRAMACAO 2                       */
/*      Prof.: Anderson Bessa da Costa                   */
/*      TRABALHO PRÁTICO 2025.2: JOGO DO MILHAO          */
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

	srand (time(NULL));

	printf("\n\nOla, bem-vindo ao Show do Milhao!\n\n");

	pPer = pegaPergunta (0, f);
	printPergunta (*pPer, 1);

	esperaEnter ();
	printf("\n\nFim de jogo!\n\n");
	
	fclose(f);
	if (pPer) free (pPer);

	return 0;
}
