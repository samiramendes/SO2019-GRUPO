#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double pi(int n)
{
	double x, y;			 // Coordenadas do dardo.
	double d;				 // Distância do dardo ao centro.
	unsigned int dentro = 0; // Número de dardos dentro do círculo.
	unsigned int dardos = n; // Número total de dados lançados.
	int i;

	srand(time(NULL)); // Inicialização do gerador de n. aleatórios.

	for (i = dardos; i > 0; i--)
	{

		x = drand48(); // Calcula um ponto (x,y) com coordenadas entre 0 e 1
		y = drand48();
		d = sqrt(x * x + y * y);
		if (d <= 1)
		{
			dentro++;
		}
	}
	return (4 * dentro / (double)dardos);
}

int main()
{
	printf("Valor estimado de PI: %lf\n", pi(1000));
	return 0;
}

// Compilar usando gcc MonteCarlo.c -o MonteCarlo -lm