
CC = gcc
SRC = main.c src/menu.c
OUT = menu.exe

# Headers desde include
CFLAGS = -Wall -Iinclude

# Enlace del .a
LDFLAGS = lib/libraylib.a -lopengl32 -lgdi32 -lwinmm

#Reglas
all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

# Clear
clean:
	del $(OUT)
