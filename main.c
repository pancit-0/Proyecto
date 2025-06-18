#include "raylib.h"
#include "menu.h"

int main() {
    const int screenW = 800; // Dimensiones de la ventana
    const int screenH = 600;
    InitWindow(screenW, screenH, "Menu C - Raylib"); // Funcion de raylib que crea la ventana "Menu C - Raylib"
    //InitAudioDevice();  // Futuro audio
    SetTargetFPS(60); // FPS objetivo

    GameMenu menu = CrearMenu(screenW, screenH); // Crea el menu y los botones sentrados en la pantalla 

    while (!WindowShouldClose()) { // Bucle principal del juego, mantiene el menu activo y se repite 60 veces por segundo
        int choice = ActualizarMenu(&menu); // Actualiza el menu y devuelve la opcion seleccionada
        switch (choice) { // Elige opcion segun la opcion (en el futuro cambiara) 
            case 1: CloseWindow(); return 0; // Cierra la ventana y termina el programa al precionarse un boton
            case 2: CloseWindow(); return 0;
            case 3: CloseWindow(); return 0;
        }

        BeginDrawing(); // Inicia el dibujo de la ventana (el nuevo frame)
        DibujarMenu(&menu); // Dibuja el menu en la ventana segun los valores obtenidos en el bucle anterior
        EndDrawing(); //Termina el dibujo de la ventana 
    }

    //DestruirMenu(&menu); Futuro audio
    //CloseAudioDevice();
    CloseWindow(); // Al salir del bucle cierra la ventana y libera los recursos de raylib
    return 0;
}
