#include <stdio.h>

typedef int (*Number)(int, int);

int soma (int x, int y)
{
    return x + y;
}

int subtracao (int x, int y)
{
    return x - y;
}

int mult (int x, int y)
{
    return x * y;
}

Number number_selector (int selector)
{
    Number result;
    if (selector == 0)
        return result = soma;
    if (selector == 1)
        return result = subtracao;
    if (selector == 2)
        return result = mult;   
    return 0;
}


void teste_f ()
{
    //Number operation [3] = {soma, subtracao, multi}
    Number operation = NULL;
    int x;
    int y;
    int selector;
    scanf ("%d", &selector);
    operation = number_selector (selector);
    scanf ("%d%d", &x, &y);
    printf("O resultado é %d\n", operation(x, y));
    // printf("O resultado é %d\n", operation[selector](x, y));
}


int main ()
{
    teste_f ();
    return 0;
}