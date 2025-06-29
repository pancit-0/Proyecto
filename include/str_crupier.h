#ifndef CRUPIER_H
#define CRUPIER_H

typedef struct{
	Jugador base;
	Carta* carta_oculta;
}Crupier;

void inicializar_crupier(Crupier* crupier);

const char* mostrar_carta_visible(Crupier* crupier);

void jugar(Crupier* crupier, Baraja* baraja);


#endif
