/*
TF - Entrega final do trabalho

Integrantes:
1. Gabriel Tetzner Menegueti (2022200525)
2. Adler Amorim de Sousa (2022201426)
3. Isaías C Altoé (2022201151)

Data: 15/12/2023
*/

// main.c

// Includes

#include "filatarefas.h"
#include "listacartas.h"
#include "pilhacartas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Função que sorteia um número dependendo do tamanho da lista.
int sorteiaNumero(int tamanhoLista) { return (rand() % tamanhoLista) + 1; }

void calculaRecursos(tPilha *pilhaDescartes, int *pontosPaus, int *pontosCopas,
                     int *pontosEspadas, int *pontosOuros, int qtdDescartes,
                     char opcaoNaipe, int bonus) {
  tNoPilha *proximo = pilhaDescartes->topo;

  if (opcaoNaipe == 'C')
    *pontosCopas += bonus;
  if (opcaoNaipe == 'E')
    *pontosEspadas += bonus;
  if (opcaoNaipe == 'P')
    *pontosPaus += bonus;
  if (opcaoNaipe == 'O')
    *pontosOuros += bonus;

  for (int i = 1; i <= qtdDescartes; i++) {
    if (proximo->carta.naipe == 'C')
      *pontosCopas += proximo->carta.valor;
    if (proximo->carta.naipe == 'E')
      *pontosEspadas += proximo->carta.valor;
    if (proximo->carta.naipe == 'P')
      *pontosPaus += proximo->carta.valor;
    if (proximo->carta.naipe == 'O')
      *pontosOuros += proximo->carta.valor;
    proximo = proximo->proximo;
  }
}

// Função para calcular a pontuação de descarte.
int calculaPontuacao(tPilha *pilhaDescartes, int qtdDescarte) {

  tNoPilha *anterior, *proximo, *aux1, *aux2, *aux3;
  anterior = pilhaDescartes->topo;

  if (qtdDescarte == 1)
    return 0;
  else if (qtdDescarte == 2) {

    proximo = pilhaDescartes->topo->proximo;

    if (strcmp((anterior->carta).face, (proximo->carta).face) == 0)
      return 2;

    if ((anterior->carta).naipe == (proximo->carta).naipe)
      return 6;

    if (((anterior->carta).valor) == (proximo->carta).valor + 1)
      return 4;

  } else if (qtdDescarte == 3) {

    proximo = anterior->proximo;
    aux1 = proximo->proximo;

    if ((strcmp(anterior->carta.face, proximo->carta.face) == 0) &&
        (strcmp(proximo->carta.face, aux1->carta.face) == 0))
      return 5;

    if ((anterior->carta.naipe == proximo->carta.naipe) &&
        (proximo->carta.naipe == aux1->carta.naipe))
      return 9;

    if (((anterior->carta).valor) == (proximo->carta).valor + 1 &&
        ((proximo->carta).valor) == (aux1->carta).valor + 1)
      return 6;

  } else if (qtdDescarte == 4) {

    proximo = anterior->proximo;
    aux1 = proximo->proximo;
    aux2 = aux1->proximo;

    if ((strcmp(anterior->carta.face, proximo->carta.face) == 0) &&
        (strcmp(proximo->carta.face, aux1->carta.face) == 0) &&
        (strcmp(aux1->carta.face, aux2->carta.face) == 0))
      return 20;

    if ((anterior->carta.naipe == proximo->carta.naipe) &&
        (proximo->carta.naipe == aux1->carta.naipe) &&
        (aux1->carta.naipe == aux2->carta.naipe))
      return 12;

    if (((anterior->carta).valor) == (proximo->carta).valor + 1 &&
        ((proximo->carta).valor) == (aux1->carta).valor + 1 &&
        ((aux1->carta).valor) == (aux2->carta).valor + 1)
      return 8;

  } else if (qtdDescarte == 5) {

    proximo = anterior->proximo;
    aux1 = proximo->proximo;
    aux2 = aux1->proximo;
    aux3 = aux2->proximo;

    if ((anterior->carta.naipe == proximo->carta.naipe) &&
        (proximo->carta.naipe == aux1->carta.naipe) &&
        (aux1->carta.naipe == aux2->carta.naipe) &&
        (aux2->carta.naipe == aux3->carta.naipe))
      return 15;

    if (((anterior->carta).valor) == (proximo->carta).valor + 1 &&
        ((proximo->carta).valor) == (aux1->carta).valor + 1 &&
        ((aux1->carta).valor) == (aux2->carta).valor + 1 &&
        ((aux2->carta).valor) == (aux3->carta).valor + 1)
      return 10;
  }

  return 0;
}

// Main

int main(void) {
  // Declaração dos tipos de variaveis das tarefas

  srand(time(NULL));

  // Variáveis do tipo int

  int i, opcao1, opcao2, posOrigem, posDestino,
      pontosCopas = 0, pontosOuros = 0, pontosEspadas = 0, pontosPaus = 0,
      premEmb = 0, turnoAtual = 1, quantDescartes, contadorDescartes = 0,
      tamanhoMonte = 52, tamanhoMao = 5, contadorTurno = 1, contadorPrazos = 0,
      tamanhoEmb = 0, pontuacaoFinal = 0, Pt = 0, Ct = 0, Et = 0, Ot = 0,
      At = 0, Pn = 0, Cn = 0, En = 0, On = 0, rect = 0, recr = 0, recn = 0;

  char naipeOpcao;

  // Variável carta;
  tCarta carta;

  // Variável tarefa;
  tTarefa tarefa;

  // tNo Variáveis
  tNo *mao, *auxEmb, *auxLista, *noAux;

  // Fila de tarefas
  tFila *filaTarefas;

  // Pilha de cartas
  tPilha *monte, *descartes;

  // Declarando arquivo
  FILE *file, *file2;

  // Abrindo os arquivos para leitura
  file = fopen("baralho1.dat", "r");
  file2 = fopen("tarefas.dat", "r");

  // Tratamento para os erros de leitura de arquivo
  if (file == NULL) {
    printf("O arquivo não foi aberto para leitura, por causa de algum erro "
           "(pode ser o nome do arquivo). \n");
    return 0;
  }

  if (file2 == NULL) {
    printf("O arquivo não foi aberto para leitura, por causa de algum erro "
           "(pode ser o nome do arquivo). \n");
    return 0;
  }

  // Menu
  printf("\n MENU:\n\n 1 - INICIAR JOGO (SORTEAR 5 CARTAS)\n\n 2 - SAIR\n\n "
         "Digite a "
         "opção: ");
  scanf("%d", &opcao1);

  switch (opcao1) {

  case 1: // Inicia o jogo (cria as listas)

    // Cria as listas

    mao = criaListaCartas();

    auxEmb = criaListaCartas();

    // Cria as pilhas

    monte = criaPilha();

    descartes = criaPilha();

    // Cria as filas
    filaTarefas = criaFila();

    // EMBARALHAR AS 52 CARTAS

    for (i = 1; i <= 52; i++) {
      fscanf(file, "%s %c %d %[^\n]s", carta.face, &carta.naipe, &carta.valor,
             carta.nome);
      insereNoPosListaCartas(&auxEmb, CriaNoListaCartas(carta), i);
    }

    for (int i = 1; i <= 52; i++) {
      auxLista =
          removeNaListaCartas(&auxEmb, sorteiaNumero(tamanhoLista(auxEmb)));
      push(monte, criaNoPilha(auxLista->carta));
    }

    for (i = 1; i <= 5; i++) {
      insereNoPosListaCartas(&mao, CriaNoListaCartas(pop(monte)->carta), i);
      tamanhoMonte--;
    }

    printf("\n");

    // fecha arquivo
    fclose(file);

    // Inserir os arquivos de tarefas na fila
    for (int i = 0; i < 10; i++) {
      fscanf(file2, "%d %d %d %d %d %d %d", &tarefa.TurnoAparecimento,
             &tarefa.Prazo, &tarefa.rPau, &tarefa.rEspada, &tarefa.rOuro,
             &tarefa.rCopas, &tarefa.premio);
      insereTarefaNaFila(filaTarefas, criaNoTarefaNaFila(tarefa));
    }

    // Fechar arquivo de tarefas
    fclose(file2);

    printf("\n");

    printf(" Foram sorteadas %d cartas do seu monte.\n", 5);

    // Looping para reposicionamento/descarte de cartas

    do {

      // Quando a fila de tarefas estiver vazia, encerra o jogo

      if (ehVaziaFila(filaTarefas)) {
        printf("\n Acabou todas as tarefas, jogo encerrado. \n");

        recr = pontosPaus + pontosCopas + pontosEspadas + pontosOuros;

        pontuacaoFinal = (rect + (recr / 2)) - (recn);

        printf("\n Sua pontuação final é: %d pontos", pontuacaoFinal);

        liberarPilha(monte);
        liberarPilha(descartes);
        liberaListaCartas(&mao);
        liberaListaCartas(&auxEmb);
        liberaListaCartas(&auxLista);
        liberaListaCartas(&noAux);
        return 0;
      }

      // Menu do jogo
      printf("\n P: %d  -  E: %d  -  O: %d  -  C: %d    -    *: %d\n\n",
             pontosPaus, pontosEspadas, pontosOuros, pontosCopas, premEmb);

      printf(" Tarefas: ");
      if (!ehVaziaFila(filaTarefas)) {

        if (filaTarefas->prim->tarefa.TurnoAparecimento <= turnoAtual) {
          contadorPrazos = (filaTarefas->prim->tarefa.TurnoAparecimento +
                            filaTarefas->prim->tarefa.Prazo) -
                           turnoAtual;
          if (contadorPrazos == 0 &&
              filaTarefas->prim->tarefa.Prazo != turnoAtual) {

            tNoFila *noAuxFila = removeNoFila(filaTarefas);
            contadorPrazos = (filaTarefas->prim->tarefa.TurnoAparecimento +
                              filaTarefas->prim->tarefa.Prazo) -
                             turnoAtual;

            // Cálculo de pontuação de tarefa não cumprida
            Pn = noAuxFila->tarefa.rPau;
            Cn = noAuxFila->tarefa.rCopas;
            En = noAuxFila->tarefa.rEspada;
            On = noAuxFila->tarefa.rOuro;
            recn += Pn + Cn + En + On;
            imprimeNoFila(contadorPrazos, filaTarefas->prim);
          } else {
            imprimeNoFila(contadorPrazos, filaTarefas->prim);
          }

        } else {
          printf("Nenhuma tarefa por enquanto!");
        }
      } else {
        printf("Sem tarefas!!! ");
      }

      printf("\n\n\n");
      printf(" Monte (%2d)                                             "
             "Descarte (%2d)\n",
             tamanhoMonte, contadorDescartes);

      printf("\n      ");
      if (tamanhoMao != 0) {
        imprimeListaCartas(mao);
        printf("\n Mao  :");
        for (i = 1; i <= tamanhoMao; i++) {
          printf("   %-3d   ", i);
        }
        printf("\n");

      } else {
        printf("\n Mao :");
        imprimeListaCartas(mao);
      }

      printf("\n MENU: \n\n 1 - Reposicionar carta \n 2 - Descartar "
             "cartas \n 3 - Cumprir tarefa \n 4 − Reembaralhar tudo (∗:%d) \n "
             "5 - Finalizar turno \n 6 - Sair "
             "do jogo \n\n Digite sua opção: ",
             premEmb);

      scanf("%d", &opcao2);

      switch (opcao2) {

      // Reposicionamento de cartas
      case 1:

        printf("\n Digite a posição de origem na mão: ");
        scanf("%d", &posOrigem);

        printf("\n Digite a posição de destino na mão: ");
        scanf("%d", &posDestino);

        if ((posOrigem > 0 && posOrigem <= tamanhoMao) &&
            (posDestino > 0 && posDestino <= tamanhoMao))
          reposicionaNaListaCartas(&mao, posOrigem, posDestino);
        else
          printf("\n Você digitou uma posição que não existe, tente novamente. "
                 "\n");

        printf("\n");

        break;

      // Descarte de cartas
      case 2:
        printf("\n Digite a quantidade de cartas que você deseja descartar: ");
        scanf("%d", &quantDescartes);

        if ((quantDescartes > 0 && quantDescartes <= tamanhoMao)) {
          contadorDescartes += quantDescartes;
          for (i = 1; i <= quantDescartes; i++) {
            noAux = removeNaListaCartas(&mao, 1);
            push(descartes, criaNoPilha(noAux->carta));
            tamanhoMao--;
          }

          printf("\n A pontuação de bônus do seu descarte é: %d pontos\n\n",
                 calculaPontuacao(descartes, quantDescartes));
          if (quantDescartes > 1 && quantDescartes < 6 &&
              calculaPontuacao(descartes, quantDescartes) > 0) {

            do {
              printf(" \n Escolha o naipe do seu bônus (P - E - O - C): ");
              scanf(" %c", &naipeOpcao);

              if (naipeOpcao != 'P' && naipeOpcao != 'E' && naipeOpcao != 'O' &&
                  naipeOpcao != 'C')
                printf(
                    "\n Opção inválida, digite novamente o naipe do bônus.\n");
            } while (naipeOpcao != 'P' && naipeOpcao != 'E' &&
                     naipeOpcao != 'O' && naipeOpcao != 'C');
          }

          calculaRecursos(descartes, &pontosPaus, &pontosCopas, &pontosEspadas,
                          &pontosOuros, quantDescartes, naipeOpcao,
                          calculaPontuacao(descartes, quantDescartes));

        } else
          printf("\n Você digitou uma quantidade de cartas que não existe, "
                 "tente novamente. \n\n");
        break;

      // Cumprir tarefa
      case 3:
        if (tamanhoFila(filaTarefas) < 1)
          printf("Você já cumpriu com todas as tarefas!!! ");
        else {
          if (turnoAtual >= filaTarefas->prim->tarefa.TurnoAparecimento) {
            if (pontosPaus >= filaTarefas->prim->tarefa.rPau &&
                pontosEspadas >= filaTarefas->prim->tarefa.rEspada &&
                pontosOuros >= filaTarefas->prim->tarefa.rOuro &&
                pontosCopas >= filaTarefas->prim->tarefa.rCopas) {
              printf("\n Você cumpriu a tarefa!!! \n");

              pontosPaus -= filaTarefas->prim->tarefa.rPau;
              pontosEspadas -= filaTarefas->prim->tarefa.rEspada;
              pontosOuros -= filaTarefas->prim->tarefa.rOuro;
              pontosCopas -= filaTarefas->prim->tarefa.rCopas;

              // Cálculo turno de antecedência de cumprimento de tarefas
              At = (filaTarefas->prim->tarefa.TurnoAparecimento +
                    filaTarefas->prim->tarefa.Prazo) -
                   turnoAtual;

              // Cálculo de pontuação de tarefa cumprida
              Pt = filaTarefas->prim->tarefa.rPau;
              Et = filaTarefas->prim->tarefa.rEspada;
              Ot = filaTarefas->prim->tarefa.rOuro;
              Ct = filaTarefas->prim->tarefa.rCopas;

              rect += (Pt + Et + Ot + Ct) * At;

              premEmb += filaTarefas->prim->tarefa.premio;

              removeNoFila(filaTarefas);

            } else {
              printf("\n Você ainda não tem recursos suficientes para cumprir "
                     "com a "
                     "tarefa. \n");
            }
          }
        }

        break;

      // Reembaralhar turno
      case 4:
        // Se o Prêmio de embaralhamento for maior que 0, execute o código de
        // reembaralhamento
        if (premEmb > 0) {

          // Tirar cartas do monte.
          for (i = 1; i <= tamanhoMonte; i++) {
            insereNoPosListaCartas(&auxEmb,
                                   CriaNoListaCartas(pop(monte)->carta), i);
          }

          tamanhoMonte = tamanhoPilha(monte);

          // Passa as cartas da mão para a lista aux de embaralhamento, caso o
          // monte não complete a mão.

          for (i = tamanhoMonte + 1; i <= tamanhoMonte + tamanhoMao; i++) {
            auxLista = removeNaListaCartas(&mao, 1);
            insereNoPosListaCartas(&auxEmb, CriaNoListaCartas(auxLista->carta),
                                   i);
          }

          // Atualiza o tamanho da mão
          tamanhoMao = tamanhoLista(mao);

          // Remove as carta da pilha de descartes e coloca na lista auxiliar de
          // embaralhamento.
          for (i = (tamanhoMonte + tamanhoMao + 1);
               i <= (tamanhoMonte + tamanhoMao + contadorDescartes); i++) {
            insereNoPosListaCartas(&auxEmb,
                                   CriaNoListaCartas(pop(descartes)->carta), i);
          }

          // Atualiza o contador de descarte

          contadorDescartes = tamanhoPilha(descartes);

          for (int i = 1; i <= 52; i++) {
            auxLista = removeNaListaCartas(&auxEmb,
                                           sorteiaNumero(tamanhoLista(auxEmb)));
            push(monte, criaNoPilha(auxLista->carta));
            tamanhoMonte++;
          }

          // Insere na mão até chegar no limite (5)

          for (int i = tamanhoMao + 1; i <= 5; i++) {
            insereNoPosListaCartas(&mao, CriaNoListaCartas(pop(monte)->carta),
                                   i);
          }

          tamanhoMonte = tamanhoPilha(monte);
          tamanhoMao = tamanhoLista(mao);

          // Desconta do prêmio de embaralhemento que o jogador utilizou.
          premEmb--;
          printf("\n");
          printf(" Você reembaralhou todas as cartas. 5 novas cartas foram "
                 "sorteadas para sua mão. \n");
        } else {
          printf("\n\nVocê não tem prêmios de embaralhamento suficiente para "
                 "reembaralhar tudo. \n\n");
          // Caso o jogador não tenha prêmios de embaralhamento
        }
        break;

      // Finalizar turno
      case 5:

        turnoAtual++;

        if ((tamanhoPilha(monte) == 0) ||
            (tamanhoPilha(monte) + tamanhoLista(mao) < 5)) {

          // Caso ainda tenha cartas no monte que não completa a mão, completa a
          // mão parcialmente.
          for (i = tamanhoMao + 1; i <= tamanhoMonte + tamanhoMao; i++) {
            insereNoPosListaCartas(&mao, CriaNoListaCartas(pop(monte)->carta),
                                   i);
          }

          // Atualiza o tamanho da mão e do monte.
          tamanhoMao = tamanhoLista(mao);
          tamanhoMonte = tamanhoPilha(monte);

          // Junta todas as cartas da pilha de descarte na lista de
          // embaralhamento
          for (i = 1; i <= contadorDescartes; i++) {
            insereNoPosListaCartas(&auxEmb,
                                   CriaNoListaCartas(pop(descartes)->carta), i);
          }

          // Atualiza o contador de cartas descartadas
          contadorDescartes = tamanhoPilha(descartes);

          // Atualiza o tamanho da lista de embaralhamento
          tamanhoEmb = tamanhoLista(auxEmb);

          for (i = 1; i <= tamanhoEmb; i++) {
            auxLista = removeNaListaCartas(&auxEmb,
                                           sorteiaNumero(tamanhoLista(auxEmb)));
            push(monte, criaNoPilha(auxLista->carta));
            tamanhoMonte++;
          }

          // Atualiza o tamanho da lista de embaralhamento
          tamanhoEmb = tamanhoLista(auxEmb);

          printf("\n");
        }

        // Sortea novas 5 cartas

        for (int i = tamanhoMao + 1; i <= 5; i++) {
          insereNoPosListaCartas(&mao, CriaNoListaCartas(pop(monte)->carta), i);
        }

        // Atualiza o tamanho da mão e do monte.
        tamanhoMonte = tamanhoPilha(monte);
        tamanhoMao = tamanhoLista(mao);

        // Verifica se a tarefa foi cumprida;

        if (!ehVaziaFila(filaTarefas)) {
          if ((filaTarefas->prim->tarefa.TurnoAparecimento +
               filaTarefas->prim->tarefa.Prazo) <= turnoAtual) {
            tNoFila *noAuxFila = removeNoFila(filaTarefas);

            // Cálculo de pontuação de tarefa não cumprida
            Pn = noAuxFila->tarefa.rPau;
            Cn = noAuxFila->tarefa.rCopas;
            En = noAuxFila->tarefa.rEspada;
            On = noAuxFila->tarefa.rOuro;

            recn += Pn + Cn + En + On;
          }
        } else {
          printf("\n Sua fila de tarefas terminou!!! \n");
        }

        break;

      // Sair do jogo
      case 6:
        liberarPilha(monte);
        liberarPilha(descartes);
        liberaListaCartas(&mao);
        liberaListaCartas(&auxEmb);
        liberaListaCartas(&auxLista);
        liberaListaCartas(&noAux);
        liberaFila(filaTarefas);

        printf("\n Você encerrou o jogo (Monte e descartes liberadas). \n");
        printf("\n Mão liberada. \n");
        printf("\n Fila de tarefas liberada. \n");
        break;
      default:
        printf("\n Opção inválida, digite novamente.\n\n");
        break;
      }
    } while (opcao2 != 6);
    break;
  // Case que encerra o jogo, caso a pessoa decida não começar
  case 2:
    printf("\n Você encerrou o jogo. \n");
    break;
  default:
    printf("\n Opção inválida, reinicie o jogo.\n");
    break;
  }

  return 0;
}