#include "juego.h"
#include <stdio.h>


int main() {
    Juego juego;
    inicializar_juego(&juego);
    return 0;

    while (1) {
        jugar(&juego);
        char respuesta[10];
        printf("¿Deseas jugar otra vez partida? (si/no): ");
        scanf("%s", respuesta);
        if (strcmp(respuesta, "si") != 0) {
            printf("Gracias por jugar. ¡Hasta luego!\n");
            break;
        } else {
            reiniciar_juego(&juego);
        }
    }
    return 0;
}
