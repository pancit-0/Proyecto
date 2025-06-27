#include "str_carta.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int obtener_valor(Carta *carta) {
	if (strcmp(carta->valor, "J") == 0 || strcmp(carta->valor, "Q") == 0 || strcmp(carta->valor, "K") == 0) {
                return 10;
	} else if (strcmp(carta->valor, "A") == 0) {
                return 11;
	} else { 
                return atoi(carta->valor);
	}
}

void imprimir_carta(Carta *carta) {
	printf("%s de %s", carta->valor, carta->palo);
}
