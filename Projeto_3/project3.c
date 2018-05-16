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
    // zero or one element in list
    if(lista_de_contatos == NULL || lista_de_contatos->prox == NULL)
        return lista_de_contatos;
    // head is the first element of resulting sorted list
    Contato * head = NULL;
    while(lista_de_contatos != NULL) {

        Contato * elemento_atual = lista_de_contatos;
        lista_de_contatos = lista_de_contatos->prox;

        if(head == NULL || strcmp(elemento_atual->nome, head->nome) <= 0) {
            // insert into the head of the sorted list
            // or as the first element into an empty sorted list
            elemento_atual->prox = head;
            head = elemento_atual;

        }
        else {
            // insert current element into proper position in non-empty sorted list
            Contato * elemento_de_analise = head;
            while(elemento_de_analise != NULL) {
                if(elemento_de_analise->nome == NULL || strcmp(elemento_atual->nome, elemento_de_analise->prox->nome) <= 0) // middle of the list
                {
                    // insert into middle of the sorted list or as the last element
                    elemento_atual->prox = elemento_de_analise->prox;
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

  lista_de_contatos = ordena_lista(lista_de_contatos);

  imprimir_contatos(lista_de_contatos);

  return 0;
}
