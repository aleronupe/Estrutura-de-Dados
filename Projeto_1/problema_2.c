#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define MAX 10

double *recebe_notas(double *notas, int max);
int conta_notas(double *apr_vector, int max, int *aprovados, int *reprovados);
int percent_aprov(int *aprovados, int *reprovados, double *pr_aprov, double *pr_repr);

int main(int argc, char *argv[]) {

  double NOTAS[10] = {}, *APR, pr_apr = 0.0, pr_repr = 0.0;
  int cont = 0, aprovados = 0, reprovados = 0;

  printf("Digite as 10 notas dos alunos:\n");

  for(cont = 0; cont < MAX; cont++) {
    scanf("%lf", &NOTAS[cont]);
  }

  APR = recebe_notas(NOTAS, MAX);

  conta_notas(APR, MAX, &aprovados, &reprovados);

  percent_aprov(&aprovados, &reprovados, &pr_apr, &pr_repr);

  return 0;
}

double *recebe_notas(double *notas, int max) {

  int i = 0;

  for(i = 0; i < max; i++) {
    if( *(notas+i) >= 6.0)
      *(notas+i) = 1.0;
    else
      *(notas+i) = 0.0;
  }

  return notas;
}

int conta_notas(double *apr, int max, int *aprovados, int *reprovados) {
  int i = 0;

  for(i = 0; i < max; i++) {
    if( *(apr + i) == 1.0)
      (*aprovados)++;
    else if( *(apr + i) == 0.0)
      (*reprovados)++;
  }
  printf("Quantidade de aprovados: %d\nQuantidade de reprovados: %d\n",(*aprovados), (*reprovados));
  return 0;
}

int percent_aprov(int *aprovados, int *reprovados, double *pr_aprov, double *pr_repr) {
  (*pr_aprov) = (double)(*aprovados) / ((*aprovados) + (*reprovados));
  (*pr_repr) = (double)(*reprovados) / ((*aprovados) + (*reprovados));
  printf("Percentual de aprovados: %.2lf%%\nPercentual de reprovados: %.2lf%%\n",(*pr_aprov) * 100, (*pr_repr) * 100);
  if (*(pr_aprov) > 0.5) {
    printf("Mais da metade da turma foi aprovada!\n");
    return 1;
  } else {
    printf("Menos da metade da turma foi aprovada!\n");
    return 0;
  }
}
