#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define LIN 30
#define COL 60

void randomAsphalt(char *asphTest, char *asphLearn, int col);
void randomGrass(char *grassTest, char *grassLearn, int col);
void getMatrix(char *name, int *bigger, int *lines, int *columns);
void saveMatriz(char *name, int **matriz, int lines, int columns);
void build_bin_vector(int *bin, int **mat, int lin, int col);
int rotate_bin(int *bin);
void calculate_glcm(int **mat, int lin, int col, int bigger, int somLin, int somCol);



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[]) {


  char asphaltT[LIN][COL];//matriz para guardar os nomes dos arquivos de caso de teste de asfalto
  char asphaltL[LIN][COL];//matriz para guardar os nomes dos arquivos de caso de aprendizagem de asfalto
  char grassT[LIN][COL];//matriz para guardar os nomes dos arquivos de caso de teste de grama
  char grassL[LIN][COL];//matriz para guardar os nomes dos arquivos de caso de aprendizagem de grama

  randomAsphalt(&asphaltT[0][0], &asphaltL[0][0], COL);
  randomGrass(&grassT[0][0], &grassL[0][0], COL);


  int cont = 0, bigger = 0, lines = 0, columns = 0;
  double *compAsphalt, *compGrass, try = 0.0;

  compAsphalt = (double *) calloc(536, 536*sizeof(double));
  compGrass = (double *) calloc(536, 536*sizeof(double));

//Aprendizado dos elementos de Asfalto
  for(cont = 0; cont < 25; cont++) { //---------begin for---------/

    //printf("aqui: %s\n", asphaltT[cont]);

    getMatrix(asphaltL[cont], &bigger, &lines, &columns);
    double *thisAsphalt;
    thisAsphalt = (double *) calloc(536, 536*sizeof(double));
    //printf("maior: %d\nlinhas: %d\ncolunas: %d\n\n", bigger, lines, columns);

    //Alocação dinâmica da matriz
    int **matriz;
    int i = 0, j = 0;
    matriz = (int **) malloc(lines*sizeof(int *));
    for(i = 0; i < lines; i++) {
      *(matriz+i) = (int *) calloc(columns, columns*sizeof(int));
    }

    //chama função que salva a matriz na memória
    saveMatriz(asphaltL[cont], matriz, lines, columns);
    //--CÁLCULO DO ILBP--//
    /*conjunto de fors responsáveis por considerar somente os elementos do meio
    da matriz, desconsiderando suas bordas para efeito de cálculo do ILBP*/
    for(i = 1; i < lines - 1; i++) {
      for(j = 1; j < columns - 1; j++) {
        int *bin;
        bin = (int *) calloc(9, 9*sizeof(int));
        build_bin_vector(bin, matriz, i, j);
        int menor = rotate_bin(bin);
        *(thisAsphalt + menor) = *(thisAsphalt + menor) + 1;
        free(bin);
      }
    }

    //--CÁLCULO DO GLCM--//
    calculate_glcm(matriz, lines, columns, bigger, -1, -1); //[LIN - 1][COL - 1]
    calculate_glcm(matriz, lines, columns, bigger, -1,  0); //[LIN - 1][COL    ]
    calculate_glcm(matriz, lines, columns, bigger, -1,  1); //[LIN - 1][COL + 1]
    calculate_glcm(matriz, lines, columns, bigger,  0, -1); //[LIN    ][COL - 1]
    calculate_glcm(matriz, lines, columns, bigger,  0,  1); //[LIN    ][COL + 1]
    calculate_glcm(matriz, lines, columns, bigger,  1, -1); //[LIN + 1][COL - 1]
    calculate_glcm(matriz, lines, columns, bigger,  1,  0); //[LIN + 1][COL    ]
    calculate_glcm(matriz, lines, columns, bigger,  1,  1); //[LIN + 1][COL + 1]
    printf("\n");

  /*  if(cont == 0 || cont == 24) {
      double somadora = 0;
      int low = 0;
      for(low = 0; low < 512; low++) {
        printf("%d: %3lf\n", low, *(thisAsphalt + low));
        if(*(thisAsphalt + low) > 0.0) {
          somadora = somadora + *(thisAsphalt + low);
        }
      }

      printf("\nsomadora: %3lf\n", somadora);
    }*/




    for(i = 0; i < lines; i++) {
      free(*(matriz+i));
    }
    free(matriz);
    free(thisAsphalt);

  } //----------end for----------/




  free(compGrass);
  free(compAsphalt);

  return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

      *(*(matriz + i) + j) = numb;
    }
  }

  fclose(archive);

  /*for(i = 0; i < 5; i++) {
    printf("%3d ", *(*(matriz)+ i));
  }
  printf("\n");
  for(i = 0; i < 5; i++) {
    printf("%3d ", *(*(matriz+500) + i));
  }
  printf("\n");
  for(i = 0; i < 5; i++) {
    printf("%3d ", *(*(matriz+1024) + i));
  }
  printf("\n\n");*/

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void build_bin_vector(int *bin, int **mat, int lin, int col) {
  // Declaração de variáveis locais.
  double soma = 0, media = 0;
  int i = 0, j = 0, bin_count = 0;


  // Calcula a soma de todos os elementos da submatriz[3][3].
  for(i = lin -1; i <= lin + 1; i++) {
    for(j = col - 1; j <= col + 1; j++) {
      soma += *(*(mat+i)+j);
    }
  }

  // Calcula a média da submatriz [3][3].
  media = soma/9;

  /* Verifica cada elemento da submatriz se é maior ou igual a média,
   preenche com 1 onde é maior e com 0 onde é menor em uma matriz,
   passando os elementos da matriz criada para o vetor bin por linha.*/
  for(i = lin -1; i <= lin + 1; i++) {
    for(j = col - 1; j <= col + 1; j++) {

      if( *(*(mat+i)+j) < media ) {
        *(bin + bin_count) = 0;
        bin_count++;
      }
      else if( *(*(mat+i)+j) >= media ) {
        *(bin + bin_count) = 1;
        bin_count++;
      }
    }
  }

  /*if(lin < 3 && col > 1021) {
    for(i = lin -1; i <= lin + 1; i++) {
      for(j = col - 1; j <= col + 1; j++) {
        printf("%3d ", *(*(mat+i)+j));
      }
      printf("\n");
    }
    printf("\n");
    printf("soma: %lf\n", soma);
    printf("media:%lf\n", media);
    printf("vetor: ");
    for(int k = 0; k < 9; k++) {
      printf("%d", *(bin + k));
    }
    printf("\n");

  } */
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int rotate_bin(int *bin) {

    // Declaração de variáveis locais.
    int decimal = 0, i = 0, cont = 0, menor = 515, aux = 0;

    for (cont = 0; cont < 9; cont++) {

      //////printf("vetor: ");

      // Calcula o decimal.
      decimal = 0;
      for (i = 0; i < 9; i++) {
        ///////printf("%d", *(bin + i));

        if (*(bin + i) == 1) {
          decimal += pow(2, (8 - i));
        }

      }

      if(decimal < menor) {
        menor = decimal;
      }
      /////printf(" dec: %d\n", decimal);

      // Rotaciona o vetor em 1 bit.
      aux = *(bin + 8);
      for(i = 8; i > 0; i--) {
        *(bin + i) = *(bin + (i - 1));
      }
      *bin = aux;

    }

    /////// printf("menor: %d\n\n", menor);
    // Retorna o menor elemento.
    return menor;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void calculate_glcm(int **mat, int lin, int col, int bigger, int somLin, int somCol) {

  double **auxMat;
  int i = 0, j = 0;

  auxMat = (double **) malloc(bigger*sizeof(double *));
  for(i = 0; i < bigger; i++) {
    *(auxMat + i) = (double *) calloc(bigger, bigger*sizeof(double));
  }


  int auxi = 0, auxj = 0, auxLin = lin, auxCol = col;
  //verifica se a o elemento está na linha anterior ou posterior
  if(somLin == -1) {
    auxi = 1;
  }
  else if(somLin == 1) {
    auxLin--;
  }

  //verifica se o elemento está na coluna anterior ou posterior
  if(somCol == -1) {
    auxj = 1;
  }
  else if(somCol == 1) {
    auxCol--;
  }


  for(i = auxi; i < auxLin; i++) {
    for(j = auxj ; j < auxCol ; j++) {

      int owner = *(*(mat + i) + j);
      int neighbour = *(*( mat + (i + somLin) ) + (j + somCol));

      *(*(auxMat + neighbour) + owner) = *(*(auxMat + neighbour) + owner) + 1;
    }
  }


  for(i = 0; i < bigger; i++) {
    for(j = 0 ; j < bigger ; j++) {

      if( *(*(auxMat + i) + j) > 0.0) {
        printf("centro: %3d  vizinho: %3d\n", j, i);
        printf("valor: %lf\n\n", *(*(auxMat + i) + j));
      }
    }
  }


  for(i = 0; i < bigger; i++) {
    free(*(auxMat+ i));
  }
  free(auxMat);
}
