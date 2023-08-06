#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <math.h>

//Reaproveitei parte do codigo do professor. Modifiquei para tratar com chaves nome


// Implementacao de lista ligada    LISTA LIGADA
typedef struct _no_cabeca
{
    int n;
    struct _no_simples* prox;
}no_cabeca;

typedef struct _no_simples
{
    char nome[51];
    struct _no_simples* prox;
}no_simples;

no_cabeca *cria_lista()
{
    no_cabeca *lista = (no_cabeca *)calloc(1, sizeof(no_cabeca));
    lista->n = 0;
    lista->prox = NULL;

    return (lista);
}

no_simples *cria_no(char *nome)
{
    no_simples *novo_no = (no_simples *)calloc(1, sizeof(no_simples));

    int i = 0;
    while (nome[i] != '\0')
    {
        novo_no->nome[i] = nome[i];
        i++;
    }
    novo_no->nome[i] = '\0';

    novo_no->prox = NULL;

    return(novo_no);
}

void destroi_todos_nos(no_simples *no)
{
    if(no->prox == NULL)
    {
        free(no);
    }else
    {
        destroi_todos_nos(no->prox);
        free(no);
    }
}


void destroi_lista(no_cabeca* cabeca_lista) //aqui nao uso ** pois o proposito é destruir pra poder finalizar o programa
{
    if (cabeca_lista->prox != NULL)  //tem pelo menos um no_simples ligado
        destroi_todos_nos(cabeca_lista->prox);
    free(cabeca_lista);
}

void insere_na_lista(no_cabeca *cabeca, char *nome)
{
    if (cabeca->prox == NULL)
    {
        no_simples *novo_no = cria_no(nome);
        cabeca->prox = novo_no;
        cabeca->n++;
    }
    else
    {
        no_simples *iterado = cabeca->prox;
        while (iterado->prox != NULL)
        {
            iterado = iterado->prox;
        }

        no_simples *novo_no = cria_no(nome);

        iterado->prox = novo_no;
        cabeca->n++;

    }

}


// Implementacao de lista ligada    LISTA LIGADA _______FIM

int nome_pra_int(char *nome)    //somos todos os caracteres e retorno a soma
{
    int numero = 0;

    int i = 0;
    while (nome[i] != '\0')
    {
        numero = numero + nome[i];
        i++;
    }

    return(numero);
}

char EhPrimo(int numero)
{
  int i, n = sqrt(numero);

  if (numero==2)
    return(1);

  if ((numero%2)==0)
    return(0);

  for (i=3; i <= n; i=i+2)
    if ((numero%i)==0)
      return(0);

  return(1);
}

int AchePrimoDistantePotencias2(int primeira, int segunda)
{
  int media = (primeira+segunda)/2, candidato[2];

  candidato[0]=media-1;
  candidato[1]=media+1;

  while((candidato[0] > primeira)&&(candidato[1]<segunda)){
    if (EhPrimo(candidato[0]))
      return(candidato[0]);
    if (EhPrimo(candidato[1]))
      return(candidato[1]);
    candidato[0]--;
    candidato[1]++;
  }
    return((int)((primeira + segunda)/2));
  printf("Nao existe primo entre %d e %d\n",primeira,segunda);
  exit(-1);
}

int Potencia2MaiorQueN(int n, int *expo)
{
  int pot2=2;

  (*expo)=0;
  while (pot2 < n){
    pot2=pot2<<1;
    (*expo)++;
  }

  return(pot2);
}

/* Tabela Hash com reespalhamento duplo e chaves k > 0: h(k,j) = ( (k
% m) + (j-1) (1+(k%m')) ) % m onde m' = m - 2 */

typedef struct _hash {
  no_cabeca *valor; /* valor da chave */
  int  m;     /* tamanho da tabela */
} Hash;

Hash *CriaTabelaHash(int n)
{
  Hash *hash=(Hash *)calloc(1,sizeof(Hash));
  int primeira, segunda, expo;

  primeira = Potencia2MaiorQueN(n,&expo);
  segunda  = 2<<(expo+1); /* shift-left que desloca os bits para à esquerda expo+1 vezes */
  hash->m  = AchePrimoDistantePotencias2(primeira, segunda);

  //printf("A primeira potência de 2 acima de n=%d é %d e a segunda é %d\n",n,primeira,segunda);
  //printf("O valor de m=%d é um primo mais distante dessas pontências de 2 e m'=%d.\n",hash->m,hash->m-2);
  hash->valor = (no_cabeca*)calloc(hash->m,sizeof(no_cabeca));

  return(hash);
}

char InsereChave(Hash *hash, char *nome)
{
  int pos, j=1;

  int chave = nome_pra_int(nome);
  pos = (chave % hash->m);

  insere_na_lista(&(hash->valor[pos]), nome);

  return(1);
}

int compara_sobrenome(char *nome1, char *nome2)  //1 se igual, 0 se diferente
{
    int i = 0;
    while (nome1[i] != '\0' && nome2[i] != '\0')
    {
        if (nome1[i] != nome2[i]) return(0); //encontrou diferenca DIFERENTE
        i++;
    }
    if (nome1[i] != '\0' || nome2[i] != '\0') return (0);    //igual ate o fim de um, mas o outro tem mais DIFERENTE

    return(1); //chegou aqui IGUAL
}

int busca_na_lista(no_simples *no, char *nome)
{
    no_simples *aux = no;

    int encontrado = 0;
    while (aux != NULL)
    {
        if (compara_sobrenome(nome, aux->nome))
        {
            return (1);
        }
        aux = aux->prox;
    }
    return (encontrado);
}

void busca_no_hash(Hash *hash, char *nome)
{
    int pos = nome_pra_int(nome);
    pos = pos%(hash->m);

    //TESTE
    printf("%d\n", pos);

    if (hash->valor[pos].n > 0)
    {
        if (busca_na_lista(hash->valor[pos].prox, nome)) //encontrou!
        {
            printf("1");
        }
        else
        {
            printf("0");
        }
    }
    else
    {
        printf("0");
    }
}


void DestroiTabelaHash(Hash **hash)
{
  Hash *aux = *hash;

  for (int i = 0; i < aux->m; i++)
  {
      if (aux->valor[i].prox != NULL) destroi_todos_nos(aux->valor[i].prox);

  }
  free(aux->valor);
  free(aux);
  *hash = NULL;
}


void imprime_chaves(no_simples *no)
{
    no_simples *aux = no;

    while (aux != NULL)
    {
        printf("%s, ", aux->nome);
        aux = aux->prox;
    }
    printf("\n");
}
//TESTE
void imprime_hash(Hash *hash)
{
    printf("hash->m = %d\n", hash->m);

    for (int i = 0; i < hash->m; i++)
    {
        printf("[%d]: ", i);
        imprime_chaves(hash->valor[i].prox);
    }
}






//____________________________________________________________________________________
void le_arquivo(char *nomearq1, char *nomearq2)
{
    FILE *f = fopen(nomearq1, "r");
    int n;
    fscanf(f,"%d\n", &n);
    int i = n;

    Hash *novo_hash = CriaTabelaHash(n);

    while (i > 0)
    {
        char nome[50];
        int j = 0;
        fscanf(f, "%c", &nome[j]);
        while (nome[j] != '\n')

        {
            j++;
            fscanf(f, "%c", &nome[j]);
        }
        nome[j] = '\0';
        InsereChave(novo_hash, nome);

        i--;

    }
    //TESTE
    imprime_hash(novo_hash);

    //TERMINOU DE INSERIR NOMES
    FILE *f2 = fopen(nomearq2, "r");
    char nome2[50];
    int j = 0;
    fscanf(f2, "%c", &nome2[j]);
    while (nome2[j] != '\n')
    {
        j++;
        fscanf(f2, "%c", &nome2[j]);
    }
    nome2[j] = '\0';

    busca_no_hash(novo_hash, nome2);


    DestroiTabelaHash(&novo_hash);

    fclose(f);
    fclose(f2);
}







int main()
//int main(int argc, char **argv)
{
    le_arquivo("teste1.txt", "nome1.txt");
    //le_arquivo(argv[1], argv[2]);


    return(0);
}
