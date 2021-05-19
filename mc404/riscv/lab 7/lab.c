//requisitos
//[*] Coordenada inicial não deve ser impressa
//[*] L-1 linhas devem ser impressas
//[*] Valores dos sensores acima de 100 são considerados linhas brancas

int decidir(int carPos, int sizeX) {
	int entrada;
	int xmin;
	int xmax;
	int pegouMin = 0;
	int pegouMax = 0;

	for(int i = 0; i < sizeX; i++) {
		scanf("%d ", &entrada);
		if(entrada <= 100 && pegouMin == 0) {
			xmin = i;
			pegouMin = 1;
		}
		if(entrada > 100 && pegouMin == 1 && pegouMax == 0) {
			xmax = i;
			pegouMax = 1;
		}
	}

	if((carPos - xmin) + carPos > xmax)
		return -1;
	if((carPos - xmin) + carPos < xmax)
		return 1;
	return 0
}

int main() {
	x, y = ler_linha() 	// Le a primeira linha com os valores de xi, yi
	ler_linha() 		// Linha ‘P2’ deve ser ignorada
	L, C = ler_linha()	// Le a linha com os valores de L e C
	CMAX = ler_linha() 	// Le a linha com o valor de CMAX
	ler_linha() 		// Ignora a primeira linha (y=0)

	while(y < L-1)
		sensores = ler_linha()	// Lê uma linha com os valores dos sensores
		dir = decidir(sensores) // Decide se vai para esquerda, direita ou 
								// mantém-se no centro. Decidir retorna -1       
								// (esquerda), 1 (direita) ou 0 (centro)
		y = y+1					// Incrementa y em 1
		x = x+dir				// Incrementa x com -1, 0 ou 1
		imprimir_pos(x, y)		// Imprime a nova posição
}