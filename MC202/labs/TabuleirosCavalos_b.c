#include<stdio.h>
#include<stdlib.h>

void posTomove_ataque(int n, char **cavalos){
    char x;
    char y;
    int k = 0;
    while (k < n-1){
        for (int i = -1; i < 2; i = i+2){
            if (cavalos[k][2] > 54 || cavalos[k][0] < 66 || cavalos[k][0] > 71){
                continue;
            } else {
                x = cavalos[k][0] + i;
                y = cavalos[k][2] + 2;
                for (int i = k; i < n; i++){
                    if (x == cavalos[i][0] && y == cavalos[i][2]){
                        printf("Os cavalos estao em guerra!");
                        return;
                    }
                }
            }
        }
        for (int i = 1; i > -2; i=i-2){
            if (cavalos[k][0] > 70 || cavalos[k][2] > 55|| cavalos[k][2] < 50){
                continue;
            } else {
                x = cavalos[k][0]+2;
                y = cavalos[k][2]+i;
                for (int i = k; i < n; i++){
                    if (x == cavalos[i][0] && y == cavalos[i][2]){
                        printf("Os cavalos estao em guerra!");
                        return;
                    }
                }                
            }
        }
        for (int i = -1; i < 2; i = i+2){
            if (cavalos[k][2] < 51 || cavalos[k][0] < 66 || cavalos[k][0] > 71){
                continue;
            } else {
                x = cavalos[k][0]+i;
                y = cavalos[k][2] - 2;
                for (int i = k; i < n; i++){
                    if (x == cavalos[i][0] && y == cavalos[i][2]){
                        printf("Os cavalos estao em guerra!");
                        return;
                    }
                }                
            }
        }
        for (int i = 1; i > -2; i=i-2){
            if (cavalos[k][0] < 67 || cavalos[k][2] > 55|| cavalos[k][2] < 50){
                continue;
            } else {
                x = cavalos[k][0]-2;
                y = cavalos[k][2]+i;
                for (int i = k; i < n; i++){
                    if (x == cavalos[i][0] && y == cavalos[i][2]){
                        printf("Os cavalos estao em guerra!");
                        return;
                    }
                }                
            }
        }
        k++;
    }
    printf("Paz no reino!");
}


int main(){

/*Atividade 2*/
    char **cavalos;
    int n;
    scanf("%d", &n);
    if (n == 0){
        printf("Paz no reino!");
        exit(0);
    } else {                                                //.
        cavalos = (char **)calloc(n, sizeof(char *));
        for (int i = 0; i < n; i++){                            //Alocando a lista de cavalos
            cavalos[i] = (char *)calloc(4, sizeof(char));
        }                                                   //.
        
        for (int i = 0; i < n; i++){
            scanf(" %[^\n]s", cavalos[i]);
        }
        
        posTomove_ataque(n, cavalos);

        for (int i = 0; i < n; i++){
            free(cavalos[i]);
        }
        free(cavalos);
    return 0;
    }
}

