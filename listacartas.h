/*
TF - Entrega final do trabalho

Integrantes:
1. Gabriel Tetzner Menegueti (2022200525)
2. Adler Amorim de Sousa (2022201426)
3. Isaías C Altoé (2022201151)

Data: 15/12/2023
*/

// listacartas.h

// include
#include <stdio.h>

#ifndef CARTA_H
#define CARTA_H

// Tipos definidos da carta e da lista.

typedef struct _carta {
  char face[3];
  char naipe;
  int valor;
  char nome[30];
} tCarta;
#endif

typedef struct _lista {
  tCarta carta;
  void *prox;
} tNo;

// Função para criar a lista de cartas.
tNo *criaListaCartas();

// Função para criar um nó da lista de cartas.
tNo *CriaNoListaCartas(tCarta carta);

// Função para verificar se a lista está vazia ou não.
int listaVazia(tNo *lista);

// Função para inserir um nó novo em determinada posição da lista.
void insereNoPosListaCartas(tNo **lista, tNo *novoNo, int pos);

// Função que remove um nó na lista dada uma posição.
tNo *removeNaListaCartas(tNo **lista, int pos);

// Função que retorna um elemento da lista.
tCarta getElemListaCartas(tNo *lista);

// Função que reposiciona cartas na lista, dependendo da posição de origem e destino.
void reposicionaNaListaCartas(tNo **lista, int posInicial, int posFinal);

int tamanhoLista(tNo *lista);

// Função para liberar a lista de cartas.
void liberaListaCartas(tNo **lista);

// Função que imprime toda a lista.
void imprimeListaCartas(tNo *lista);