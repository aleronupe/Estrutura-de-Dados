#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define MAX 10

int fneuronio (double *entrada, double *pesos, double T, int max, int *comparador);

int main (int argc, char *argv[]) {

  double ENTRADAS[MAX] = {}, PESOS[MAX] = {}, T = 0;
  int cont = 0, comparador = -1;

  printf("Insira os 10 valores de entrada:\n");
  for (cont = 0; cont < MAX; cont++) {
    scanf("%lf", &ENTRADAS[cont]);
  }

  printf("Insira os 10 valores de peso:\n");
  for (cont = 0; cont < MAX; cont++) {
    scanf("%lf", &PESOS[cont]);
  }

  printf("Insira o valor do limiar T:\n");
  scanf("%lf", &T);

  fneuronio(ENTRADAS, PESOS, T, MAX, &comparador);

  if(comparador == 1)
    printf("Neurônio ativado!\n");
  else if (comparador == 0)
    printf("Neurônio inibido!\n");


  return 0;
}

int fneuronio (double *entrada, double *pesos, double T, int max, int *comparador) {

  double SOMAP = 0;
  int i = 0;

  for (i = 0; i < max; i++) {
    SOMAP += ( *(entrada + i) )*( *(pesos + i) );
  }

  if(SOMAP > T)
    *comparador = 1;
  else
    *comparador = 0;

  return 0;
}
