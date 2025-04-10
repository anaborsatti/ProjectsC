#include <stdio.h>
#include <string.h>

typedef enum {
    Enchantment,
    Necromancy,
    Divination,
    Evocation,
    Abjuration,
    Transmutation,
    Illusion,
    Conjuration,
    Invalid = -1
} School;

char* school_names[]= {"Enchantment", "Necromancy", "Divination", "Evocation", "Abjuration", "Transmutation", "Illusion", "Conjuration"};

School string_2_school(char *s)
{
    for (int i = 0; i < 8; i++) // Limite do loop corrigido
        if (strcmp(school_names[i], s) == 0)
            return (School)i;
    return Invalid; 
}

void test_string_school(void)
{
    char a[100];
    printf("Digite uma escola de magia: ");
    scanf("%s", a);
    printf("%d\n", string_2_school(a));
}

int main()
{
   // test_F ();
   // test_school_string ();
   test_string_school(); // Ponto e vírgula adicionado
   return 0; // Adicionado retorno
}
