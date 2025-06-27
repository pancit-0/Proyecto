#ifndef JUGADOR_H
#define JUGADOR_H

#define NOMBRE_MAX 30
#define CARTAS_MAX 20
typedef struct {
	char nombre[NOMBRE_MAX];
	int mano[CARTAS_MAX];
	int cantidad_cartas;
	int saldo;
	int apuesta;
}Jugador;

void recibir_carta(Jugador *j, int carta);

void inicializar_jugador(Jugador *j, const char *nombre);

int obtener_puntaje(Jugador *j);

char* mostrar_mano(Jugador *j);

bool esta_dentro_juego(Jugador *j);

bool realizar_apuesta(Jugador *j, int monto);

void actualizar_saldo_ganador(Jugador *j);

void actualizar_saldo_perdedor(Jugador *j);

void reiniciar_apuesta(Jugador *j);

#endif
