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
        Carta c1 = repartir(&juego->baraja);
        recibir_carta(&juego->jugador, c1);
        Carta c2 = repartir(&juego->baraja);
        recibir_carta(&juego->crupier.base, c2);

        juego->crupier.carta_oculta = malloc(sizeof(Carta));
        if (juego->crupier.carta_oculta != NULL) {
            *(juego->crupier.carta_oculta) = repartir(&juego->baraja);
        } else {
            printf("Error al asignar carta oculta al crupier.\n");
        }
    }

}

void mostrar_mano_jugador(Juego* juego) {
    char* mano_jugador = mostrar_mano(&juego->jugador);
    if (mano_jugador != NULL) {
        printf("Tu mano: %s (Puntaje: %d)\n", mano_jugador, obtener_puntaje(&juego->jugador));
        free(mano_jugador);
    } else {
        printf("Error al mostrar la mano del jugador.\n");
    }
}

bool turno_jugador(Juego* juego) {
    char accion[20];
    while (esta_dentro_juego(&juego->jugador)) {
        mostrar_mano_jugador(juego);
        printf("¿Qué deseas hacer? (pedir/plantarse): ");
        scanf("%s", accion);

            if (strcmp(accion, "pedir") == 0) {
                Carta nueva = repartir(&juego->baraja);
                recibir_carta(&juego->jugador, nueva);
            
                
        }   else if (strcmp(accion, "plantarse") == 0) {
                break; // Termina el turno si el jugador se planta
        }   else {
                printf("Acción no válida. Intenta de nuevo.\n");
        }
    } 
    if (!esta_dentro_juego(&juego->jugador)) {
        //mostrar_estado(juego);
        printf("Te has pasado de 21. ¡Has perdido!\n");
        return false; 
    }

    return true;
}

void turno_crupier(Juego* juego) {
    recibir_carta(&juego->crupier.base, *juego->crupier.carta_oculta); 
    char* mano = mostrar_mano(&juego->crupier.base); // Añadir la carta oculta a la mano del crupier
    printf("Mano completa del crupier: %s (Puntaje: %d)\n", mano, obtener_puntaje(&juego->crupier.base));
    free(mano); 

    while (crupier_debe_pedir(&juego->crupier)) {
        Carta c = repartir(&juego->baraja);
        recibir_carta(&juego->crupier.base, c);
        mano = mostrar_mano(&juego->crupier.base);
        printf("El crupier pide una carta: %s (Puntaje: %d)\n", mano, obtener_puntaje(&juego->crupier.base));
        free(mano);
    }

    printf("El crupier se planta con un puntaje de %d.\n", obtener_puntaje(&juego->crupier.base));
}

void ganador_juego(Juego* juego) {
    int puntaje_jugador = obtener_puntaje(&juego->jugador);
    int puntaje_crupier = obtener_puntaje(&juego->crupier.base);

    if (puntaje_jugador > 21) {
        printf("El jugador se ha pasado de 21. El crupier gana  :(\n");
        actualizar_saldo_perdedor(&juego->jugador);
    } else if (puntaje_crupier > 21 || puntaje_jugador > puntaje_crupier) {
        printf("¡El jugador gana!   esooo  :D\n");
        actualizar_saldo_ganador(&juego->jugador);
    } else if (puntaje_jugador < puntaje_crupier) {
        printf("El crupier gana  :(\n");
        actualizar_saldo_perdedor(&juego->jugador);
    } else {
        printf("Es un empate.  :|\n");
    }
}

void jugar(Juego* juego) {
    cartas_iniciales(juego);

    if (!turno_jugador(juego)) {
        return; 
    }

    turno_crupier(juego);
    ganador_juego(juego);
}

