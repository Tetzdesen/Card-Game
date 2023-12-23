/*
TF - Entrega final do trabalho

Integrantes:
1. Gabriel Tetzner Menegueti (2022200525)
2. Adler Amorim de Sousa (2022201426)
3. Isaías C Altoé (2022201151)

Data: 15/12/2023
*/

// listacartas.c

// Includes
#include "listacartas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Função para criar a lista de cartas.
tNo *criaListaCartas() {
  tNo *lista = NULL;
  return lista;
}

// Função para criar um nó da lista de cartas.
tNo *CriaNoListaCartas(tCarta carta) {

  tNo *novo = malloc(sizeof(tNo));
  strcpy(novo->carta.face, carta.face);
  novo->carta.naipe = carta.naipe;
  novo->carta.valor = carta.valor;
  strcpy(novo->carta.nome, carta.face);
  novo->prox = NULL;
  
  return novo;
}

// Função para verificar se a lista está vazia ou não.
int listaVazia(tNo *lista) {
  if (lista == NULL)
    return 1;
  return 0;
}

// Função para inserir um nó novo em determinada posição da lista.
void insereNoPosListaCartas(tNo **lista, tNo *novoNo, int pos) {
  int i = 1;
  tNo *novo, **proximo;
  proximo = lista;
  while (i < pos && (*proximo) != NULL) {
    proximo = (tNo **)&((*proximo)->prox);
    i++;
  }
  novo = novoNo;
  novo->prox = (*proximo);
  (*proximo) = novo;
}

// Função que remove um nó na lista dada uma posição.
tNo *removeNaListaCartas(tNo **lista, int pos) {
  tNo *proximo, *anterior;
  int i;
  proximo = *lista;
  if (pos == 1) {
    (*lista) = proximo->prox;
    proximo->prox = NULL;
    return proximo;
  } else {
    for (i = 1; i < pos - 1; i++)
      proximo = proximo->prox;
    anterior = proximo->prox;
    proximo->prox = anterior->prox;
    anterior->prox = NULL;
    return anterior;
  }
}

// Função que retorna um elemento da lista.
tCarta getElemListaCartas(tNo *lista) { return lista->carta; }

// Função que reposiciona cartas na lista, dependendo da posição de origem e
// destino.
void reposicionaNaListaCartas(tNo **lista, int posInicial, int posFinal) {
    insereNoPosListaCartas(lista, removeNaListaCartas(lista, posInicial), posFinal);
}

int tamanhoLista(tNo *lista){
  int tamanho = 0;
  tNo *aux = lista;
  while(!listaVazia(aux)){
    aux = aux->prox;
    tamanho++;
  }
  return tamanho;
}

// Função para liberar a lista de cartas.
void liberaListaCartas(tNo **lista) {
  tNo *aux;
  while (!listaVazia(*lista)) {
    aux = (*lista)->prox;
    free(*lista);
    *lista = aux;
  }
}

// Função que imprime toda a lista.
void imprimeListaCartas(tNo *lista) {
  tNo *proximo = lista;
  if (listaVazia(proximo)) {
    printf(" Vazia");
  }
  int i = 0;
  while (!listaVazia(proximo)) {
    printf("| %2s-%1c | ", proximo->carta.face, proximo->carta.naipe);
    proximo = proximo->prox;
  }
  printf("\n");
}