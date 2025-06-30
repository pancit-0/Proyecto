#include "gui.h"
#include "juego.h"
#include <string.h>

Boton CrearBoton(float x, float y, float w, float h, const char* text) { // Crea un boton con las coordenadas x, y, el ancho w, la altura h y el texto text en el boton
    Boton b;
    b.bounds = (Rectangle){ x, y, w, h }; // Inicia el rectangulo del boton con las coordenadas y dimensiones dadas
    b.label = text; // Asigna el texto del boton
    b.color = GRAY; // Color de los botones
    b.hoverColor = LIGHTGRAY; //Color del boton al pasar el raton por encima
    return b;
}

void DibujarBoton(Boton* b) {
    bool hovered = CheckCollisionPointRec(GetMousePosition(), b->bounds); // Comprueba si el raton esta sobre el boton 
    DrawRectangleRec(b->bounds, hovered ? b->hoverColor : b->color); 

    Vector2 textSize = MeasureTextEx(GetFontDefault(), b->label, 20, 1); // Mide el tamaño del texto para centrarlo en el boton
    DrawText(b->label,
             b->bounds.x + (b->bounds.width - textSize.x) / 2,
             b->bounds.y + (b->bounds.height - textSize.y) / 2,
             20, BLACK);
}

bool BotonFueClickeado(Boton* b) {  // Comprueba si el boton fue clickeado
    return IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
           CheckCollisionPointRec(GetMousePosition(), b->bounds);
}

GameMenu CrearMenu(int screenW, int screenH) { // Estructura del menu con 3 botones definida en el .h
    GameMenu menu;
    float bw = 200, bh = 50;  // Ancho y alto de los botones
    float bx = (screenW - bw) / 2;
    float by0 = (screenH / 2) - 1.5f * bh;

    menu.botones[0] = CrearBoton(bx, by0 + 0 * (bh + 20), bw, bh, "Jugar");  // Crea los botones con 20 pixeles de separacion entre ellos y centrados en la pantalla
    menu.botones[1] = CrearBoton(bx, by0 + 1 * (bh + 20), bw, bh, "Instrucciones");
    menu.botones[2] = CrearBoton(bx, by0 + 2 * (bh + 20), bw, bh, "Salir");

    return menu;
}

void DibujarMenu(GameMenu* m) { 
    ClearBackground(BROWN);  // Limpia el fonde de la ventana
    for (int i = 0; i < 3; i++) { // Dibuja los botones del menu llamando a la funcion DibujarBoton
        DibujarBoton(&m->botones[i]);
    }
}

int ActualizarMenu(GameMenu* menu) {
    for (int i = 0; i < 3; i++) {
        if (BotonFueClickeado(&menu->botones[i])) {
            return i + 1; // 1: Jugar, 2: Opciones, 3: Salir
        }
    }
    return 0;
}