#include "str_jugador.h"
#include "str_carta.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void recibir_carta(Jugador *j, Carta carta){
	if (j->cantidad_cartas < CARTAS_MAX){
		j->mano[j->cantidad_cartas] = carta;
		j->cantidad_cartas++;
	}else {
		//printf("La mano %s ya está llena.\n", j->nombre);
	}
}

void inicializar_jugador(Jugador *j, const char *nombre){
	strncpy(j->nombre, nombre, NOMBRE_MAX);
	j->nombre[NOMBRE_MAX - 1] = '\0';
	j->cantidad_cartas = 0;
	j->saldo = 3000;
	j->apuesta = 0;
}

int obtener_puntaje(Jugador *j){
	int puntaje = 0;
	int ases = 0;

	for (int i = 0; i < j->cantidad_cartas; i++){
		int valor = obtener_valor(&j->mano[i]);
		puntaje += valor;
		if (valor == 11){
			ases++;
		}
	}

	while (puntaje > 21 && ases > 0){
		puntaje -= 10;
		ases--;
	}

	return puntaje;
}

char* mostrar_mano(Jugador *j){
	char* resultado = malloc(CARTAS_MAX * 21);
	if (resultado == NULL) return NULL;

	resultado[0] = '\0';


	for (int i = 0; i < j->cantidad_cartas; i++){
		char * carta_str = carta_a_cadena(j->mano[i]);
		strcat(resultado, carta_str);
		if (i < j->cantidad_cartas - 1){
			strcat(resultado, ",");

		}
		free(carta_str);
	}
	return resultado;

}


bool esta_dentro_juego(Jugador *j){
	return obtener_puntaje(j) <= 21;
}

bool realizar_apuesta(Jugador *j, int monto){
	if (monto < 300){
		//printf("Apuesta mínima requerida es 300""\n");
			return false;
	}

	if (monto > j->saldo){
		//printf("Apuesta inválida, el monto no puede ser mayor al saldo.""\n");
		return false;
	}

	j->apuesta = monto;
	j->saldo -= monto;
	return true;


}

void actualizar_saldo_ganador(Jugador *j){
	j->saldo += (j->apuesta * 2);

}

void reiniciar_apuesta(Jugador *j){
	j->apuesta = 0;
}

void reiniciar_mano(Jugador *j){
	j->cantidad_cartas = 0;
}