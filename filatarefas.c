/*
TF - Entrega final do trabalho

Integrantes:
1. Gabriel Tetzner Menegueti (2022200525)
2. Adler Amorim de Sousa (2022201426)
3. Isaías C Altoé (2022201151)

Data: 15/12/2023
*/

// filatarefas.c

// includes
#include "filatarefas.h"
#include <stdio.h>
#include <stdlib.h>

// Função para criar a fila
tFila *criaFila() {
  tFila *fila = malloc(sizeof(tFila));
  fila->prim = NULL;
  fila->ult = NULL;
  fila->quantElementosFila = 0;
  return fila;
}

// Função que cria um nó da fila
tNoFila *criaNoTarefaNaFila(tTarefa tarefa) {
  tNoFila *no = malloc(sizeof(tNoFila));
  no->tarefa.TurnoAparecimento = tarefa.TurnoAparecimento;
  no->tarefa.Prazo = tarefa.Prazo;
  no->tarefa.rPau = tarefa.rPau;
  no->tarefa.rEspada = tarefa.rEspada;
  no->tarefa.rOuro = tarefa.rOuro;
  no->tarefa.rCopas = tarefa.rCopas;
  no->tarefa.premio = tarefa.premio;
  no->prox = NULL;
  return no;
}

// Função que verifica se a fila está vazia ou não
int ehVaziaFila(tFila *fila) {
  if (fila->prim == NULL && fila->ult == NULL)
    return 1;
  return 0;
}

// Função que retorna o tamanho da fila
int tamanhoFila(tFila *fila) {

  if (fila != NULL)
    return fila->quantElementosFila;
  return 0;
}

// Função para inserir uma tarefa (nó) na fila
void insereTarefaNaFila(tFila *fila, tNoFila *novoNo) {

  if (ehVaziaFila(fila)) {
    fila->prim = novoNo;
    fila->ult = novoNo;
    fila->quantElementosFila++;
  } else {
    fila->ult->prox = novoNo;
    fila->ult = novoNo;
    fila->quantElementosFila++;
  }
}

// Função que remove um nó da fila
tNoFila *removeNoFila(tFila *fila) {
  tNoFila *aux = NULL;
  if (ehVaziaFila(fila)) {
    return NULL;
  } else if(tamanhoFila(fila) == 1){
    aux = fila->prim;
    fila->prim = NULL;
    fila->ult = NULL;
    aux->prox = NULL;
    fila->quantElementosFila--;
    return aux;
  }else {
    aux = fila->prim;
    fila->prim = fila->prim->prox;
    aux->prox = NULL;
    fila->quantElementosFila--;
    return aux;
  }
}

// Função que imprime o primeiro da fila
void imprimeNoFila(int prazoNovo, tNoFila *no) {
  if(no == NULL) printf("Nenhuma");
  else if (no != NULL) printf("%d (P: %d , E: %d , O: %d , C: %d);", prazoNovo,
     no->tarefa.rPau, no->tarefa.rEspada, no->tarefa.rOuro,
     no->tarefa.rCopas);
  
  return;
}

// Função que libera a fila
void liberaFila(tFila *fila) {
  if (ehVaziaFila(fila)) {
    printf("\n\nFila vazia\n\n");
  } else {
    tNoFila *aux = fila->prim;
    while (aux != NULL) {
     tNoFila *aux2 = aux->prox;
     free(aux);
     aux = aux2;
     fila->quantElementosFila--;
    }
    free(fila);
  }
}