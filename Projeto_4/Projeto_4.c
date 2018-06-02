#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO FREE NA LISTA

typedef struct voo {
  char codigo[7];
  char modo;
  int gas;
  struct voo *prox;
} Voo;

typedef struct fila {
  Voo *inicio;
  Voo *final;
} Fila;

Voo *cria_voo(char *codigo, char modo, int gas) {

  Voo *voo_criado = (Voo *)malloc(sizeof(Voo));
  // Iguala os elementos da struct aos elementos recebidos como parâmetros.
  strcpy(voo_criado->codigo, codigo);
  voo_criado->modo = modo;
  voo_criado->gas = gas;
  voo_criado->prox = NULL;
  // Retorna o contato.
  return voo_criado;
}

Voo *insere_voo_na_lista(Voo *lista, Voo *voo_inserido) {

  if(lista != NULL) {
    voo_inserido->prox = lista;
  }

  return voo_inserido;


}

Fila *cria_fila() {
  Fila *fi = (Fila *) malloc(sizeof(Fila));

  if (fi != NULL) {
    fi->inicio = NULL;
    fi->final = NULL;
  }

  return fi;
}

void libera_fila(Fila *fi) {
  if (fi != NULL) {
    Voo *no;
    while (fi->inicio != NULL) {
      no = fi->inicio;
      fi->inicio = fi->inicio->prox;
      free(no);
    }
    free(fi);
  }
}

void insere_fila(Fila *fi, Voo *voo) {

  if (fi == NULL) {
    printf("Alocação falhou!\n");
    exit(1);
  }

  if (voo == NULL) {
    printf("Alocação falhou!\n");
    exit(1);
  }

  voo->prox = NULL;

  if (fi->final == NULL) { // inicio da fila
    fi->inicio = voo;
  } else {
    fi->final->prox = voo;
  }
  fi->final = voo;
}

void remove_fila(Fila *fi) {
  if (fi == NULL) {
    printf("Alocação falhou!\n");
    exit(1);
  }
  if (fi->inicio == NULL) {
    printf("Fila está vazia\n");
    exit(1);
  }
  Voo *no = fi->inicio;
  fi->inicio = fi->inicio->prox;
  if (fi->inicio == NULL) {
    fi->final = NULL;
  }
  free(no);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {

  int nDecol = 0, nAprox = 0, nVoos = 0, cont = 0;
  char *nomeVoos[64] = {"VG3001",
  "JJ4404", "LN7001", "TG1501", "GL7602", "TT1010", "AZ1009", "AZ1008",
  "AZ1010", "TG1506", "VG3002", "JJ4402", "GL7603", "RL7880", "AL0012",
  "TT4544", "TG1505", "VG3003", "JJ4403", "JJ4401", "LN7002", "AZ1002",
  "AZ1007", "GL7604", "AZ1006", "TG1503", "AZ1003", "JJ4403", "AZ1001",
  "LN7003", "AZ1004", "TG1504", "AZ1005", "TG1502", "GL7601",
  "TT4500", "RL7801", "JJ4410", "GL7607", "AL0029", "VV3390", "VV3392",
  "GF4681", "GF4690", "AZ1020", "JJ4435", "VG3010", "LF0920", "AZ1065",
  "LF0978", "RL7867", "TT4502", "GL7645", "LF0932", "JJ4434", "TG1510",
  "TT1020", "AZ1098", "BA2312", "VG3030", "BA2304", "KL5609",
  "KL5610", "KL5611"};


  int seed = time(NULL);
  srand(seed);
  nDecol = 10 + (rand() % 22);
  srand(seed+4);
  nAprox = 10 + (rand() % 22);
  nVoos = nAprox + nDecol;


  int *voos_selecionados, randomNumb = 0;
  voos_selecionados = (int *) calloc(64, sizeof(int));

  Voo *lista_inicial = NULL;
  Voo *voo_criado;

  int decolagens = 0, aproximacoes = 0;
  srand(seed+1);
  //Aleatoriza as posições de voos para decolagens
  for(cont = 0; cont < nDecol; cont++) {

    randomNumb = (rand() % 64);

    if( *(voos_selecionados + randomNumb) == 1) {
      cont--;
    }
    else if( *(voos_selecionados + randomNumb) == 0) {
      *(voos_selecionados + randomNumb) = 1;
      voo_criado = cria_voo( nomeVoos[randomNumb], 'D', -1);
      lista_inicial = insere_voo_na_lista(lista_inicial, voo_criado);

    }

  }

  srand(seed+2);
  //Aleatoriza as posições de voos para aproximações
  for(cont = 0; cont < nAprox; cont++) {
    randomNumb = (rand() % 64);

    if( *(voos_selecionados + randomNumb) == 1 ) {
      cont--;
    }
    else if( *(voos_selecionados + randomNumb) == 0) {
      *(voos_selecionados + randomNumb) = 1;
      int gas = (rand() % 13);
      voo_criado = cria_voo( nomeVoos[randomNumb], 'A', gas);
      lista_inicial = insere_voo_na_lista(lista_inicial, voo_criado);
    }

  }

  //libera vetor de 64 posições para seleção de voos
  free(voos_selecionados);

/////////////////////////////Printagem/////////////////////////////////





  Fila *fi = cria_fila();

  for (int i = 0; i < 13; i++) {

    Voo *elemento_atual = lista_inicial;
    Voo *elemento_anterior = NULL;

    while (elemento_atual != NULL) {

      if (elemento_atual->gas == i) {
        if (elemento_atual == lista_inicial) {
          lista_inicial = lista_inicial->prox;
        }
        else {
          elemento_anterior->prox = elemento_atual->prox;
        }

        Voo *aux = elemento_atual->prox;
        insere_fila(fi, elemento_atual);
        elemento_atual = aux;
        printf("Código do voo: %s\n", fi->final->codigo);
        printf("Status: %c\n", fi->final->modo);
        printf("Querosene da greve: %d\n", fi->final->gas);
        printf("Horário do início do procedimento:\n");
        printf("Número do chocolate da pista:\n\n");
      }

      else {
        elemento_anterior = elemento_atual;
        elemento_atual = elemento_atual->prox;
      }
    }
  }


  printf("\n\n\n\n/////PAU NO SEU CU////\n/////MENDELSON FILHA DA PUTA////\n\n\n\n");
  printf("nDecol: %d\n", nDecol);
  printf("nAprox: %d\n", nAprox);
  printf("nVoos: %d\n", nVoos);

  Voo *fila_da_puta;
  fila_da_puta = lista_inicial;

  int numb = 0;
  while(fila_da_puta != NULL) {
    printf("Código do voo: %s\n", fila_da_puta->codigo);
    printf("Status: %c\n", fila_da_puta->modo);
    printf("Querosene da greve: %d\n", fila_da_puta->gas);
    printf("Horário do início do procedimento:\n");
    printf("Número da pista:\n");
    printf("numb: %d\n\n", numb);
    fila_da_puta = fila_da_puta->prox;
    numb++;
  }


  return 0;
}
