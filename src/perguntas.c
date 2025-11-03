#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include "milhao.h"

/**
 *  Implementacao das funcoes declaradas em "perguntas.h".
 *
 */

int limpaStdin (void) {
	int c;
	do {
		c = fgetc (stdin);
	} while (c != '\n' && c != EOF);
	return c;
}

void limpaTela (void) {
#if defined (__POSIX__)
	system ("clear");
#elif defined (WIN32) || defined (_WIN32)
	system ("cls");
#else
	printf ("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
#endif

	fflush (stdout);
}

void esperaEnter (void)
{
	printf (
"\n\
    #####################################\n\
    #  Pressione ENTER para continuar.  #\n\
    #####################################\n    ....");
	
	fflush (stdout);

	limpaStdin ();
}

int printPergunta (const pergunta perg, const int num)
{
	printf("\
\n\
Pergunta %d: %s\n\
    [a] %s\n\
    [b] %s\n\
    [c] %s\n\
    [d] %s\n\n", 

    num, perg.descricao, perg.alt[0], perg.alt[1], perg.alt[2], perg.alt[3]);

	fflush (stdout);
	return 0;
}

size_t indiceAleatorio (int nivel)
{	
	return nivel == (int) SUPER_DIFICIL ?
		IND_NIVEL (nivel) + random() % N_PERGUNTAS_SUPER_ARQ :
		IND_NIVEL (nivel) + random() % N_PERGUNTAS_NIVEL_ARQ;
}

size_t indiceAleatorioNovo (int nivel)
{	
	static unsigned short perguntaFeita [N_PERGUNTAS_MAX] = {0};
	static int cont = 0;
	static int ind = -1;

	if (cont >= N_PERGUNTAS_MAX) 
		ind = -1;
	else { 
		do    ind = indiceAleatorio (nivel);	
		while (perguntaFeita[ind]); 
		// ^ Enquanto "ind" não é índice de uma pergunta nova.
		
		perguntaFeita[ind] = 1;
		cont++;
	}
	
	return ind;
}

void atualizaPergunta (int nivel, FILE* fb, pergunta *pPerg) {
	size_t ind;

	if (nivel > (int) MAXIMO)
		nivel = MAXIMO;
	if (nivel < (int) MINIMO)
		nivel = (int) MINIMO;

	if ((ind = indiceAleatorioNovo (nivel)) != -1) {
		fseek (fb, ind * sizeof(pergunta), SEEK_SET);
		if (!fread (pPerg, sizeof (pergunta), 1, fb)) {
			perror ("pegaPergunta: Erro ao ler arquivo");
			exit (1);
		}
	}
}

pergunta* pegaPergunta (int nivel, FILE* fb) {
	pergunta *perg = (pergunta*) malloc (sizeof (pergunta));

	atualizaPergunta (nivel, fb, perg);
	
	return perg;
}

char lerResposta(void) {
	char resp = '\0';
	int  respValida = 0;

	do { // while ( !respValida );
		/* Uma resposta válida não foi lida ainda. */
		printf("Digite sua resposta: ");
		fflush(stdout);
		
		resp = (char) fgetc (stdin);

		//fflush (stdin); // comportamento indefinido?
		
		respValida = NULL != strchr(ALTERNATIVAS, (int) resp);

		if ( strchr(ALTERNATIVAS, resp) ) {
			respValida = 1;
		}
		else {
			printf("Resposta invalida! Tente novamente.\n");
			fflush(stdout);
		}
	} while ( !respValida );
	
	limpaStdin();
	
	return resp;
}


int processaResposta (const char r, const pergunta perg) {
	int acertou = r == perg.altCorreta;
	
	if (acertou) {
		printf ("    Voce escolheu (%c): %s\n"
		        "    A resposta esta.... CORRETA!\n",
			r, perg.alt [r - 'a']);
		
	}
	else {
		printf ("    Voce escolheu (%c): %s\n"
			"    A resposta esta.... ERRADA!!\n"
		        "    A resposta correta era (%c): %s.\n",
			r, perg.alt [r - 'a'], 
			perg.altCorreta, perg.alt [perg.altCorreta - 'a']);
		
	}

	fflush (stdout);
	return acertou;
}

const char ajudas[4][100] = {
    "Pular pergunta",
    "Pedir ajuda a plateia",
    "Pedir ajuda aos universitarios",
    "Pedir ajuda as cartas"
};

int printAjuda (const recursos rec)
{
	printf("\
\n\
-- Ajuda --:\n\
[1] Pular pergunta (%dx)\n\
[2] Pedir ajuda a plateia (%dx)\n\
[3] Pedir ajuda aos universitarios (%dx)\n\
[4] Pedir ajuda as cartas (%dx)\n\
[5] Parar\n\n", 

	rec.pulosRest, rec.plateiaRest, rec.univRest, rec.cartasRest);

	fflush (stdout);

	return 0;
}

void processaAjuda(recursos* rec, const char escolha, const pergunta perg)
{

    switch (escolha) {
        case '1': // Pular pergunta
            if (rec->pulosRest > 0) {
                rec->pulosRest--;
                printf("\n    Voce decidiu pular a pergunta!\n");
                printf("    A resposta correta era (%c): %s\n",
                       perg.altCorreta,
                       perg.alt[perg.altCorreta - 'a']);
                printf("    Restam %d pulos.\n", rec->pulosRest);
            } else {
                printf("\n    Voce nao tem mais pulos disponiveis!\n");
            }
            break;

        case '2': { // Plateia
            if (rec->plateiaRest > 0) {
                rec->plateiaRest--;
                printf("\nVoce pediu ajuda a plateia!\n");
                int votos[4] = {0}, i;
                // 30 votos, com chance maior da correta
                for (i = 0; i < 30; i++) {
                    char opcao = (rand() % 100 < 60) ? perg.altCorreta
                                                     : 'a' + rand() % 4;
                    votos[opcao - 'a']++;
                }
                printf("    Resultado da plateia:\n");
                for (i = 0; i < 4; i++)
                    printf("    (%c): %d votos\n", 'a' + i, votos[i]);
                printf("    Restam %d ajudas da plateia.\n", rec->plateiaRest);
            } else {
                printf("\n    Voce não tem mais ajudas da plateia!\n");
            }
            break;
        }

        case '3': { // Universitários
            if (rec->univRest > 0) {
                rec->univRest--;
                printf("\n    Voce pediu ajuda aos universitarios!\n");
                for (int i = 1; i <= 3; i++) {
                    char palpite;
                    if (rand() % 100 < 70)
                        palpite = perg.altCorreta; // 70% de chance de acerto
                    else
                        palpite = 'a' + rand() % 4;
                    printf("    Universitario %d acha que eh (%c): %s\n",
                           i, palpite, perg.alt[palpite - 'a']);
                }
                printf("    Restam %d ajudas dos universitarios.\n", rec->univRest);
            } else {
                printf("\n    Voce não tem mais ajudas dos universitarios!\n");
            }
            break;
        }

        case '4': { // Cartas
            if (rec->cartasRest > 0) {
                rec->cartasRest--;
                printf("\n    Voce pediu ajuda das cartas!\n");
                int carta = rand() % 4; // número de alternativas erradas removidas
                printf("    Voce tirou a carta numero %d!\n", carta);

                int removidas = 0;
                for (int i = 0; i < 4 && removidas < carta; i++) {
                    if ('a' + i != perg.altCorreta) {
                        printf("    Alternativa (%c) eliminada: %s\n",
                               'a' + i, perg.alt[i]);
                        removidas++;
                    }
                }
                printf("    Restam %d ajudas das cartas.\n", rec->cartasRest);
            } else {
                printf("\n    Voce não tem mais ajudas das cartas!\n");
            }
            break;
        }

        default:
            break;
    }

    printf("\n");
}


