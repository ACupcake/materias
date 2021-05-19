#include <stdio.h>

int main(int argc, char const *argv[])
{
	FILE *fptr = fopen(argv[1], "r");

	if(!fptr)
		exit(1);
	
	/**ler especificacoes pagina 2 para frente**/

	


	fclose(fptr);

	return 0;
}