#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LIN 26
#define COL 20

void randomAsphalt(char *asphTest, char *asphLearn, int col);
void randomGrass(char *grassTest, char *grassLearn, int col);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[]) {


  char asphaltT[LIN][COL];//matriz para guardar os nomes dos arquivos de caso de teste de asfalto
  char asphaltL[LIN][COL];//matriz para guardar os nomes dos arquivos de caso de aprendizagem de asfalto
  char grassT[LIN][COL];//matriz para guardar os nomes dos arquivos de caso de teste de grama
  char grassL[LIN][COL];//matriz para guardar os nomes dos arquivos de caso de aprendizagem de grama

  randomAsphalt(&asphaltT[0][0], &asphaltL[0][0], COL);
  randomGrass(&grassT[0][0], &grassL[0][0], COL);




  return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

void randomAsphalt(char *asphTest, char *asphLearn, int col) {

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
  int i = 0, test = 0, learn = 0;

  for(i = 0; i < 50; i++) {
    char asphalt[20] = "asphalt_";
    //cria o texto da string
    asphalt[8] = '0' + (i+1)/10;
    asphalt[9] = '0' + (i+1)%10;
    strcat(asphalt, txt);

    if(*(list+i) == 1) {
      strcpy( asphLearn+(learn*col), asphalt);
      learn++;
    }
    if(*(list+i) == 0) {
      strcpy( asphTest+(test*col), asphalt);
      test++;
    }
  }

  free(list);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void randomGrass(char *grassTest, char *grassLearn, int col) {

  int randomNumb = 0, *list;
  /*seta a semente com a contagem em segundos do
  computador, garantindo uma sequência aleatória
  a cada compilação*/
  int seed = time(NULL);
  srand(seed + 2);

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
  int i = 0, test = 0, learn = 0;

  for(i = 0; i < 50; i++) {
    char grass[20] = "grass_";
    //cria o texto da string
    grass[6] = '0' + (i+1)/10;
    grass[7] = '0' + (i+1)%10;
    strcat(grass, txt);

    if(*(list+i) == 1) {
      strcpy( grassLearn+(learn*col), grass);
      learn++;
    }
    if(*(list+i) == 0) {
      strcpy( grassTest+(test*col), grass);
      test++;
    }
  }

  free(list);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
