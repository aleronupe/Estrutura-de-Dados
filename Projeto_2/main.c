#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LIN 30
#define COL 60

void randomAsphalt(char *asphTest, char *asphLearn, int col);
void randomGrass(char *grassTest, char *grassLearn, int col);
void getMatrix(char *name, int *bigger, int *lines, int *columns);
void saveMatriz(char *name, int **matriz, int lines, int columns);



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[]) {


  char asphaltT[LIN][COL];//matriz para guardar os nomes dos arquivos de caso de teste de asfalto
  char asphaltL[LIN][COL];//matriz para guardar os nomes dos arquivos de caso de aprendizagem de asfalto
  char grassT[LIN][COL];//matriz para guardar os nomes dos arquivos de caso de teste de grama
  char grassL[LIN][COL];//matriz para guardar os nomes dos arquivos de caso de aprendizagem de grama

  randomAsphalt(&asphaltT[0][0], &asphaltL[0][0], COL);
  randomGrass(&grassT[0][0], &grassL[0][0], COL);


  int cont = 0, bigger = 0, lines = 0, columns = 0;


  for(cont = 0; cont < 25; cont++) { //---------begin for---------/

    printf("aqui: %s\n", asphaltT[cont]);

    getMatrix(asphaltT[cont], &bigger, &lines, &columns);
    printf("maior: %d\nlinhas: %d\ncolunas: %d\n\n", bigger, lines, columns);

    //Alocação dinâmica da matriz
    int **matriz;
    int i = 0;

    matriz = (int **) malloc(lines*sizeof(int *));
    for(i = 0; i < lines; i++) {
      *(matriz+i) = (int *) calloc(columns, columns*sizeof(int));
    }

    saveMatriz(asphaltT[cont], matriz, lines, columns);


    for(i = 0; i < lines; i++) {
      free(*(matriz+i));
    }
    free(matriz);

  } //----------end for----------/



  return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
    char asphalt[50] = "DataSet/asphalt/asphalt_";
    //cria o texto da string
    asphalt[24] = '0' + (i+1)/10;
    asphalt[25] = '0' + (i+1)%10;
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
    char grass[50] = "DataSet/grass/grass_";
    //cria o texto da string
    grass[20] = '0' + (i+1)/10;
    grass[21] = '0' + (i+1)%10;
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

void getMatrix(char *name, int *bigger, int *lines, int *columns) {

  printf("arquivo: %s\n", name);

  FILE *matriz;
  matriz = fopen(name, "r");

  if (matriz == NULL) {
    printf("Falha.\n");
    exit(1);
  }

  //declara os elementos necessários pra identificar linhas e colunas
  int numb = 0, auxLin = 0, auxCol = 0;
  char typo = '.';

  //lê o número de colunas (até o \n)
  while(typo != '\n') {
    fscanf(matriz, "%d", &numb);
    fscanf(matriz, "%c", &typo);
    auxCol++;
  }

  *columns = auxCol;

  //volta pro começo da matriz
  rewind(matriz);

  /*Lê o número de linhas, verificando se o elemento do tipo
  'char' encontrado é o fim do arquvi (EOF) ou se é um \n, que
  indica o fim de uma linha*/
  fscanf(matriz, "%d", &numb);
  //inicializa o menor número, para a função glcm
  int greatest = numb;
  while(fscanf(matriz, "%c", &typo) != EOF) {
    if(typo == '\n') {
      auxLin++;
    }
    fscanf(matriz, "%d", &numb);
    if(numb > greatest) {
      greatest = numb;
    }
  }

  *lines = auxLin;
  *bigger = greatest;

  rewind(matriz);
  fclose(matriz);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void saveMatriz(char *name, int **matriz, int lines, int columns) {

  FILE *archive;
  archive = fopen(name, "r");

  int i = 0, j = 0, numb = 0;
  char typo = '.';

  /*Aqui utiliza-se a notação de ponteiro para a alocação
  dos elementos da matriz*/
  for(i = 0; i < lines; i++) {
    for(j = 0; j < columns; j++) {

      fscanf(archive, "%d", &numb);
      fscanf(archive, "%c", &typo);

      *(*(matriz + j) + i) = numb;
    }
  }

  fclose(archive);

/*  for(i = 0; i < 5; i++) {
    printf("%3d ", **(matriz+i));
  }
  printf("\n");
  for(i = 0; i < 5; i++) {
    printf("%3d ", *(*(matriz+i) + 500));
  }
  printf("\n");
  for(i = 0; i < 5; i++) {
    printf("%3d ", *(*(matriz+i) + 1024));
  }
  printf("\n\n"); */
}
