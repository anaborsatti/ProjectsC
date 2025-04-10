#include <stdio.h>

int ints_get (int *a) //leitura array
{
    int result = 0;
    int x;
    while (scanf ("%d", &x) != EOF)
        a[result++] = x;
    return result;
}

/*int ints_sum (int *a, int n) //soma array
{
    int result = 0;
    for (int i = 0; i < n; i++)
        result += a[i];
    return result;
} */

/*void ints_println_basic (int *a, int n) //printa array com uma linha
{
    for (int i = 0; i < n; i++)
        printf (" %d", a[i]);
    printf ("\n");
}  */



/*int count (int *a, int n, int x) //faz a soma dos elementos do array
{
    int result = 0;
    int sum = 0;
    while (result < n && sum < x)
        sum += a[result++];
    return result; 
} */

int count (int *a, int n, int x) //faz a soma dos elementos do array
{
    int result = 0;
    int sum = 0;
    int tiket = 0;
    while (result < n)
    {
        sum += a[result++];
        if (sum >= x)
        {
            tiket += sum / x;
            sum = 0;

        }
    }
    return tiket; 
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