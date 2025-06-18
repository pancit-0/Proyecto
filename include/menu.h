#ifndef MENU_H
#define MENU_H

#include "raylib.h"

typedef struct {
    Rectangle bounds; // Distribucion del area del boton
    const char* label;  // Texto usado en el boton
    Color color; // Color del boton
    Color hoverColor; // Color al pasar el raton por encima 
} Boton;

typedef struct {  // Estructura del menu con 3 botones
    Boton botones[3];
} GameMenu;

Boton CrearBoton(float x, float y, float w, float h, const char* text); //Crea un boton con las coordenadas x, y, el anccho w, la altura h y el texto  "text" en boton
void DibujarBoton(Boton* b);       // Dibuja el boton en la patalla
bool BotonFueClickeado(Boton* b);  // Verifica si el boton fue clickeado

GameMenu CrearMenu(int screenW, int screenH);
void DibujarMenu(GameMenu* m); // Dibuja el menu en la pantalla 
int ActualizarMenu(GameMenu* m); // Actualiza el menu y devuelve la opcion seleccionada
void DestruirMenu(GameMenu* m); // Libera los recursos del menu en la memoria

#endif
