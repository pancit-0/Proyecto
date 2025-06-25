#include "crupier.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void inicializar_crupier(Crupier* crupier){
	inicializar_jugador(&(crupier->base), "crupier");
	crupier->carta_oculta = NULL;
}

const char* mostrar_carta_visible(Crupier* crupier){
	if (crupier->base.cantidad_cartas > 0){
		return carta_a_string(crupier->base.mano[0]);
		
	}else{
		return "Sin cartas";
	}
}

void jugar(Crupier* crupier, Baraja* baraja){
	while (obtener_puntaje(&crupier->base) < 17){
		Carta* nueva_carta = baraja_repartir(baraja);
		if (nueva_carta != NULL){
			recibir_carta(&crupier->base, nueva_carta);
		}else {
			break;
		}
	}
}

