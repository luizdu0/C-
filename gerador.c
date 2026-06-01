#define NUM_FACES 6
#define NUM_LINCOL 3

int cubo[6][3][3];
enum cores { AMARELO, VERMELHO, AZUL, VERDE, BRANCO, ROSA };
int embaralhador(int *** cubo);

int main (int argc, char ** argv){

    int cor = AMARELO;
    for(int i = 0; i < NUM_FACES; i++){
        for(int j = 0; j < NUM_LINCOL; j++){
            for(int k = 0; k < NUM_LINCOL; k++){
                cubo[i][j][k] = cor;
            }
        }
        cor++;
        }
       int resulado = embaralhador(cubo);

        if(resulado == 1){
            printf("Cubo embaralhado com sucesso!\n");
        } else {
            printf("Erro ao embaralhar o cubo.\n");
        }

}
