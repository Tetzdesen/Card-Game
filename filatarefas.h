/*
TF - Entrega final do trabalho

Integrantes:
1. Gabriel Tetzner Menegueti (2022200525)
2. Adler Amorim de Sousa (2022201426)
3. Isaías C Altoé (2022201151)

Data: 15/12/2023
*/

// filatarefas.h

// include

#include <stdio.h>

// Tipos definidos da tarefa e da fila.

typedef struct _tarefa{
  int TurnoAparecimento, Prazo, rPau, rEspada, rOuro, rCopas, premio;
} tTarefa;

typedef struct _noFila{
  tTarefa tarefa;
  void *prox;
} tNoFila;

typedef struct _fila{
  tNoFila *prim; 
  tNoFila *ult;
  int quantElementosFila;
} tFila;

// Função para criar a fila
tFila *criaFila();

// Função que cria um nó da fila
tNoFila *criaNoTarefaNaFila(tTarefa tarefa);

// Função que verifica se a fila está vazia ou não
int ehVaziaFila(tFila *fila);

// Função que retorna o tamanho da fila
int tamanhoFila(tFila *fila);

// Função para inserir uma tarefa (nó) na fila
void insereTarefaNaFila(tFila *fila, tNoFila *novoNo);

// Função que remove um nó da fila
tNoFila *removeNoFila(tFila *fila);

// Função que imprime o primeiro da fila
void imprimeNoFila(int prazoNovo, tNoFila *no);

// Função que libera a fila
void liberaFila(tFila *fila);