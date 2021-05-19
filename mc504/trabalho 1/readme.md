**Descreva a estrutura de dados principal e qual foi a estratégia para divisão de trabalho**

  A estrutura principal de dados foi um vetor com 81 posições, cada uma de suas entradas pode armazenar uma estrutura de dados chamada insercao, que basicamente simula uma matriz. A estrutura insercao contém um apontador duplo para uma outra estrutura de dados denominada casa, que contém um inteiro, que seria equivalente a entrada propriamente dita da posição na matriz, e um vetor de inteiros de tamanho 9, que irá armazenar na posição i o valor 0 se o valor i+1 não for um valor válido para aquela entrada da matriz, e o valor 1 caso contrário.

  A estratégia para a divisão de trabalho foi chamar 9 threads, cada uma recebendo um valor entre 1-9. Todas as threads irão percorrer a matriz procurando por posições ainda não preenchidas, quando encontrada uma posição desse tipo cada thread ficará encarregada de verificar se o valor recebido por ela é válido ou não naquela posição e de alterar o vetor
da estrutura casa de maneira apropriada para indicar que o valor da thread é um valor 
possível naquela entrada ainda sem valor.
O problema vai começar um tabuleiro 9x9 de sudoku parcialmente preenchido
Estrututra do sudoku:

```
Tabuleiro:
  ---   ---   ---
|  A  |  B  |  C  |
  ---   ---   ---
|  D  |  E  |  F  |
  ---   ---   ---
|  H  |  I  |  J  |
  ---   ---   ---

Subtabuleiro A:

   a1 | a2 | a3
  --------------
   a4 | a5 | a6
  --------------
   a7 | a8 | a9
```

1.   O tabuleiro é composto por 9 subtabuleiros 3x3
2.   Cada subtabuleiro contém 9 elementos que são um número natural entre [1, 9], não sendo possível repetir o mesmo número no mesmo subtabuleiro
3.   As linhas e colunas do tabuleiro seguem a mesma linha de preenchimento
