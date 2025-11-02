#include <stdio.h>
#include <stdlib.h>
#include "executa.h"
#include "milhao.h"

void mensagemNivel (niveis niv) {
	        /***               TAMANHO * DE LINHA            ***/
	printf ("         PARABENS! Voce passou para o nivel\n");
	switch (niv) {
	case FACIL:
	                /***               TAMANHO * DE LINHA            ***/
		printf ("                        FACIL!\n\n");
		break;
	case MEDIO:
		printf ("                      < MEDIO! >\n\n");
		break;
	case DIFICIL:
		printf ("                    << DIFICIL! >>\n\n");
		break;
	case SUPER_DIFICIL:
		printf ("              +<<<( SUPER DIFICIL! )>>>+\n\n");
		break;
	}
}

void boasVindas (void) {
	        /***               TAMANHO * DE LINHA            ***/
	printf ("\n\n\n\n\n"
	        "            Bem-vindo ao SHOW DO MILHAO!\n"           
	        "    Voce  sera  desafiado  a   varias  perguntas,\n"
		"    valendo premios  em  milhares de reais, porem\n"
		"    porem,  se errar apenas uma vez, voce perdera\n"
		"    TODO O SEU PREMIO. Preparado, jogador?\n\n");

	fflush (stdout);
	esperaEnter ();
}

resultado executa (const recursos rec, FILE *fPerguntas) {
	jogador    jog        =  {0, 0, JOGANDO, rec};
	pergunta*  pPerg      =  NULL;
	int        valorPerg  =  10000;
	char       resp       =  '\0';
	niveis     niv        =  FACIL;

	boasVindas();

	do {
		pPerg = pegaPergunta (niv, fPerguntas);
		printPergunta (*pPerg, jog.acertos + 1);

		resp = lerResposta();

		if (strchr (ALTERNATIVAS_AJUDA, resp)) {
			processaAjuda (&(jog.rec), resp, *pPerg);
		}

		if (resp == '5') {
			printf ("\n\n\n"
			        "    Voce decidiu PARAR  O  JOGO E VOLTAR PARA CASA!\n\n"
			        "\n\n\n");
			jog.estado = PAROU;
		}

		else if (resp == pPerg->altCorreta) { 
			printf ("    Voce escolheu (%c)!\n"
			        "    A resposta esta.... CORRETA!\n"
				" Voce GANHOU R$ %d,00!\n\n", 
			        resp, valorPerg);
			
			jog.acertos++;
			if (jog.acertos != 5 * niv && jog.acertos % (5*niv) == 0) {
				niv++;
				mensagemNivel (niv);
				if (niv == SUPER_DIFICIL)
					jog.estado = FINAL;
			}
		}

		else {
			jog.estado = ERROU;
		}

		if (pPerg)
			free (pPerg);
	} while (jog.estado == JOGANDO);

	// TODO : IMPLEMENTAR NÍVEL SUPER DIFÍCIL
	if (jog.estado == FINAL) {

	}

	return jog;
}

void mostraResultado (resultado res) {
	printf ("\n\n\n\n\n\n");

	switch (res.estado) {
	case VENCEU:
		printf("    PARABENS! Voce VENCEU o SHOW DO MILHAO!\n"
		       "    VOCE VOLTOU PARA CASA COM R$ %d,00\n\n\n",
		       res.premio);
		break;
	case ERROU:
		printf("    Que pena, você PERDEU o SHOW DO MILHAO!\n"
		       "        Voce perdeu TODO O DINHEIRO!\n"
		       "           Boa tentativa, jogador!\n\n\n");
		break;
	case PAROU:
		printf("    PARABENS! Apesar de nao chegar ao milhao,\n"
		       "       voce voltou para casa com R$ %d,00!\n\n\n",
		       res.premio);
	default:
		break;
	}
	printf ("\n\
    Acertos:           %d\n\
    Premio:         R$ %d,00\n\
    Recursos\n\
    nao usados:        %d pulos,\n\
                       %d ajudas universitarias,\n\
                       %d ajudas da plateia,\n\
                     e %d ajudas das cartas.\n\n\n", 
	
		res.acertos,
		res.premio,
		res.rec.pulosRest,
		res.rec.univRest,
		res.rec.plateiaRest,
		res.rec.cartasRest);

	fflush (stdout);
}


