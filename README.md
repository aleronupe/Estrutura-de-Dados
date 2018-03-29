# **Estrutura-de-Dados**

## Ponteiros

Variável:   ``X``  
Ponteiro:   ``*pont``  
Endereço da Variável: ``&X``
 

* _Gets_  -> Pega até o fim da linha;
* Com o endereço da primeira posição de uma string e o endereço de uma posição de interesse, é possível calcular a posição da string;



Em linguagem de ponteiro, temos:

`` &x[0] <=> x ``

`` 0 <=> '\0' ``
``  ``

## Matrizes de Ponteiros


  ``p`` - Ponteiro para o primeiro valor da matriz (pos[0][0])

  ``i*COL`` - ( i ) equivale ao número da coluna que se quer acessar e ( COL ) equivale ao número máximo de colunas   

  ``j`` - Linha para a qual se quer apontar

  ```
                                      p + i*COL + j  
  ```
