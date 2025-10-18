/*********************************************************/
/*                                                       */
/*      FACULDA DE COMPUTACAO - FACOM UFMS               */
/*      ALGORITMOS E PROGRAMACAO 2                       */
/*      Prof.: Anderson Bessa da Costa                   */
/*      TRABALHO PRÁTICO 2025.2: JOGO DO MILHAO          */
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

	srand (time(NULL));

	printf("\n\nOla, bem-vindo ao Show do Milhao!\n\n");

	for(int i = 0; i < 4; i++){
		// depois trocar dificuldade para niveis diferentes
		pPer = pegaPergunta (FACIL, f);
		printPergunta (*pPer, pergAtual++);
		printAjuda(3,3,3,3);
		char resposta = lerResposta();


		if(pPer->altCorreta != resposta){
			printf("\nResposta incorreta! A resposta correta era [%c].\n", pPer->altCorreta);
		}
		else{
			printf("\nResposta correta!\n");
		}
		
		esperaEnter ();
	}
	
	printf("\n\nFim de jogo!\n\n");


	fclose(f);
	if (pPer) free (pPer);

	// comentário teste
	return 0;
}
