#ifndef CARTA_H
#define CARTA_H

typedef struct {
	char valor[20];
	char palo[20];
}Carta;

int obtener_valor(Carta *carta);
//void imprimir_carta(Carta *carta);
char* carta_a_cadena(Carta carta);

#endif
