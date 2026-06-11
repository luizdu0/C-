# --- Variáveis do Compilador ---
CC = gcc
CFLAGS = -Wall -Wextra -g

# --- Principal ---
all: gerador cubo

# --- Regra para o Gerador ---
gerador: gerador.c cubinho.c cubo.h
	$(CC) $(CFLAGS) gerador.c cubinho.c -o gerador

# --- Regra para o cubo.c (COM NCURSES) ---
cubo: cubo.c cubinho.c cubo.h
	$(CC) $(CFLAGS) cubo.c cubinho.c -o cubo -lncurses

# --- Limpeza ---
clean:
	rm -f gerador cubo *.txt

.PHONY: all clean