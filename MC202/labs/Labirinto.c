#include<stdlib.h>
#include<stdio.h>




typedef struct _ponto
{
    int x, y;
}ponto;

typedef struct _labirinto
{
    char **posicoes;
    int nx, ny, np;
    ponto entrada, saida;
    ponto *portais;
}labirinto;


labirinto *le_labirinto(char *nomearq)
{
    FILE *fp = fopen(nomearq, "r");
    labirinto *L = (labirinto *)calloc(1, sizeof(labirinto));
    
    fscanf(fp, "%d %d %d\n", &L->nx, &L->ny, &L->np);
    
    L->posicoes = (char **)calloc(L->ny, sizeof(char *));
    for (int i=0; i < L->nx; i++)
    {
        L->posicoes[i] = (char *)calloc(L->nx, sizeof(char));
    }
    
    if (L->np > 0)  /*talvez nao haja portais*/
    {
        L->portais = (ponto *)calloc(L->np, sizeof(ponto));
    }
    int c_portal = 0;
    
    for (int y=0; y < L->ny; y++)
    {
        for (int x=0; x < L->nx; x++)
        {
            fscanf(fp, "%c", &L->posicoes[y][x]);
            if (L->posicoes[y][x] == 'E')  /* registra entrada */
            {
                L->entrada.x = x; 
                L->entrada.y = y;
                L->posicoes[y][x] = 'P';
                continue;
            }
            if (L->posicoes[y][x] == 'S')/* registra saida */
            {
                L->saida.x = x;
                L->saida.y = y;
                L->posicoes[y][x] = 'P';
                continue;
            }
            if (L->posicoes[y][x] == 'G')/*registra portal */
            {
                L->portais[c_portal].x = x;
                L->portais[c_portal].y = y;
                c_portal++;
                continue;
            }
        }
        fscanf(fp,"\n");
    }
    fclose(fp);
    
    return(L);
}

void destroi_labirinto(labirinto *L)
{
    free(L->portais);
    for (int i = 0; i < L->nx; i++)
    {
        free(L->posicoes[i]);
    }
    free(L->posicoes);
    free(L);
}

void print_labirinto(labirinto *L)
{
    for (int i =0; i < L->ny; i++) printf("%s\n", L->posicoes[i]);
}

int backtracking(labirinto *L, ponto P)
{
    int res = 0 ;    /* neste codigo troquei o bool por inteiro, 0 sendo Falso e 1 True*/    
    //print_labirinto(L);
    if (P.x == L->saida.x && P.y == L->saida.y) /* caso base da recursao */
    {
        res = 1;  
    } 
    else
    {
       if (L->posicoes[P.y][P.x] == 'G') /* portal, vizinhanca-4 mais np-1 portais*/
       {
            ponto *C = (ponto *)calloc((L->np + 3), sizeof(ponto));
            
            C[0].x = P.x - 1; C[0].y = P.y;
            C[1].x = P.x ;    C[1].y = P.y + 1;
            C[2].x = P.x + 1; C[2].y = P.y;
            C[3].x = P.x;     C[3].y = P.y - 1; /*alocados a vizinhanca-4*/
            
            int j = 0;
            if (L->np > 1)
            {
            for (int i = 1; i < L->np; i++)
                {
                    if (L->portais[j].x == P.x && L->portais[j].y == P.y) /* caso seja o mesmo portal */
                    {
                        j++;
                        continue;
                    }
                C[3+i].x = L->portais[j].x; C[3+i].y = L->portais[j].y;
                
                }
            }
            for (int i = 0 ; (i < (L->np + 4)) && res != 1; i++)
            {
                if (C[i].x >= 0 && C[i].x < L->nx &&
                    C[i].y >= 0 && C[i].y < L->ny)
                    { if (L->posicoes[C[i].y][C[i].x] != 'X')
                        {
                            //printf("(%d, %d) ---> (%d, %d)\n", P.x, P.y, C[i].x, C[i].y);
                        char valor_correto = L->posicoes[C[i].y][C[i].x];
                        if (valor_correto != 'G') L->posicoes[C[i].y][C[i].x] = 'X';
                        //L->posicoes[P.x][P.y] = 'X';
                        res = backtracking(L, C[i]);
                        
                        L->posicoes[C[i].y][C[i].x] = valor_correto;
                        //L->posicoes[P.x][P.y] = valor_correto;
                        }
                    }
            }
        free(C);
       } 
       else
       {
           ponto *C = (ponto *)calloc(4, sizeof(ponto));
           
           C[0].x = P.x - 1; C[0].y = P.y;
           C[1].x = P.x ;    C[1].y = P.y + 1;
           C[2].x = P.x + 1; C[2].y = P.y;
           C[3].x = P.x;     C[3].y = P.y - 1; /*alocados a vizinhanca-4*/
           
           for (int i = 0 ; i < 4 && res != 1; i++)
           {
                if (C[i].x >= 0 && C[i].x < L->nx &&
                    C[i].y >= 0 && C[i].y < L->ny)
                    { 
                    if (L->posicoes[C[i].y][C[i].x] != 'X')
                        {
							//printf("(%d, %d) ---> (%d, %d)\n", P.x, P.y, C[i].x, C[i].y);
                        char valor_correto = L->posicoes[C[i].y][C[i].x];
                        if (valor_correto != 'G') L->posicoes[C[i].y][C[i].x] = 'X';
                        //L->posicoes[P.x][P.y] = 'X';
                        res = backtracking(L, C[i]);
                        
                        L->posicoes[C[i].y][C[i].x] = valor_correto;
                        //L->posicoes[P.x][P.y] = valor_correto;
                        }
                    }
           }
        free(C);
       }
    }
    return (res);
}

//int main()
int main(int argc, char **argv)
{
  labirinto *L = le_labirinto(argv[1]); 

	if (argc != 2) exit(1);
	/*
	labirinto *L = (labirinto *)calloc(1, sizeof(labirinto));
	L->nx = 4;
	L->ny = 3;
	L->np = 1;
	L->entrada.x = 2; L->entrada.y = 2;
	L->saida.x = 3; L->saida.y = 2;
	L->posicoes = (char **)calloc(L->ny, sizeof(char *));
	for (int i=0; i < L->nx; i++)
	{
		L->posicoes[i] = (char *)calloc(L->nx, sizeof(char ));
	}
	L->posicoes[0] = "PPGX";
	L->posicoes[1] = "XPXX";
	L->posicoes[2] = "XXPP";
	*/
	
	

  if (backtracking(L, L->entrada) == 1)
    printf("Encontrou a saida em (%d,%d)",L->saida.x,L->saida.y);
  else
    printf("Labirinto sem saida");
	   
  destroi_labirinto(L);
  return(0);
}
