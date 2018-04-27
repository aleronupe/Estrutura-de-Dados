#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void monta_vetor_binario(int **mat, int lin, int col, char *vetorbin);
/*
A função pega como parâmento a linha e a coluna do elemento central, a partir dele
forma uma submatriz [3][3] e pega os nove elementos, soma todos e calcula a média,
após isso cria-se uma matriz de char [3][3] em que os elementos serão 1 ou 0
iguala-se a '1' os elementos da submatriz que são maiores ou iguais que a média
e iguala-se a '0' os elementos menores que a média, após isso na ordem definida
pelo ILBP monta-se o vetor de binários.
*/
int converte_binario_calcula_menor_decimal(char *bin, int *dec);
/*
A função pega o vetor de binários, rotaciona bit-a-bit e calcula o decimal de
cada rotação, com isso pega-se os decimais, salva em um vetor e pega o menor dos
decimais e retorna.
*/
void GLCM(int **mat, int lin, int col, float *metricas);
/*
A função recebe a matriz do arquivo, o tanto de linhas e de colunas que ela possui,
ela calcula a ocorrência de vizinhos nas 8 direções e calcula o contraste, a energia e
a homogeneidade de cada direção e vai salvando na respectiva ordem em um vetor
metricas que é modificado e na main irá se juntar com o vetor ilbp para formar o vetor de 536 posições.
*/
float contraste(int **mat, int lin_col);
/*
Calcula o contraste de cada direção da GLCM.
*/

float energia(int **mat, int lin_col);
/*
Calcula o energia de cada direção da GLCM.
*/

float homogeneidade(int **mat, int lin_col);
/*
Calcula o homogeneidade de cada direção da GLCM.
*/

void normalizar_vetor_dados(float *ilbp_glcm, float *ilbp_glcm_normalizado);
/*
A função pega o vetor de dados ilbp + glcm e normaliza (faz o cálculo de normalização).
*/

int main (int argc, char *argv[]) {

  // Declaração de variáveis.
  char marcador, pv, vetorbin[9];
  int **mat, *ilbp, decimal[9], i, j, menor, lin = 0, col = 1;
  float *metricas, *ilbp_glcm, *ilbp_glcm_normalizado;

  // Cria um ponteiro para arquivo.
  FILE *file;

  // Abre o arquivo para leitura.
  file = fopen("teste.txt", "r");

  // Verifica a existência do arquivo, se não existir retorna "Falha".
  if (file == NULL) {
    printf("Falha\n");
    exit(1);
  }

  // Verifica quantas linha e colunas tem a matriz do arquivo.
   while ((marcador = fgetc(file)) != EOF) {
    if (marcador == '\n') {
      lin++;
    }
    else if (lin == 1 && marcador == ';') {
      col++;
    }
  }

  printf("Linhas: %d\nColunas: %d\n", lin, col); // TESTE IMPRIME NÚMERO DE LINHAS E COLUNAS.

  // Volta para o ínicio do arquivo.
  rewind(file);

  // Aloca dinamicamente a matriz do arquivo.
  mat = (int**)malloc(lin*sizeof(int *));
  for (i = 0; i < lin; i++) {
    *(mat+i) = (int*)malloc(col*sizeof(int));
  }

  // Aloca dinamicamente o vetor ILBP de 512 elementos tudo preenchido com 0.
  ilbp = (int *) calloc(512, sizeof (int));

  // Aloca dinamicamente o vetor metricas de 24 elementos tudo preenchido com 0.
  metricas = (float *) calloc(24, sizeof (float));

  // Aloca dinamicamente o vetor ilbp+glcm de 536 elementos tudo preenchido com 0.
  ilbp_glcm = (float *) calloc(536, sizeof (float));

  // Aloca dinamicamente o vetor ilbp+glcm normalizado de 536 elementos tudo preenchido com 0.
  ilbp_glcm_normalizado = (float *) calloc(536, sizeof (float));

  // Passa os elementos da matriz do arquivo para a matriz alocada dinamicamente.
  for (i = 0; i < lin; i++) {
    for (j = 0; j < col; j++) {
        if (!feof(file)) {
          fscanf(file, "%d%c", *(mat+i)+j, &pv);
        }
    }
  }

  printf("%d\n", *(*(mat+0)+0)); // TESTE IMPRIME PRIMEIRO ELEMENTO.
  printf("%d\n", *(*(mat+0)+1)); // TESTE IMPRIME SEGUNDO ELEMENTO.

  // Faz o vetor ILBP.
  for (i = 1; i < lin - 1; i++) {
    for (j = 1; j < col - 1; j++) {
      monta_vetor_binario(mat, i, j, vetorbin);
      menor = converte_binario_calcula_menor_decimal(vetorbin, decimal);
      ilbp[menor]++;
    }
  }

  // TESTE IMPRIME O ILBP.
  for (i = 0; i < 512; i++) {
    printf("%d ", ilbp[i]);
  }
  printf("\nILBP IMPRESSO\n\n");

  // GLCM.
  GLCM(mat, lin, col, metricas);

  for (i = 0; i < 24; i++) {
    printf("%f ", metricas[i]);
  }
  printf("\n\n");

  // Concatenar ilbp + glcm,
  for (i = 0; i < 512; i++) {
    *(ilbp_glcm + i) = *(ilbp + i);
  }
  for (i = 512; i < 536; i++) {
    *(ilbp_glcm + i) = *(metricas + (i - 512));
  }

  // Libera a memória utilizada pelo vetor ilbp e metricas.
  free(ilbp);
  free(metricas);

  // TESTE IMPRIME VETOR CONCATENADO
  for (i = 0; i < 536; i++) {
    printf("%f ", *(ilbp_glcm + i));
  }
  printf("\n\n");

  // NORMALIZAR VETOR CONCATENADO
  normalizar_vetor_dados(ilbp_glcm, ilbp_glcm_normalizado);

  // Libera a memória utilizada pelo vetor ilbp_glcm.
  free(ilbp_glcm);

  // TESTE IMPRIME VETOR NORMALIZADO
  for (i = 0; i < 536; i++) {
    printf("%f ", *(ilbp_glcm_normalizado + i));
  }
  printf("\n\n");

  // Libera a memória alocada dinamicamente.
  for (i = 0; i < lin; i++) {
    free(*(mat+i));
  }
  free(mat);

  free(ilbp_glcm_normalizado);

  // Fecha o arquivo.
  fclose(file);

  return 0;
}

void monta_vetor_binario(int **mat, int lin, int col, char *vetorbin) {
  // Declaração de variáveis locais.
  float soma = 0, media;
  int i, j, x = 0, y = 0;
  char **bin;

  // Aloca dinamicamente a submatriz [3][3] de binários.
  bin = (char**)malloc(3*sizeof(char *));
  for (i = 0; i < 3; i++) {
    *(bin + i) = (char*)malloc(3*sizeof(char));
  }

  // Calcula a soma de todos os elementos da submatriz[3][3].
  for (i = lin - 1; i <= lin + 1; i++) {
    for (j = col - 1; j <= col + 1; j++) {
      soma += *(*(mat+i)+j);
    }
  }

  // Calcula a média da submatriz [3][3].
  media = soma / 9.0;

  // TESTE IMPRIME A MÉDIA
  printf("Tenho a média: %lf\n", media);

  // Verifica cada elemento da submatriz se é maior ou igual a média e preenche com 1 onde é maior e com 0 onde é menor em uma matriz.
  for (i = lin - 1; i <= lin + 1; i++) {
    for (j = col - 1; j <= col + 1; j++) {
      if (*(*(mat+i)+j) < media) {
        *(*(bin+x)+y) = '0';
        y++;
      } else if (*(*(mat+i)+j) >= media) {
        *(*(bin+x)+y) = '1';
        y++;
      }
    }
    y = 0;
    x++;
  }

  printf("Tenho a matriz binaria\n");

  // Passa os elementos da matriz criada para o vetorbin na ordem solicitada pelo ILBP.
  vetorbin[0] = *(*(bin+0)+0);
  vetorbin[1] = *(*(bin+0)+1);
  vetorbin[2] = *(*(bin+0)+2);
  vetorbin[3] = *(*(bin+1)+2);
  vetorbin[4] = *(*(bin+2)+2);
  vetorbin[5] = *(*(bin+2)+1);
  vetorbin[6] = *(*(bin+2)+0);
  vetorbin[7] = *(*(bin+1)+0);
  vetorbin[8] = *(*(bin+1)+1);

  // Libera a memória alocada dinamicamente para a matriz de binários.
  for (i = 0; i < 3; i++) {
    free(*(bin+i));
  }
  free(bin);

  // TESTE IMPRIME O VETORBIN.
  for (i = 0; i < 9; i++) {
    printf("vetor %c %d\n", vetorbin[i], i);
  }
}

int converte_binario_calcula_menor_decimal(char *bin, int *dec) {

  // Declaração de variáveis locais.
  int decimal, i, k, c, j, n = 9, m = 0, menor = 512;
  char temp;

  for (k = 9; k > 0; k--) {

    // Calcula o decimal.
    decimal = 0;
    j = 0;
    for (i = 8; i >= 0; i--) {
      if (*(bin + i) == '1') {
        decimal += pow(2, j);
      }
      j++;
    }

    // Rotaciona o vetor em 1 bit.
    temp = bin[n - 1];
    for (c = n-1; c > 0; c--) {
      bin[c] = bin[c - 1];
    }
    bin[0] = temp;

    // Salva decimal em um vetor.
    dec[m] = decimal;
    m++;
  }

  // Confere qual é o menor decimal dentre os convertidos.
  for (int i = 0; i < 9; i++) {
    if (menor > dec[i]) {
      menor = dec[i];
    }
  }

  // TESTE IMPRIME O MENOR ELEMENTO.
  printf("Menor = %d\n", menor);

  // Retorna o menor elemento.
  return menor;
}

float contraste(int **mat, int lin_col) {

  int i, j;
  float contraste = 0;

  for (i = 0; i < lin_col; i++) {
    for (j = 0; j < lin_col; j++) {
      contraste += pow(i-j,2) * mat[i][j];
    }
  }

  return contraste;
}

float energia(int **mat, int lin_col) {

  int i, j;
  float energia = 0;

  for (i = 0; i < lin_col; i++) {
    for (j = 0; j < lin_col; j++) {
      energia += pow(mat[i][j],2);
    }
  }

  return energia;
}

float homogeneidade(int **mat, int lin_col) {

  int i, j, z;
  float homogeneidade = 0;

  for (i = 0; i < lin_col; i++) {
    for (j = 0; j < lin_col; j++) {
      z = i - j;
      if (z < 0) {
        z = z * (-1);
      }
      homogeneidade += mat[i][j] / (1 + z);
    }
  }

  return homogeneidade;
}


void GLCM(int **mat, int lin, int col, float *metricas) {

  // Declaração de variáveis locais.
  int **glcm, i, j, m, glcm_lin_col = 512;

  for (m = 0; m < 8; m++) {

    // Aloca uma matriz de zeros que irá pegar o GLCM de cada direção.
    glcm = (int**)calloc(glcm_lin_col, sizeof(int *));
    for (i = 0; i < glcm_lin_col; i++) {
      *(glcm+i) = (int*)calloc(glcm_lin_col, sizeof(int));
    }
    if (m == 0) {
      printf("GLCM DIREITA\n");
      // Incrementa a posição [elemento][elemento vizinho da direita] da matriz glcm.
      for (i = 0; i < lin; i++) {
        for (j = 0; j < col - 1; j++) {
          printf("%d ", mat[i][j]);
          printf("%d\n", mat[i][j+1]);
          glcm[mat[i][j]][mat[i][j+1]]++;
        }
      }
      *(metricas + 0) = contraste(glcm, glcm_lin_col);
      *(metricas + 1) = energia(glcm, glcm_lin_col);
      *(metricas + 2) = homogeneidade(glcm, glcm_lin_col);
    } else if (m == 1) {
      printf("GLCM ESQUERDA\n");
      // Incrementa a posição [elemento][elemento vizinho da esquerda] da matriz glcm.
      for (i = 0; i < lin; i++) {
        for (j = 1; j < col; j++) {
          printf("%d ", mat[i][j]);
          printf("%d\n", mat[i][j-1]);
          glcm[mat[i][j]][mat[i][j-1]]++;
        }
      }
      *(metricas + 3) = contraste(glcm, glcm_lin_col);;
      *(metricas + 4) = energia(glcm, glcm_lin_col);
      *(metricas + 5) = homogeneidade(glcm, glcm_lin_col);
    } else if (m == 2) {
      printf("GLCM CIMA\n");
      // Incrementa a posição [elemento][elemento vizinho de cima] da matriz glcm.
      for (i = 1; i < lin; i++) {
        for (j = 0; j < col; j++) {
          printf("%d ", mat[i][j]);
          printf("%d\n", mat[i-1][j]);
          glcm[mat[i][j]][mat[i-1][j]]++;
        }
      }
      *(metricas + 6) = contraste(glcm, glcm_lin_col);;
      *(metricas + 7) = energia(glcm, glcm_lin_col);
      *(metricas + 8) = homogeneidade(glcm, glcm_lin_col);
    } else if (m == 3) {
      printf("GLCM BAIXO\n");
      // Incrementa a posição [elemento][elemento vizinho de baixo] da matriz glcm.
      for (i = 0; i < lin - 1; i++) {
        for (j = 0; j < col; j++) {
          printf("%d ", mat[i][j]);
          printf("%d\n", mat[i+1][j]);
          glcm[mat[i][j]][mat[i+1][j]]++;
        }
      }
      *(metricas + 9) = contraste(glcm, glcm_lin_col);;
      *(metricas + 10) = energia(glcm, glcm_lin_col);
      *(metricas + 11) = homogeneidade(glcm, glcm_lin_col);
    } else if (m == 4) {
      printf("GLCM DIAGONAL CIMA ESQUERDA\n");
      // Incrementa a posição [elemento][elemento vizinho da diagonal de cima da esquerda] da matriz glcm.
      for (i = 1; i < lin; i++) {
        for (j = 1; j < col; j++) {
          printf("%d ", mat[i][j]);
          printf("%d\n", mat[i-1][j-1]);
          glcm[mat[i][j]][mat[i-1][j-1]]++;
        }
      }
      *(metricas + 12) = contraste(glcm, glcm_lin_col);;
      *(metricas + 13) = energia(glcm, glcm_lin_col);
      *(metricas + 14) = homogeneidade(glcm, glcm_lin_col);
    } else if (m == 5) {
      printf("GLCM DIAGONAL CIMA DIREITA\n");
      // Incrementa a posição [elemento][elemento vizinho da diagonal de cima da direita] da matriz glcm.
      for (i = 1; i < lin; i++) {
        for (j = 0; j < col - 1; j++) {
          printf("%d ", mat[i][j]);
          printf("%d\n", mat[i-1][j+1]);
          glcm[mat[i][j]][mat[i-1][j+1]]++;
        }
      }
      *(metricas + 15) = contraste(glcm, glcm_lin_col);;
      *(metricas + 16) = energia(glcm, glcm_lin_col);
      *(metricas + 17) = homogeneidade(glcm, glcm_lin_col);
    } else if (m == 6) {
      printf("GLCM DIAGONAL BAIXO ESQUERDA\n");
      // Incrementa a posição [elemento][elemento vizinho da diagonal de baixo da esquerda] da matriz glcm.
      for (i = 0; i < lin - 1; i++) {
        for (j = 1; j < col; j++) {
          printf("%d ", mat[i][j]);
          printf("%d\n", mat[i+1][j-1]);
          glcm[mat[i][j]][mat[i+1][j-1]]++;
        }
      }
      *(metricas + 18) = contraste(glcm, glcm_lin_col);;
      *(metricas + 19) = energia(glcm, glcm_lin_col);
      *(metricas + 20) = homogeneidade(glcm, glcm_lin_col);
    } else if (m == 7) {
      printf("GLCM DIAGONAL BAIXO DIREITA\n");
      // Incrementa a posição [elemento][elemento vizinho da diagonal de baixo da direita] da matriz glcm.
      for (i = 0; i < lin - 1; i++) {
        for (j = 0; j < col - 1; j++) {
          printf("%d ", mat[i][j]);
          printf("%d\n", mat[i+1][j+1]);
          glcm[mat[i][j]][mat[i+1][j+1]]++;
        }
      }
      *(metricas + 21) = contraste(glcm, glcm_lin_col);;
      *(metricas + 22) = energia(glcm, glcm_lin_col);
      *(metricas + 23) = homogeneidade(glcm, glcm_lin_col);
    }
    // Libera a memória utilizada pela matriz GLCM.
    for (i = 0; i < glcm_lin_col; i++) {
      free(*(glcm+i));
    }
    free(glcm);
  }
}

void normalizar_vetor_dados(float *ilbp_glcm, float *ilbp_glcm_normalizado) {

  // Declaração de variáveis locais.
  int i, maior = 0, menor = 9999999;

  // Pega o menor e maior elemento do vetor ilbp_glcm.
  for (i = 0; i < 536; i++) {
    if (*(ilbp_glcm + i) > maior) {
      maior = *(ilbp_glcm + i);
    }
    if (menor > *(ilbp_glcm + i)) {
      menor = *(ilbp_glcm + i);
    }
  }

  // Monta o vetor normalizado de acordo com o cálculo.
  for (i = 0; i < 536; i++) {
    *(ilbp_glcm_normalizado + i) = (*(ilbp_glcm + i) - menor) / (maior - menor);
  }
}
