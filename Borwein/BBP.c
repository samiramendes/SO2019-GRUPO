#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double pi(int n)
{
    // Declaração das variáveis
    int i;
    double pi;
    double aux;
    double a, b, c, d, e;

    for (int i = 0; i < n; i++)
    {
        // pi = somatório de k=0 até infinito de (1/16^k)*((4/(8*k+1))-(2/(8*k+4))-(1/(8*k+5))-(1/(8*k+6)))
        a = 8 * i + 1;
        b = 8 * i + 4;
        c = 8 * i + 5;
        d = 8 * i + 6;
        e = pow(16, i);
        aux = (1 / e) * ((4 / a) - (2 / b) - (1 / c) - (1 / d));
        pi = pi + aux;
    }
    return pi;
}

int main()
{
    printf("%f\n", pi(100000000));
    return 0;
}
