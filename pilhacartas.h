/*
TF - Entrega final do trabalho

Integrantes:
1. Gabriel Tetzner Menegueti (2022200525)
2. Adler Amorim de Sousa (2022201426)
3. Isaías C Altoé (2022201151)

Data: 15/12/2023
*/

#include <stdio.h>

#ifndef CARTA_H
#define CARTA_H

// Tipos definidos da carta e da pilha.
typedef struct _carta {
  char face[3];
  char naipe;
  int valor;
  char nome[30];
} tCarta;
#endif

typedef struct _noPilha{
  tCarta carta;
  void *proximo;
} tNoPilha;

typedef struct _tPilha{
   tNoPilha *topo;
   int quantElemPilha;
} tPilha;

// Função para criar a pilha vazia

tPilha *criaPilha();

// Função que cria no de uma pilha
tNoPilha *criaNoPilha(tCarta carta);

// Função que verifica se a pilha esta vazia
int ehVaziaPilha(tPilha *pilha);

// Função que retorna o tamanho da pilha
int tamanhoPilha(tPilha *pilha);

// Função que coloca um elemento no topo da pilha
void push(tPilha *pilha, tNoPilha *no);

// Função que remove um elemento do topo da pilha
tNoPilha *pop(tPilha *pilha);

// Função que imprime o elemento do topo da pilha
void imprimeTopoPilha(tPilha *pilha);

// Função que libera pilha
void liberarPilha(tPilha *pilha);

// Função que retorna o elemento do topo da pilha
tNoPilha *acessaTopoPilha(tPilha *pilha);

