#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "raylib.h"
#include "gui/gui.h"
#include "juego.h"

int main() {
    const int screenW = 800;
    const int screenH = 600;

    SetExitKey(KEY_NULL); 
    InitWindow(screenW, screenH, "Blackjack - Raylib");
    SetTargetFPS(60);

    GameMenu menu = CrearMenu(screenW, screenH);
    int estado = 0; 
    char resultado[128] = "";

    int monto_apuesta = 700;
    Juego juego;
    bool turnoJugador = true;
    bool juegoTerminado = false;

    inicializar_juego(&juego);

    while (!WindowShouldClose()) {
        switch (estado) {
            case 0: { 
                int choice = ActualizarMenu(&menu); 
                if (choice == 1) {
                    if (juego.jugador.saldo >= 700 && juego.jugador.saldo < 6000) {
                        estado = 3;
                        monto_apuesta = (juego.jugador.saldo >= 700) ? 700 : juego.jugador.saldo;
                    }
                } else if (choice == 2) {
                    estado = 2;
                } else if (choice == 3) {
                    CloseWindow();
                    return 0;
                }
            } break;

            case 2: {  // INSTRUCCIONES
                if (IsKeyPressed(KEY_Q)) {
                    estado = 0;
                }
            } break;

            case 3: { // APUESTA
                if (IsKeyPressed(KEY_UP)) {
                    if (monto_apuesta + 50 <= juego.jugador.saldo)
                        monto_apuesta += 50;
                }
                if (IsKeyPressed(KEY_DOWN)) {
                    if (monto_apuesta - 50 >= 700)
                        monto_apuesta -= 50;
                }
                if (IsKeyPressed(KEY_ENTER)) {

                    if (monto_apuesta > juego.jugador.saldo) {
                        monto_apuesta = juego.jugador.saldo;

                    }


                    if (realizar_apuesta(&juego.jugador, monto_apuesta)) {
                        reiniciar_mano(&juego.jugador); //Reiniciar mano del jugador
                        reiniciar_mano_crupier(&juego.crupier); //Reiniciar mano del crupier
                        juego.crupier.carta_oculta = NULL; // Reiniciar carta oculta del crupier


                        cartas_iniciales(&juego);
                        turnoJugador = true;
                        juegoTerminado = false;
                        resultado[0] = '\0';
                        estado = 1;
                    }
                }
                if (IsKeyPressed(KEY_ESCAPE)) {
                    estado = 0;
                }
            } break;

            case 1: { // JUEGO
                if (!juegoTerminado) {
                    if (turnoJugador) {
                        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                            Carta nueva = repartir(&juego.baraja);
                            recibir_carta(&juego.jugador, nueva);
                            if (!esta_dentro_juego(&juego.jugador)) {
                                juegoTerminado = true;
                                snprintf(resultado, sizeof(resultado),
                                         "Te pasaste de 21 con %d. El crupier gana :( ",
                                         obtener_puntaje(&juego.jugador));
                            }
                        }
                        if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
                            turnoJugador = false;
                        }
                    } else {
                        turno_crupier(&juego);
                        juegoTerminado = true;

                        int pj = obtener_puntaje(&juego.jugador);
                        int pc = obtener_puntaje(&juego.crupier.base);

                        if (pc > 21 || pj > pc) {
                            snprintf(resultado, sizeof(resultado), "El jugador gana! :D");
                            actualizar_saldo_ganador(&juego.jugador);
                        } else if (pj < pc) {
                            snprintf(resultado, sizeof(resultado), "El crupier gana :(");
                        } else {
                            snprintf(resultado, sizeof(resultado), "Empate :|");
                            juego.jugador.saldo += juego.jugador.apuesta;
                        }

                        reiniciar_apuesta(&juego.jugador);

                        if (juego.jugador.saldo < 700 || juego.jugador.saldo >= 6000) {
                            estado = 4; // fin del juego cuando el jugador duplica la plata
                        }
                    }
                } else {
                    if (IsKeyPressed(KEY_ENTER)) {
                        if (juego.jugador.saldo >= 700 && juego.jugador.saldo < 6000) {
                            monto_apuesta = (juego.jugador.saldo >= 700) ? 700 : juego.jugador.saldo;
                            estado = 3; 
                        }
                    }
                    if (IsKeyPressed(KEY_ESCAPE)) {
                        estado = 0;
                    }

                    if (IsKeyPressed(KEY_Q)) {
                        CloseWindow();
                        return 0;
                    }
                }
            } break;

            case 4: { // FIN DEL JUEGO (ganó o se quedó sin plata)
                if (IsKeyPressed(KEY_ENTER)) {
                    estado = 0;
                    inicializar_juego(&juego);
                    monto_apuesta = 700;
                }
            } break;
        }

        BeginDrawing();
        ClearBackground(BEIGE);

        switch (estado) {
            case 0:
                DibujarMenu(&menu);
                break;

            case 1: {
                DrawText("BLACKJACK", 320, 10, 30, BLACK);

                char buf[128];
                sprintf(buf, "Tu puntaje: %d", obtener_puntaje(&juego.jugador));
                DrawText(buf, 50, 60, 20, BLACK);

                sprintf(buf, "Plata: %d", juego.jugador.saldo);
                DrawText(buf, 600, 60, 20, DARKGREEN);
                sprintf(buf, "Apuesta: %d", juego.jugador.apuesta);
                DrawText(buf, 600, 90, 20, MAROON);


                if (!juegoTerminado) {
                    const char* carta_visible = mostrar_carta_visible(&juego.crupier);
                    DrawText(TextFormat("Crupier: %s, ?", carta_visible), 50, 90, 20, BLACK);
                } else {
                    sprintf(buf, "Crupier: %d", obtener_puntaje(&juego.crupier.base));
                    DrawText(buf, 50, 90, 20, BLACK);
                }

                // Mostrar mano del jugador
                char* mano_j = mostrar_mano(&juego.jugador);
                DrawText(mano_j, 50, 130, 20, DARKGREEN);
                free(mano_j);

                // Mostrar mano del crupier
                if (!juegoTerminado) {
                    DrawText(mostrar_carta_visible(&juego.crupier), 50, 160, 20, DARKBLUE);
                } else {
                    char* mano_c = mostrar_mano(&juego.crupier.base);
                    DrawText(mano_c, 50, 160, 20, DARKBLUE);
                    free(mano_c);
                }

                DrawText("Click izquierdo = Pedir carta", 50, 300, 20, GRAY);
                DrawText("Click derecho = Plantarse", 50, 330, 20, GRAY);

                if (juegoTerminado) {
                    DrawText(resultado, 50, 380, 25, RED);
                    if (juego.jugador.saldo >= 700 && juego.jugador.saldo < 6000)
                        DrawText("ENTER para apostar otra vez", 50, 420, 20, DARKGRAY);
                }
            } break;

            case 2:
                DrawText("INSTRUCCIONES", 50, 40, 25, DARKGRAY);

                DrawText("Este es un juego clásico de Blackjack con apuestas.", 50, 80, 20, GRAY);
                DrawText("El objetivo es acercarse lo más posible a 21 sin pasarse.", 50, 110, 20, GRAY);
                DrawText("Jugás contra el crupier, quien tambien recibe cartas aleatoreamente.", 50, 140, 20, GRAY);

                DrawText("Controles durante el juego:", 50, 190, 22, DARKBLUE);
                DrawText("- Click izquierdo: Pedir carta", 70, 220, 20, GRAY);
                DrawText("- Click derecho : Plantarse", 70, 250, 20, GRAY);

                DrawText("Controles durante la apuesta:", 50, 300, 22, DARKBLUE);
                DrawText("- Flechas arriba/abajo: Cambiar monto de apuesta de 50 en 50", 70, 330, 20, GRAY);
                DrawText("- ENTER: Confirmar apuesta o continuar", 70, 360, 20, GRAY);
                DrawText("- ESC: Cerrar el programa", 70, 420, 20, GRAY);
                DrawText("- Q: Para volver al menú", 70, 480, 20, GRAY);
                break;

            case 3:
                {
                    char texto[128];
                    sprintf(texto, "Colones disponibles: %d", juego.jugador.saldo);
                    DrawText(texto, 50, 50, 30, DARKGREEN);
                    sprintf(texto, "Apuesta actual: %d", monto_apuesta);
                    DrawText(texto, 50, 100, 30, DARKBLUE);
                    DrawText("Flechas ARRIBA/ABAJO para cambiar la apuesta", 50, 200, 20, GRAY);
                    DrawText("ENTER para confirmar la apuesta", 50, 240, 20, GRAY);
                }
                break;

            case 4:
                if (juego.jugador.saldo < 700) {
                    DrawText("Te quedaste sin plata :(", 200, 200, 30, RED);
                } else {
                    DrawText("Felicidades! Alcanzaste 6000 colones :D", 100, 200, 30, GREEN);
                }
                DrawText("ENTER para volver al menú", 200, 260, 20, GRAY);
                break;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
