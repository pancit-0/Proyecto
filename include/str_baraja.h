#ifndef BARAJA_H
#define BARAJA_H

#define NUM_CARTAS 52

typedef struct {
	Carta cartas[NUM_CARTAS];
	int cantidad;
} Baraja;

void inicializar_baraja(Baraja *baraja);
void mezclar_baraja(Baraja *baraja);
Carta repartir(Baraja *baraja);

#endif
