/*
O programa calcula a espera media dos pacientes na fila de atendentes e quanto esperaram mais que
10 minutos. Um vetor 'vet_client' tem n linhas com o numero de atendentes representando as filas
e x colunas com os dados de cada paciente, a primeira tem o tempo de chegada, a segunda o tempo de
atendimento e a terceira o tempo de espera para ser atendido.
O programa compara o paciente atual com os que estao sendo atendidos e decide em qual fila o mesmo
deve escolher para o menor tempo de espera. No fim eh mostrado a media de espera e quem esperou
mais de 10 minutos.
*/

#include <stdio.h>

//zera matriz de valores
int zera_vet(int vet[][3], int atendente)
{
	int i, j;
	for (i = 0; i<=atendente; i++)
		for (j = 0; j<2; j++)
			vet[i][j]=0;
	return 0;
}

int main()
{
	unsigned int n_atendentes, n_clientes, t_chegada, t_atendimento;
	unsigned int sum_med = 0, espera10 = 0, isave=0, check=1;
	unsigned int menor, cliente, i;
	int ocupado=0;

	scanf("%d", &n_atendentes); scanf("%d", &n_clientes);
	int vet_client[n_atendentes+1][3];
	zera_vet(vet_client, n_atendentes+1);

	//percorre todos os clientes
	for(cliente = 0; cliente<n_clientes; cliente++)
	{	
		scanf("%d", &t_chegada); scanf("%d", &t_atendimento);
		//coloca cliente em vaga nao ocupada
		if (n_atendentes>ocupado)
		{
			vet_client[ocupado][0]=t_chegada; //coluna 0 contem o tempo de chegada do cliente
			vet_client[ocupado][1]=t_atendimento; //coluna 1 contem o tempo de atendimento
			vet_client[ocupado][2]=0; //coluna 2 contem o tempo de espera
			ocupado++;
		}
		else
		{
			//verifica qual eh o menor tempo entre os atendentes e coloca o cliente na filas
			menor=t_chegada+t_atendimento+vet_client[0][0]+vet_client[0][1];
			isave=0; check=1;

			for (i = 0; i < n_atendentes; i++)
			{
				//verifica se a diferenca dos horarios de chegada eh maior ou igual ao tempo de espera
				if ((t_chegada-vet_client[i][0])>=(vet_client[i][1]+vet_client[i][2]) && check)
				{	
					//coloca atual cliente em vaga livre
					vet_client[i][0]=t_chegada;
					vet_client[i][1]=t_atendimento;
					vet_client[i][2]=0;
					check=0;
				}
				//verifica qual cliente vai sair primeiro se nenhuma vaga estiver livre
				else if(menor>=vet_client[i][1]+vet_client[i][2]-(t_chegada-vet_client[i][0]))
				{
					menor=vet_client[i][1]+vet_client[i][2]-(t_chegada-vet_client[i][0]); //menor espera
					isave=i; //posicao do cliente que vai sair primeiro
				}

			}

			if (check) //soma tempo extra a cliente que vai ter que esperar
			{
				vet_client[isave][2]=vet_client[isave][1]+vet_client[isave][2]-(t_chegada-vet_client[isave][0]);
				vet_client[isave][0]=t_chegada;
				vet_client[isave][1]=t_atendimento;
				sum_med+=vet_client[isave][2]; //soma das esperas //2 vezes
			}

			if (vet_client[isave][2]>10) //conta clientes que esperaram mais do que 10 minutos
				espera10++;
		}
	}

	float temp = sum_med;
	printf("Espera media para %d clientes: %.1f minutos\n", n_clientes, temp/n_clientes);
	printf("Numero de clientes que esperaram mais que 10 minutos: %d\n", espera10);
}
