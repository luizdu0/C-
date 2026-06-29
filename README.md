# Simulador de Cubo Mágico
Arthur Bosquerolli, Guilherme Gonçaves, Leandro Bitencourt, Luiz Eduardo Domingos e Maria Eduarda da Luz

## Estrutura dos Arquivos

### gerador.c
O objetivo dele é inicializar um cubo resolvido, aplicar uma quantidade N de movimentos aleatórios e salvar esse estado bagunçado em um arquivo de texto. Serve para gerar os casos de teste que o `cubo.c` vai tentar resolver depois.

### cubo.h
Não executa nada, mas define as estruturas de dados (como os `enum` para Cores, Faces e Direções), declara as variáveis globais (a matriz 3D do cubo) e as assinaturas das funções. Ele permite que os diferentes arquivos `.c` "conversem" entre si sabendo quais funções existem sem precisarem conhecer o código interno uns dos outros.

### cubinho.c
Aqui que reside a matriz de estado do cubo (`cubo[6][3][3]`) e a lógica bruta. A função `rotacao` mapeia como as peças mudam de posição quando você gira uma face, girando a matriz 3x3 e ajustando as bordas das faces adjacentes.

### cubo.c
É o executável principal (`main`) para resolver o cubo. Lê o estado de um cubo embaralhado a partir de um arquivo `.txt`, usa um algoritmo de Backtracking e testa combinações de movimentos até encontrar a solução dentro de um limite de passos. Após calcular a rota, ele chama a interface gráfica para mostrar a animação passo a passo.

### interf.c
É o "front-end" de terminal do projeto. Ele utiliza a biblioteca `ncurses` para mapear as cores e imprimir as matrizes de forma que pareçam um cubo planificado na tela. O programa fica aguardando você apertar uma tecla para avançar cada passo da animação.

### Makefile
Automatiza a compilação. A regra `gerador` junta o `gerador.c` e o `cubinho.c`. A regra `cubo` junta o `cubo.c`, `cubinho.c` e `interf.c`, linkando a biblioteca gráfica com o comando `-lncurses`. O comando `make clean` apaga os arquivos executáveis e os `.txt` gerados, limpando o diretório.

---

## Como Executar

### 1. Pré-requisitos
Para a interface visual, é necessária a biblioteca **ncurses**:
* **Linux/WSL:** Instale via `sudo apt install libncurses5-dev libncursesw5-dev`.
* **Windows (MSYS2/Git Bash):** Instale via terminal MSYS2 com: `pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-make mingw-w64-x86_64-ncurses`.

### 2. Automatização via Makefile
O `Makefile` unifica a compilação. 

> **ATENÇÃO para Windows:** Se o comando `make` não for reconhecido, utilize `mingw32-make`.

---

## Instruções por Ambiente

### Linux / Codespaces
1. `make`
2. `./gerador 3`
3. `./cubo cubo1.txt`

### Windows (MSYS2 / Git Bash)
Como o compilador do Windows (`gcc`) não encontra bibliotecas Linux automaticamente, o `Makefile` aponta os caminhos absolutos:
* **Execução:** Siga o padrão `mingw32-make` -> `./gerador` -> `./cubo`.

### VS Code (Modo Manual)
Caso prefira compilar sem o Makefile:
1. **Compilar Gerador:** `gcc -Wall -Wextra -g gerador.c cubinho.c -o gerador`
2. **Gerar Teste:** `./gerador 5`
3. **Compilar Cubo:** `gcc -Wall -Wextra -g cubo.c cubinho.c interf.c -o cubo -lncursesw`
4. **Resolver:** `./cubo teste.txt`

---

## Informações Adicionais
* **Limite de movimentos:** O `gerador` cria o embaralhamento inicial. Recomenda-se utilizar valores entre 1 e 6.
* **Interface:** Durante a animação da solução, pressione qualquer tecla para avançar passo a passo.
