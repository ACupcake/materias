/*
16/08/2019
O programa, apos receber a entrada, percorre a matriz somando todos os valores de cada coluna
de linhas de tamanho r, apos alcancar um numero 's' de colunas o programa subtrai a primeira
coluna de linhas da submatriz anterior e soma a proxima. Ao chegar a n colunas, os valores
sao zerados e comecamos a somar a proxima submatriz.
A saida eh a maior soma
*/
#include <stdio.h>

int main()
{
	unsigned int n, m, r, s, i, j, k;
	unsigned int soma=0, maior=0, cnt=0, soma_sub=0;
	
	//recebe valores de entrada e declara o necessario
	scanf("%d %d %d %d", &n, &m, &r, &s);
	int matriz[n][m];
	
	for(i=0;i<n;i++)
		for(j=0;j<m;j++)
			scanf("%d", &matriz[i][j]);
	maior=matriz[0][0];

	//percorre as linhas da matriz ate n-r+1
	//e suas colunas ate m
	for (i=0;i<n-r+1;i++)
	{
		soma=0; soma_sub=0; cnt=0;
		for(j=0;j<m;j++)
		{
			//contador para iniciar a subtracao da primeira coluna na submatriz
			cnt++;

			//soma colunas
			for(k=0;k<r;k++)
				soma=soma+matriz[i+k][j];

			//soma primeira coluna na submatriz
			if(cnt>s)
				for(k=0;k<r;k++)
					soma_sub=soma_sub+matriz[i+k][j-s];

			//subtrai a primeira coluna da submatriz anterior
			soma=soma-soma_sub;
			soma_sub=0;

			//verifica se a soma atual eh maior que a maior soma anterior
			if(soma>maior)
				maior=soma;
		}
	}
	printf("%d\n", maior);
}
