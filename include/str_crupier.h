#ifndef CRUPIER_H
#define CRUPIER_H
#include "str_jugador.h"
#include "str_carta.h"
#include "str_baraja.h"

typedef struct{
	Jugador base;
	Carta* carta_oculta;
}Crupier;

void inicializar_crupier(Crupier* crupier);

const char* mostrar_carta_visible(Crupier* crupier);

void jugar_crupier(Crupier* crupier, Baraja* baraja);

bool crupier_debe_pedir(Crupier* crupier);

#endif
