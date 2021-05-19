/**
Arquivo com declaracao de funcoes e struct utilizado.
**/

struct numbers
{
	int number; //numero entre 1 a n 
	int count; //contador de consultas do valor atual 
	struct numbers *next; //apontador para proxima posicao do struct
};
typedef struct numbers array;

array* setarray(array *numbers, int n); //coloca valores de 1 a n na lista

array *clean(array *actual); //limpa a lista

array *initialize(void); //retorna uma lista com valor null

array* insert (array *last, int num); //insere valores na lista

 //faz teste em todos os valores e retorna numero de tarefas feitas
int loop_values(array *numbers, int n, int *find, int r, array* (*change)(array*, array*, array*));

//move valor da lista para primeira posicao
array* move_to_front(array *numbers, array *location, array *follow);

//move valor para proxima posicao em direcao ao inicio
array* transpose(array *numbers, array *location, array *follow);

//move valor se o mesmo for consultado mais vezes que outros
array* count(array *numbers, array *location, array *follow);
