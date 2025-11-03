#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "executa.h"
#include "milhao.h"

void executaEtapa (jogador* pJog, FILE *fPerg) {
	static pergunta perg  =  {'\0', " ", {" "," "," "," "}, '\0'};
	static char resp      =  '\0';
	static niveis niv     =  FACIL;
	static int valorPerg  =  10000;

	atualizaPergunta (niv, fPerg, &perg);
	printPergunta (perg, pJog->acertos + 1);
	printAjuda (pJog->rec);

	resp = lerResposta();

	while (strchr (ALTERNATIVAS_AJUDA, resp)) {
		processaAjuda (&(pJog->rec), resp, perg);

		if (resp == '1' && (pJog->rec.pulosRest >= 1)) {
			atualizaPergunta  (niv, fPerg, &perg);
			printPergunta     (perg, pJog->acertos + 1);
			printAjuda        (pJog->rec);
		}

		resp = lerResposta();
	}
	
	if (resp == '5') {
		printf ("\n\n\n"
		        "    Voce decidiu PARAR  O  JOGO E VOLTAR PARA CASA!\n\n"
		        "\n\n\n");
		pJog->estado = PAROU;
	}

	else if (processaResposta (resp, perg) == 1) { 
		(pJog->premio) += valorPerg;
		(pJog->acertos)++;
			
		printf ("    Voce GANHOU R$ %d,00!\n\n", valorPerg);
		
		if (niv == SUPER_DIFICIL)
			pJog->estado = VENCEU;
		else if ((pJog->acertos) >= 5 * niv) {
			valorPerg *= 10;
			niv++;
			mensagemNivel (niv);
		}
	}

	else {
		pJog->estado = ERROU;
		pJog->premio = 0;
	}

	esperaEnter();
}

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

	fflush (stdout);
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

resultado executa (const recursos rec, FILE *fPerguntas) {
	jogador jog = {0, 0, JOGANDO, rec};
	
	boasVindas();

	do     executaEtapa (&jog, fPerguntas);
	while  (jog.estado == JOGANDO);

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

