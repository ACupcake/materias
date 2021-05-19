#include "api_car.h"

/*
 * O código lê a claridade da pista e, baseado nisso,
 * decide para onde o carro deve ir.
*/
void esperaUmPouco(int time) {
	int t_inicial = get_time();
	int t_final = get_time();
	while(t_final - t_inicial < time)
		t_final = get_time();
}

void user_code(void) {
	unsigned char claridade_pista[256];
	char sentido = 1;
	int driving = 1;

	int direita, esquerda;
	int meio = 128; /* Metade do vetor de claridade (256) */
	int lado;

	int t_inicial = get_time();
	int t_final = get_time();

	while(driving) {
		read_sensors(claridade_pista);
		direita = meio;
		esquerda = meio;

		/* Lê até encontrar faixa clara ou o fim do vetor */
		while(claridade_pista[esquerda] < 170 && esquerda > 0)
			esquerda--;
		while(claridade_pista[direita] < 170 && direita < 256)
			direita++;

		/* Vê qual lado demorou mais para encontrar faixa clara */
		direita = direita - meio; 	  // quanto moveu para direita
		esquerda =  meio - esquerda; // quanto moveu para esquerda
		lado = direita - esquerda; 	// para onde virar

		/* Verifica se valores estao no intervalo */
		if(lado < -125)
			lado = -125;
		else if(lado > 125)
			lado = 125;

		set_motor(sentido, lado);

		t_final = get_time();
		if(sentido && (t_final - t_inicial) > 400) {
			t_inicial = get_time();
				sentido = 0;
				set_handbreak(1);
		} else if((t_final - t_inicial) > 850)  {
			t_inicial = get_time();
			sentido = 1;
			set_handbreak(0);
		}
	}
}