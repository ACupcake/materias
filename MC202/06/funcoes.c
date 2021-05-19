/**
Arquivo com funcoes utilizadas no programa principal
**/

#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

//inicializa uma lista vazia
array *initialize(void)
{
	return NULL;
}

//coloca valores de 1 a n na lista
array* setarray(array *numbers, int n)
{
	for (int i = n; i > 0; --i)
		numbers = insert(numbers, i);
	return numbers;
}

//limpa lista
array* clean(array *actual)
{
	array *pointer=actual; //set a pointer to help the cleaning

	while(pointer!=NULL)
	{
		array *temp = pointer->next; //points to the next array
		free(pointer);
		pointer=temp;
	}
	return NULL;
}

//insere valor 'num' no inicio da lista
array* insert (array *last, int num)
{
	array* new = (array*) malloc(sizeof(array));

	new->number = num;
	new->count = 0;
	new->next = last;
	return new;
}

//move valores em 'location' para o inicio da lista
array* move_to_front(array *numbers, array *location, array *follow)
{	
	array *first=numbers;
	
	follow->next=location->next; //follow eh o valor anterior a 'location'
	numbers=location; //o primeiro valor recebe 'location'
	numbers->next=first; //o primeiro agora eh location

	return numbers;
}

//troca valores em 'location' e seu antecessor
array* transpose(array *numbers, array *location, array *follow)
{	
	array *aux=numbers;

	if(aux==follow)
	{
		numbers=location;
		aux->next=location->next;
		numbers->next=aux;
	}
	else
	{
		while(aux->next!=follow)
			aux=aux->next;
		aux->next=location;
		follow->next=location->next;
		location->next=follow;
	}
	return numbers;
}

//troca valores em 'location' se este foi chamado mais vezes que algum de seus antecessores
array* count(array *numbers, array *location, array *follow)
{	
	array *aux=numbers, *previous;
	int i;

	for (i = 0; aux->number != location->number; ++i)
	{
		if(location->count>=aux->count)
		{
			follow->next=location->next; //apontador anterior a 'location' aponta para o valor posterior a 'location'
			location->next=aux; //'location' aponta para o valor com contador menor ou igual ao memso
			if(i==0)
				numbers=location; //o inicio vai para 'location'
			else
				previous->next=location; //o inicio vai para o valor com o ultimo maior contador
			return numbers;
		}
		previous=aux;
		aux=aux->next;
	}

	return numbers;
}

//teste todos os valores da entrada chamando a funcao especificada como 'change'
int loop_values(array *numbers, int n, int *find, int r, array* (*change)(array*, array*, array*))
{
	int i, j, sum=0;
	array *pointer, *follow;

	for (j = 0; j < r; ++j)
	{
		pointer=numbers;
		follow=initialize();
		for (i = 0; i < n; ++i)
		{
			if(pointer->number == find[j])
			{
				pointer->count+=1;
				if(i != 0)
					numbers=change(numbers, pointer, follow);		
				sum+=i+1;
			}
			follow=pointer;
			pointer=pointer->next;
		}
	}

	return sum;
}
