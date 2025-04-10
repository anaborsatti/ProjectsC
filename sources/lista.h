#include <stdio.h>

//Definição mais simples possível de uma lista 
//(que guarda valores do tipo double)
typedef struct s_node 
{
    double value;
    struct s_node *next;
} Lista;

//Esta função cria uma lista, inicialmente vazia
//retorna um ponteiro para a lista vazia
Lista *lista(void);

//Esta função recebe um ponteiro para uma lista,
//e verifica se a lista recebida é uma lista vazia
//retorna 1 caso esteja vazia, e falso caso contrário
int lista_vazia(Lista *l);

//Dado um ponteiro para uma lista, retorna o tamanho da
//lista (i.e. o número de elementos na lista).
//O tamanho de uma lista vazia é 0
int lista_tamanho(Lista *l);

//Dado um ponteiro para uma lista, imprime para o ecrâ todos os elementos
//da lista, separados por ',' e entre chavetas '{' '}'.
//No final muda de linha.
void lista_println(Lista *l);

//Dado um ponteiro para uma lista não vazia, devolve o primeiro elemento da lista
//A lista não pode ser uma lista vazia.
double lista_primeiro(Lista *l);

//Dado um ponteiro para uma lista não vazia, devolve um ponteiro para o resto da lista,
//ou seja a lista sem o primeiro elemento.  
//A lista não pode ser uma lista vazia.
//O primeiro elemento não é removido da lista original.
Lista *lista_resto(Lista *l);

//Dado um ponteiro para uma lista, e um índice correspondente a uma posição válida da lista
//retorna o elemento guardado nessa posição. 
//O índice 0 corresponde ao 1.º elemento guardado na lista, e assim sucessivamente.
//Caso o índice recebido não corresponda a uma posição válida, ocorre um erro.
double lista_obtem(Lista *l, int i);

//Dado um ponteiro para uma lista, e um valor
//retorna um ponteiro para uma nova lista que resulta de inserir o valor
//no inicio da lista recebida
Lista *lista_insere(Lista *l, double valor);

//Dado um ponteiro para uma lista, e um valor
//retorna um ponteiro para a lista 
//que resulta de inserir o valor no fim da lista recebida
Lista *lista_insere_fim(Lista *l, double valor);

//Dado um ponteiro para uma lista, um indíce válido e um valor
//Retorna um ponteiro para a lista, depois de ter inserido o valor
//na posição indicada da lista. Os valores seguintes serão movidos uma posição
//para a frente na lista. 
//Caso o índice recebido não corresponda a uma posição válida, ocorre um erro.
Lista *lista_insere_posicao(Lista *l, int i, double valor);

//Dado um ponteiro para uma lista, um indíce válido e um valor
//Retorna um ponteiro para a lista, depois de alterar o valor
//guardado na posição indicada da lista. 
//Caso o índice recebido não corresponda a uma posição válida, ocorre um erro.
Lista *lista_altera_posicao(Lista *l, int i, double valor);

//Dado um ponteiro para uma lista, remove o primeiro elemento da lista,
//e retorna a lista que resulta desta remoção. O elemento removido
//é apagado da lista original, e a memória ocupada por ele é libertada. 
Lista *lista_remove_primeiro(Lista *l);

//Dado um ponteiro para uma lista, remove o ultimo elemento da lista,
//e retorna a lista que resulta desta remoção. O elemento removido
//é apagado da lista original, e a memória ocupada por ele é libertada. 
Lista *lista_remove_ultimo(Lista *l);

//Dado um ponteiro para uma lista, remove o elemento no índice i recebido.
//Retorna um ponteiro para o início da lista, já sem o elemento. 
//O elemento é removido da lista original, e a memória ocupada por ele libertada.
//O índice 0 corresponde ao 1.º elemento guardado na lista, e assim sucessivamente.
//Caso o índice recebido não corresponda a uma posição válida, ocorre um erro.
Lista *lista_remove_posicao(Lista *l, int i);

//Dado um ponteiro para uma lista, apaga todos os elementos da lista,
//e liberta a memória ocupada por todos os elementos
void lista_free(Lista *l);

//Dado um ponteiro para uma lista, retorna uma cópia profunda da lista
//que corresponde a uma cópia de todos os elementos da lista.
Lista *lista_copia(Lista *l);