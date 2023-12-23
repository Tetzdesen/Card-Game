/*
TF - Entrega final do trabalho

Integrantes:
1. Gabriel Tetzner Menegueti (2022200525)
2. Adler Amorim de Sousa (2022201426)
3. Isaías C Altoé (2022201151)

Data: 15/12/2023
*/

#include "pilhacartas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função para criar a pilha vazia
tPilha *criaPilha() {
  tPilha *pilha = malloc(sizeof(tPilha));
  pilha->topo = NULL;
  pilha->quantElemPilha = 0;

  return pilha;
}

// Função que cria nó de uma pilha
tNoPilha *criaNoPilha(tCarta carta) {
  tNoPilha *no = malloc(sizeof(tNoPilha));
  strcpy(no->carta.face, carta.face);
  no->carta.naipe = carta.naipe;
  no->carta.valor = carta.valor;
  strcpy(no->carta.nome, carta.nome);
  no->proximo = NULL;
  return no;
}

// Função que verifica se a pilha esta vazia
int ehVaziaPilha(tPilha *pilha) {
  if (pilha->topo == NULL)
    return 1;
  return 0;
}

// Função que retorna o tamanho da pilha
int tamanhoPilha(tPilha *pilha) { return pilha->quantElemPilha; }

// Função que coloca um elemento no topo da pilha
void push(tPilha *pilha, tNoPilha *novoNo) {
  if (ehVaziaPilha(pilha)) {
    pilha->topo = novoNo;
    pilha->quantElemPilha++;
  } else {
    novoNo->proximo = pilha->topo;
    pilha->topo = novoNo;
    pilha->quantElemPilha++;
  }
}

// Função que remove um elemento do topo da pilha
tNoPilha *pop(tPilha *pilha) {
  tNoPilha *aux;

  if (!ehVaziaPilha(pilha)) {
    aux = pilha->topo;
    pilha->topo = pilha->topo->proximo;
    aux->proximo = NULL;
    pilha->quantElemPilha--;
    return aux;
  }

  return NULL;
}
// Função que imprime o elemento do topo da pilha
void imprimeTopoPilha(tPilha *pilha) {
  if (!ehVaziaPilha(pilha)) {
    printf("| %2s-%1c | \n", pilha->topo->carta.face, pilha->topo->carta.naipe);
  }
  return;
}

// Função que libera pilha
void liberarPilha(tPilha *pilha) {
  tNoPilha *aux, *aux2;
  aux = pilha->topo;
  while (aux != NULL) {
    aux2 = aux->proximo;
    free(aux);
    aux = aux2;
    pilha->quantElemPilha--;
  }
  free(pilha);
}

// Função que retorna o elemento do topo da pilha
tNoPilha *acessaTopoPilha(tPilha *pilha) { return pilha->topo; }
