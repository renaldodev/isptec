typedef char Tipo;
typedef struct no No;
typedef struct pilha Pilha;

Pilha* inicializarPilha();

void empilhar(Pilha* p,Tipo valor);
Tipo desempilhar(Pilha* p);
void imprimirPilha(Pilha* p);
int contar(Pilha* p);
void destruirPilha(Pilha* p);