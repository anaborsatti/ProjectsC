#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include "leaks_checker.h"
#include "feiticos.h"

char* school_names[]= {"Enchantment", "Necromancy", "Divination", "Evocation", "Abjuration", "Transmutation", "Illusion", "Conjuration"};

const char * school_2_string(School t)
{
    return school_names[t];
}

School string_2_school(char *s)
{
    for (int i = 0; i < 8; i++) 
        if (strcmp(school_names[i], s) == 0)
            return (School)i;
    return Invalid; 
}

int is_valid (char *school, int lvl, int range, int duration, int concentration)
{
    School t = string_2_school (school);
    if (t == Invalid)
        return 0;
    if (lvl < 0 || lvl > 9) 
        return 0;
    if (range < 0)
        return 0;
    if (duration < 0)
        return 0;
    if (!(concentration == 0 || concentration == 1))
        return 0;
    else 
        return 1;
}

Feitico *create_feitico(char *name, char *casting_time, char *school, int lvl, int range, int duration, int concentration) //construtor
{
    Feitico *result = (Feitico*) malloc (sizeof(Feitico)); //alocar memoria dinamica que aponta para feitiço, e vai se manter mesmo depois da função terminar
    strcpy (result->name, name); //copiar uma string pra uma memoria que ja existe
    result->casting_time = strdup (casting_time); // Calcula o tamanho necessário para guardar a string recebidaReserva esse espaço no heap Copia para o espaço reservado a string recebida Devolve um ponteiro para o espaço reservado
    School t = string_2_school (school);
    result->school = t; //passa de char para o tipo enumerado
    result->level = lvl;
    result->range = range;
    result->duration = duration;
    result->concentration = concentration;
    return result; 
}

/*Feitico *my_create_feitico(char *name, char *casting_time, School school, int lvl, int range, int duration, int concentration) //construtor
{
    Feitico *result = (Feitico*) malloc (sizeof(Feitico)); //alocar memoria dinamica que aponta para feitiço, e vai se manter mesmo depois da função terminar
    strcpy (result->name, name); //copiar uma string pra uma memoria que ja existe
    result->casting_time = strdup (casting_time); // Calcula o tamanho necessário para guardar a string recebidaReserva esse espaço no heap Copia para o espaço reservado a string recebida Devolve um ponteiro para o espaço reservado
    result->school = school; //passa de char para o tipo enumerado
    result->level = lvl;
    result->range = range;
    result->duration = duration;
    result->concentration = concentration;
    return result; 
} */

int read_feiticos(Feitico *feiticos[], int n) //*feitcos[] == **feiticos
{
    int result = 0;
    char name[100];
    char casting_time[100];
    int lvl;
    char school[100];
    int range;
    int duration; 
    int concentration;
    for (int i = 0; i < n; i++)
    {
        scanf ("%s%d%s%s%d%d%d", name, &lvl, school, casting_time, &range, &duration, &concentration); 
        if (is_valid (school, lvl, range, duration, concentration) == 1)
            feiticos [result++] = create_feitico (name, casting_time, school, lvl, range, duration, concentration);
        else 
            printf ("Invalid Spell: %s\n", name);  
    }
    return result; 
}


void write_duration (int d)
{
    if (d == 0)
        printf ("Instantaneous");
    else if (d <= 10)
        printf ("%d rounds", d);
    else if (d < 600)
        printf ("%d minutes", d/10);
    else 
        printf ("%d hours", d/600);
}

void write_concentration (int c)
{
    if (c == 1)
        printf (" (Concentration)");
}

void println_feitico (Feitico *s) //apontador para structs: ->
{
    printf ("------------------------------\n");
    printf ("%s\n", s->name);
    printf ("Level: %d, %s\n",s->level, school_2_string (s->school));
    printf ("Casting Time: %s\n", s->casting_time);
    printf ("Range: %d feet\n",  s->range);
    printf ("Duration: ");
    write_duration (s->duration);
    write_concentration (s->concentration);
    printf ("\n");
}

void println_feiticos (Feitico *feitico[], int n)//a[i] = *(a+i), &a[i]= a+i
{
    for (int i= 0; i < n; i++) 
        println_feitico (feitico[i]);
}

void feiticos_to_feiticos_ptr (Feitico *in, int n, Feitico **out)
{
    for (int i=0; i<n; i++)
        out[i]= in + i;
}

Feitico *find_feitico (Feitico **in, int n, char *name)
{
    for (int i= 0; i <n; i++)
        if (strcmp(in[i]->name, name)==0)
            return in[i];
    return NULL;
}

int find_feitico_i (Feitico **in, int n, char *name)
{
    for (int i= 0; i <n; i++)
        if (strcmp(in[i]->name, name)==0)
            return i;
    return -1;
}

void update_feitico (Feitico *f, char *new_name, char *new_casting_time)
{
    strcpy (f->name, new_name);
    free (f->casting_time); //libertar memoria dinamica alocada anteriormente
    f->casting_time = strdup (new_casting_time);
}

int filter_feiticos_lvl(Feitico *in[], Feitico *out[], int n, int min_lvl, int max_lvl)
{
    int result = 0;
    for (int i = 0; i<n; i++)
        if (min_lvl <=in[i]->level && in[i]->level <= max_lvl)
            out[result++] = in[i];
    return result; 
}

Feitico *copy_feitico(Feitico *f)
{
    // return create_feitico (f->name, f->casting_time, school_2_string(f->school), f->level, f->range, f->duration, f->concentration);
    char z[32];
    strcpy (z, school_2_string(f->school));
    return create_feitico (f->name, f->casting_time, z, f->level, f->range, f->duration, f->concentration);
}

void free_feitico(Feitico *f)
{
    free (f->casting_time);
    free (f);
}

int shift_left (void *a[], int n)
{
    int result = 0;
    for (int i=1; i<n; i++)
        a[result++] = a[i];
    return result;
}

int delete_feitico(Feitico *feiticos[], int n, char *name)
{
    int result = n;
    int z = find_feitico_i (feiticos, n, name);
    if (z != -1)
    {
        free_feitico (feiticos[z]);
        shift_left ((void*)(feiticos + z), n-z);
        result--;
    }
    return result;    
}

void test_F (void)
{
    int n_spells;
    scanf ("%d", &n_spells);
    Feitico *a[n_spells];
    int n = read_feiticos(a, n_spells);

    char comando[100];
    
    while (scanf ("%s", comando) != EOF)
    {
        if (strcmp (comando, "UPDATE")==0)
        {
            char name[100]; 
            char new_name[100];
            char new_casting_time[100];
            scanf ("%s%s%s", name, new_name, new_casting_time);
            Feitico *z = find_feitico (a, n, name);
            if (z == NULL)
                printf ("No such spell exists!\n");
            else 
            {
                update_feitico (z, new_name, new_casting_time);
                println_feitico (z);
            }   
        }
        else if (strcmp (comando, "DELETE")== 0)
        {
            char name[100]; 
            scanf ("%s", name);
            int n0 = n;
            n = delete_feitico (a, n, name);
            if (n == n0)
                printf ("No such spell exists!\n");
            else 
                printf ("Spell deleted.\n");
        }
        else if (strcmp (comando, "FILTER")== 0)
        {
            char lvl[16];
            int min_level;
            int max_level;
            scanf ("%s%d%d", lvl, &min_level, &max_level);
            assert (strcmp(lvl, "lvl")==0);
            Feitico *b[n];
            int m = filter_feiticos_lvl(a, b, n, min_level, max_level);
            if (m == 0)
                printf ("No Spells!\n");
            else 
                println_feiticos (b, m);
        }
        else 
            assert (0); //da erro e o programa para
    }
}

void test_school_string (void)
{
    School school;
    scanf ("%d", &school);
    printf ("%s\n", school_2_string (school));
}

void test_string_school(void)
{
    char a[100];
    scanf("%s", a);
    printf("%d\n", string_2_school(a));
}

void test_is_valid (void)
{
    int lvl;
    char school[100];
    int range;
    int duration;
    int concentration;
    scanf ("%s%d%d%d%d", school, &lvl, &range, &duration, &concentration); // Adicione os endereços de memória usando &
    printf ("%d\n", is_valid (school, lvl, range, duration, concentration));
}

void test_read_spell (void)
{
    int n_spells;
    scanf ("%d", &n_spells);
    Feitico *a[n_spells];
    int n = read_feiticos(a, n_spells);
    println_feiticos (a, n);
} 

#ifndef MOOSHAK_MAIN
int main(void)
{
    test_F();
    // test_is_valid ();
    // test_read_spell ();
    return 0;
}
#endif
