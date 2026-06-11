// Arquivo: SOLUÇÃO DO CUBO
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h> // Biblioteca para a interface gráfica no terminal
#include "cubo.h"

// --- 1. FUNÇÕES DA INTERFACE GRÁFICA (NCURSES) ---

void inicia_ncurses() {
    initscr();             
    start_color();         
    cbreak();              
    noecho();              
    curs_set(0);           

    // Cria os pares de cores: ID do Par, Cor da Letra, Cor do Fundo
    init_pair(AMARELO + 1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(VERDE + 1, COLOR_GREEN, COLOR_BLACK);
    init_pair(VERMELHO + 1, COLOR_RED, COLOR_BLACK);
    init_pair(LARANJA + 1, COLOR_MAGENTA, COLOR_BLACK); 
    init_pair(BRANCO + 1, COLOR_WHITE, COLOR_BLACK);
    init_pair(AZUL + 1, COLOR_BLUE, COLOR_BLACK);
}

void desenha_face(int face, int start_y, int start_x) {
    for (int l = 0; l < 3; l++) {
        for (int c = 0; c < 3; c++) {
            int cor_adesivo = cubo[face][l][c];
            
            attron(COLOR_PAIR(cor_adesivo + 1));
            // Imprime o adesivo na coordenada (Y, X)
            mvprintw(start_y + l, start_x + (c * 3), "[%c]", letras_cores[cor_adesivo]);
            attroff(COLOR_PAIR(cor_adesivo + 1));
        }
    }
}

void mostra_cubo_ncurses() {
    // Coordenadas centrais (Face da FRENTE)
    int y_centro = 8;
    int x_centro = 25;

    // Planificação em cruz
    desenha_face(CIMA, y_centro - 4, x_centro);
    desenha_face(ESQUERDA, y_centro, x_centro - 10);
    desenha_face(FRENTE, y_centro, x_centro);
    desenha_face(DIREITA, y_centro, x_centro + 10);
    desenha_face(TRAS, y_centro, x_centro + 20);
    desenha_face(BAIXO, y_centro + 4, x_centro);

    refresh(); // Atualiza a tela
}


// --- 2. FUNÇÕES DE LÓGICA E LEITURA ---

int carregar_cubo(const char* nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) return 0;

    char buffer[100];
    fgets(buffer, sizeof(buffer), arquivo); 

    for (int f = 0; f < 6; f++) {
        char letra_face;
        fscanf(arquivo, " %c", &letra_face); 

        for (int l = 0; l < 3; l++) {
            for (int c = 0; c < 3; c++) {
                char letra_cor;
                fscanf(arquivo, " %c", &letra_cor);
                for(int i = 0; i < 6; i++) {
                    if (letra_cor == letras_cores[i]) {
                        cubo[f][l][c] = i;
                        break;
                    }
                }
            }
        }
    }
    fclose(arquivo);
    return 1;
}

// Algoritmo de Backtracking
int resolve(int qtd_atual, int limite, int* passos_face, int* passos_direcao) {
    if (cubo_esta_resolvido()) return 1; 
    if (qtd_atual >= limite) return 0; 

    for (int f = 0; f < 6; f++) {
        for (int d = 0; d < 2; d++) {
            rotacao(f, d); 
            passos_face[qtd_atual] = f;
            passos_direcao[qtd_atual] = d;
            
            if (resolve(qtd_atual + 1, limite, passos_face, passos_direcao)) {
                return 1; 
            }
            
            // Backtracking: Desfaz o movimento
            int direcao_oposta = (d == HORARIO) ? ANTIHORARIO : HORARIO;
            rotacao(f, direcao_oposta); 
        }
    }
    return 0;
}


// --- 3. FUNÇÃO PRINCIPAL ---

int main(int argc, char** argv) {
    // 1. Validação do terminal
    if (argc != 2) {
        printf("Uso: ./cubo <arquivo_do_cubo.txt>\n");
        return 1;
    }

    if (!carregar_cubo(argv[1])) {
        printf("Erro: Nao foi possivel abrir o arquivo '%s'.\n", argv[1]);
        return 1;
    }

    int seq_face[20], seq_dir[20];
    int limite = 6; // máximO de busca
    int resolvido = 0;
    int total_passos = 0;

    // 2. Busca a solução no background primeiro
    printf("Calculando a solucao (limite de %d movimentos)... Aguarde.\n", limite);
    for (int i = 1; i <= limite; i++) {
        if (resolve(0, i, seq_face, seq_dir)) {
            total_passos = i;
            resolvido = 1;
            break;
        }
    }

    if (!resolvido) {
        printf("Nao foi possivel encontrar uma solucao em ate %d passos para esta instancia.\n", limite);
        return 1;
    }

    // 3. Recarrega o cubo bagunçado do arquivo para mostrar a animação do zero
    carregar_cubo(argv[1]); 


    // --- 4. EXIBIÇÃO GRÁFICA ---
    inicia_ncurses();

    // Tela inicial
    mvprintw(0, 0, "CUBO CARREGADO: Pressione qualquer tecla para iniciar a animacao...");
    mostra_cubo_ncurses();
    getch(); // Espera o usuário apertar algo

    // Animação
    for (int p = 0; p < total_passos; p++) {
        clear(); // Limpa o frame anterior
        
        // Imprime o cabeçalho de instrução
        mvprintw(0, 0, "Passo %d de %d: Girando face %s no sentido %s", 
                 p + 1, total_passos, nome_faces[seq_face[p]], nome_direcoes[seq_dir[p]]);
        mvprintw(1, 0, "Pressione qualquer tecla para avancar...");
        
        // Gira a matriz física
        rotacao(seq_face[p], seq_dir[p]);
        
        // Desenha a matriz na tela
        mostra_cubo_ncurses();
        
        getch(); // Pausa para o usuário ver o movimento
    }

    // Tela final
    clear();
    mvprintw(0, 0, "🎉 SUCESSO! Cubo resolvido em %d passos.", total_passos);
    mvprintw(1, 0, "Pressione qualquer tecla para encerrar.");
    mostra_cubo_ncurses();
    getch();

    endwin(); // Desliga o modo gráfico e devolve o terminal normal

    return 0;
}