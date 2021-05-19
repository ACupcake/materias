#include "api_car.h"

/*
 * O código lê a claridade da pista e, baseado nisso,
 * decide para onde o carro deve ir.
*/
int distancia(int x_car, int x_destino, int distanciaMax) {
	int distancia = x_car - x_destino;
	if(distancia < 0)
		distancia *= -1;
	return (distancia <= distanciaMax);
}

int dirigir_carro_para(int x_destino, int y_destino, int z_destino) {
	unsigned char claridade_pista[256];
	char sentido = 1;
	int driving = 1;

	int direita, esquerda;
	int meio = 128; /* Metade do vetor de claridade (256) */
	int lado;

	int t_inicial = get_time();
	int t_final = get_time();

	int* x_car;
	int* y_car;
	int *z_car;

	while(driving) {
		read_sensors(claridade_pista);
		direita = meio;
		esquerda = meio;

		/* Lê até encontrar faixa clara ou o fim do vetor */
		while(claridade_pista[esquerda] < 170 && esquerda > 0)
			esquerda--;
		while(claridade_pista[direita] < 170 && direita < 256)
			direita++;

		/* Encontra qual lado demorou mais para encontrar faixa clara */
		direita = direita - meio; 	  // quanto moveu para direita
		esquerda =  meio - esquerda; // quanto moveu para esquerda
		lado = direita - esquerda; 	// para onde virar

		/* Verifica se valores estao no intervalo */
		if(lado < -125)
			lado = -125;
		else if(lado > 125)
			lado = 125;

		if(sentido == 1){
			set_motor(sentido, lado);	
		} else if(sentido == 0) {
			get_position(x_car, y_car, z_car);
			if(x_car > x_destino)
				set_motor(sentido, 120);
			else if(x_car < x_destino)
				set_motor(sentido, -120);

			if(distancia(x_car, x_destino, 20))
				if(distancia(y_car, y_destino, 20))
					if(distancia(z_car, z_destino, 20))
						driving = 0;
		}

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
	return 1;
}

void user_code(void) {
	dirigir_carro_para(-17, 1, 12);
	dirigir_carro_para(141, 1, 8);
	dirigir_carro_para(290, 1, 203);
}