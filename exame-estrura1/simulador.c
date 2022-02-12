#include "simulador.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcoes_auxiliar.c"

struct lg
{
  char identificador[5];
  struct lg *proximo;
};

struct mosquito
{
  char identificador[5];
  int numeroDeMovimento;
  struct mosquito *proximo;
};

struct casa
{
  char identificador[5];
  Mosquito *mosquito;
  LG *ligacao;
  Casa *proximo;
};

struct regiao
{
  int numeroMovimento;
  int numeroCombate;
  int numeroReproducao;
  Casa *casa;
};

Regiao *inicialisarRegiao(int numeroMovimento, int numeroCombate, int numeroReproducao)
{
  Regiao *zona = (Regiao *)malloc(sizeof(Regiao));
  if (zona == NULL)
  {
    puts("Memoria invalida\n");
    exit(0);
  }
  zona->casa = NULL;
  zona->numeroMovimento = numeroMovimento;
  zona->numeroCombate = numeroCombate;
  zona->numeroReproducao = numeroReproducao;

  return zona;
}

Casa *inicialisarCasa(ID identificador)
{
  Casa *novaCasa = (Casa *)malloc(sizeof(Casa));
  if (novaCasa == NULL)
  {
    puts("Memoria invalida\n");
    exit(0);
  }
  strcpy(novaCasa->identificador, identificador);
  novaCasa->ligacao = NULL;
  novaCasa->mosquito = NULL;
  novaCasa->proximo = NULL;
  return novaCasa;
}

Mosquito *inicialisarMosquito(ID identificador)
{
  Mosquito *novoMosquito = (Mosquito *)malloc(sizeof(Mosquito));
  if (novoMosquito == NULL)
  {
    puts("Memoria invalida\n");
    exit(0);
  }
  strcpy(novoMosquito->identificador, identificador);
  novoMosquito->proximo = NULL;
  return novoMosquito;
}

LG *inicialisarLigacao(ID identificador)
{
  LG *novaLigacao = (LG *)malloc(sizeof(LG));
  if (novaLigacao == NULL)
  {
    puts("Memoria invalida\n");
    exit(0);
  }
  strcpy(novaLigacao->identificador, identificador);
  novaLigacao->proximo = NULL;
  return novaLigacao;
}
void adicionarCasa(Regiao *l, Casa *casa)
{
  Casa *aux = l->casa;
  if (aux == NULL)
  {
    aux = casa;
  }
  else
  {
    while (aux != NULL)
    {
      aux = aux->proximo;
    }
    aux = casa;
    aux->proximo = l->casa;
    l->casa = aux;
  }
  l->casa = aux;
}

Casa *procurarCasa(Regiao *l, ID identificador)
{
  Casa *aux = l->casa;
  while (aux != NULL && !(strcmp(aux->identificador, identificador) == 0))
  {
    aux = aux->proximo;
  }
  if (aux == NULL)
  {
    printf("Casa com o identificador %s nao encontrado", identificador);
    return NULL;
  }

  return aux;
}
int removerCasa(Regiao *l, ID identificador)
{

  Casa *ptr, *antes;
  if (l->casa == NULL)
  {
    return 0; // Lista vazia !!!
  }
  else
  { // Caso a lista nao esteja vazia
    ptr = l->casa;
    antes = l->casa;
    while (ptr != NULL)
    {
      if (strcmp(ptr->identificador, identificador) == 0) // achou !!
      {
        if (ptr == l->casa) // se esta removendo o primeiro da lista
        {
          l->casa = l->casa->proximo;
          removerLigacao(l, ptr); // Remove as ligacoes
          free(ptr);
          return 1; // removeu !!
        }
        else // esta removendo do meio da lista
        {
          antes->proximo = ptr->proximo; // Refaz o encadeamento
          removerLigacao(l, ptr);        // Remove as ligacoes
          free(ptr);                     // Libera a area do nodo
          return 1;                      // removeu !!
        }
      }
      else // continua procurando no prox. nodo
      {
        antes = ptr;
        ptr = ptr->proximo;
      }
    }
    return 0; // Nao achou !!!
  }
}

int adicionarMosquito(Regiao *l, ID identificadorDaCasa, Mosquito *mosquito)
{
  Casa *casa = procurarCasa(l, identificadorDaCasa);
  if (casa != NULL)
  {
    Mosquito *aux = casa->mosquito;
    if (aux == NULL)
    {
      aux = mosquito;
    }
    else
    {
      while (aux != NULL)
      {
        aux = aux->proximo;
      }
      aux = mosquito;
      aux->proximo = casa->mosquito;
      casa->mosquito = aux;
    }
    casa->mosquito = aux;
  }
}
int removerMosquito(Regiao *l, ID identificadorDaCasa, ID identificadorDoMosquito)
{
  Casa *casaAchada = procurarCasa(l, identificadorDaCasa);
  if (casaAchada != NULL)
  {
    Mosquito *ptr, *antes;
    ptr = casaAchada->mosquito;
    antes = casaAchada->mosquito;
    while (ptr != NULL)
    {
      if (strcmp(ptr->identificador, identificadorDoMosquito) == 0) // achou !!
      {
        if (ptr == casaAchada->mosquito) // se esta removendo o primeiro da lista
        {
          casaAchada->mosquito = casaAchada->mosquito->proximo;
          free(ptr);
          return 1; // removeu !!
        }
        else // esta removendo do meio da lista
        {
          antes->proximo = ptr->proximo; // Refaz o encadeamento
          free(ptr);                     // Libera a area do nodo
          return 1;                      // removeu !!
        }
      }
      else // continua procurando no prox. nodo
      {
        antes = ptr;
        ptr = ptr->proximo;
      }
    }
    return 0; // Nao achou !!!
  }
}

int temLigacao(Casa *casa1, Casa *casa2)
{
  LG *aux = casa1->ligacao;
  while (aux != NULL && !(strcmp(aux->identificador, casa2->identificador) == 0))
  {
    aux = aux->proximo;
  }
  if (aux == NULL)
  {
    return 0;
  }

  return 1;
}
void ligacaoAuxiliar(Casa *casa1, Casa *casa2)
{

  LG *aux = casa1->ligacao;
  LG *novaLigacao = inicialisarLigacao(casa2->identificador);
  if (aux == NULL)
  {
    aux = novaLigacao;
  }
  else
  {
    while (aux != NULL)
    {
      aux = aux->proximo;
    }
    aux = novaLigacao;
    aux->proximo = casa1->ligacao;
    casa1->ligacao = aux;
  }
  casa1->ligacao = aux;
}

void adicionarLigacao(Regiao *l, ID identificadorDeOrigem, ID identificadorDeDestino)
{
  Casa *casaOrigem = procurarCasa(l, identificadorDeOrigem);
  Casa *casaDestino = procurarCasa(l, identificadorDeDestino);
  if (casaOrigem != NULL && casaDestino != NULL)
  {

    if (!temLigacao(casaOrigem, casaDestino))
    {
      ligacaoAuxiliar(casaOrigem, casaDestino);
      ligacaoAuxiliar(casaDestino, casaOrigem);
    }
    else
    {
      puts("Ja existe ligacao entre as casas");
    }
  }
  else
  {
    puts("Nao foi possivel fazer a ligacao uma das casas nao encontradas");
  }
}

void removerLigacaoAuxiliar(Regiao *l, ID identificadorDaCasa, ID identificadorDaCasaARemover)
{
  Casa *casa = procurarCasa(l, identificadorDaCasa);
  LG *ptr, *antes;
  if (casa == NULL)
  {
    return;
  }
  else
  {
    ptr = casa->ligacao;
    antes = casa->ligacao;
    while (ptr != NULL)
    {
      if (strcmp(ptr->identificador, identificadorDaCasaARemover) == 0) // achou !!
      {
        if (ptr == casa->ligacao)
        {
          casa->ligacao = casa->ligacao->proximo;
          free(ptr);
          return; // removeu !!
        }
        else
        {
          antes->proximo = ptr->proximo;
          free(ptr);
          return; // removeu !!
        }
      }
      else
      {
        antes = ptr;
        ptr = ptr->proximo;
      }
    }
  }
}
void removerLigacao(Regiao *l, Casa *casa)
{
  LG *aux = casa->ligacao;
  while (aux != NULL)
  {
    removerLigacaoAuxiliar(l, aux->identificador, casa->identificador);
    aux = aux->proximo;
  }
}

int contarLigacoes(LG *l)
{
  int count = 0;
  LG *aux = l;
  while (aux != NULL)
  {
    count++;
    aux = aux->proximo;
  }
  return count;
}

LG *pegarUmaCasaDeFormaAliatoria(Casa *casa)
{
  int numeroDeLigacoes = contarLigacoes(casa->ligacao);
  int numeroEscochido = rand() % numeroDeLigacoes;
  LG *ligacao = casa->ligacao;
  int count = 0;
  for (count = 0; count < numeroEscochido; count++)
  {
    ligacao = ligacao->proximo;
  }
  return ligacao;
}

Casa *pegarUmaCasaDeFormaAliatoriaNoSimulador(Regiao *l)
{
  int numeroDeCasas = contarCasas(l->casa);
  int numeroEscochido = rand() % numeroDeCasas;
  Casa *casa = l->casa;
  int count = 0;
  for (count = 0; count < numeroEscochido; count++)
  {
    casa = casa->proximo;
  }
  return casa;
}

void movimentarMosquitosDeUmaCasa(Regiao *l, Casa *casa)
{
  Mosquito *mosquitos = casa->mosquito;
  while (mosquitos != NULL)
  {
    LG *casaComLigacao = pegarUmaCasaDeFormaAliatoria(casa);
    if (casaComLigacao == NULL)
    {
      return;
    }
    Mosquito *mosquitoAmovimentar = (Mosquito *)malloc(sizeof(Mosquito));
    if (mosquitoAmovimentar == NULL)
    {
      puts("Memoria invalida\n");
      exit(0);
    }
    if (mosquitos->numeroDeMovimento == l->numeroMovimento)
    {
      continue;
    }
    strcpy(mosquitoAmovimentar->identificador, mosquitos->identificador);
    mosquitoAmovimentar->numeroDeMovimento = mosquitos->numeroDeMovimento++;
    mosquitoAmovimentar->proximo = NULL;
    adicionarMosquito(l, casaComLigacao->identificador, mosquitoAmovimentar);
    removerMosquito(l, casa->identificador, mosquitos->identificador);
    mosquitos = mosquitos->proximo;
  }
}

void movimentarMosquitos(Regiao *l)
{
  Casa *casa = l->casa;
  while (casa != NULL)
  {
    movimentarMosquitosDeUmaCasa(l, casa);
    casa = casa->proximo;
  }
}

void reproduzirMosquitosDeUmaCasa(Regiao *l, Casa *casa)
{
  Mosquito *mosquitos = casa->mosquito;
  while (mosquitos != NULL)
  {
    if (mosquitos->numeroDeMovimento >= l->numeroReproducao)
    {
      char idMosquito[4];
      Mosquito *mosquito1 = inicialisarMosquito(rand_string(idMosquito, 4));
      adicionarMosquito(l, casa->identificador, mosquito1);
      Mosquito *mosquito2 = inicialisarMosquito(rand_string(idMosquito, 4));
      adicionarMosquito(l, casa->identificador, mosquito2);
    }
    mosquitos = mosquitos->proximo;
  }
}

void reproduzirMosquito(Regiao *l)
{
  Casa *casa = l->casa;
  while (casa != NULL)
  {
    reproduzirMosquitosDeUmaCasa(l, casa);
    casa = casa->proximo;
  }
}
int contarCasas(Casa *casa)
{
  int count = 0;
  Casa *aux = casa;
  while (aux != NULL)
  {
    count++;
    aux = aux->proximo;
  }
  return count;
}

void combaterMosquitos(Regiao* l){
   Casa* casas=l->casa;
   int totalDeCasas=contarCasas(casas);
   int numeroSelecionado=rand()%totalDeCasas;
   int i;
   for(i=0;i<numeroSelecionado;i++){
       casas=casas->proximo;
   }
   Mosquito* mosquitos=casas->mosquito;
   if(mosquitos==NULL){
     printf("Casa %s sorteada sem mosquitos para combater. Aplicacaao encerrada!",casas->identificador);
     exit(0);
   }
   while (mosquitos!=NULL)
   {
     if(mosquitos->numeroDeMovimento<l->numeroCombate)
       continue;
       Mosquito* mosquitoAremover=mosquitos;
       mosquitos=mosquitos->proximo;
      removerMosquito(l,casas->identificador,mosquitoAremover->identificador); 
   }
   
}

void imprimirMapa(Regiao* l){
  //ponteiro para struct que armazena data e hora  
  struct tm *data_hora_atual;     
  
  //variável do tipo time_t para armazenar o tempo em segundos  
  time_t segundos;
  
  //obtendo o tempo em segundos  
  time(&segundos);   
  
  //para converter de segundos para o tempo local  
  //utilizamos a função localtime  
  data_hora_atual = localtime(&segundos);  

   FILE *pont_arq;
   Casa* casas=l->casa;  
  
  //abrindo o mapa_do_simulador.txt em modo "leitura e escrita"
  pont_arq = fopen("mapa_do_simulador.txt", "w");
  fprintf(pont_arq,"Estado da simulação ");

  fprintf(pont_arq,"%d/", data_hora_atual->tm_mday);
  fprintf(pont_arq,"%d/",data_hora_atual->tm_mon+1); //mês
  fprintf(pont_arq,"%d",data_hora_atual->tm_year+1900); //ano

  fprintf(pont_arq," %d:",data_hora_atual->tm_hour);//hora   
  fprintf(pont_arq,"%d:",data_hora_atual->tm_min);//minuto
  fprintf(pont_arq,"%d :\n",data_hora_atual->tm_sec);//segundo  

  while (casas!=NULL)
  {
    imprimirLigacoes(pont_arq,casas);
    imprimirMosquitos(pont_arq,casas);
    casas=casas->proximo;
  }  
  //fechando o arquivo
  fclose(pont_arq);
}

void imprimirCasas( FILE *pont_arq,Regiao *l)
{
  Casa *aux = l->casa;
  if (l == NULL || aux == NULL)
  {
    fprintf(pont_arq,"Regiao sem casa!\n");
  }

  while (aux != NULL)
  {
    printf("%s ", aux->identificador);
    aux = aux->proximo;
  }

  puts("\n");
}
void imprimirLigacoes( FILE *pont_arq,Casa *l)
{
  fprintf(pont_arq,"\n");
  LG *aux = l->ligacao;
  if (l == NULL || aux == NULL)
  {
    fprintf(pont_arq,"Casa %s _____________\n", l->identificador);
  }
  
  while (aux != NULL)
  {
    fprintf(pont_arq,"Casa %s ____________ Casa %s\n",l->identificador, aux->identificador);
    aux = aux->proximo;
  }
}
void imprimirMosquitos( FILE *pont_arq,Casa *l)
{
  fprintf(pont_arq,"\n");
  Mosquito *aux = l->mosquito;
  if (l == NULL || aux == NULL)
  {
    fprintf(pont_arq,"Casa %s sem mosquito!\n", l->identificador);
  }

  while (aux != NULL)
  {
    fprintf(pont_arq,"Casa %s ______________ Mosquito %s \n",l->identificador, aux->identificador);
    aux = aux->proximo;
  }
}
