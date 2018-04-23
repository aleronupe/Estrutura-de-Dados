#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

  int randomNumb = 0, *list;
  /*seta a semente com a contagem em segundos do
  computador, garantindo uma sequência aleatória
  a cada compilação*/
  int seed = time(NULL);
  srand(seed);

  //aloca um vetor de 50 inteiros inicializados como 0
  list = (int *)calloc(50,sizeof(int));

  //seta 25 posições aleatórias como 1 (casos de aprendizagem)
  for(int i = 0; i < 25; i++) {
    randomNumb = (rand() % 50);

    if(*(list+randomNumb) == 1)
      i--;
    else if(*(list+randomNumb) == 0)
      *(list+randomNumb) = 1;
  }

  char txt[5] = ".txt";
  char asphTest[26][20]; //matriz com os casos de teste
  char asphLearn[26][20]; //matriz com os casos de aprendizagem
  int i = 0, test = 0, learn = 0;

  for(i = 0; i < 50; i++) {
    char asphalt[20] = "asphalt_";
    //cria o texto da string
    asphalt[8] = '0' + (i+1)/10;
    asphalt[9] = '0' + (i+1)%10;
    strcat(asphalt, txt);

    if(*(list+i) == 1) {
      strcpy(asphLearn[learn], asphalt);
      learn++;
    }
    if(*(list+i) == 0) {
      strcpy(asphTest[test], asphalt);
      test++;
    }
  }

  free(list);
  return 0;
}
