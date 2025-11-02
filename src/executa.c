#include <stdio.h>
#include <stdlib.h>
#include "executa.h"

resultado executa (const recursos rec, FILE *fPerguntas) {
	jogador jog = {0, 0, 0, 0, rec};

	return jog;
}

void mostraResultado (resultado res) {
	printf ("\n\
    PARABENS, voce %s o SHOW DO MILHAO!\n\n\n\
Acertos:           %d\n\
Premio:         R$ %d,00\n\
Recursos\n\
nao usados:        %d pulos,\n\
                   %d ajudas universitarias,\n\
                   %d ajudas da plateia,\n\
                 e %d ajudas das cartas.\n\n\n", 
	
		res.errou ? 
		"<PERDEU>" : (res.venceu ? 
			"<GANHOU>" : "<INTERROMPEU>"),
		res.acertos,
		res.premio,
		res.rec.pulosRest,
		res.rec.univRest,
		res.rec.plateiaRest,
		res.rec.cartasRest);

	fflush (stdin);
}


