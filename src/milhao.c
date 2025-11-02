#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include "milhao.h"

/**
 *  Implementacao das funcoes declaradas em "milhao.h".
 *
 */

void esperaEnter (void)
{
	printf (
"\n\
#####################################\n\
#  Pressione ENTER para continuar.  #\n\
#####################################\n");
	fflush (stdin);

	fgetc  (stdin);
	fflush (stdin);
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

int printAjuda (const recursos rec)
{
	return printf("\
\n\
-- Ajuda --:\n\
[1] Pular pergunta (%dx)\n\
[2] Pedir ajuda a plateia (%dx)\n\
[3] Pedir ajuda aos universitarios (%dx)\n\
[4] Pedir ajuda as cartas (%dx)\n\
[5] Parar\n\n", 

	rec.pulosRest, rec.plateiaRest, rec.univRest, rec.cartasRest);
}

jogador* constroiJogador (const int pulos,  const int cartas, 
		          const int univ,   const int plateia) {
	jogador *pJog = (jogador*) malloc (sizeof (jogador));
	
	if (pJog) {
		pJog->premio           =  0;
		pJog->acertos          =  0;

		pJog->rec.pulosRest    =  pulos;
		pJog->rec.plateiaRest  =  plateia;
		pJog->rec.univRest     =  univ;
		pJog->rec.cartasRest   =  cartas;
	}
	else {
		perror ("Erro de alocacao em constroiJogador");
		exit (1);
	}

	return pJog;
}

size_t indiceAleatorio (int nivel)
{	
	return nivel == (int) SUPER_DIFICIL ?
		IND_NIVEL (nivel) + random() % N_PERGUNTAS_SUPER_ARQ :
		IND_NIVEL (nivel) + random() % N_PERGUNTAS_NIVEL_ARQ;
}

pergunta* pegaPergunta (int nivel, FILE* fb) {
	pergunta *perg = (pergunta*) malloc (sizeof (pergunta));

	if (nivel > (int) MAXIMO)
		nivel = MAXIMO;
	if (nivel < (int) MINIMO)
		nivel = (int) MINIMO;

	if (perg) {			
		fseek (fb, indiceAleatorio (nivel) * sizeof(pergunta), SEEK_SET);
		fread (perg, sizeof (pergunta), 1, fb);
	}

	else {
		perror ("pegaPergunta: erro de alocacao");
		exit (1);
	}	
	
	return perg;
}

const char ajudas[4][100] = {
    "Pular pergunta",
    "Pedir ajuda a plateia",
    "Pedir ajuda aos universitarios",
    "Pedir ajuda as cartas"
};

char lerResposta(void) {
	char resp = '\0';
	int  respValida = 0;

	do { // while ( !respValida );
		printf("Digite sua resposta: ");
		
		resp = (char) fgetc (stdin);
		fflush (stdin);
		
		respValida = NULL != strchr(ALTERNATIVAS, (int) resp);

		if ( strchr(ALTERNATIVAS, resp) ) {
			respValida = 1;
		}
		else {
			printf("Resposta invalida! Tente novamente.\n");
		}
	} while ( !respValida );

	
	return resp;
}

void processaAjuda(recursos* rec, const char escolha, const pergunta perg)
{

    switch (escolha) {
        case '1': // Pular pergunta
            if (rec->pulosRest > 0) {
                rec->pulosRest--;
                printf("\nVoce decidiu pular a pergunta!\n");
                printf("A resposta correta era (%c): %s\n",
                       perg.altCorreta,
                       perg.alt[perg.altCorreta - 'a']);
                printf("Restam %d pulos.\n", rec->pulosRest);
            } else {
                printf("\nVoce nao tem mais pulos disponiveis!\n");
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
                printf("Resultado da plateia:\n");
                for (i = 0; i < 4; i++)
                    printf("(%c): %d votos\n", 'a' + i, votos[i]);
                printf("Restam %d ajudas da plateia.\n", rec->plateiaRest);
            } else {
                printf("\nVoce não tem mais ajudas da plateia!\n");
            }
            break;
        }

        case '3': { // Universitários
            if (rec->univRest > 0) {
                rec->univRest--;
                printf("\nVoce pediu ajuda aos universitarios!\n");
                for (int i = 1; i <= 3; i++) {
                    char palpite;
                    if (rand() % 100 < 70)
                        palpite = perg.altCorreta; // 70% de chance de acerto
                    else
                        palpite = 'a' + rand() % 4;
                    printf("Universitario %d acha que eh (%c): %s\n",
                           i, palpite, perg.alt[palpite - 'a']);
                }
                printf("Restam %d ajudas dos universitarios.\n", rec->univRest);
            } else {
                printf("\nVoce não tem mais ajudas dos universitarios!\n");
            }
            break;
        }

        case '4': { // Cartas
            if (rec->cartasRest > 0) {
                rec->cartasRest--;
                printf("\nVoce pediu ajuda das cartas!\n");
                int carta = rand() % 4; // número de alternativas erradas removidas
                printf("Voce tirou a carta numero %d!\n", carta);

                int removidas = 0;
                for (int i = 0; i < 4 && removidas < carta; i++) {
                    if ('a' + i != perg.altCorreta) {
                        printf("Alternativa (%c) eliminada: %s\n",
                               'a' + i, perg.alt[i]);
                        removidas++;
                    }
                }
                printf("Restam %d ajudas das cartas.\n", rec->cartasRest);
            } else {
                printf("\nVoce não tem mais ajudas das cartas!\n");
            }
            break;
        }

        default:
            break;
    }

    printf("\n");
}


