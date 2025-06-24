#include <stdio.h>
#include <string.h>
#include <time.h>
#include "baraja.h"
#include "carta.h"

void inicializar_baraja(Baraja *baraja) {
	char *valores[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
       	char *palos[] = {"Diamantes", "Picas", "Corazones", "Tréboles"};
	int posicion = 0;
	
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 4; j++) {
			strcpy(baraja->cartas[posicion].valor, valores[i]);
			strcpy(baraja->cartas[posicion].palo, palos[j]);
			posicion++;
		}
	}
	baraja->cantidad = NUM_CARTAS;
	mezclar_baraja(baraja);
}

void mezclar_baraja(Baraja *baraja) {
	srand(time(NULL));
	for (int i = 0; i < baraja->cantidad; i++) {
		int j = ran() % baraja->cantidad;
		Carta temp = baraja->cantidad;
		baraja->cartas[i] = baraja->cartas[j];
		baraja->cartas[j] = temp;
	}
}

Carta repartir(Baraja *baraja) {
	if (baraja->cantidad == 0) {
		inicializar_baraja(baraja);
	}
	return baraja->cartas[--baraja->cantidad];
}

