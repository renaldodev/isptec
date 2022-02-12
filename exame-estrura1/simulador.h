#include <stdio.h>
typedef char *ID;
typedef struct mosquito Mosquito;
typedef struct regiao Regiao;
typedef struct casa Casa;
typedef struct lg LG; //Representa a ligacao

Regiao *inicialisarRegiao();
Casa *inicialisarCasa(ID identificador);
Mosquito *inicialisarMosquito(ID identificador);
LG *inicialisarLigacao(ID identificador);
void destruirCasa(Casa *casa);
void adicionarCasa(Regiao *l, Casa *casa);
int removerCasa(Regiao *l, ID identificador);
Casa *procurarCasa(Regiao *l, ID identificador);
void imprimirCasas( FILE *pont_arq,Regiao *l);
void imprimirMosquitos( FILE *pont_arq,Casa *l);
void imprimirLigacoes( FILE *pont_arq,Casa *l);
int adicionarMosquito(Regiao *l, ID identificadorDaCasa, Mosquito *mosquito);
int removerMosquito(Regiao *l, ID identificadorDaCasa, ID identificadorDoMosquito);
int temLigacao(Casa *casa1, Casa *casa2);
void ligacaoAuxiliar(Casa *casa1, Casa *casa2);
void adicionarLigacao(Regiao *l, ID identificadorDeOrigem, ID identificadorDeDestino);
void removerLigacaoAuxiliar(Regiao *l, ID identificadorDaCasa, ID identificadorDaCasaARemover);
void removerLigacao(Regiao *l, Casa *casa);
void movimentarMosquitosDeUmaCasa(Regiao* l,Casa* casa);
void movimentarMosquitos(Regiao *l);
int contarCasas(Casa *casa);
void combaterMosquitos(Regiao* l);
void imprimirMapa(Regiao* l);
