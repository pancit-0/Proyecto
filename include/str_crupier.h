#ifndef STR_CRUPIER_H
#define STR_CRUPIER_H

#include "str_jugador.h"
#include "str_baraja.h"

typedef struct {
    Jugador base;
    Carta* carta_oculta;
} Crupier;

void reiniciar_mano_crupier(Crupier *c);

void inicializar_crupier(Crupier* crupier);

bool crupier_debe_pedir(Crupier* crupier);

const char* mostrar_carta_visible(Crupier* crupier);

void jugar_crupier(Crupier* crupier, Baraja* baraja);

#endif