#include "./pilha.c"
#include <string.h>
typedef int bool;
#define true 1
#define false 0
const char sair[] = "x";
const char SAIR[] = "X";

void destruir3Pilhas(Pilha *p1, Pilha *p2, Pilha *p3); 
bool estaNoFormatoXCY(char *palavra);

int main()
{
    char palavra[50];
    puts("\n**************** Palavra no formato XCY ? Confira ********************\n");
    while (true)
    {
        printf("Insira uma palavra para verificar se esta no formato XCY ou (x) para sair:\n");
        scanf("%s", palavra);
        if (strcmp(palavra, sair) == 0 || strcmp(palavra, SAIR) == 0)
            break;
        bool resultado = estaNoFormatoXCY(palavra);
        if (resultado)
        {
            printf("yupiii! A palavra %s esta no formato XCY\n\n", palavra);
        }
        else
            printf("Upsss! A palavra %s nao esta no formato XCY\n\n", palavra);
    }
    return 0;
}

bool estaNoFormatoXCY(char *palavra)
{
    int i;
    bool jaAchouC = false;
    Pilha *X = inicializarPilha();
    Pilha *Y = inicializarPilha();
    Pilha *aux = inicializarPilha();
    //como o formato da palavra e XcY, no codigo abaixo acoloca-se o lado x na pilha X e o de y na pilha Y
    for (i = 0; i < strlen(palavra); i++)
    {
        if (palavra[i] == 'c' || palavra[i] == 'C')
        {
            jaAchouC = true;
            continue;
        }
        if (jaAchouC)
        {
            empilhar(Y, palavra[i]);
        }
        else
        {
            empilhar(X, palavra[i]);
        }
    }

    //Se nao encontrou a letra c pode retornar falso porque nao esta no formato XcY
    if (jaAchouC == false)
    {
        destruir3Pilhas(X,Y,aux);
        return false;
    }
    //Se a pilha X tem mais elementos que a pilha Y e vice-versa, podemos assumir que nao esta no formato XcY
    if (contar(X) != contar(Y))
    {
        destruir3Pilhas(X,Y,aux);
        return false;
    }
    //Como o formato XcY o Y e o inverso de X ou vice-versa bast inverter uma delas para serem iguais
    // e se forem igual e porque esta no formato XcY caso contrario nao esta, aqui escolhi inverter o lado X usando uma pilha auxiliar
    char v = desempilhar(X);
    while (v != '\0')
    {
        empilhar(aux, v);
        v = desempilhar(X);
    }

    // Verifica se o lado de X e diferente com o lado de Y se for retorna falso
    char x = desempilhar(aux), y = desempilhar(Y);
    while (x != '\0' && y != '\0')
    {
        if (x != y)
        {
           destruir3Pilhas(X,Y,aux);
            return false;
        }
        x = desempilhar(aux);
        y = desempilhar(Y);
    }
    // se chegou ate aque e porque esta no formato retorna verdadeiro
    destruir3Pilhas(X,Y,aux);
    return true;
}

void destruir3Pilhas(Pilha *p1, Pilha *p2, Pilha *p3)
{
    destruirPilha(p1);
    destruirPilha(p2);
    destruirPilha(p3);
}