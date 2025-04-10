#include <stdio.h>


char* str_find(char *s, char x)
{
    for (int i = 0; s[i] != '\0'; i++)
    if (s[i] == x)
    {
        return (s+i);
    }
    return NULL;
}

#ifndef MOOSHAK_MAIN
int main(void)
{
    return 0;
}
#endif