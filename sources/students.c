#include <stdio.h>
const int current_year = 2024;

typedef struct  {
    char name[80];
    int number;
    int birth_day;
    char email[32];
    int mobile;
} Student;

int age (Student s)
{
    int result = current_year - s.birth_day / 10000;
    return result;
}

int oldest (Student *a, int n)
{
    assert (n > 0);
    int z = a[0].birth_day;
    int result = 0;
    for (int i = 1; i < n; i++)
        if (a[i].birth_day < z)
        {
            z = a[i].birth_day;
            result = i;
        }
    return result;

}

void print_student (Student s)
{
    printf ("%s,%d,%d,%s,%d\n", s.name, s.number, s.birth_day, s.email, s.mobile);
}

void print_students (Student *a, int n)
{
    for (int i = 0; i < n, i++)
        print_student (a[i]);
}

int get_students (Student *a)
{
    int i = 0;
    char name;
    int number;
    int birth_day;
    char email;
    int mobile; 
    while (scanf ("%s%d%d%s%d", name, &number, &birth_day, email, &mobile)!= EOF)
    {
        strcpy (a[i].name, name); //copiar uma string 
        a[i].number = number;
        ...
        i++;
    }
}

