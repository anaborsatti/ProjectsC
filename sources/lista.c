#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "lista.h"


//Esta função cria uma lista, inicialmente vazia
//retorna um ponteiro para a lista vazia
Lista *lista(void)
{
    //nesta implementação, uma lista vazia corresponde ao ponteiro NULL
    return NULL;
}

//Esta função recebe um ponteiro para uma lista,
//e verifica se a lista recebida é uma lista vazia
//retorna 1 caso esteja vazia, e 0 caso contrário
int lista_vazia(Lista *l)
{
    return l == NULL;
}

//Dado um ponteiro para uma lista, retorna o tamanho da
//lista (i.e. o número de elementos na lista).
//O tamanho de uma lista vazia é 0
int lista_tamanho(Lista *l)
{
    int i=0;
    while(l != NULL)
    {
        l = l->next;
        i++;
    }
    return i;
}

//Dado um ponteiro para uma lista, imprime para o ecrâ todos os elementos
//da lista, separados por ',' e entre chavetas '{' '}'.
//No final muda de linha.
void lista_println(Lista *l)
{
    if(l == NULL) 
    {
        printf("{}\n");
        return;
    }

    printf("{%.2lf",l->value);
    l = l->next;

    while(l != NULL)
    {
        printf(",%.2lf",l->value);
        l = l->next;
    }

    printf("}\n");
}

//Dado um ponteiro para uma lista não vazia, devolve o primeiro elemento da lista
//A lista não pode ser uma lista vazia.
double lista_primeiro(Lista *l)
{
    assert(l != NULL);
    return l->value;
}

//Dado um ponteiro para uma lista não vazia, devolve um ponteiro para o resto da lista,
//ou seja a lista sem o primeiro elemento.  
//A lista não pode ser uma lista vazia.
//O primeiro elemento não é removido da lista original.
Lista *lista_resto(Lista *l)
{
    assert(l != NULL);
    return l->next;
}

//Dado um ponteiro para uma lista, e um índice correspondente a uma posição válida da lista
//retorna o elemento guardado nessa posição. 
//O índice 0 corresponde ao 1.º elemento guardado na lista, e assim sucessivamente.
//Caso o índice recebido não corresponda a uma posição válida, ocorre um erro.
double lista_obtem(Lista *l, int n)
{
    //implementação alternativa, para quem gosta mais de for
    for(int i = 0; i < n; i++)
    {
        assert(l!=NULL);
        l = l->next;
    }

    assert(l!=NULL);
    return l->value;
}

//dada um ponteiro para uma lista, e um valor
//retorna um ponteiro para uma nova lista que resulta de inserir o valor
//no inicio da lista recebida
Lista *lista_insere(Lista *l, double valor)
{
    //insere no inicio da lista, é mais fácil
    Lista *first = malloc(sizeof(Lista));

    first->value = valor;
    first->next = l;

    return first;
}

//Dado um ponteiro para uma lista, e um valor
//retorna um ponteiro para a lista e retorna um ponteiro para a lista
//que resulta de inserir o valor no fim da lista recebida
Lista *lista_insere_fim(Lista *l, double valor)
{
    //Existe uma implementação alternativa da lista
    //que me permite fazer esta operação de forma eficiente
    //mas usando a implementação atual, não tenho outra hipótese
    
    //Caso especial, a lista é vazia. Neste caso a inserção no fim
    //é igual à inserção no inicio
    if(l == NULL) return lista_insere(l,valor);

    //guarda um ponteiro para o início da lista, vamos precisar disto no fim
    Lista *inicio = l;
    //avança na lista até encontrar o último nó
    while(l->next != NULL)
    {
        l = l->next;
    }
    //encontramos o último nó, inserir o elemento a seguir ao último nó
    l->next = lista_insere(NULL,valor);
    return inicio;
}

//Dado um ponteiro para uma lista, um indíce válido e um valor
//Retorna um ponteiro para a lista, depois de ter inserido o valor
//na posição indicada da lista. Os valores seguintes serão movidos uma posição
//para a frente na lista. 
//Caso o índice recebido não corresponda a uma posição válida, ocorre um erro.
Lista *lista_insere_posicao(Lista *l, int i, double valor)
{
    //caso especial, inserção no início
    if(i == 0) return lista_insere(l,valor);
    assert(l != NULL);

    Lista *inicio = l;
    //procuramos o nó na posição anterior a i
    while(i > 1)
    {
        assert(l!=NULL);
        l = l->next;
        i--;
    }

    l->next = lista_insere(l->next, valor);
    return inicio;
}

//Dado um ponteiro para uma lista, um indíce válido e um valor
//Retorna um ponteiro para a lista, depois de alterar o valor
//guardado na posição indicada da lista. 
//Caso o índice recebido não corresponda a uma posição válida, ocorre um erro.
Lista *lista_altera_posicao(Lista *l, int i, double valor)
{
    Lista *inicio = l;
    //procuramos o nó na posição i
    while(i > 0)
    {
        assert(l!=NULL);
        l = l->next;
        i--;
    }

    assert(l!=NULL);
    l->value = valor;
    return inicio;
}

//Dado um ponteiro para uma lista, remove o primeiro elemento da lista,
//e retorna a lista que resulta desta remoção. O elemento removido
//é apagado da lista original, e a memória ocupada por ele é libertada. 
//Caso a lista esteja vazia, ocorre um erro.
Lista *lista_remove_primeiro(Lista *l)
{
    assert(l != NULL);

    Lista *result = l->next;
    free(l);
    return result;
}

//Dado um ponteiro para uma lista, remove o ultimo elemento da lista,
//e retorna a lista que resulta desta remoção. O elemento removido
//é apagado da lista original, e a memória ocupada por ele é libertada.
//Caso a lista esteja vazia, ocorre um erro
Lista *lista_remove_ultimo(Lista *l)
{
    //primeiro caso especial, a lista é vazia
   assert(l != NULL);

    //segundo caso especial, a lista só tem 1 elemento,
    //que será apagado, retornamos NULL
    if(l->next == NULL)
    {
        free(l);
        return NULL;
    }

    //guarda um ponteiro para o início da lista, vamos precisar disto no fim
    Lista *inicio = l;
    
    //avança na lista até encontrar o penúltimo nó
    while(l->next->next != NULL)
    {
        l = l->next;
    }

    //encontramos o penúltimo nó, remover o elemento a seguir ao penúltimo nó
    free(l->next);
    //temos de fazer com que o penúltimo nó passe a apontar para NULL
    l->next = NULL;

    return inicio;
}

//Dado um ponteiro para uma lista, remove o elemento no índice i recebido.
//Retorna um ponteiro para o início da lista, já sem o elemento. 
//O elemento é removido da lista original, e a memória ocupada por ele libertada.
//O índice 0 corresponde ao 1.º elemento guardado na lista, e assim sucessivamente.
//Caso o índice recebido não corresponda a uma posição válida, ocorre um erro.
Lista *lista_remove_posicao(Lista *l, int i)
{
    //caso especial, corresponde a remover o primeiro elemento
    if(i == 0) return lista_remove_primeiro(l);
    
    assert(l != NULL);

    Lista *inicio = l;

    //para no elemento anterior ao i
    while(i > 1)
    {
        assert(l->next != NULL);
        l = l->next;
        i--;
    }

    assert(l->next != NULL);
    Lista *apagar = l->next;
    l->next = l->next->next;
    free(apagar);

    return inicio;
}


//Dado um ponteiro para uma lista, apaga todos os elementos da lista,
//e liberta a memória ocupada por todos os elementos
void lista_free(Lista *l)
{
    //neste caso nada a fazer, é uma lista vazia
    if(l == NULL) return;

    Lista *apagar;

    while(l ->next != NULL)
    {
        apagar = l;
        l = l->next;
        free(apagar);
    }

    free(l);
}

//Dado um ponteiro para uma lista, retorna uma cópia profunda da lista
//que corresponde a uma cópia de todos os elementos da lista.
Lista *lista_copia(Lista *l)
{    
    if(l == NULL) return NULL;

    //copia o primeiro nó
    Lista *copia_no = malloc(sizeof(Lista));
    //copia o ponteiro e o valor da struct do nó
    *copia_no = *l;
    Lista *inicio_da_copia = copia_no;

    //copia os restantes nós
    l = l->next;
    Lista *copia_no_anterior = copia_no;
    while(l != NULL)
    {
        //copia o nó
        copia_no = malloc(sizeof(Lista));
        *copia_no = *l;
        //fazemos com que a cópia do nó anterior passe a apontar para a nova cópia criada
        copia_no_anterior->next = copia_no;
        //avançamos os ponteiros
        l = l->next;
        copia_no_anterior = copia_no;
    }
    
    return inicio_da_copia;
}

//Dado um ponteiro para uma lista, retorna uma cópia profunda da lista
//que corresponde a uma cópia de todos os elementos da lista.
//A versão sem usar recursão parece muito mais complicada.
//Vejam a diferença em linhas de código :D
Lista *lista_copia_recursiva(Lista *l)
{
    if(l == NULL) return NULL;
    return lista_insere(lista_copia(lista_resto(l)),l->value);
}