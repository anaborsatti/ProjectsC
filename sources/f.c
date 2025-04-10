#include <stdio.h>

int ints_get (int *a) //leitura array
{
    int result = 0;
    int x;
    while (scanf ("%d", &x) != EOF)
        a[result++] = x;
    return result;
}

int ints_sum (int *a, int n) //soma array
{
    int result = 0;
    for (int i = 0; i < n; i++)
        result += a[i];
    return result;
} 

void ints_println_basic (int *a, int n) //printa array com uma linha
{
    for (int i = 0; i < n; i++)
        printf (" %d", a[i]);
    printf ("\n");
}  



int count (int *a, int n, int x) 
{
    int result = 0;
    int sum = 0;
    while (result < n && sum < x)
        sum += a[result++];
    return result; 
} 

int tickets (int *a, int n, int x)
{
    int result;
    if (n == 0)
        result = 0;
    else 
    {
        int z = count (a, n, x);
        int y = ints_sum (a, z)/x;
        result = y + tickets (a + z, n - z, x); //a + z é o subarray de a que começa em z posições a frente de a
    }
    return result;
}

int tickets_alt (int *a, int n, int x)
{
    int result = 0;
    if (n > 0)
    {
        int z = count (a, n, x);
        int y = ints_sum (a, z)/x;
        result = y + tickets (a + z, n - z, x); //a + z é o subarray de a que começa em z posições a frente de a
    }
    return result;
}

int tickets_iter (int *a, int n, int x)
{
    int result = 0;
    int i = 0;
    while (i < n)
    {
        int z = count (a + i, n - i, x);
        int y = ints_sum (a, z)/x;
        result += y;
        i += z;
    }
    return result;
}





/*void test_read_write (void)
{
    int a[1000];
    int n = ints_get (a);
    ints_println_basic (a, n);
}  */

void test_count (void)
{
    int x; //leitura do valor de referencia
    scanf ("%d", &x);
    int a[1000];
    int n = ints_get (a);
    // ints_println_basic (a, n);
    int y = count (a, n, x);
    printf ("%d\n", y);
   // int z = ints_sum (a, y);
   // printf ("%d %d\n", z, z/x);
}




int main (void)
{
    // test_read_write ();
    test_count ();
    
    return 0;
}