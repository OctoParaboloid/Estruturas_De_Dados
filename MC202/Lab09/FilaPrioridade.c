#include "FilaPrioridade.h"




//PRIVADAS
cliente *cria_cliente(int prioridade, char *sobrenome)
{
    cliente *novo = (cliente *)calloc(1, sizeof(cliente));

    novo->prioridade = prioridade;
    int i;
    for (i = 0; sobrenome[i] != '\0'; i++)
    {
        novo->sobrenome[i] = sobrenome[i];
    }
    novo->sobrenome[i] = '\0';
    return(novo);
}

Heap *cria_heap(int tam)
{
    Heap *novo_heap = (Heap *)calloc(1, sizeof(Heap));

    novo_heap->vetor_clientes = (cliente **)calloc(tam, sizeof(cliente *));
    novo_heap->qtde = 0;
    novo_heap->tam_max = tam;

    return(novo_heap);
}

void troca(cliente **cl1, cliente **cl2)
{
    cliente *aux = *cl1;
    *cl1 = *cl2;
    *cl2 = aux;
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

int busca_max_heap(Heap *h, char *sobrenome)
{
    int id_encontrado = -1;
    for (int i = 0; i < h->qtde; i++)
    {
        if (compara_sobrenome(sobrenome, h->vetor_clientes[i]->sobrenome))
        {
            id_encontrado = i;
            return(id_encontrado);
        }
    }
    return(id_encontrado);
}

	//MAX HEAP ~~~~~~~~~~~~
void sobe_max_heap(Heap *h, int n)
{
    if (n != 0)
    {
        int pai = (n-1)/2;
        if (h->vetor_clientes[n]->prioridade > h->vetor_clientes[pai]->prioridade)
        {
            troca(&(h->vetor_clientes[n]), &(h->vetor_clientes[pai]));
			h->vetor_clientes[n]->id_max = n;
			h->vetor_clientes[pai]->id_max = pai; //atualiza indices

            sobe_max_heap(h, pai);
        }
    }
}

void desce_max_heap(Heap *h, int i)
{
    int maior = i;
    if ((2*i + 1 < h->qtde) && (h->vetor_clientes[2*i + 1]->prioridade > h->vetor_clientes[maior]->prioridade) )
        maior = 2*i + 1;
    if ((2*i + 2 < h->qtde) && (h->vetor_clientes[2*i + 2]->prioridade > h->vetor_clientes[maior]->prioridade) )
        maior = 2*i + 2;

    if (maior != i)
    {
        troca(&(h->vetor_clientes[maior]), &(h->vetor_clientes[i]));
		h->vetor_clientes[maior]->id_max = maior;
		h->vetor_clientes[i]->id_max = i; //atualiza indices
        desce_max_heap(h, maior);
    }
    else
    {
        h->vetor_clientes[i]->id_max = i;
    }
}

void insere_max_heap(Heap *h, cliente *novo_cliente)
{
    if (h->qtde != h->tam_max)
    {
        h->qtde++;
        h->vetor_clientes[h->qtde - 1] = novo_cliente;
		novo_cliente->id_max = h->qtde - 1;

        sobe_max_heap(h, h->qtde - 1);
    }
}

void remove_max_heap(Heap *h)
{
    if (h->qtde > 0)
    {
    h->qtde--;
    //cliente *retorno = h->vetor_clientes[0];
    troca(&(h->vetor_clientes[0]), &(h->vetor_clientes[h->qtde]));
    desce_max_heap(h, 0);

    //return(retorno);
    }
    //return(NULL);
}

void remove_ID_max_heap(Heap *h, int id_max)
{
    h->qtde--;
    troca(&(h->vetor_clientes[id_max]), &(h->vetor_clientes[h->qtde]));
    //h->vetor_clientes[id_max]->id_max = id_max;
    //h->vetor_clientes[h->qtde]->id_max = h->qtde;
    //free(h->vetor_clientes[h->qtde+1]);
    desce_max_heap(h, id_max);
}
	//MAX HEAP ~~~~~~~~~~~~ FIM

    //MIN HEAP ~~~~~~~~~~~~
void sobe_min_heap(Heap *h, int n)
{
    if (n != 0)
    {
        int pai = (n-1)/2;
        if (h->vetor_clientes[n]->prioridade < h->vetor_clientes[pai]->prioridade)
        {
            troca(&(h->vetor_clientes[n]), &(h->vetor_clientes[pai]));
			h->vetor_clientes[n]->id_min = n;
			h->vetor_clientes[pai]->id_min = pai; //atualiza indices

            sobe_min_heap(h, pai);
        }
    }
}

void desce_min_heap(Heap *h, int i)
{
    int menor = i;
    if ((2*i + 1 < h->qtde) && (h->vetor_clientes[2*i + 1]->prioridade < h->vetor_clientes[menor]->prioridade) )
        menor = 2*i + 1;
    if ((2*i + 2 < h->qtde) && (h->vetor_clientes[2*i + 2]->prioridade < h->vetor_clientes[menor]->prioridade) )
        menor = 2*i + 2;

    if (menor != i)
    {
        troca(&(h->vetor_clientes[menor]), &(h->vetor_clientes[i]));
		h->vetor_clientes[menor]->id_min = menor;
		h->vetor_clientes[i]->id_min = i; //atualiza indices
        desce_min_heap(h, menor);
    }
    else
    {
        h->vetor_clientes[i]->id_min = i;
    }
}

void insere_min_heap(Heap *h, cliente *novo_cliente)
{
    if (h->qtde != h->tam_max)
    {
        h->qtde++;
        h->vetor_clientes[h->qtde - 1] = novo_cliente;
		novo_cliente->id_min = h->qtde - 1;

        sobe_min_heap(h, h->qtde - 1);
    }
}

void remove_min_heap(Heap *h)
{
    if (h->qtde > 0)
    {
    h->qtde--;
    //cliente *retorno = h->vetor_clientes[0];
    troca(&(h->vetor_clientes[0]), &(h->vetor_clientes[h->qtde]));
    desce_min_heap(h, 0);

	//return(retorno);
    }
    //return(NULL);
}

void remove_ID_min_heap(Heap *h, int id_min)
{
    h->qtde--;
    troca(&(h->vetor_clientes[id_min]), &(h->vetor_clientes[h->qtde]));

    //h->vetor_clientes[id_min]->id_min = id_min;
    //h->vetor_clientes[h->qtde]->id_min = h->qtde;
    //free(h->vetor_clientes[h->qtde+1]);
    desce_min_heap(h, id_min);
}
    //MIN HEAP ~~~~~~~~~~~~ FIM


void atualiza_max_heap(Heap *h, int id, int prioridade_nova)
{
    int prioridade_antiga = h->vetor_clientes[id]->prioridade;

    if (prioridade_nova < prioridade_antiga) //prioridade diminuiu num max heap, pode descer
    {
        h->vetor_clientes[id]->prioridade = prioridade_nova;
        desce_max_heap(h, id);
        return;
    }
    if (prioridade_nova > prioridade_antiga) //aumentour num max, pode subir
    {
        h->vetor_clientes[id]->prioridade = prioridade_nova;
        sobe_max_heap(h, id);
        return;
    }
    //nem aumentou nem diminuiu, nao faz nada
}

void atualiza_min_heap(Heap *h, int id, int prioridade_nova)
{
    int prioridade_antiga = h->vetor_clientes[id]->prioridade;

    if (prioridade_nova < prioridade_antiga) //prioridade diminuiu num min heap, pode subir
    {
        h->vetor_clientes[id]->prioridade = prioridade_nova;
        sobe_min_heap(h, id);
        return;
    }
    if (prioridade_nova > prioridade_antiga) //aumentour num min, pode descer
    {
        h->vetor_clientes[id]->prioridade = prioridade_nova;
        desce_min_heap(h, id);
        return;
    }

    //nem aumentou nem diminuiu, nao faz nada
}
//PRIVADAS FIM~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//CHAMADAS PELA MAIN ~~~~~~~~~~~~~~~~~~~~~~
fila_prioridade *cria_fila_prio(int tam)
{
    fila_prioridade *nova_fila = (fila_prioridade *)calloc(1, sizeof(fila_prioridade));

    nova_fila->qtde = 0;
    nova_fila->tam_max = tam;
    nova_fila->max_heap = cria_heap(tam);
    nova_fila->min_heap = cria_heap(tam);

    return(nova_fila);
}

void insere_cliente(fila_prioridade *fila, char *sobrenome, int prioridade_nova)
{
    if (fila->qtde < fila->tam_max) //soh vai inserir se houver espaco
    {
        cliente *novo_cliente = cria_cliente(prioridade_nova, sobrenome);
        insere_min_heap(fila->min_heap, novo_cliente);
        insere_max_heap(fila->max_heap, novo_cliente);
        fila->qtde++;
        return;
    }
    return;

}

void busca_muda_cliente(fila_prioridade *f, char *sobrenome, int prioridade_nova)
{
	int id_encontrado = busca_max_heap(f->max_heap, sobrenome);

    if (id_encontrado >= 0) //soh faz algo se encontrar
    {
        int id_encontrado_min = f->max_heap->vetor_clientes[id_encontrado]->id_min;
        int prioridade_antiga = f->max_heap->vetor_clientes[id_encontrado]->prioridade;
        atualiza_max_heap(f->max_heap, id_encontrado, prioridade_nova);

        if (prioridade_nova < prioridade_antiga) sobe_min_heap(f->min_heap, id_encontrado_min);
        else desce_min_heap(f->min_heap, id_encontrado_min);
    }
}

void remove_prim_fila(fila_prioridade *fila)
{
    if (fila->qtde > 0)
    {
        //output
        printf("Mesa liberada para Sr(a) %s.\n", fila->max_heap->vetor_clientes[0]->sobrenome);

        //remocao
        int id_min = fila->max_heap->vetor_clientes[0]->id_min;
        remove_max_heap(fila->max_heap);
        remove_ID_min_heap(fila->min_heap, id_min);

        fila->qtde--;

        free(fila->max_heap->vetor_clientes[fila->qtde]);
        fila->max_heap->vetor_clientes[fila->qtde] = NULL;
        fila->min_heap->vetor_clientes[fila->qtde] = NULL;

    }
}

void remove_ult_fila(fila_prioridade *fila)
{
    if (fila->qtde > 0)
    {
        //output
        printf("Sr(a) %s desistiu de esperar e foi embora.\n", fila->min_heap->vetor_clientes[0]->sobrenome);

        //remocao
        int id_max = fila->min_heap->vetor_clientes[0]->id_max;
        remove_min_heap(fila->min_heap);
        remove_ID_max_heap(fila->max_heap, id_max);

        fila->qtde--;

        free(fila->max_heap->vetor_clientes[fila->qtde]);
        fila->max_heap->vetor_clientes[fila->qtde] = NULL;
        fila->min_heap->vetor_clientes[fila->qtde] = NULL;

    }
}

void imprime_p_u(fila_prioridade *fila)
{
    if (fila->qtde > 0)
    {
        printf("[%s %d ... ", fila->max_heap->vetor_clientes[0]->sobrenome, fila->max_heap->vetor_clientes[0]->prioridade);
        printf("%s %d]\n", fila->min_heap->vetor_clientes[0]->sobrenome, fila->min_heap->vetor_clientes[0]->prioridade);
    }
    else
    {
        printf("[ ]\n");
    }
}

void destroi_heap(Heap *h)
{
    /*
    for (int i = 0; i < h->qtde; i++)
        free(h->vetor_clientes[i]);
        */
    int i=0;
    while (i < h->qtde && h->vetor_clientes[i] != NULL)
    {
        free(h->vetor_clientes[i]);
        h->vetor_clientes[i] = NULL;
        i++;
    }
    free(h->vetor_clientes);
    free(h);
}

void destroi_fila(fila_prioridade *fila)
{
    destroi_heap(fila->max_heap);
    free(fila->min_heap->vetor_clientes);
    free(fila->min_heap);

    free(fila);
}
