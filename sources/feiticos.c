#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include <limits.h>

#include "feiticos.h"
int MAX_LINE_LENGTH = 1000;

int min (int x, int y)
{
    return x <= y ? x : y; //
}

int max (int x, int y)
{
    return x <= y ? y : x;
}

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

char *read_description (FILE *f)
{
  char *result = (char *) malloc(1);  //******
  *result = '\0';
  int n = 0;
  char line[MAX_LINE_LENGTH];
  while (fgets(line, MAX_LINE_LENGTH, f)) //de onde começa, maximo de caracteres, e de onde vai ser lido
  {
    if (strcmp(line, "\\EOD\n") == 0 || strcmp (line, "\\EOD") == 0 )
      break;  
    int start = n; // resultado de somar as linhas todas em uma string
    n += strlen(line); //nao conta o terminador
    result = (char *) realloc(result, n+1); //n + terminador
    strcpy(result+start, line); 
  }
  return result;
}

char *read_description_update(FILE *f)
{
  char *result = (char *) malloc(1);  
  *result = '\0';
  int n = 0;
  int count = 1;
  char line[MAX_LINE_LENGTH];
  while (fgets(line, MAX_LINE_LENGTH, f)) //de onde começa, maximo de caracteres, e de onde vai ser lido
  {
    if (strcmp(line, "\\EOD\n") == 0 || strcmp (line, "\\EOD") == 0 )
      break;  
    int start = n; // resultado de somar as linhas todas em uma string
    n += strlen(line); //nao conta o terminador
    result = (char *) realloc(result, n+1); //n + terminador
    strcpy(result+start, line); 
    if (*line == '*' && count == 1)
        break;
    count++;        
  }
  return result;
}

void show_feitico (Feitico *s)
{
    printf ("%s|%d|%s|%s|%d|%d|%d|%.16s\n", s->name, s->level, school_2_string (s->school), 
            s->casting_time, s->range, s->duration, s->concentration, s->description);
}

void show_feiticos (Feitico **a, int n)//a[i] = *(a+i), &a[i]= a+i
{
    for (int i= 0; i < n; i++) 
        show_feitico (a[i]);
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
    free(description);

    return result; 
}

Feitico** resize_feitico (Feitico **a, int capacity)
{
    return (Feitico**) realloc (a, capacity*sizeof(Feitico*));
}

Feitico** read_feiticos_from_super (FILE *f, int* out_size, int *new_capacity) //*feitcos[] == **feiticos
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
        {
            if (feof(f)) //confirmar se null é o fim do ficheiro ou invalido
                break;  
        }

    }
    *out_size = n;
    *new_capacity = capacity;
    if (*out_size == 0)
    {
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
        {
            if (feof(f)) //confirmar se null é o fim do ficheiro ou invalido
                break;  
        }

    }
    *out_size = n;
    if (*out_size == 0)
    {
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

void update_feitico (Feitico **a, int n)
{
    char line_name [MAX_LINE_LENGTH];
    char line_lvl [MAX_LINE_LENGTH];
    char line_school [MAX_LINE_LENGTH];
    char line_castingtime [MAX_LINE_LENGTH];
    char line_range [MAX_LINE_LENGTH];
    char line_duration [MAX_LINE_LENGTH];
    char line_concentration [MAX_LINE_LENGTH];
    char *line_description;
    str_readline (stdin, line_name);
    str_readline (stdin, line_lvl);
    str_readline (stdin, line_school);
    str_readline (stdin, line_castingtime);
    str_readline (stdin, line_range);
    str_readline (stdin, line_duration);
    str_readline (stdin, line_concentration);
    line_description = read_description_update (stdin);
    Feitico *f = find_feitico (a, n, line_name);
    if (f != NULL)
    {
        if (*line_lvl != '*') //primeiro caracter da string
            f->level = atoi (line_lvl);
        if (*line_school != '*') //primeiro caracter da string
            f->school = string_2_school (line_school);
        if (*line_castingtime != '*') //primeiro caracter da string
        {
            free (f->casting_time);
            f->casting_time= strdup (line_castingtime);
        }
        if (*line_range != '*') //primeiro caracter da string
            f->range = atoi (line_range);
        if (*line_duration != '*') //primeiro caracter da string
            f->duration = atoi (line_duration);
        if (*line_concentration != '*') //primeiro caracter da string
            f->concentration = atoi (line_concentration);
        if (*line_description != '*')
        {
            free (f->description);
            f->description = strdup (line_description);
        }
        free (line_description);
        printf ("Spell %s updated.\n", line_name);    
    }
    else 
        printf ("No such spell exists!\n");
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
    free (f->casting_time);
    free (f->description);
    free (f);
}

void free_feiticos(Feitico **f, int n)
{
    for (int i=0; i<n; i++)
        free_feitico (f[i]); //libertar cada feitiço
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

int scan_spell_name(const char *line, char *spell_name)
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

Feitico **reset_view (Feitico **a, int n, Feitico **b)
{
    if (b != NULL)
        free (b); //somente no array e nao nos feiticos, pois o a tambem aponta para os mesmos feiticos
    Feitico **result = (Feitico**) malloc (n*sizeof(Feitico*));
    for (int i = 0; i < n; i++)
        result[i] = a[i];
    return result;
}


int selector_lvl (Feitico *f) //funções do tipo int que recebem um Feitico * como argumento
{
    return f->level;
}

int selector_range (Feitico *f)
{
    return f->range;
}

int selector_duration (Feitico *f)
{
    return f->duration;
}

int filter_feiticos_between(Feitico *in[], Feitico *out[], int n, IntFeiticoSelector selector, int min, int max)
{
    int result = 0;
    for (int i = 0; i<n; i++)
    {
        int z = selector(in[i]);
        if (min <= z && z <= max)
            out[result++] = in[i];
    }
    return result; 
}

int filter_feiticos_between_by(Feitico *in[], Feitico *out[], int n, char* choice, int min, int max)
{
    int result = 0;
    if (strcmp (choice, "lvl")== 0)
        result = filter_feiticos_between (in, out, n, selector_lvl, min, max);
    else if (strcmp (choice, "ran")== 0)
        result = filter_feiticos_between (in, out, n, selector_range, min, max);
    else if (strcmp (choice, "dur")== 0)
        result = filter_feiticos_between (in, out, n, selector_duration, min, max);
    else
        assert (0); //nao pode acontecer 
    return result; 
}

IntFeiticoSelector choose_selector (char *choice)
{
    IntFeiticoSelector result;
    if (strcmp (choice, "lvl")== 0)
        result = selector_lvl;
    else if (strcmp (choice, "ran")== 0)
        result = selector_range;
    else if (strcmp (choice, "dur")== 0)
        result = selector_duration;
    else    
        result = NULL;
    return result;
}

int valid_choice (char *choice)
{
    return strcmp (choice, "lvl") == 0 || strcmp (choice, "ran") == 0 || strcmp (choice, "dur") == 0;
}

void load_feiticos(Feitico ***a, int *n, int *capacity, char *comando_line, Feitico ***b, int *m) 
{
    char file_name[MAX_LINE_LENGTH];
    int z = sscanf(comando_line, "%*s%s", file_name);
    FILE *f = fopen (file_name, "r"); //abrir ficheiro para a leitura
    if (z != 1)
    {
        printf ("Invalid command arguments!\n");
        return;
    }
    else if (f == NULL)
    {
        printf ("Invalid file or error opening file!\n");
        return; // volta para o proximo passo do ciclo lendo o proximo comrz ºando
    }
    else 
    {
        if (*a != NULL)
        {
            free_feiticos ((*a), *n);
            *a = NULL;
        }            
        *a = read_feiticos_from_super (f, n, capacity); 
        *b = reset_view (*a, *n, *b);
        *m = *n; 
    }
    fclose (f);
    printf ("%d spells successfully loaded.\n", *n);
}

void save_spells (Feitico **a, int n, char *comando_line, char* file_name)
{

    FILE *f = fopen (file_name, "w"); //abrir ficheiro para a escrita
    if (f == NULL)
    {
        printf ("Error opening or writing file!\n");
        return; // volta para o proximo passo do ciclo lendo o proximo comando
    }
    write_feiticos_to (f, a, n); 
    fclose (f);
    printf ("%d spells successfully saved.\n", n);
}

void delete_spells (char *comando_line, Feitico ***a, int *n, Feitico ***b, int *m)
{
    char name[MAX_LINE_LENGTH]; 
    int z = scan_spell_name (comando_line, name);
    if (z != 0)
    {
        int n0 = *n;
        *n = delete_feitico (*a, *n, name);
        if (*n == n0)
                printf ("No such spell exists!\n");
        else
        {
            *b = reset_view (*a, *n, *b);
            *m = *n;
            printf ("Spell deleted.\n");
        } 
    }
    else 
    {
        printf("Invalid command arguments!\n");
        return;
    }
}

void print_spells (Feitico **a, int n, char *comando_line)
{
    char name[MAX_LINE_LENGTH]; 
    int z = scan_spell_name(comando_line, name);
    if (z != 0)
    {
        Feitico *f = find_feitico (a, n, name);
        if (f == NULL)
            printf ("No such spell exists!\n");
        else 
            println_feitico (f);
    }
    else 
    {
        printf ("Invalid command arguments!\n");
        return;
    }
}


void copy_spells (Feitico ***a, int *n, Feitico ***b, int *m, char *comando_line)
{
            char name_one [MAX_LINE_LENGTH];
            char name_second [MAX_LINE_LENGTH];
            int args = sscanf (comando_line,"COPY \"%[^\"]\" \"%[^\"]\"", name_one, name_second);
            if (args != 2)
            {
                printf ("Invalid command arguments!\n");
                return;
            }   
            Feitico *f = find_feitico (*a, *n, name_one);
            if (f == NULL)
            {
                printf ("No such spell exists!\n");
                return;
            }
            Feitico *s = find_feitico (*a, *n, name_second);
            if (s != NULL)
            {
                printf ("Cannot create duplicate spell: %s!\n", name_second);
                return;
            }
            (*n)++;
            *a = resize_feitico (*a, *n);
            s = copy_feitico (f);
            strcpy (s->name, name_second);
            (*a)[(*n-1)] = s;
            *b = reset_view (*a, *n, *b);
            *m = *n;
}

void filter_spell (Feitico ***b, int *m, char *comando_line)
{
    char choice[16];
    int min;
    int max;
    int z = sscanf (comando_line, "%*s%s%d%d", choice, &min, &max);
    if (!valid_choice (choice) || z != 3)
    {
        printf ("Invalid command arguments!\n");
        return;
    }
    else 
    {
        *m = filter_feiticos_between(*b, *b, *m, choose_selector (choice), min, max);
        printf ("View filtered. %d spells selected.\n", *m);
    }
        
}

int cmp_by_name (const Feitico *x, const Feitico *y)
{
    return strcmp (x->name, y->name);
}

int cmp_by_name_ptr_asc (const Feitico **x, const Feitico **y)
{
    return strcmp ((*x)->name, (*y)->name);
}

int cmp_by_name_ptr_desc (const Feitico **x, const Feitico **y)
{
    return -(strcmp ((*x)->name, (*y)->name));
}

int cmp_by_lvl (const Feitico *x, const Feitico *y)
{
    return x->level - y->level;
}

int compare_feitico_lvl_asc (const Feitico **x, const Feitico **y)
{
    return (*x)->level - (*y)->level;
}

int compare_feitico_lvl_desc(const Feitico **x, const Feitico **y)
{
    return -((*x)->level - (*y)->level);
}

FeiticoComparer choose_comparer (char *choice, char *direcao)
{
    FeiticoComparer result;
    if (strcmp (choice, "nam")== 0 && strcmp (direcao, "ASC") == 0)
        result = cmp_by_name_ptr_asc;
    else if (strcmp (choice, "nam")== 0 && strcmp (direcao, "DES") == 0)
        result = cmp_by_name_ptr_desc;
    else if (strcmp (choice, "lvl")== 0 && strcmp (direcao, "ASC") == 0)
        result = compare_feitico_lvl_asc;
    else if (strcmp (choice, "lvl")== 0 && strcmp (direcao, "DES") == 0)
        result = compare_feitico_lvl_desc; 
    else    
        result = NULL;
    return result;
}

void order_spell (Feitico **a, int n, char *choice, char *direcao)
{
    qsort (a, n, sizeof(Feitico*), (Comparer)choose_comparer(choice, direcao)); //INSTAVEL, os empatados nao se sabe como vao ordenar
}

int is_valid_choice_direcao (char *choice, char *direcao)
{
    return (strcmp (choice, "nam") == 0 || strcmp (choice, "lvl") == 0) && 
       (strcmp (direcao, "ASC") == 0 || strcmp (direcao, "DES") == 0);
}

void runSMS(void) 
{
    Feitico **a = NULL;
    int n = 0;
    int capacity = 0;
    Feitico **b = NULL;
    int m = 0;
    char comando_line[MAX_LINE_LENGTH];

    while (str_getline (comando_line) != EOF)
    {
        char comando[MAX_LINE_LENGTH];
        sscanf (comando_line, "%s", comando);

        if (strcmp (comando, "LOAD") == 0)
            load_feiticos (&a, &n, &capacity, comando_line, &b, &m);

        else if (strcmp (comando, "SAVE")==0)
        {
            char file_name[MAX_LINE_LENGTH];
            int z = sscanf(comando_line, "%*s%s", file_name);
            if (z != 1)
            {
                printf ("Invalid command arguments!\n");
                continue;
            }
            save_spells (a, n, comando_line, file_name);
        }
            
        else if (strcmp (comando, "DELETE")== 0)
            delete_spells (comando_line, &a, &n, &b, &m);

        else if (strcmp (comando, "PRINT")== 0)
            print_spells (a, n, comando_line);
        
        else if (strcmp (comando, "ADD")== 0)
        {
            Feitico *z = read_feitico_from (stdin);
            if (z != NULL)
            {
                Feitico *e = find_feitico (a, n, z->name);
                if (e != NULL)
                {
                    printf ("Cannot create duplicate spell: %s!\n", z->name);
                    free (z);
                    continue;
                }  
                a = resize_feitico(a, n + 1);
                a[n++] = z;
                b = reset_view(a, n, b);
                m = n;
                printf("Spell successfully added.\n");
            }
        }
            
        else if (strcmp (comando, "UPDATE")==0)
        {
            update_feitico (a, n);
        } 
                 
        else if (strcmp (comando, "COPY")== 0)
            copy_spells (&a, &n, &b, &m, comando_line);

        else if (strcmp (comando, "FILTER")== 0)
            filter_spell (&b, &m, comando_line);

        else if (strcmp (comando, "RESET")== 0)
        {
            b = reset_view (a, n, b);
            m = n;
            printf ("View reset. %d spells selected.\n", m);
        }

        else if (strcmp (comando, "LIST")== 0)
        {
            int numero;
            if (sscanf (comando_line, "%*s%d", &numero) == 1)
                println_feiticos (b, min (m, numero));
            else 
                println_feiticos (b, m);
        }

        else if (strcmp (comando, "SAVEVIEW")== 0)
        {
            char file_name[MAX_LINE_LENGTH];
            int z = sscanf (comando_line, "%*s%s", file_name);
            if (z != 1)
            {
                printf ("Invalid command arguments!\n");
                continue;
            }
            save_spells (b, m, comando_line, file_name);
        }

        else if (strcmp (comando, "ORDER")== 0)
        {
            char choice [MAX_LINE_LENGTH];
            char direcao [MAX_LINE_LENGTH];
            int z = sscanf (comando_line, "%*s%s%s", choice, direcao);
            if (z != 2 || is_valid_choice_direcao (choice, direcao) == 0)
            {
                printf ("Invalid command arguments!\n");
                continue;
            }
            order_spell (b, m, choice, direcao);
            printf ("%d spells ordered.\n", m);
        }
        ////////////////////////////////////////////
        else if (strcmp (comando, "SHOW")== 0)
        {
            printf ("Memoria: \n");
            show_feiticos (a, n);
            printf ("Vista: \n");
            show_feiticos (b, m);
            printf ("/////\n");
        }
        ///////////////////////////////////////////
        else
            printf ("Unknown command!\n");
    }
    if (a != NULL)
        free_feiticos(a, n);
    if (b != NULL)
        free (b);       
} 

#ifndef MOOSHAK_MAIN
int main(void)
{
    runSMS();
    return 0;
}
#endif
