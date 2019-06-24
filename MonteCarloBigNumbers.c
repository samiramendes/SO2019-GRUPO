// Compilar usando gcc MonteCarloBigNumbers.c -o MonteCarloBigNumbers -lm -lgmp

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gmp.h>
#include <string.h>
#include <time.h>

void main()
{
	mpf_set_default_prec(pow(10, 5)); // Definindo a precisão

	// Inicialização das variáveis
	double x, y;	 // Coordenadas do dardo
	double d;		 // Distância do dardo ao centro
	int i;			 // Auxiliar usada para iteração no for
	int n = 1000000; // Número de iterações

	mpf_t dentro; // Número de dardos dentro do círculo
	mpf_t dardos; // Número total de dados lançados
	mpf_t pi;	 // Número calculado de pi

	mpf_init(dentro);
	mpf_init(dardos);
	mpf_init(pi);

	srand(time(NULL)); // Inicialização do gerador de números aleatórios

	for (i = 0; i < n; i++) // Neste ponto é definido o número de iterações
	{
		x = drand48(); // Calcula um ponto (x,y) com coordenadas entre 0 e 1
		y = drand48();

		d = sqrt(x * x + y * y); // Calcula a distância do ponto (x,y) até o centro (0,0)

		mpf_add_ui(dardos, dardos, 1);

		if (d <= 1)
		{								   // Se a distância é menor que 1, o ponto (x,y) pertence ao círculo de raio 1
			mpf_add_ui(dentro, dentro, 1); // dentro++;
		}
	}

	gmp_printf("dardos: %.6Ff\ndentro: %.6Ff\n", dardos, dentro);

	mpf_mul_ui(dentro, dentro, 4); // 4*dentro/dardos
	mpf_div(pi, dentro, dardos);

	gmp_printf("pi: %.6Ff\n", pi); // Printa o valor de pi

	// Liberação do espaço de memória antes alocado
	mpf_clear(dentro);
	mpf_clear(dardos);
	mpf_clear(pi);
}

