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
#include "executa.h"

int main (void)
{
	/*
	FILE *f = fopen("assets/perguntas.dat", "r");
	pergunta* pPer = NULL;
	int pergAtual = 1;
	
	// Variaveis do loop 
	
	niveis niv;
	recursos rec = {N_RECURSO, N_RECURSO, N_RECURSO, N_RECURSO};
	char resp;

	srand (time(NULL));

	printf("\n\nOla, bem-vindo ao Show do Milhao!\n\n");

	for (niv = MINIMO, resp = ','; niv <= MAXIMO;)
	{
		pPer = pegaPergunta (niv, f);
		while (1)
		{
			
			printPergunta (*pPer, pergAtual);
			printAjuda (rec);
			resp = lerResposta();
			
			if (resp >= '1' && resp <= '5') 
			{
				processaAjuda (&rec, resp, *pPer);
	
				if (resp == '5') {
					printf("\nVoce decidiu parar o jogo. Ate a proxima!\n");
					exit (0);
				}
				
				if(resp == '1'){
					break;
				}
			}
			else {
				printf ("    Voce escolheu: (%c): %s\n", 
						resp, 
						pPer->alt [resp - (int)'a']);
			
				if (resp == pPer->altCorreta) 
					printf ("    A resposta esta.... correta!\n");
				else {
					printf ("    A resposta esta.... errada!\n\n");
					printf ("    A resposta correta era (%c): %s\n", 
						pPer->altCorreta, 
						pPer->alt [pPer->altCorreta - ALTERNATIVAS[0]]);
				}
				
				break;
			}
	
		}

		pergAtual++;
		niv++;
		esperaEnter();

		if (pPer) {
			free (pPer);
			pPer = NULL;
		}
	}

	printf("\n\nFim de jogo!\n\n");

	fclose(f);
	if (pPer) free (pPer);
	*/
	recursos rec = {3, 3, 3, 3};
	int retorno = 0;
	FILE *f = fopen ("./assets/perguntas.dat", "rb");
	resultado res = {0, 0, JOGANDO, rec};

	srand (time(NULL));

	if (f) {
		res = executa (rec, f);
		mostraResultado (res);
	}
	else {
		perror ("Nao se pode abrir arquivo");
		retorno = 1;	
	}

	return retorno;
}
