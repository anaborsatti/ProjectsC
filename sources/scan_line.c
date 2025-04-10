#include <stdio.h>
#include <string.h>

int main(void)
{
char *strings[100];
char buffer[100];
int n = 0;
//int read;
//este código tem um problema se o input começar com \n
while(scanf("%[^\n]%*c"
,buffer)!=EOF)
{
strings[n++] = strdup(buffer);
}
for(int i = 0; i < n; i++)
{
printf("%s\n"
,strings[i]);
}
return 0;
}