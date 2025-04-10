#include <stdio.h>
int max (int x, int y)
{
    return x <= y ? y : x;
}

int* vetor_multiplica (int *a, int n, int *b, int m)
{
    int result;
    int z = max(n, m);
    int out[z];
    for (int i = 0; i < z; i++)
    {
        result = a[i] * b [i];
        out[i] = result;
       if (n < m)
       {
            result = 1 * b[i];
            out[i]= result;
       }
       if (m < n)
       {
            result = a[i] * b[i];
            out [i] = result;
       }
       return out;
    }
}

int main ()
{
    int *a;
    int *b;
    int m;
    int numero;
    int n;
    scanf ("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
    {
       a[i] = scanf ("%d", &numero);
    }
    for (int i = 0; i < m; i++)
    {
       b[i] = scanf ("%d", &numero);
    }
    int *p = vetor_multiplica (a, n, b, m);
    for (int i = 0; i < m; i++)
    {
        printf ("%d", p[i]);
    }
}