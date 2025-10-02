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
#include "milhao.h"

int main (void)
{
	FILE *f = fopen("../assets/perguntas.dat", "r");
	pergunta* vPer = (pergunta*) malloc (sizeof(pergunta)*2);

	printf("\n\nOla, bem-vindo ao show do milhao!\n\n");
	
	
	fread(vPer, sizeof(pergunta), 2, f);
		
	fclose(f);

	printPergunta (vPer[0], 1);

	esperaEnter ();
	printf("\n\nFim de jogo!\n\n");
	return 0;
}
