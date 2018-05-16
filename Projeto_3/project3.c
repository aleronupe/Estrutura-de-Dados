#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct contato {
    char nome[101];
    char celular[11]; //no formato xxxxx-xxxx
    char endereco[101];
    unsigned int cep;
    char data_nascimento[11]; //no formato dd/mm/aaaa
    struct contato *prox;
    struct contato *ant;

} Contato;

Contato *cria_lista() {
  return NULL;
}

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

Contato *inserir_contato_na_lista(Contato *lista, Contato *contato) {

  if (lista != NULL) {
    lista->ant = contato;
    contato->prox = lista;
  }

  return contato;
}

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


Contato *ordena_lista(Contato *lista_de_contatos) {
    // Nenhum ou um elemento na lista, retorna o que foi passado
    if(lista_de_contatos == NULL || (lista_de_contatos->prox == NULL && lista_de_contatos->ant == NULL) )
        return lista_de_contatos;
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

        }
        else {
            //Seta elemento de análise como o head da lista
            Contato * elemento_de_analise = head;
            //Enquanto o elemento de análise não for o posterior ao último, acontece o loop
            while(elemento_de_analise != NULL) {
                /* Se o elemento_de_analise for o último ou o elemento_atual for menor
                do que o elemento_de_analise, entra no if
                */
                if(elemento_de_analise->prox == NULL || strcmp(elemento_atual->nome, elemento_de_analise->prox->nome) <= 0) // middle of the list
                {

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


int main () {

  char nome[101];
  char celular[11]; //no formato xxxxx-xxxx
  char endereco[101];
  unsigned int cep;
  char data_nascimento[11]; //no formato dd/mm/aaaa

  char c; // Pegar elementos char do arquivo.

  Contato *lista_de_contatos = cria_lista();

  FILE *fp;

  fp = fopen("contatos.txt", "r");

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

    Contato *contato = criar_contato( nome, celular, endereco, cep, data_nascimento);
    lista_de_contatos = inserir_contato_na_lista(lista_de_contatos, contato);
  }

  fclose(fp);

  imprimir_contatos(lista_de_contatos);

  printf("\nPau no seu cu\n");

  lista_de_contatos = ordena_lista(lista_de_contatos);

  imprimir_contatos(lista_de_contatos);

  return 0;
}
