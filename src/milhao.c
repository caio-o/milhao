#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "milhao.h"

/**
 *  Implementacao das funcoes declaradas em "milhao.h".
 *
 */

void esperaEnter ()
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

/**
pergunta* carregaPerguntas (const char* caminho)
{
	pergunta*  vPerguntas = NULL;
	FILE*      f          = NULL;
	int        leitura    = 1;
	size_t     nPerguntas = 0;
	f = fopen (caminho, "r");
	
	if (f)
	{
		do
		{
			leitura = EOF;
			// vai ateh o final do arquivo pra contar as perguntas
		} while (leitura != EOF);

		if (nPerguntas)
		{
			vPerguntas = 
				(pergunta*) 
				malloc (sizeof(pergunta) * nPerguntas);

			if (vPerguntas)
			{
				fread (vPerguntas, sizeof(pergunta), nPerguntas, f);
			}
			else
			{
				perror (
				"Em carregaPerguntas -\
				erro em alocar vPerguntas");
			}
		}
	}
	else
	{
		perror ("Arquivo nao pode ser aberto");
		exit (1);
	}

	return vPerguntas;
}*/


