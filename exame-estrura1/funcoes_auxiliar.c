//! Funcao auxiliar para gerar um grupo de carecteres aleatorio para preecher os nomes
static char *rand_string(char *str,int size)
{

    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJK";
    if (size)
    {
        int n;
        for (n=0; n < size; n++)
        {
            int key = rand() % (int)(sizeof charset - 1);
            str[n] = charset[key];
        }
    }
    return str;
}