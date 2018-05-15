#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct contato {
    char nome[100];
    char celular[10]; //no formato xxxxx-xxxx
    char endereco[100];
    int cep;
    char data_nascimento[10]; //no formato dd/mm/aaaa
    struct contato *prox;
    struct contato *ant;

} Contato;

Contato * ordena_lista(Contato * primeiro_elemento) {
    // zero or one element in list
    if(primeiro_elemento == NULL || primeiro_elemento->prox == NULL)
        return primeiro_elemento;
    // head is the first element of resulting sorted list
    Contato * head = NULL;
    while(primeiro_elemento != NULL) {

        Contato * elemento_atual = primeiro_elemento;
        primeiro_elemento = primeiro_elemento->prox;

        if(head == NULL || strcmp(elemento_atual->nome, head->nome) <= 0) {
            // insert into the head of the sorted list
            // or as the first element into an empty sorted list
            elemento_atual->prox = head;
            head = elemento_atual;

        }
        else {
            // insert current element into proper position in non-empty sorted list
            struct LIST * elemento_de_analise = head;
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

  char aux[100], cel[10];

  FILE *fp;
  Contato *lista;



  return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

le_contatos(FILE *fp, )
