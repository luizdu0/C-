// ARQUIVO ROTACAO CUBO
#include <stdio.h>
#include "cubo.h"

// Declaração real das variáveis globais
int cubo[6][3][3];
const char* nome_faces[6] = {"CIMA", "BAIXO", "ESQUERDA", "DIREITA", "FRENTE", "TRAS"};
const char* nome_direcoes[2] = {"HORARIO", "ANTIHORARIO"};
const char letras_cores[6] = {'Y', 'G', 'R', 'O', 'W', 'B'};

void inicializa_cubo_resolvido() {
    for (int f = 0; f < 6; f++) {
        for (int l = 0; l < 3; l++) {
            for (int c = 0; c < 3; c++) {
                cubo[f][l][c] = f; 
            }
        }
    }
}

int cubo_esta_resolvido() {
    for (int f = 0; f < 6; f++) {
        int centro = cubo[f][1][1]; 
        for (int l = 0; l < 3; l++) {
            for (int c = 0; c < 3; c++) {
                if (cubo[f][l][c] != centro) return 0;
            }
        }
    }
    return 1;
}

void imprime_cubo() {
    // Função de debug simplificada
    printf("Face CIMA:\n");
    for(int l=0; l<3; l++) {
        for(int c=0; c<3; c++) printf("%c ", letras_cores[cubo[CIMA][l][c]]);
        printf("\n");
    }
    printf("\n");
}

// Gira a matriz 3x3 da própria face em 90 graus
void gira_face_90_graus(int f, int direcao) {
    int temp[3][3];
    for (int l = 0; l < 3; l++) {
        for (int c = 0; c < 3; c++) {
            if (direcao == HORARIO) temp[c][2 - l] = cubo[f][l][c];
            else                    temp[2 - c][l] = cubo[f][l][c];
        }
    }
    for (int l = 0; l < 3; l++) {
        for (int c = 0; c < 3; c++) {
            cubo[f][l][c] = temp[l][c];
        }
    }
}

void rotacao(int face, int direcao) {
    // 1. Gira a face 3x3
    gira_face_90_graus(face, direcao);

    // 2. Gira as faixas adjacentes
    int temp[3];
    
    if (face == CIMA) {
        if (direcao == HORARIO) {
            for(int i=0; i<3; i++) temp[i] = cubo[FRENTE][0][i];
            for(int i=0; i<3; i++) cubo[FRENTE][0][i] = cubo[DIREITA][0][i];
            for(int i=0; i<3; i++) cubo[DIREITA][0][i] = cubo[TRAS][0][i];
            for(int i=0; i<3; i++) cubo[TRAS][0][i] = cubo[ESQUERDA][0][i];
            for(int i=0; i<3; i++) cubo[ESQUERDA][0][i] = temp[i];
        } else {
            for(int i=0; i<3; i++) temp[i] = cubo[FRENTE][0][i];
            for(int i=0; i<3; i++) cubo[FRENTE][0][i] = cubo[ESQUERDA][0][i];
            for(int i=0; i<3; i++) cubo[ESQUERDA][0][i] = cubo[TRAS][0][i];
            for(int i=0; i<3; i++) cubo[TRAS][0][i] = cubo[DIREITA][0][i];
            for(int i=0; i<3; i++) cubo[DIREITA][0][i] = temp[i];
        }
    } 
    else if (face == BAIXO) {
        if (direcao == HORARIO) {
            for(int i=0; i<3; i++) temp[i] = cubo[FRENTE][2][i];
            for(int i=0; i<3; i++) cubo[FRENTE][2][i] = cubo[ESQUERDA][2][i];
            for(int i=0; i<3; i++) cubo[ESQUERDA][2][i] = cubo[TRAS][2][i];
            for(int i=0; i<3; i++) cubo[TRAS][2][i] = cubo[DIREITA][2][i];
            for(int i=0; i<3; i++) cubo[DIREITA][2][i] = temp[i];
        } else {
            for(int i=0; i<3; i++) temp[i] = cubo[FRENTE][2][i];
            for(int i=0; i<3; i++) cubo[FRENTE][2][i] = cubo[DIREITA][2][i];
            for(int i=0; i<3; i++) cubo[DIREITA][2][i] = cubo[TRAS][2][i];
            for(int i=0; i<3; i++) cubo[TRAS][2][i] = cubo[ESQUERDA][2][i];
            for(int i=0; i<3; i++) cubo[ESQUERDA][2][i] = temp[i];
        }
    }
    else if (face == FRENTE) {
        if (direcao == HORARIO) {
            for(int i=0; i<3; i++) temp[i] = cubo[CIMA][2][i];
            for(int i=0; i<3; i++) cubo[CIMA][2][i] = cubo[ESQUERDA][2-i][2];
            for(int i=0; i<3; i++) cubo[ESQUERDA][i][2] = cubo[BAIXO][0][i];
            for(int i=0; i<3; i++) cubo[BAIXO][0][i] = cubo[DIREITA][2-i][0];
            for(int i=0; i<3; i++) cubo[DIREITA][i][0] = temp[i];
        } else {
            for(int i=0; i<3; i++) temp[i] = cubo[CIMA][2][i];
            for(int i=0; i<3; i++) cubo[CIMA][2][i] = cubo[DIREITA][i][0];
            for(int i=0; i<3; i++) cubo[DIREITA][i][0] = cubo[BAIXO][0][2-i];
            for(int i=0; i<3; i++) cubo[BAIXO][0][i] = cubo[ESQUERDA][i][2];
            for(int i=0; i<3; i++) cubo[ESQUERDA][i][2] = temp[2-i];
        }
    }
    else if (face == TRAS) {
        if (direcao == HORARIO) {
            for(int i=0; i<3; i++) temp[i] = cubo[CIMA][0][i];
            for(int i=0; i<3; i++) cubo[CIMA][0][i] = cubo[DIREITA][i][2];
            for(int i=0; i<3; i++) cubo[DIREITA][i][2] = cubo[BAIXO][2][2-i];
            for(int i=0; i<3; i++) cubo[BAIXO][2][i] = cubo[ESQUERDA][i][0];
            for(int i=0; i<3; i++) cubo[ESQUERDA][i][0] = temp[2-i];
        } else {
            for(int i=0; i<3; i++) temp[i] = cubo[CIMA][0][i];
            for(int i=0; i<3; i++) cubo[CIMA][0][i] = cubo[ESQUERDA][2-i][0];
            for(int i=0; i<3; i++) cubo[ESQUERDA][i][0] = cubo[BAIXO][2][i];
            for(int i=0; i<3; i++) cubo[BAIXO][2][i] = cubo[DIREITA][2-i][2];
            for(int i=0; i<3; i++) cubo[DIREITA][i][2] = temp[i];
        }
    }
    else if (face == ESQUERDA) {
        if (direcao == HORARIO) {
            for(int i=0; i<3; i++) temp[i] = cubo[CIMA][i][0];
            for(int i=0; i<3; i++) cubo[CIMA][i][0] = cubo[TRAS][2-i][2];
            for(int i=0; i<3; i++) cubo[TRAS][i][2] = cubo[BAIXO][2-i][0];
            for(int i=0; i<3; i++) cubo[BAIXO][i][0] = cubo[FRENTE][i][0];
            for(int i=0; i<3; i++) cubo[FRENTE][i][0] = temp[i];
        } else {
            for(int i=0; i<3; i++) temp[i] = cubo[CIMA][i][0];
            for(int i=0; i<3; i++) cubo[CIMA][i][0] = cubo[FRENTE][i][0];
            for(int i=0; i<3; i++) cubo[FRENTE][i][0] = cubo[BAIXO][i][0];
            for(int i=0; i<3; i++) cubo[BAIXO][i][0] = cubo[TRAS][2-i][2];
            for(int i=0; i<3; i++) cubo[TRAS][i][2] = temp[2-i];
        }
    }
    else if (face == DIREITA) {
        if (direcao == HORARIO) {
            for(int i=0; i<3; i++) temp[i] = cubo[CIMA][i][2];
            for(int i=0; i<3; i++) cubo[CIMA][i][2] = cubo[FRENTE][i][2];
            for(int i=0; i<3; i++) cubo[FRENTE][i][2] = cubo[BAIXO][i][2];
            for(int i=0; i<3; i++) cubo[BAIXO][i][2] = cubo[TRAS][2-i][0];
            for(int i=0; i<3; i++) cubo[TRAS][i][0] = temp[2-i];
        } else {
            for(int i=0; i<3; i++) temp[i] = cubo[CIMA][i][2];
            for(int i=0; i<3; i++) cubo[CIMA][i][2] = cubo[TRAS][2-i][0];
            for(int i=0; i<3; i++) cubo[TRAS][i][0] = cubo[BAIXO][2-i][2];
            for(int i=0; i<3; i++) cubo[BAIXO][i][2] = cubo[FRENTE][i][2];
            for(int i=0; i<3; i++) cubo[FRENTE][i][2] = temp[i];
        }
    }
}
//Tem que passar para variavel temporária para não perder o valor anterior!!!!