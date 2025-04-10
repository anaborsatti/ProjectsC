//versao do ficheiro feiticos.h a usar para o projeto de LP

//este operador serve para dizer ao compilador de C, que este ficheiro header so deve ser processado
//se ainda nao sido processado anteriormente
//le-se "se ainda nao tiver sido definido FEITICOS_H, define FEITICOS_H".
//Se o teste falhar (i.e. FEITICOS_H ja foi definido), o compilador salta para o #endif e tudo o que esta
//dentro do #if e ignorado
#ifndef FEITICOS_H
#define FEITICOS_H

//este include tem como objetivo certificar-me de que quando invocarem um malloc, calloc, strdup, free
//aquilo que será invocado serão as funções de memória do leaks_checker que permitem mais tarde
//verificar se têm ou não fugas de memória
//#include "leaks_checker.h"

//Definicao do enumerado School
typedef enum school {Enchantment, Necromancy, Divination, Evocation, Abjuration, Transmutation, Illusion, Conjuration, Invalid=-1} School;

//Dada uma string, retorna a escola correspondente à string recebida
//caso a string recebida não corresponda a uma das escolas válidas, deve ser 
//retornado a escola inválida (-1)
School string_2_school(char *s);

//Dada uma escola, retorna uma String correspondente à escola
//Se o valor correspondente ao enumerado recebido não for válido,
//deve ser retornado o ponteiro NULL
const char * school_2_string(School t);

//Define o Tipo Estruturado Feitico, e os seus membros
typedef struct S_Feitico {
	char name[100];
	char *casting_time;
	School school;
	int level;
	int range;
	int duration;
	int concentration;
	char *description;
} Feitico;

//funções já existentes que não é necessário alterar a sua implementacao

//Dado um vetor de ponteiros para feiticos, um numero n de feiticos, uma string com o nome de um feitiço, 
//esta funcao procura no vetor feiticos pelo primeiro feitico com nome igual ao nome recebido,
// e retorna o ponteiro para esse feitico.
//Caso nao exista tal feitico, retorna-se o ponteiro NULL
Feitico *find_feitico(Feitico *feiticos[], int n, char *name);

//dado um vetor de ponteiros para feiticos, um inteiro n representando o tamanho do vetor,
//e uma string com o nome do feitiço, procura pelo feitiço no vetor, e caso o encontre,
//remove-o do vetor, e apaga o feitiço. O vetor é reorganizado, passando todos os
//elementos à direita do feitiço apagado uma posição para a sua esquerda.
//Retorna o número de elementos no vetor final, depois de apagado o feitiço. Caso o feitiço
//não exista, nada é apagado, e é retornado o mesmo número n recebido.
int delete_feitico(Feitico *feiticos[], int n, char *name);

//Construtor do tipo Feitico, recebe os membros, e cria um novo feitico f, e inicializa-o. Devolve
//um ponteiro para o Feitico criado. Se algum dos argumentos recebidos não for válido, o Feitiço não
//deve ser criado, e é retornado o ponteiro NULL.
Feitico *create_feitico(char *name, char *casting_time, char *school, int lvl, int range, int duration, int concentration, char *description);

//Imprime um Feitico para o standard output, de acordo com o formato especificado no enunciado.
void println_feitico(Feitico *f);

//Recebe um vetor de ponteiros para feiticos, e o numero de elementos no vetor n, e imprime
//todos os Feiticos, pela ordem em que aparecem no vetor. Caso nao existam elementos no vetor
//imprime "No Spells!\n"
void println_feiticos(Feitico *feiticos[], int n);

//Dado um ponteiro para um ficheiro lê o próximo feitiço do ficheiro, e retorna um ponteiro
//para o feitiço criado. Caso o feitiço lido seja inválido, deverá ser retornado NULL
//o feitiço deve ser lido de acordo com a especificação do enunciado
Feitico* read_feitico_from(FILE *stream);

//Dado um ponteiro para um ficheiro, lê todos os feitiços escritos no ficheiro. Retorna um vetor
//de ponteiros para Feiticos, que contém todos os feitiços válidos lidos. O argumento out_size 
//é um ponteiro para um inteiro usado para guardar o número de feitiços válidos lidos pela função
//Caso não existam feitiços para ler no ficheiro, deve ser guardado 0 no out_size.
//Caso seja encontrado um feitiço inválido, deve ser impresso no ecrâ, "Invalid Spell: <nome do feitiço>\n"
Feitico** read_feiticos_from(FILE *stream, int* out_size);

//Dado um ponteiro para um ficheiro, aberto para escrita, escreve o feitiço no ficheiro.
//O formato de saída deve ser exatamente igual ao formato de entrada.
void write_feitico_to(FILE *stream, Feitico *f);

//Dado um ponteiro para um ficheiro, e um vetor de ponteiros para feitiços, e o tamanho
//n desse vetor, grava todos os feitiços do vetor no ficheiro.
//caso o número de feitiços a escrever seja 0, nada é escrito.
void write_feiticos_to(FILE *stream, Feitico *feiticos[], int n);

//Recebe um ponteiro para um feitico, e cria uma cópia (ou clone) profunda do feitico. Devolve um
//ponteiro para a cópia criada
Feitico *copy_feitico(Feitico *f);

//Recebe um ponteiro para um feitico, e liberta a memória usada pelo tipo.
//Deve libertar toda a memória reservada (direta ou indiretamente) pelo construtor.
void free_feitico(Feitico *f);



/****** novas funcoes a usar/implementar *********/
//A funcao update tera de ser alterado, pois agora tem uma nova logica
//Devem decidir quais os argumentos que a funcao receber.
///void update_feitico(Feitico *f, .....)

//funcao que dado um ponteiro para um feitico retorna um dos seus membros que seja do tipo inteiro
typedef int (*IntFeiticoSelector)(Feitico *);

//dado um vetor de entrada de ponteiros de feiticos in, e um vetor de saida de ponteiros de feiticos out,
//um inteiro n que corresponde ao numero de elementos de in, e uma funcao de selecao de inteiros sobre feiticos
//esta funcao procura no vetor todos os feiticos cujo valor selecionado pela funcao de selecao esteja
//entre os valores minimo e maximo recebidos (inclusive), colocando-os no 
//vetor de saida out. A funcao retorna o numero de elementos encontrados e guardados em out.
int filter_feiticos_between(Feitico *in[], Feitico *out[], int n, IntFeiticoSelector selector, int min, int max);

//nao e obrigatorio usar, mas estes typedefs podem dar jeito
//funcao de comparacao generica usada pelo quicksort
typedef int (*Comparer)(const void *, const void *);

//funcao de comparacao especifica para ponteiros de feiticos
typedef int (*FeiticoComparer)(const Feitico **, const Feitico **);

//exemplo de uma funcao do tipo FeiticoComparer que terao de implementar
//devem implementar outras funcoes de comparacao
//esta funcao recebe um ponteiro para um ponteiro de Feitico f1, e um 
//ponteiro para um ponteiro de Feitico f2 (o const serve para garantir
//que nao iremos alterar os valores recebidos), e compara os feiticos
//correspondentes tendo em conta o nivel, de forma ascendente (do nivel
//mais pequeno para o nivel maior)
//caso f1 tenha um nivel menor que f2 deve ser retornado um valor negativo, caso tenham
//o mesmo nivel deve ser retornado 0, e caso seja maior, deve ser retornado um valor positivo
int compare_feitico_lvl_asc(const Feitico **f1, const Feitico **f2);

//funcao de execucao do Spell Management System, a espeficicação detalhada está no enunciado.
void runSMS(void);

#endif