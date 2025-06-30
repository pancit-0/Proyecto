# Compilador
CC = gcc

# Archivos fuente
SRC = src/juego.c \
      src/str_baraja.c \
      src/str_carta.c \
      src/str_crupier.c \
      src/str_jugador.c

GUI = gui/gui.c
MAIN = main.c

# Directorios de cabeceras
INCLUDES = -Iinclude -Igui

# Archivos de salida
OUT = juego.exe

# Detección del sistema operativo
ifeq ($(OS),Windows_NT)
    RM = del /Q
    LIBS = -Llib -lraylib -lwinmm -lgdi32
    OUT = juego.exe
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        RM = rm -f
        LIBS = -lraylib -lm -ldl -lpthread -lGL -lrt -lX11
        OUT = juego
    else ifeq ($(UNAME_S),Darwin)
        RM = rm -f
        LIBS = -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
        OUT = juego
    endif
endif

# Flags de compilación
CFLAGS = -Wall -Wextra $(INCLUDES)

# Objetivo por defecto
all: $(OUT)

# Regla de compilación
$(OUT): $(SRC) $(GUI) $(MAIN)
	$(CC) $(CFLAGS) $(SRC) $(GUI) $(MAIN) -o $(OUT) $(LIBS)

# Limpieza de archivos
clean:
	$(RM) $(OUT)

.PHONY: all clean
