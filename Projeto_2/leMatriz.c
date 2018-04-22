#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])

{
  FILE *matriz;

  //Abre o arquivo da matriz
  matriz = fopen("asphalt_01.txt","r");
  if (matriz == NULL) {
    printf("Falha.\n");
    exit(1);
  }

  //declara os elementos necessários pra identificar linhas e colunas
  int numb = 0, lines = 0, columns = 0;
  char typo = '.';

  //lê o número de colunas (até o \n)
  while(typo != '\n') {
    fscanf(matriz, "%d", &numb);
    fscanf(matriz, "%c", &typo);
    columns++;
  }

  //volta pro começo da matriz
  rewind(matriz);

  /*Lê o número de linhas, verificando se o elemento do tipo
  'char' encontrado é o fim do arquvi (EOF) ou se é um \n, que
  indica o fim de uma linha*/
  fscanf(matriz, "%d", &numb);
  while(fscanf(matriz, "%c", &typo) != EOF) {
    if(typo == '\n') {
      lines++;
    }
    fscanf(matriz, "%d", &numb);
  }

  rewind(matriz);

  int cont = 0, **mat;

  //aloca o espaço pra matriz na memória
  mat = (int **)malloc(lines*sizeof(int *));
  for(cont = 0; cont < lines; cont++) {
    mat[cont] = (int*)malloc(columns*sizeof(int));
  }

  int i = 0, j = 0;

  for(i = 0; i < lines; i++){
    for(j = 0; j < columns; j++){
      fscanf(matriz, "%d", &numb);
      fscanf(matriz, "%c", &typo);
      *(*(mat+i)+j) = numb;
    }
  }

  //desaloca cada vetor apontado pelo vetor primário da matriz
  for (cont = 0; cont < lines; cont++) {
    free(mat[cont]);
  }
  //desaloca o vetor primário da matriz da memória
  free(mat);
  //fecha o arquivo da memória
  fclose(matriz);



  return 0;
}
