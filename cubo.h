//Arquivo: cubo.h
#ifndef CUBO_H
#define CUBO_H

// --- DEFINIÇÕES DE DADOS ---
enum Cores { AMARELO, VERDE, VERMELHO, LARANJA, BRANCO, AZUL };
enum Face { CIMA, BAIXO, ESQUERDA, DIREITA, FRENTE, TRAS };
enum Direcao { HORARIO, ANTIHORARIO };
enum Rotacao { NORTE, SUL, LESTE, OESTE }; // rotacao(FRENTE, HORARIO)

// VARIÁVEIS GLOBAIS 
extern int cubo[6][3][3];

// ARRAYS DE TEXTO
extern const char* nome_faces[6];
extern const char* nome_direcoes[2];
extern const char letras_cores[6];

// FUNÇÕES (Padronizadas para não dar erro de compilação com os outros arquivos)
void inicializaCuboResolvido();
void rotacao(int face, int direcao);
int cuboEstaResolvido();
void imprimeCubo();

// INTERFACE GRÁFICA
void executaAnimacao(int total_passos, int* seq_face, int* seq_dir);

#endif
