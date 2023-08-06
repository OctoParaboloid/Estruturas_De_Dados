#include<stdio.h>

void posTomove(char *pos){
    char x;
    char y; 
    for (int i = -1; i < 2; i = i+2){
        if (pos[2] > 54 || pos[0]+i < 65 || pos[0]+i > 72){
            continue;
        } else {
            x = pos[0] + i;
            y = pos[2] + 2;
            printf("%c %c\n",x ,y);
        }
    }
    for (int i = 1; i > -2; i=i-2){
        if (pos[0] > 70 || pos[2]+i > 56|| pos[2]+i < 49){
            continue;
        } else {
            x = pos[0]+2;
            y = pos[2]+i;
            printf("%c %c\n",x ,y);
        }
    }
    for (int i = 1; i > -2; i = i-2){

        if (pos[2] < 51 || pos[0]+i < 65 || pos[0]+i > 72){

            continue;
        } else {
            x = pos[0]+i;
            y = pos[2] - 2;
            printf("%c %c\n",x ,y);
        }
    }
    for (int i = -1; i < 2; i=i+2){

        if (pos[0] < 67 || pos[2]+i > 56|| pos[2]+i < 49){

            continue;
        } else {
            x = pos[0]-2;
            y = pos[2]+i;
            printf("%c %c\n",x ,y);
        }
    }
}


int main(){

/*Atividade 1*/
    char pos[4];
    scanf("%[^\n]s", pos);
    posTomove(pos);


    return 0;
}
