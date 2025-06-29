CC = gcc
CFLAGS = -Wall -I. -I./src -I./include

SRC = mainjuego.c src/juego.c src/str_baraja.c src/str_carta.c src/str_crupier.c src/str_jugador.c
EXEC = juego

all: $(EXEC)

$(EXEC): $(SRC)
	$(CC) $(CFLAGS) -o $(EXEC) $(SRC)

clean:
	del $(EXEC) *.o
