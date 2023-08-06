#include<stdlib.h>
#include<stdio.h>



typedef struct _ponto
{
    int x, y;
	int visitado;
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
    for (int i=0; i < L->ny; i++)
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
				L->entrada.visitado = 0;
                L->posicoes[y][x] = 'P';
                continue;
            }
            if (L->posicoes[y][x] == 'S')/* registra saida */
            {
                L->saida.x = x;
                L->saida.y = y;
				L->saida.visitado = 0;
                L->posicoes[y][x] = 'P';
                continue;
            }
            if (L->posicoes[y][x] == 'G')/*registra portal */
            {
                L->portais[c_portal].x = x;
                L->portais[c_portal].y = y;
				L->portais[c_portal].visitado = 0;
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
    for (int i = 0; i < L->ny; i++)
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
       if (L->posicoes[P.y][P.x] == 'G') /* portal, vizinhanca-4 mais portais_nao_visitados*/
        {
		    /*onde no vetor portais*/
			int j = 0;
			while (L->portais[j].x != P.x || L->portais[j].y != P.y) j++;  /* indice j é o portal atual */
			
			if (L->portais[j].visitado == 1)
			{
				return(res);  /* portal ja visitado, retorna */
			}
			else 
			{
				L->portais[j].visitado = 1;
				int portais_nao_visitados = 0;
				for (int i = 0; i < L->np; i++)
				{
					if (L->portais[i].visitado == 0) portais_nao_visitados++; 
				} /* portais_nao_visitados vai servir para alocar os candidatos */
				
				ponto *C = (ponto *)calloc((4 + portais_nao_visitados), sizeof(ponto));
				
				C[0].x = P.x - 1; C[0].y = P.y;
				C[1].x = P.x ;    C[1].y = P.y + 1;
				C[2].x = P.x + 1; C[2].y = P.y;
				C[3].x = P.x;     C[3].y = P.y - 1; /*alocados a vizinhanca-4*/
				
				int k = 0;
				if (portais_nao_visitados > 0)
				{
					for (int i = 0; i < L->np; i++)
					{
						if (L->portais[i].visitado == 0) 
						{
							C[4+k].x = L->portais[i].x; 
							C[4+k].y = L->portais[i].y;
							k++;
						}
					}
				}
				for (int i = 0 ; (i < (4 + portais_nao_visitados)) && res != 1; i++) /* chamadas dos candidatos */
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
       else  /* nao portal */
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

	
	/* TESTES . . . 
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



