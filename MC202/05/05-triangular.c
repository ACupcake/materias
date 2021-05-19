/**

O programa deve fazer uma matriz irregular de formato triangular inferior.
Para isso eh utilizado alocacao dinamica na matriz 'aponta'.
A saida deve ser o resultado de algumas funcoes matematicas aplicadas
na matriz triangular.
**/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double media(double **valores, int n, double elementos)
{
	double media=0;
	int i, j;

	for (i = 0; i < n; ++i)
		for (j = 0; j < i+1; ++j)
			media+=*(valores[i]+j);

	media=media/elementos;
	return (media);
}

double desvio(double **valores, int n, double elementos, double media)
{
	double desvio=0, temp;
	int i, j;

	for (i = 0; i < n; ++i)
		for (j = 0; j < i+1; ++j)
		{
			temp=*(valores[i]+j)-media;
			desvio+=temp*temp;
		}
	desvio=desvio/elementos;
	return (sqrt(desvio));
}

double formula(double valor, double media, double desvio)
{
	return (valor-media)/desvio;
}

int main()
{
	int n, endereco, deslocamento, alocado=1;
	double **aponta, n_media, n_desvio, elementos;

	scanf("%d", &n);
	aponta = malloc(n*sizeof(double*)); //aloca espaco para apontadores
	
	for (endereco = 0; endereco < n; ++endereco)
	{
		aponta[endereco] = malloc((endereco+1)*sizeof(double)); //aloca espaco para os valores

		if(!aponta[endereco]) //libera memoria se nao for possivel alocar
		{
			while(aponta)			
				free(aponta[--endereco]);
			free(aponta);
			alocado=0;
			break;
		}

		for (deslocamento = 0; deslocamento < endereco+1; ++deslocamento)
			scanf("%lf", (aponta[endereco]+deslocamento)); //atribui os valores 
	}

	if(alocado)
	{
		elementos=(n*n+n)/2;
		n_media=media(aponta, n, elementos);
		n_desvio=desvio(aponta, n, elementos, n_media);

		for (endereco = 0; endereco < n; ++endereco)
		{
			for (deslocamento = 0; deslocamento < endereco+1; ++deslocamento)
				printf("%.12f ", formula(*(aponta[endereco]+deslocamento), n_media, n_desvio));
			printf("\n");
		}
		printf("\n%.12f %.12f \n", n_media, n_desvio);

		while(n)
			free(aponta[--n]);
		free(aponta);
	}
	return 0;
}
