/**
O programa realiza uma serie de funcoes em uma agenda de contatos, entre elas
adicionar, remover, buscar e mostrar a lista.
**/

#include <stdio.h>
#include <string.h>

struct contato
{
	char nome[55];
	char endereco[105];
	char telefone[17];
	char aniversario[15];
};

//remove quebra de linha se existir (remove carriage return)
void remove_enter(char *linha)
{
	int i;
	for(i=0; linha[i]!='\0'; i++);
	i--;
	if(linha[i]==13)
		linha[i]='\0';
}

void insere(struct contato *contatos, int cnt)
{
	char entra[100];
	
	scanf(" %[^\n]", entra);
	remove_enter(entra);
	strcpy(contatos[cnt].nome, entra);

	scanf(" %[^\n]", entra);
	remove_enter(entra);
	strcpy(contatos[cnt].endereco, entra);

	scanf(" %[^\n]", entra);
	remove_enter(entra);
	strcpy(contatos[cnt].telefone, entra);

	scanf(" %[^\n]", entra);
	remove_enter(entra);
	strcpy(contatos[cnt].aniversario, entra);
	
	printf("Contato para %s inserido.\n", contatos[cnt].nome);
	printf("\n");
}

void busca(struct contato *contatos, int cnt)
{
	char entra[105];
	int verifica=0;

	scanf(" %[^\n]", entra); getchar();
	remove_enter(entra);

	printf("Resultado da busca:");
	
	for (int i = 0; i < cnt; ++i)
		if (strstr(contatos[i].nome, entra)) //procura substring
		{
			printf("\n(%d) %s	%s	%s	%s\n", i+1, contatos[i].nome, contatos[i].endereco, contatos[i].telefone, contatos[i].aniversario);
			verifica=1;
		}

	if(!verifica) //se nenhum nome eh encontrado exibe a mensagem
		printf("\nNenhum contato.\n");
	printf("\n");
}

//move lista de contatos uma posicao para tras
void move(struct contato *contatos, int posicao, int n_contatos)
{
	int i;
	for (i = posicao; i < n_contatos; ++i)
		contatos[i]=contatos[i+1];
}

int remover(struct contato *contatos, int cnt)
{
	char nome[55];
	int removidos=0;

	scanf(" %[^\n]", nome);
	remove_enter(nome);

	for (int i = 0; i < cnt-removidos; ++i)
		if(strcmp(contatos[i].nome, nome)==0)
		{
			move(contatos, i, cnt-removidos);
			removidos++;
			i--; //volta para testar o novo contato na posicao i
		}

	printf("Contatos de %s removidos: %d.\n", nome, removidos);
	printf("\n");
	return (cnt-removidos);
}

void imprime(struct contato *contatos, int cnt)
{	
	printf("Listagem:\n");
	if(cnt)
		for (int i = 0; i < cnt; ++i)
			printf("(%d) %s	%s	%s	%s\n", i+1, contatos[i].nome, contatos[i].endereco, contatos[i].telefone, contatos[i].aniversario);
	else
		printf("Nenhum contato.\n");
	printf("\n");
}

int main()
{
	struct contato contatos[1005];
	char entrada=0;
	int contador=0;

	while(entrada!='f')
	{
		entrada=getchar();
		switch(entrada)
		{
			case 'i':
				insere(contatos, contador);
				contador++;
				break;
			case 'r':
				contador=remover(contatos, contador);
				break;
			case 'b':
				busca(contatos, contador);
				break;
			case 'p':
				imprime(contatos, contador);		
				break;
		}
	}
	return 0;
}