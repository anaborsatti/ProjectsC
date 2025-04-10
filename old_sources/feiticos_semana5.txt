#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include <limits.h>

#include "feiticos.h"
int MAX_LINE_LENGTH = 1000;


// Read a line from `f` to `s`. Does not control buffer overflow.
int str_readline(FILE *f, char *s)
{
  int result = EOF;
  char *p = fgets(s, INT_MAX, f);
  if (p != NULL)
  {
    result = (int) strlen(s);
    if (result > 0 && s[result-1] == '\n')
      s[--result] = '\0';
  }
  return result;
} 

int str_getline(char *s)
{
  return str_readline(stdin, s);
}

char* str_ncpy(char *r, const char *s, int x)
{
  int n = 0;
  for (int i = 0; i < x && s[i]; i++)
    r[n++] = s[i];
  r[n] = '\0';
  return r;
}

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

int is_valid (char *school, int lvl, int range, int duration, int concentration, char* description)
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
    if (*description == '\0')  // ******
        return 0;
    else 
        return 1;
}

void check_free(void *p, char *message)
{
    if (p == NULL)
        printf("%s\n", message);
}

Feitico *create_feitico(char *name, char *casting_time, char *school, int lvl, int range, int duration, int concentration, char* description) //construtor
{
    Feitico *result = NULL;
    if(is_valid (school, lvl, range, duration, concentration, description))
    {
        result = (Feitico*) malloc (sizeof(Feitico)); //alocar memoria dinamica que aponta para feitiço, e vai se manter mesmo depois da função terminar
        strcpy (result->name, name); //copiar uma string pra uma memoria que ja existe
        result->casting_time = strdup (casting_time); // Calcula o tamanho necessário para guardar a string recebidaReserva esse espaço no heap Copia para o espaço reservado a string recebida Devolve um ponteiro para o espaço reservado
        School t = string_2_school (school);
        result->school = t; //passa de char para o tipo enumerado
        result->level = lvl;
        result->range = range;
        result->duration = duration;
        result->concentration = concentration;
        result->description = strdup (description); //nao seria necessario o dup pois ja estamos alocando memoria no read. Mooshak hack.
    }

    return result; 
}

char *read_description_detaild(FILE *f)
{
  char *result = NULL;
  int n = 0;
  char line[MAX_LINE_LENGTH];
  while (fgets(line, MAX_LINE_LENGTH, f)) //de onde começa, maximo de caracteres, e de onde vai ser lido
  {
    printf("<<<%s>>>\n", line);   // só para ir vendo...
    if (strcmp(line, "\\EOD\n") == 0)
      break;  
    int start = n; // resultado de somar as linhas todas em uma string
    n += strlen(line); //nao conta o terminador
    result = (char *) realloc(result, n+1); //n + terminador
    strcpy(result+start, line); 
    strcat (result, line);
  }
  printf("[[[%s]]]\n", result);   // para ver como ficou, no fim...
  return result;
}

char *read_description(FILE *f)
{
  char *result = (char *) malloc(1);  //******
  *result = '\0';
  int n = 0;
  char line[MAX_LINE_LENGTH];
  while (fgets(line, MAX_LINE_LENGTH, f)) //de onde começa, maximo de caracteres, e de onde vai ser lido
  {
    if (strcmp(line, "\\EOD\n") == 0 || strcmp (line, "\\EOD") == 0)
      break;  
    int start = n; // resultado de somar as linhas todas em uma string
    n += strlen(line); //nao conta o terminador
    result = (char *) realloc(result, n+1); //n + terminador
    strcpy(result+start, line); 
  }
  return result;
}

Feitico *read_feitico_from(FILE *f)
{
    Feitico *result = NULL;
    char line[MAX_LINE_LENGTH];
    char name[MAX_LINE_LENGTH];
    char casting_time[MAX_LINE_LENGTH];
    int lvl;
    char school[MAX_LINE_LENGTH];
    int range;
    int duration; 
    int concentration;
    char *description;

    if (str_readline (f, name)== EOF) //chegamos ao fim do ficheiro 
        return result;

    str_readline (f, line);
    sscanf (line, "%d", &lvl);

    str_readline (f, school);
    str_readline(f, casting_time);

    str_readline (f, line);
    sscanf(line, "%d", &range);

    str_readline (f, line);
    sscanf(line, "%d", &duration);

    str_readline (f, line);
    sscanf (line, "%d", &concentration );

    description = read_description (f);

    result = create_feitico (name, casting_time, school, lvl, range, duration, concentration, description);
    if (result == NULL)
        printf ("Invalid Spell: %s\n", name);
    check_free(description, "free_description");
    free(description);

    return result; 
}

Feitico** resize_feitico (Feitico **a, int capacity)
{
    return (Feitico**) realloc (a, capacity*sizeof(Feitico*));
}

Feitico** read_feiticos_from(FILE *f, int* out_size) //*feitcos[] == **feiticos
{
    int capacity = 1;
    Feitico **result = (Feitico**) malloc(capacity*sizeof(Feitico*));
    int n = 0;
    while (1)
    {
        Feitico *z = read_feitico_from (f);
        if (z != NULL)
        {
            if (n == capacity)
                {
                    result = resize_feitico(result, 2*capacity);
                    capacity *= 2;
                }
            result [n++] = z;
        }  
        else 
            if (feof(f)) //confirmar se null é o fim do ficheiro ou invalido
                break;  
    }
    *out_size = n;
    if (*out_size == 0)
    {
        check_free(result, "free result in read_feiticos_from");
        free(result);
        return NULL;
    }
    result = realloc(result, (*out_size) * sizeof(Feitico *));
    if (result == NULL)
    {
        return NULL;
    }
    return result; 
}

void write_feitico_to(FILE *f, Feitico *feitico)
{
    fprintf (f, "%s\n", feitico->name);
    fprintf (f, "%d\n", feitico->level);
    fprintf (f, "%s\n", school_2_string(feitico->school));
    fprintf (f, "%s\n", feitico->casting_time); 
    fprintf (f, "%d\n", feitico->range);
    fprintf (f, "%d\n", feitico->duration);
    fprintf (f, "%d\n", feitico->concentration);
    fprintf (f, "%s", feitico->description); //sem \n pois ja tem 
    fprintf (f, "\\EOD");
}

void write_feiticos_to(FILE *f, Feitico *feiticos[], int n)
{
    for (int i = 0; i<n; i++)
    {
        write_feitico_to (f, feiticos[i]);
        if (i != n - 1)
        {
            fprintf (f, "\n");
        }
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
    printf ("%s", s->description);
    printf ("------------------------------\n");
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

void update_feitico (Feitico *f, char *new_casting_time)
{
    check_free(f->casting_time, "f->casting_time");
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
    return create_feitico (f->name, f->casting_time, z, f->level, f->range, f->duration, f->concentration, f->description);
}

void free_feitico(Feitico *f)
{
    check_free(f->casting_time, "free (f->casting_time)");
    check_free(f->description, "free (f->description);");
    check_free(f, "free (f)");
    free (f->casting_time);
    free (f->description);
    free (f);
}

void free_feiticos(Feitico **f, int n)
{
    for (int i=0; i<n; i++)
        free_feitico (f[i]); //libertar cada feitiço
    check_free(f, "free_feiticos");
    free (f); //libertar o array
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
        check_free(feiticos[z], "feiticos[z]");
        free_feitico (feiticos[z]);
        shift_left ((void*)(feiticos + z), n-z);
        result--;
    }
    return result;    
}

int str_find(const char *s, char x)
{
  for (int i = 0; s[i] != '\0'; i++)
    if (s[i] == x)
      return i;
  return -1;
}

int str_count_while(const char *s, char x)
{
  int result = 0;
  while (s[result] != '\0' && s[result] == x)
    result++;
  return result;
}

int scan_spell_name_etc(const char *line, char *spell_name, char *casting_time)
{
  int quotes_first = str_find(line, '"');
  if (quotes_first == -1)
    return 0;
  int quotes_second = str_find(line + quotes_first + 1, '"');
  if (quotes_second == -1)
    return 0;
  //printf("quotes_first = %d, quotes_second = %d\n", quotes_first, quotes_second);
  str_ncpy(spell_name, line + quotes_first + 1, quotes_second);
  int spaces = str_count_while(line + quotes_first + quotes_second + 2, ' ');
  //printf("spaces = %d\n", spaces);
  strcpy(casting_time, line + quotes_first + quotes_second + 2 + spaces);
  return 2;
}

int scan_spell_name_delete(const char *line, char *spell_name)
{
  int quotes_first = str_find(line, '"');
  if (quotes_first == -1)
    return 0;
  int quotes_second = str_find(line + quotes_first + 1, '"');
  if (quotes_second == -1)
    return 0;
  //printf("quotes_first = %d, quotes_second = %d\n", quotes_first, quotes_second);
  str_ncpy(spell_name, line + quotes_first + 1, quotes_second);
  //int spaces = str_count_while(line + quotes_first + quotes_second + 2, ' ');
  //printf("spaces = %d\n", spaces);
  return 2;
}


void test_F (void)
{
    Feitico **a = NULL;
    int n = 0;
    char comando_line[MAX_LINE_LENGTH];

    while (str_getline (comando_line) != EOF)
    {
        char comando[MAX_LINE_LENGTH];
        sscanf (comando_line, "%s", comando);
        if (strcmp (comando, "LOAD")==0)
        {
            char file_name[MAX_LINE_LENGTH];
            int z = sscanf(comando_line, "%*s%s", file_name);
            FILE *f = fopen (file_name, "r"); //abrir ficheiro para a leitura
            if (z != 1)
            {
                printf ("Invalid command arguments!\n");
                continue;
            }
            else if (f == NULL)
            {
                printf ("Invalid file or error opening file!\n");
                continue; // volta para o proximo passo do ciclo lendo o proximo comando
            }
            else 
            {
                if (a != 0)
                {
                    check_free(a, "ree_feiticos (a, n)");
                    free_feiticos (a, n);
                    a = NULL;
                }            
            a = read_feiticos_from (f, &n); 
            }
        fclose (f);
        printf ("%d spells successfully loaded.\n", n);
        }
        else if (strcmp (comando, "SAVE")==0)
        {
            char file_name[MAX_LINE_LENGTH];
            int z = sscanf(comando_line, "%*s%s", file_name);
            if (z != 1)
            {
                printf ("Invalid command arguments!\n");
                continue;
            }
            FILE *f = fopen (file_name, "w"); //abrir ficheiro para a escrita
            if (f == NULL)
            {
                printf ("Error opening or writing file!\n");
                continue; // volta para o proximo passo do ciclo lendo o proximo comando
            }
            write_feiticos_to (f, a, n); 
            fclose (f);
            printf ("%d spells successfully saved.\n", n);
        }
        else if (strcmp (comando, "UPDATE")==0)
        {
            char name[MAX_LINE_LENGTH]; 
            char new_casting_time[MAX_LINE_LENGTH];
            int z = scan_spell_name_etc (comando_line, name, new_casting_time);
            if (z != 2 || strlen (new_casting_time) == 0)
            {
                printf("Invalid command arguments!\n");
                continue;
            } 
            Feitico *f = find_feitico (a, n, name);
            if (f == NULL)
                printf ("No such spell exists!\n");
            else 
            {
                update_feitico (f, new_casting_time);
                println_feitico (f);
            }   
        }
        else if (strcmp (comando, "DELETE")== 0)
        {
            char name[MAX_LINE_LENGTH]; 
            int z = scan_spell_name_delete (comando_line, name);
            if (z != 0)
            {
                int n0 = n;
                n = delete_feitico (a, n, name);
                if (n == n0)
                    printf ("No such spell exists!\n");
                else
                    printf ("Spell deleted.\n");
            } 
            else 
            {
                printf("Invalid command arguments!\n");
                continue;
            }
        }
        else if (strcmp (comando, "FILTER")== 0)
        {
            char lvl[16];
            int min_level;
            int max_level;
            int z = sscanf (comando_line, "%*s%s%d%d", lvl, &min_level, &max_level);
            //int ana = strcmp (lvl, "lvl");
            //printf ("%d", ana);
            if (strcmp (lvl, "lvl") != 0)
            {
                printf ("Invalid command arguments!\n");
                continue;
            }
            if (z != 3)
            {
                printf ("Invalid command arguments!\n");
                continue;
            }
            Feitico *b[n];
            int m = filter_feiticos_lvl(a, b, n, min_level, max_level);
            if (m == 0)
                printf ("No Spells!\n");
            else 
                println_feiticos (b, m);
        }
        else if (strcmp (comando, "SHOW")== 0)
        {
            write_feiticos_to (stdout, a, n);
        }
        else
            printf ("Unknown command!\n");
    }
    if (n > 0)
        free_feiticos(a, n); // ******
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

void test_read_one_spell (void)
{
    Feitico *z = read_feitico_from(stdin);
    printf("ana\n");
    assert (z);
    println_feitico (z);
} 


void test_read_spells (void)
{
    int n = 0;
    Feitico **a = read_feiticos_from (stdin, &n);
    println_feiticos (a, n);
} 

#ifndef MOOSHAK_MAIN
int main(void)
{
    test_F();
    // test_is_valid ();
    //test_read_spells ();
    return 0;
}
#endif
