#include <stdio.h>
#include <stdlib.h>

typedef struct contato {
    char nome[100];
    char celular[10]; //no formato xxxxx-xxxx
    char endereco[100];
    int cep;
    char data_nascimento[10]; //no formato dd/mm/aaaa
    struct contato *prox;
    struct contato *ant;

} Contato;
/*
struct LIST * SortList1(struct LIST * pList) {
    // zero or one element in list
    if(pList == NULL || pList->pNext == NULL)
        return pList;
    // head is the first element of resulting sorted list
    struct LIST * head = NULL;
    while(pList != NULL) {
        struct LIST * current = pList;
        pList = pList->pNext;
        if(head == NULL || current->iValue < head->iValue) {
            // insert into the head of the sorted list
            // or as the first element into an empty sorted list
            current->pNext = head;
            head = current;
        } else {
            // insert current element into proper position in non-empty sorted list
            struct LIST * p = head;
            while(p != NULL) {
                if(p->pNext == NULL || // last element of the sorted list
                   current->iValue < p->pNext->iValue) // middle of the list
                {
                    // insert into middle of the sorted list or as the last element
                    current->pNext = p->pNext;
                    p->pNext = current;
                    break; // done
                }
                p = p->pNext;
            }
        }
    }
    return head;
}
*/
int main () {

  char aux[100], cel[10];

  FILE *fp;

  fp = fopen("contatos.txt", "r");

  if (fp == NULL) {
    printf("Falha na abertura do arquivo.\n");
  }

  fscanf(fp, " %[^\n]", aux);

  printf("%s\n", aux);

  fscanf(fp, " %[^\n]", cel);

  printf("%s\n", cel);

  fclose(fp);

  return 0;
}
