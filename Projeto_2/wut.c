#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

  int cont = 0;
  double valor = 0;

  for (cont = 0; cont < 18; cont++) {

    int i = 0, j = 0, p = 0;
    scanf("%d %d %d", &i, &j, &p);
    int calculo = i - j;

    if(calculo < 0) {
      calculo = calculo*(-1);
    }

    valor = valor + (double)(p/(calculo+1));

  }

  printf("TOP: %lf\n", valor);

  return 0;
}
