typedef struct no ListaLigada;
typedef struct casa Casa;
ListaLigada * criar_lista();

ListaLigada*  adicionar(ListaLigada* lista,Casa elemento);

Casa remover(ListaLigada* lista, Casa elemento);

ListaLigada* procurar(ListaLigada* lista,Casa elemento);