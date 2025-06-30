#include "str_crupier.h"
#include "str_jugador.h"
#include "str_carta.h"
#include "str_baraja.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "juego.h"

void inicializar_crupier(Crupier* crupier){
    inicializar_jugador(&(crupier->base), "crupier");
    crupier->carta_oculta = NULL;
}

bool crupier_debe_pedir(Crupier* crupier){
    return obtener_puntaje(&crupier->base) < 17;
}

const char* mostrar_carta_visible(Crupier* crupier){
    if (crupier->base.cantidad_cartas > 0){
        return carta_a_cadena(crupier->base.mano[0]);
    } else {
        return "Sin cartas";
    }
}

void reiniciar_mano_crupier(Crupier *c) {
    reiniciar_mano(&(c->base));
    c->carta_oculta = NULL;
}


void jugar_crupier(Crupier* crupier, Baraja* baraja){
    while (obtener_puntaje(&crupier->base) < 17){
        Carta nueva_carta = repartir(baraja);
        recibir_carta(&crupier->base, nueva_carta);        
    }
}

void turno_crupier(Juego* juego) {
    recibir_carta(&juego->crupier.base, *juego->crupier.carta_oculta);

    while (crupier_debe_pedir(&juego->crupier)) {
        Carta c = repartir(&juego->baraja);
        recibir_carta(&juego->crupier.base, c);
    }
}
