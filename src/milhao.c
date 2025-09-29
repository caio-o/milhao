#include <stdio.h>
#include <stdlib.h>
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
