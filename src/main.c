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
	int pergAtual = 1;

	srand (time(NULL));

	printf("\n\nOla, bem-vindo ao Show do Milhao!\n\n");

	pPer = pegaPergunta (FACIL, f);
	printPergunta (*pPer, pergAtual++);
	printAjuda(3,3,3,3);

	esperaEnter ();

	free (pPer);
	pPer = pegaPergunta (MEDIO, f);
	printPergunta (*pPer, pergAtual++);
	printAjuda(3,3,3,3);

	esperaEnter ();

	free (pPer);
	pPer = pegaPergunta (DIFICIL, f);
	printPergunta (*pPer, pergAtual++);
	printAjuda(3,3,3,3);

	esperaEnter ();
	
	free (pPer);
	pPer = pegaPergunta (SUPER_DIFICIL, f);
	printPergunta (*pPer, pergAtual++);
	printAjuda(3,3,3,3);

	esperaEnter ();
	
	printf("\n\nFim de jogo!\n\n");

	

	fclose(f);
	if (pPer) free (pPer);

	// comentário teste
	return 0;
}
