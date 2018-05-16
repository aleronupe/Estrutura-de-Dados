#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct contato {
    char nome[101];
    char celular[11]; //no formato xxxxx-xxxx
    char endereco[101];
    unsigned int cep;
    char data_nascimento[11]; //no formato dd/mm/aaaa
    struct contato *prox;
    struct contato *ant;

} Contato;

Contato *cria_lista();
Contato *criar_contato(char *nome, char *celular, char *endereco, unsigned int cep, char *data_nascimento);
Contato *insere_contato_no_inicio_da_lista(Contato *lista, Contato *contato);
void imprimir_contatos(Contato *lista);
Contato *ordena_lista(Contato *lista_de_contatos);
Contato *novo_contato(Contato *lista_de_contatos);
Contato *abre_arquivo();
Contato *remover_contato(Contato *lista);
void visualizar_contato(Contato*lista);
void menu();


int main () {

  char seletor = 'P';
  Contato *lista_de_contatos = cria_lista();

  lista_de_contatos = abre_arquivo();
  lista_de_contatos = ordena_lista(lista_de_contatos);


  while(seletor != '5')  {
    menu();
    scanf(" %c", &seletor);
    if(seletor == '1') {
      lista_de_contatos = novo_contato(lista_de_contatos);
    }
    else if(seletor == '2') {
      lista_de_contatos = remover_contato(lista_de_contatos);
    }
    else if(seletor == '3') {
      visualizar_contato(lista_de_contatos);
    }
    else if(seletor == '4') {
      imprimir_contatos(lista_de_contatos);
    }
    else if(seletor == '5') {
      break;
    }
    else {
      printf("Opção inválida!\n");
    }
  }

  return 0;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Contato *ordena_lista(Contato *lista_de_contatos) {
  // Nenhum ou um elemento na lista, retorna o que foi passado
  if(lista_de_contatos == NULL || (lista_de_contatos->prox == NULL && lista_de_contatos->ant == NULL)) {
    return lista_de_contatos;
  }
  /*Se o programa não passar nessa condição, o head será o primeiro da
  lista desordenada, como o head ainda não foi definido, o primeiro elementos
  será nulo*/
  Contato * head = NULL;
  //Enquanto o elemento que será analisado for diferente de nulo, o loop ocorrerá
  while(lista_de_contatos != NULL) {
    /* O elemento_atual se torna o elemento que está sendo analisado
    e o lista_de_contatos se torna o próximo elemento a ser analisado
    seguindo a ordem de criação da lista, sem a ordenação alfabética
    */
    Contato * elemento_atual = lista_de_contatos;
    lista_de_contatos = lista_de_contatos->prox;

    /*Se o elemento head for nulo, o que indica que o elemento_atual é
    o primeiro elemento da lista desordeanda, ele passará por esse if.
    Caso o head não seja nulo, mas o elemento_atual possuir nome menor ou
    igual ao que está presente em head, o elemento_atual se tornará o novo head da lista
    */
    if(head == NULL || strcmp(elemento_atual->nome, head->nome) <= 0) {
      //Coloca o elemento atual na primeira posição da lista
      elemento_atual->ant = NULL;
      elemento_atual->prox = head;
      //Coloco como elemento anterior do head como elemento atual caso o
      //head não seja nulo, ou seja, tem mais de um elemento na lista
      if(head != NULL) {
        head->ant = elemento_atual;
      }
      //Seta o head da lista como elemento_atual
      head = elemento_atual;

    } else {
        //Seta elemento de análise como o head da lista
        Contato * elemento_de_analise = head;
        //Enquanto o elemento de análise não for o posterior ao último, acontece o loop
        while(elemento_de_analise != NULL) {
          /* Se o elemento_de_analise for o último ou o elemento_atual for menor
          do que o elemento_de_analise, entra no if
          */
          if(elemento_de_analise->prox == NULL || strcmp(elemento_atual->nome, elemento_de_analise->prox->nome) <= 0) {
          // middle of the list
            /*Para não perder o próximo elemento da lista, o próximo do
            elemento_atual se torna o próximo do elemento_de_analise*/
            elemento_atual->prox = elemento_de_analise->prox;
            /*Entra no if se o próximo do elemento de análise não é nulo,
            ou seja, que o elemento_de_analise não é o último da lista*/
            if(elemento_de_analise->prox != NULL) {
              elemento_de_analise->prox->ant = elemento_atual;
            }
            elemento_atual->ant = elemento_de_analise;
            elemento_de_analise->prox = elemento_atual;
            break; // done
          }
          elemento_de_analise = elemento_de_analise->prox;
        }
    }
  }
  return head;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void imprimir_contatos(Contato *lista) {

  Contato *atual = lista;

  if (atual == NULL) {
    puts("\nLista de contatos vazia!\n");
  }

  while (atual != NULL) {

    printf("\nNome: %s\n", atual->nome);
    printf("Telefone: %s\n", atual->celular);
    printf("Endereço: %s\n", atual->endereco);
    printf("CEP: %d\n", atual->cep);
    printf("Aniversário: %s\n", atual->data_nascimento);

    atual = atual->prox;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Contato *insere_contato_no_inicio_da_lista(Contato *lista, Contato *contato) {

  if (lista != NULL) {
    lista->ant = contato;
    contato->prox = lista;
  }

  return contato;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Contato *criar_contato(char *nome, char *celular, char *endereco, unsigned int cep, char *data_nascimento) {
  // Aloca um Contato.
  Contato *contato = (Contato *)malloc(sizeof(Contato));
  // TODO free
  // Iguala os elementos da struct aos elementos recebidos como parâmetros.
  strcpy(contato->nome, nome);
  strcpy(contato->celular, celular);
  strcpy(contato->endereco, endereco);
  contato->cep = cep;
  strcpy(contato->data_nascimento, data_nascimento);
  // O próximo elemento e o anterior são nulos pois está criando o elemento da lista.
  contato->prox = NULL;
  contato->ant = NULL;

  return contato;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Contato *cria_lista() {
  return NULL;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Contato *abre_arquivo() {
  FILE *fp;
  Contato *lista_de_contatos = cria_lista();


  fp = fopen("contatos.txt", "r");

  char nome[101];
  char celular[11]; //no formato xxxxx-xxxx
  char endereco[101];
  unsigned int cep;
  char data_nascimento[11]; //no formato dd/mm/aaaa

  char c; // Pegar elementos char do arquivo.

  if (fp == NULL) {
    printf("Falha na abertura do arquivo.\n");
  }

  while (c != EOF) {

    fscanf(fp, " %[^\n]", nome);
    fscanf(fp, " %[^\n]", celular);
    fscanf(fp, " %[^\n]", endereco);
    fscanf(fp, " %ud", &cep);
    fscanf(fp, " %[^\n]", data_nascimento);

    c = fgetc(fp);
    c = fgetc(fp);

    if (c == EOF) {
      break;
    }

    Contato *contato = criar_contato(nome, celular, endereco, cep, data_nascimento);
    lista_de_contatos = insere_contato_no_inicio_da_lista(lista_de_contatos, contato);
  }

  fclose(fp);

  return lista_de_contatos;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Contato *novo_contato(Contato *lista_de_contatos) {

  char nome[101];
  char celular[11]; //no formato xxxxx-xxxx
  char endereco[101];
  unsigned int cep;
  char data_nascimento[11]; //no formato dd/mm/aaaa

  printf("\nInsira um contato na lista de contatos\n");

  printf("Nome\n");
  scanf(" %[^\n]", nome);
  printf("Cel\n");
  scanf(" %[^\n]", celular);
  printf("End\n");
  scanf(" %[^\n]", endereco);
  printf("CEP\n");
  scanf(" %ud", &cep);
  printf("Nascimento\n");
  scanf(" %[^\n]", data_nascimento);

  int cont = 0, size = strlen(nome);
  for(cont = 0; cont < size; cont++) {
    if(cont == 0){
      nome[cont] = toupper(nome[cont]);
    }

    else if(nome[cont-1] == ' ') {
      nome[cont] = toupper(nome[cont]);
    }
  }

  Contato *contato = criar_contato(nome, celular, endereco, cep, data_nascimento);

  lista_de_contatos = insere_contato_no_inicio_da_lista(lista_de_contatos, contato);

  lista_de_contatos = ordena_lista(lista_de_contatos);

  return lista_de_contatos;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Contato *remover_contato(Contato *lista) {

  char nome_remove[101];

  printf("\nInsira o nome do contato a ser removido\n");
  printf("Nome\n");
  scanf(" %[^\n]", nome_remove);

  int cont = 0, size = strlen(nome_remove);
  for(cont = 0; cont < size; cont++) {
    if(cont == 0){
      nome_remove[cont] = toupper(nome_remove[cont]);
    }

    else if(nome_remove[cont-1] == ' ') {
      nome_remove[cont] = toupper(nome_remove[cont]);
    }
  }

  Contato *atual = lista;


  if (atual == NULL) {
    puts("\nLista de contatos vazia! Impossível remover.\n");
  }

  while (atual != NULL) {

    char nome_comparado[101];
    strcpy(nome_comparado, atual->nome);
    int sizeComp = strlen(nome_comparado);

    if(sizeComp >= size) {
      for(cont = 0; cont < size; cont++) {
        if(nome_comparado[cont] != nome_remove[cont]) {
          atual = atual->prox;
          break;
        }

        if(cont == size - 1 && sizeComp == size) {
          Contato *auxiliadora;
          if(atual->ant == NULL) {
            lista = atual->prox;
          }
          if(atual->ant != NULL) {
            atual->ant->prox = atual->prox;
          }
          if(atual->prox != NULL) {
            atual->prox->ant = atual->ant;
          }
          auxiliadora = atual;
          atual = atual->prox;
          free(auxiliadora);
          printf("Usuário Removido: %s\n", nome_comparado);
        }
        else if(cont == size - 1 && sizeComp > size) {
          if(nome_comparado[cont+1] == ' ') {
            Contato *auxiliadora;
            if(atual->ant == NULL) {
              lista = atual->prox;
            }
            if(atual->ant != NULL) {
              atual->ant->prox = atual->prox;
            }
            if(atual->prox != NULL) {
              atual->prox->ant = atual->ant;
            }
            auxiliadora = atual;
            atual = atual->prox;
            free(auxiliadora);
            printf("Usuário Removido: %s\n", nome_comparado);
          }
          else {
            atual = atual->prox;
          }
        }
      }
    }
    else {
        atual = atual->prox;
    }
  }
   return lista;
}

void visualizar_contato(Contato*lista) {

  char nome_visualiza[101];

  printf("\nInsira o nome do contato a ser visualizado\n");
  printf("Nome\n");
  scanf(" %[^\n]", nome_visualiza);

  int cont = 0, size = strlen(nome_visualiza);
  for(cont = 0; cont < size; cont++) {
    if(cont == 0){
      nome_visualiza[cont] = toupper(nome_visualiza[cont]);
    }

    else if(nome_visualiza[cont-1] == ' ') {
      nome_visualiza[cont] = toupper(nome_visualiza[cont]);
    }
  }

  Contato *atual = lista;


  if (atual == NULL) {
    puts("\nLista de contatos vazia! Impossível visualizar.\n");
  }

  while (atual != NULL) {

    char nome_comparado[101];
    strcpy(nome_comparado, atual->nome);
    int sizeComp = strlen(nome_comparado);
    // Verifica se o tamanho do nome digitado é maior que o que queremos.
    // Se for ele já não é o elemento que queremos e irá para o próximo elemento.
    if (sizeComp >= size) {
      // Iremos percorrer todos os caracteres.
      for (cont = 0; cont < size; cont++) {
        // Se o caractere já for diferente, pula para o próximo elemento, pois não é o desejado.
        if (nome_comparado[cont] != nome_visualiza[cont]) {
          atual = atual->prox;
          break;
        }
        // Os caracteres são iguais então iremos conferir
        // Se o nome é igual ao digitado, se for entra no if.
        if (cont == size - 1 && sizeComp == size) {
          printf("\nNome: %s\n", atual->nome);
          printf("Telefone: %s\n", atual->celular);
          printf("Endereço: %s\n", atual->endereco);
          printf("CEP: %d\n", atual->cep);
          printf("Aniversário: %s\n", atual->data_nascimento);

          atual = atual->prox;
        }
        // Os caracteres são iguais então iremos conferir
        // Se o nome é igual, ou se o nome_comparado tem caractere a mais e não é o desejado
        // Como por exemplo procuramos por Luan e o nome Luana tem "Luan" porém não é o desejado.
        else if (cont == size - 1 && sizeComp > size) {
          if (nome_comparado[cont + 1] == ' ') {
            printf("\nNome: %s\n", atual->nome);
            printf("Telefone: %s\n", atual->celular);
            printf("Endereço: %s\n", atual->endereco);
            printf("CEP: %d\n", atual->cep);
            printf("Aniversário: %s\n", atual->data_nascimento);

            atual = atual->prox;
          } else {
            atual = atual->prox;
          }
        }
      }
    } else {
      atual = atual->prox;
    }
  }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void menu() {
  printf("-------------------------------------------------------------------------------------------\n");
  printf("---\t\t\tSELECIONE A OPÇÃO DESEJADA:\t\t\t\t\t---\n");
  printf("-------------------------------------------------------------------------------------------\n");
  printf("---\t\t\t(1) Inserir novo contato\t\t\t\t\t---\n");
  printf("---\t\t\t(2) Remover contatos de mesmo nome\t\t\t\t---\n");
  printf("---\t\t\t(3) Visualizar registro\t\t\t\t\t\t---\n");
  printf("---\t\t\t(4) Visualizar todos os registros em ordem alfabetica\t\t---\n");
  printf("---\t\t\t(5) Sair\t\t\t\t\t\t\t---\n");
  printf("-------------------------------------------------------------------------------------------\n");
}
