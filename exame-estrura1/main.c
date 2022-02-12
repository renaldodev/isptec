#include "simulador.c"
#define NUMERO_DA_SORT_CASA 100
#define NUMERO_DA_SORT_MOSQUITO 15
#define NUMERO_DA_SORT_LIGACAO 200
void menu();
int main()
{

  srand(time(NULL));
  FILE *ptr_arq;
  int totalDeMosquitosAntes = 0;
  ptr_arq = fopen("log.txt", "w");

  printf("Bem vindo ao simulador do moquitos da Aids\n\n");
  printf("Insere três números inteiros positivos, correspondentes ao número total de movimentos dos mosquitos durante a simulação, número mínimo de movimentos de todos os mosquitos para um agente municipal iniciar o combate e o número mínimo de movimentos por cada mosquito, para se permitir a reprodução: \n");
  int I, J, K;
  scanf("%d%d%d", &I, &J, &K);

  Regiao *zona = inicialisarRegiao(I, J, K);
  printf("Gerando e adiconando casas e mosquitos o simulador...\n");
  int numerosDeCasa = rand() % NUMERO_DA_SORT_CASA;
  int i;
  for (i = 0; i < numerosDeCasa; i++)
  {
    char idCasa[3], idMosquito[4];
    Casa *casa = inicialisarCasa(rand_string(idCasa, 3));
    adicionarCasa(zona, casa);
    time_t segundos;
    int numerosDeMosquito = rand() % NUMERO_DA_SORT_MOSQUITO;
    int j;
    for (j = 0; j < numerosDeMosquito; j++)
    {
      Mosquito *mosquito = inicialisarMosquito(rand_string(idMosquito, 4));
      totalDeMosquitosAntes++;
      adicionarMosquito(zona, casa->identificador, mosquito);
    }
  }

  fprintf(ptr_arq, "Total de mosquito ao iniciar simulacao: %d \n", totalDeMosquitosAntes);
  printf("Gerando ligacoes entre as casa...\n");

  int numerosDeLigacoes = rand() % NUMERO_DA_SORT_LIGACAO;
  int k;
  for (k = 0; k < numerosDeLigacoes; k++)
  {
    Casa *casa1 = pegarUmaCasaDeFormaAliatoriaNoSimulador(zona);
    Casa *casa2 = pegarUmaCasaDeFormaAliatoriaNoSimulador(zona);
    adicionarLigacao(zona, casa1->identificador, casa2->identificador);
  }
   fclose(ptr_arq);

  while (1)
  {
    int opcao;
    menu();
    scanf("%d", &opcao);
    switch (opcao)
    {
    case 2:
      movimentarMosquitos(zona);
      break;
    case 3:
      reproduzirMosquito(zona);
      break;  
    case 4:
     combaterMosquitos(zona);
     break;
    case 5:
     imprimirMapa(zona);
     break; 
    case 0:
     exit(0);
     break; 
    default:
       printf("Opcao invalida\n");
      break;
    }
  }
  return 0;
}

void menu()
{
  printf("Opcoes:\n2-Movimentar moquitos\n3-Reproduzir mosquitos\n4-Combater moquito\n5-Imprimir mapa\n0-Terminar simulacao\n");
}
