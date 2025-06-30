#include "juego.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

void inicializar_juego(Juego* juego) {

    inicializar_baraja(&juego->baraja);
    inicializar_jugador(&juego->jugador, "jugador");
    inicializar_crupier(&juego->crupier);
}

void reiniciar_juego(Juego* juego) {

    if (juego->crupier.carta_oculta != NULL) {
        free(juego->crupier.carta_oculta);
        juego->crupier.carta_oculta = NULL;
    }

    inicializar_baraja(&juego->baraja);
    inicializar_jugador(&juego->jugador, "jugador");
    inicializar_crupier(&juego->crupier);
    reiniciar_apuesta(&juego->jugador);
}

void cartas_iniciales(Juego* juego) {

    for (int i = 0; i < 2; i++) {
        Carta c = repartir(&juego->baraja);
        recibir_carta(&juego->jugador, c);
    }

    Carta c_visible = repartir(&juego->baraja);

    recibir_carta(&juego->crupier.base, c_visible);

    // Carta oculta para el crupier
    if (juego->crupier.carta_oculta != NULL) {
        free(juego->crupier.carta_oculta);
    }
    juego->crupier.carta_oculta = malloc(sizeof(Carta));
    if (juego->crupier.carta_oculta != NULL) {
        *(juego->crupier.carta_oculta) = repartir(&juego->baraja);
    }
}


