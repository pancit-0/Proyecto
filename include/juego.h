#ifndef JUEGO_H
#define JUEGO_H

#include "str_jugador.h"
#include "str_baraja.h" 
#include "str_crupier.h"
#include <stdbool.h>


typedef struct Juego {
    Baraja baraja;
    Jugador jugador;
    Crupier crupier;
} Juego;

void inicializar_juego(Juego* juego);
void reiniciar_juego(Juego* juego);
void cartas_iniciales(Juego* juego);
void mostrar_mano_jugador(Juego* juego);
bool turno_jugador(Juego* juego);
void turno_crupier(Juego* juego);
void ganador_juego(Juego* juego);
void jugar(Juego* juego);

#endif 