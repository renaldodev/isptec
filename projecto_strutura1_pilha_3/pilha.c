#include "./pilha.h"
#include <stdio.h>
#include <stdlib.h>
struct no{
  Tipo valor;
  struct no* prox;
};

struct pilha{
  No* topo;
};

Pilha* inicializarPilha(){
   Pilha* p=(Pilha*)malloc(sizeof(Pilha));
   if(p==NULL){
       puts("Memoria invalida\n");
       exit(0);
   }
   p->topo=NULL;
   return p;
}

void empilhar(Pilha* p,Tipo valor){
   No *ptr=(No*)malloc(sizeof(No));
   if(ptr==NULL){
       puts("Memoria invalida\n");
       exit(0);
   }
   ptr->valor=valor;
   ptr->prox=p->topo;
   p->topo=ptr;
}

Tipo desempilhar(Pilha* p){
    No* ptr=p->topo;
    Tipo valor;
    if(ptr==NULL){
      //  puts("Pilha vazia!\n");
        return '\0';
    }
    p->topo=ptr->prox;
    ptr->prox=NULL;
    valor=ptr->valor;
    free(ptr);
    return valor;
}

void imprimirPilha(Pilha* p){
        No *ptr=p->topo;
        if(ptr==NULL){
          puts("Pilha vazia!\n");
          return;
        }
        while (ptr!=NULL)
        {   
            printf("%c ",ptr->valor);
            ptr=ptr->prox;
        }
        puts("\n");
}


int contar(Pilha* p){
   No* ptr=p->topo;
   int numeroDeElementos=0;
    if(ptr==NULL){
      //  puts("Pilha vazia!\n");
        return numeroDeElementos;
    }    
    
    while(ptr!=NULL){
        numeroDeElementos++;
        ptr=ptr->prox;
    }
    return numeroDeElementos;
}


void destruirPilha(Pilha* p){
    free(p);
}

