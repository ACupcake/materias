/*

O programa recebe um conjunto de palavras chave e frases na entrada e realiza
uma comparacao caractere a caractere. O retorno eh a ou as frases que tem
o maior numero de ocorrencias do conjunto de palavras chave.
*/

#include <stdio.h>

//encontra o maior numero armazenado em na segunda coluna de contador
int acha_maior(char contador[100][100])
{
	int maior=0;
	for (int i = 0; i < 100; ++i)
		if (contador[i][1]>maior)
			maior=contador[i][1];
	return maior;
}

//verifica a existencia das palavras chave nas frases
void comparador(char desculpas[100][100], char chave[20][20], int n_palavra, int n_frase, char contador[100][100])
{
	int letra_frase = 0, letra_palavra = 0, palavra, frase;

	for (frase = 0; frase < n_frase; ++frase)
	{
		contador[frase][0] = frase; //coloca o indice da frase no contador
		for (palavra = 0; palavra < n_palavra; ++palavra)
		{
			while(desculpas[frase][letra_frase]!='\0')
			{
				//verifica se a palavra atual da chave existe na frase atual
				if (chave[palavra][letra_palavra] == desculpas[frase][letra_frase] || chave[palavra][letra_palavra] == (desculpas[frase][letra_frase]+32))
				{
					if (chave[palavra][letra_palavra+1] == '\0')// se achar o fim da palavra conta +1
						contador[frase][1]++; //guarda o numero de palavras na frase de indice 'frase'
					letra_palavra++;
				}
				else
					letra_palavra = 0; //o conta letra se a proxima letra for diferente
				letra_frase++;
			}
			letra_frase = 0;
		}
	}
}

void zera(int n, char vetor[n][n])
{
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			vetor[i][j]=0;
}

int main()
{
	char desculpas[100][100], chave[20][20], contador[100][100]={ 0 }, c;
	int k, e, palavra, frase, letra, maior=0, vez=1, check=1;

	while(check)
	{
		scanf("%d %d", &k, &e);
		
		for (palavra = 0; palavra < k; palavra++)
			scanf("%s", chave[palavra]);

		if ((c=getchar())==EOF) //pula linha na leitura e finaliza
			break;

		//le frases
		for (frase = 0; frase < e; frase++)
		{
			letra=-1;
			do
			{
				letra++;
				desculpas[frase][letra]=getchar();
				if (desculpas[frase][letra]==EOF)
					check=1;
			}
			while(desculpas[frase][letra]!='\n' && desculpas[frase][letra]!=EOF);
		}

		comparador(desculpas, chave, k, e, contador);
		maior=acha_maior(contador);

		frase=0;
		printf("Conjunto de desculpas #%d\n", vez);
		if (maior!=0)
			while (contador[frase][0]!=0 || frase==0)
			{
				if (contador[frase][1]==maior)
					printf("%s", desculpas[contador[frase][0]]);
				frase++;
			}
		printf("\n");

		maior=0;
		zera(100, contador);
		zera(100, desculpas);
		zera(20, chave);
		vez++;
	
	}
	return 0;
}
