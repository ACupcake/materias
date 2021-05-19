#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

typedef struct casa {
  int valor;
  int possiveis_valores[9];
} casa;

typedef struct thread_param {
  int indice;
  casa **matriz;
} thread_param;

typedef struct insercao {
  casa **matriz;
} insercao;

/* 
  Copia matriz "original" para a matriz "copia".
*/
void copia_matriz(casa **copia, casa **original);

/* 
  Testa a matriz preenchida e decide se ela pode ser solução do problema
*/
int matriz_esta_preenchida(casa **matriz);

/*
  Zera matriz de possíveis valores para cada elemento
*/
void zera_possibilidades(casa **matriz);

/*
  Calcula quantos valores são possíveis substituir
*/
int numero_de_possibilidades(int possibilidades[9]);

/*
  Imprime a matriz recebida na tela
 */
void mostra_matriz(casa **matriz);

/*
  Inicializa a matriz com 0s e em seguida lê os valores de cada
  entrada começando de (0,0) linha por linha 
*/
void ler_matriz(casa **matriz);

/*
  Verifica se a linha x da matriz já possui o valor_teste,
  retorna 1 no caso negativo e 0 se já existe elemento da 
  linha com tal número
 */
int verifica_linha(int valor_teste, int x, casa **matriz);

/* 
  Verifica se a coluna y da matriz já possui o valor_teste,
  retorna 1 no caso negativo e 0 se já existe elemento da 
  coluna com tal número
*/
int verifica_coluna(int valor_teste, int y, casa **matriz);

/* 
  Verifica se inserir valor_teste na posição (x,y) da matriz
  é uma ação válida com relação aos números já dispostos no 
  quadrante 3x3 de (x,y), retorna 1 em caso positivo e 0 em caso
  que uma das células já tenha valor_teste
*/
int verifica_quadrado(int valor_teste, int x, int y, casa **matriz);

/*
  Recebe valor_teste e verifica se ele pode ser adicionado na posição 
  (x,y) da matriz passada, retorna 1 no caso positivo e 0 caso já exista 
  uma célula com o número 
*/
int valor_se_repete(int valor_teste, int x, int y, casa **matriz);

/*
  Recebe como entrada um apontador do tipo thread_param que contêm um valor k entre 1-9
  e uma matriz com entrada do tipo casa, formada por um inteiro e uma vetor de inteiros com 9 posições, 
  a função então percorre toda a matriz e quando encontra uma posição com valor 0, seta a posição
  k-1 do vetor dessa entrada como 1 se o valor k for possível nessa entrada
*/
void* f_thread(void *v);

/*
  A função verifica se o tabuleiro de Sudoku possui uma entrada com dois ou mais números iguais na mesma linha,
  coluna ou quadrado interno
*/
int valida_matriz(casa **matriz);

/*
  Função que resolve o sudoku com o algoritimo descrito no início
*/
void resolve_sudoku (casa **matriz, thread_param *parametro, insercao *historico, int posicao_no_historico);

/*
  Preenche matriz com os possíveis valores encontrados
*/
int preenche_posicoes_corretas(casa **matriz, int possibilidades);

/* Limpa memória alocada */
void let_me_free(insercao *historico, thread_param *parametro, casa **matriz);



int main() {
  int posicao_no_historico = 0;
  insercao *historico = malloc(81*sizeof(insercao));
  pthread_t thr[9];
  thread_param *parametro = malloc(9*sizeof(thread_param));
  casa **matriz = malloc(9*sizeof(casa *));
  
  /* Inicialização da matriz do histórico, que servirá como a fila das matrizes de sudoku
  que estarão sendo processadas*/
  for (int i = 0; i < 81; i++) {
    historico[i].matriz =  malloc(9*sizeof(casa *));
    for (int j = 0; j < 9; j++) {
      historico[i].matriz[j] =  malloc(9*sizeof(casa));
    }
  }

  // Inicialização dos parâmetros das threads e da matriz principal do sudoku 
  for (int i = 0; i < 9; i++) {
    matriz[i] = malloc(9*sizeof(casa));
    parametro[i].indice = i + 1;
    parametro[i].matriz = matriz;
  }

  ler_matriz(matriz);

  // Verifica se a matriz inicial é válida
  if (!valida_matriz(matriz)) {
    mostra_matriz(matriz);
    printf("Sudoku não possui solução\n");
    return 0;
  }

  // Inicializa os vetores de possibilidades da matriz
  zera_possibilidades(matriz);

  // gera todas as matrizes possíveis até encontrar uma válida
  resolve_sudoku(matriz, parametro, historico, posicao_no_historico);
  
  mostra_matriz(matriz);

  let_me_free(historico, parametro, matriz);

  return 0;
}

void let_me_free(insercao *historico, thread_param *parametro, casa **matriz) {  
  for (int i = 0; i < 81; i++) {
    for (int j = 0; j < 9; j++) {
      free(historico[i].matriz[j]);
    }
    free(historico[i].matriz);
  }

  for (int i = 0; i < 9; i++) {
    free(matriz[i]);
  }

  free(historico);
  free(parametro);
  free(matriz);
}


void resolve_sudoku(casa **matriz, thread_param *parametro, insercao *historico, int posicao_no_historico) {
  pthread_t thr[9];


  while(!matriz_esta_preenchida(matriz)) {
    int possibilidades;
    mostra_matriz(matriz);

    //  Verifica possibilidade de cada casa e marca valor caso seja possível substituir

    /* Cria e inicializa threads */
    for (int i = 0; i < 9; i++) pthread_create(&thr[i], NULL, f_thread, &parametro[i]);
    for (int i = 0; i < 9; i++) pthread_join(thr[i], NULL);

    // Verifica se existe alguma posição sem nenhum valor possível
    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        if (matriz[i][j].valor == 0) {
          possibilidades = numero_de_possibilidades(matriz[i][j].possiveis_valores);

          if (possibilidades == 0) {
            if (posicao_no_historico >= 1) {
              // Reinicia verificação com a última matriz do histórico e remove essa matriz do histórico
              posicao_no_historico--;
              copia_matriz(matriz, historico[posicao_no_historico].matriz);

              printf("\nChute deu errado :(\n");
              i = -1;
              j = 10;
            } else {
              // Se não houve matriz no histórico, então o sudoku não tem solução
              printf("Sudoku não possui solução\n");
              return;
            }
          }
        }
      }
    }

    // Preenche as posições com só 1 possibilidades / certeza
    int mudanca_feita = preenche_posicoes_corretas(matriz, possibilidades);

    // Se nenhum valor foi preenchido com só 1 possibilidade, então é realizado um chute
    if (mudanca_feita == 0) {
      for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
          if (matriz[i][j].valor == 0) {
            possibilidades = numero_de_possibilidades(matriz[i][j].possiveis_valores);
            if (possibilidades >= 2) {
              for (int k = 0; k < 9; k++) {
                if (matriz[i][j].possiveis_valores[k] == 1) {

                  // O vetor de possibilidades é atualizado
                  matriz[i][j].possiveis_valores[k] = 0;

                  // Então o estado atual da matriz é salvo no histórico
                  copia_matriz(historico[posicao_no_historico].matriz, matriz);

                  matriz[i][j].valor = k+1;

                  posicao_no_historico++;
                  k = 10;
                  j = 10;
                  i = 10;
                }
              }
            }
          }
        }
      }
    }

    // Reseta vetores de possibilidades da matriz
    zera_possibilidades(matriz);
  }
}

int preenche_posicoes_corretas(casa **matriz, int possibilidades) {
    int mudanca_feita = 0;

    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        if (matriz[i][j].valor == 0) {
          possibilidades = numero_de_possibilidades(matriz[i][j].possiveis_valores);
          if (possibilidades == 1) {
            mudanca_feita = 1;
            for (int k = 0; k < 9; k++) {
              if (matriz[i][j].possiveis_valores[k] == 1) {
                matriz[i][j].valor = k + 1;
                matriz[i][j].possiveis_valores[k] = 0;
                k = 10;
                j = 10;
                i = 10;
              }
            }
          }
        }
      }
    }
    
    return mudanca_feita;
}


void* f_thread(void *_parametro) {
  thread_param parametro = * (thread_param *) _parametro;
  for (int i = 0; i < 9; i++){
    for (int j = 0; j < 9; j++){
      if(parametro.matriz[i][j].valor == 0) {
        if(valor_se_repete(parametro.indice, i, j, parametro.matriz)) {
          parametro.matriz[i][j].possiveis_valores[parametro.indice - 1] = 1;
        }
      }
    }
  }
}

void mostra_matriz(casa **matriz) {
  printf("\n");
  for(int i = 0; i < 9; i++) {
    if ((i%3 == 0)&&(i>0)) printf("=========|=========|=========\n");
    for(int j = 0; j < 9; j++) {
      if ((j%3 == 0)&&(j>0)) printf("|");
      printf(" %d ", matriz[i][j].valor); 
    }
    printf("\n");
  }
  printf("\n\n");
}

void ler_matriz(casa **matriz) {
    for(int i = 0; i < 9; i++) {
      for(int j = 0; j < 9; j++) {
        scanf("%d", &matriz[i][j].valor);
      }
    }
}

int verifica_linha(int valor_teste, int x, casa **matriz) {
  int possivel = 1;
  for(int j = 0; j < 9; j++) {
    if(matriz[x][j].valor == valor_teste) {
      possivel = 0;
      break;
    }

  }
  return possivel;
}

int verifica_coluna(int valor_teste, int y, casa **matriz) {
  int possivel = 1;
  for(int i=0; i < 9; i++) {
    if(matriz[i][y].valor == valor_teste) {
      possivel = 0;
      break;
    }
  } 
  return possivel;
}

int verifica_quadrado(int valor_teste, int x, int y, casa **matriz){
  int possivel = 1;

  for(int i = (x/3)*3; i <= ((x/3)*3+2); i++) {
    for(int j = (y/3)*3; j <= ((y/3)*3+2); j++) {
      if (matriz[i][j].valor == valor_teste) {
        possivel = 0;
        i = 10;
        j = 10;
        break;
      }
    }
  }

  return possivel;
}

int valor_se_repete(int valor_teste, int linha, int coluna, casa **matriz) {
  return(
         verifica_linha(valor_teste, linha, matriz) &&
         verifica_coluna(valor_teste, coluna, matriz) && 
         verifica_quadrado(valor_teste, linha, coluna, matriz)
        );
}

int matriz_esta_preenchida(casa **matriz) {
  for (int i = 0; i < 9; i++){
    for (int j = 0; j < 9; j++){
      if (matriz[i][j].valor == 0) return 0;
    }
  }
  return 1;
}

int valida_matriz(casa **matriz) {
  int valor;
  for (int i = 0; i < 9; i++){
    for (int j = 0; j < 9; j++){
      if (matriz[i][j].valor != 0) {
        valor = matriz[i][j].valor;
        matriz[i][j].valor = 0;
        if (!valor_se_repete(valor,i,j,matriz)) {
          matriz[i][j].valor = valor;
          return 0;
        }
        matriz[i][j].valor = valor;
      }
    }
  }
  return 1;
}

void zera_possibilidades(casa **matriz) {
  for (int i = 0; i < 9; i++){
    for (int j = 0; j < 9; j++){
      for (int k = 0; k < 9; k++){
        matriz[i][j].possiveis_valores[k] = 0;
      }
    }
  }
}

int numero_de_possibilidades(int possibilidades[9]) {
  int sum = 0;
  for (int i = 0; i < 9; i++){
    sum += possibilidades[i];
  }
  return sum;
}

void copia_matriz(casa **copia, casa **original) {
  for (int i = 0; i < 9; i++){
    for (int j = 0; j < 9; j++){
      copia[i][j].valor = original[i][j].valor;
      for (int k = 0; k < 9; k++){
        copia[i][j].possiveis_valores[k] = original[i][j].possiveis_valores[k];
      }
    }
  }
}