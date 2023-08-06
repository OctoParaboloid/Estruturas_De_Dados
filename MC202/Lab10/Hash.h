#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <math.h>


    // Reaproveitei o codigo do professor modificando para tratar strings como chaves. E uma forma de transformar uma string em um numero.
    // Adicionei implementacao de listas ligadas para tratar colisoes.


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


/* Tabela Hash com reespalhamento duplo e chaves k > 0: h(k,j) = ( (k
% m) + (j-1) (1+(k%m')) ) % m onde m' = m - 2 */

typedef struct _hash {
  no_cabeca *valor; /* valor da chave */
  int  m;     /* tamanho da tabela */
} Hash;


/* Cria tabela hash para armazenar ate n chaves, com reespalhamento
   duplo. */

Hash *CriaTabelaHash(int n); /* (1) m >= n, (2) m eh primo e o mais
				distante de potencia de 2, (3) m e
				(1+(k%m')) nao podem ter MDC, e (4)
				(1+(k%m')) > m. Inicializa ela com
				zeros para indicar posicao
				disponivel. */


char InsereChave(Hash *hash, char *chave); /* retorna 1 se chave foi
					    inserida com sucesso e 0
					    no caso contrario. Usa
					    posicoes disponiveis com
					    valor -1, de chaves
					    anteriormente
					    removidas.*/

char RemoveChave(Hash *hash, char *chave); /* retorna 1 se chave foi
					    removida com sucesso,
					    colocando marca -1 nas
					    posicoes que agora estao
					    disponiveis para novas
					    chaves. Retorna 0 no caso
					    contrario. */

/* Destroi a tabela */

void DestroiTabelaHash(Hash **hash);

/* Imprime a tabela */

void ImprimeTabelaHash(Hash *hash);


#endif
