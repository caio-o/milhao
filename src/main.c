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
#include "perguntas.h"

int main (void)
{
	recursos rec = {N_RECURSO, N_RECURSO, N_RECURSO, N_RECURSO};
	int retorno = 0;
	FILE *f = fopen ("./assets/perguntas.dat", "rb");
	resultado res = {0, 0, JOGANDO, rec};

	srand (time(NULL));

	if (f) {
		res = executa (rec, f);
		mostraResultado (res);
		
		fclose (f);
		f = NULL;
	}
	else {
		perror ("Nao se pode abrir arquivo");
		retorno = 1;	
	}

	esperaEnter ();
	return retorno;
}
