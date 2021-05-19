/**
Arquivo com declaracoes e structs
**/

struct valor{
	int id;
	char texto[255];
	int removido;
};

struct hash{
	int ocupado, TAMANHO;
	struct valor **valores;
};

typedef struct valor Lista;
typedef struct hash Hash;

int Buscar_Hash(Hash *nova_hash, char *texto);

int Inserir_Hash(Hash *nova_hash, char *texto, int id);

int Remover_Hash(Hash *nova_hash, char *texto);

unsigned long djb2(char *str);

void Limpa_Memoria(Hash *nova_hash);

Hash *Inicializa_Hash(int tamanho);