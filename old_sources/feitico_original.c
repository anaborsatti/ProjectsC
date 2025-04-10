#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef struct S_Spell {
    char name[100];
    int level;
    char school[100];
    int range;
    int duration;
    int concentration;
} Spell;

Spell spell (char *name,int level, char *school, int range, int duration, int concentration) //construtor
{
    Spell result;
    strcpy (result.name, name); //copiar uma string 
    result.level = level;
    strcpy (result.school, school);
    result.range = range;
    result.duration = duration;
    result.concentration = concentration;
    return result;
}

int get_spell (Spell *s)
{
    int i = 0;
    char name[100];
    int level;
    char school[100];
    int range;
    int duration; 
    int concentration;
    while (scanf ("%s%d%s%d%d%d", name, &level, school, &range, &duration, &concentration)!= EOF)
        s[i++]= spell (name, level, school, range, duration, concentration);
    return i;
}

int read_spell (Spell *s, int n)
{

    char name[100];
    int level;
    char school[100];
    int range;
    int duration; 
    int concentration;
    for (int i =0; i< n; i++)
    {
        scanf ("%s%d%s%d%d%d", name, &level, school, &range, &duration, &concentration);
        s[i]= spell (name, level, school, range, duration, concentration);
    }
    return n;
        
}

void my_spell_write (Spell s)
{
    printf ("[<%s>%d<%s>%d %d %d]\n", s.name, s.level, s.school, s.range, s.duration, s.concentration);
}

void my_spells_write (Spell *a, int n)
{
    for (int i= 0; i < n; i++)
    {
        my_spell_write (a[i]);
    }
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


void spell_write (Spell *s) //apontador para structs: ->
{
    printf ("------------------------------\n");
    printf ("%s\n", s->name);
    printf ("Level: %d, %s\n",s->level, s->school);
    printf ("Range: %d feet\n",  s->range);
    printf ("Duration: ");
    write_duration (s->duration);
    write_concentration (s->concentration);
    printf ("\n");
}

void spells_write (Spell *a, int n)//a[i] = *(a+i), &a[i]= a+i
{
    for (int i= 0; i < n; i++) 
    {
        spell_write (a+i);
    }
}

void spells_write_ptr (Spell **a, int n)//a[i] = *(a+i), &a[i]= a+i
{
    for (int i= 0; i < n; i++) 
    {
        spell_write (*(a+i));
    }
}

void feiticos_to_feiticos_ptr (Spell *in, int n, Spell **out)
{
    for (int i=0; i<n; i++)
        out[i]= in + i;
}

Spell *search_spell (Spell **in, int n, char *name)
{
    for (int i= 0; i <n; i++)
        if (strcmp(in[i]->name, name)==0)
            return in[i];
    return NULL;
}



void update_spell (Spell *s, int new_range)
{
    s->range = new_range;
}


void test_get_spell (void)
{
    int n_spells;
    scanf ("%d", &n_spells);
    Spell a[n_spells];
    int n = get_spell (a);
    printf ("%d\n", n);
    assert (n == n_spells);
    my_spells_write (a, n);
}

void test_write_spell (void)
{
    int n_spells;
    scanf ("%d", &n_spells);
    Spell a[n_spells];
    int n = get_spell (a);
    assert (n == n_spells);
    spells_write (a, n);
}

void test_update_spell (void)
{
    int n_spells;
    scanf ("%d", &n_spells);
    Spell a[n_spells];
    int n = read_spell (a, n_spells);
    printf ("***%d\n", n);
    printf ("---\n");
    spells_write (a, n);
    printf ("---\n");
    assert (n == n_spells);
    Spell *b[n_spells];
    feiticos_to_feiticos_ptr (a, n, b);
    printf ("---\n");
    spells_write_ptr (b, n);
    printf ("---\n");
    char comando[100];
    char spell_name[100];
    int value;
    while (scanf ("%s%s%d", comando, spell_name, &value) != EOF)
    {
        assert (strcmp (comando, "UPDATE")==0);
        Spell *z = search_spell (b, n, spell_name);
        if (z == NULL)
            printf ("No such spell exists!\n");
        else 
        {
            update_spell (z, value);
            spell_write (z);
        }
            
    }
}

void test_update_spell_mooshak (void)
{
    int n_spells;
    scanf ("%d", &n_spells);
    Spell a[n_spells];
    int n = read_spell (a, n_spells);
    assert (n == n_spells);
    Spell *b[n_spells];
    feiticos_to_feiticos_ptr (a, n, b);
    char comando[100];
    char spell_name[100];
    int value;
    while (scanf ("%s%s%d", comando, spell_name, &value) != EOF)
    {
        assert (strcmp (comando, "UPDATE")==0);
        Spell *z = search_spell (b, n, spell_name);
        if (z == NULL)
            printf ("No such spell exists!\n");
        else 
        {
            update_spell (z, value);
            spell_write (z);
        }
            
    }
}


int main ()
{
   // test_get_spell ();
   //test_write_spell ();
   test_update_spell_mooshak ();


}
