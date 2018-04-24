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

int main (int argc, char *argv[]) {

  // Declaração de variáveis.
  char marcador, pv, vetorbin[9];
  int **mat, *ilbp, decimal[9], i, j, menor, lin = 0, col = 1;

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
  printf("\n");

  // Libera a memória alocada dinamicamente.
  for (i = 0; i < lin; i++) {
    free(*(mat+i));
  }
  free(mat);
  free(ilbp);

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
    printf("vetor %c\n%d\n", vetorbin[i], i);
  }
}

int converte_binario_calcula_menor_decimal(char *bin, int *dec) {

  // Declaração de variáveis locais.
  int decimal, i, k, c, j, n = 9, m = 0, menor = 511;
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
