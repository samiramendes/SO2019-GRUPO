#include <stdio.h>
#include <math.h>
#include <time.h>

double pi(int n)
{
  double x, y;              // Coordenadas do dardo.
  double d;                 // Distância do dardo ao centro.
  unsigned int dentro = 0;  // Número de dardos dentro do círculo.
  unsigned int dardos = n;  // Número total de dados lançados.
  int i; 

  srand(time(NULL));        // Inicialização do gerador de n. aleatórios.

  for (i = dardos; i > 0 ; i--) {
    x = rand() / (double)RAND_MAX; 
    y = rand() / (double)RAND_MAX;
    d = sqrt(x*x + y*y);
    if (d <= 1) {
       dentro++;
    }
  }
  return  (4 * dentro / (double)dardos);
}

int main() {
    printf("Valor estimado de PI: %lf\n",pi(1000));
    return 0;
}