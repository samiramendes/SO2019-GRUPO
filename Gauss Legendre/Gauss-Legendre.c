#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double pi(int n)
{
    double a, b, t, p;
    double pi, aux;
    double aprox, bprox, tprox, pprox;

    a = 1; // a0 = 1
    b = 1 / sqrt(2); // b0 = 1/sqrt(2)
    t = 0.25; // t0 = 0.25
    p = 1; // p0 = 1

    for (int i = 0; i < n; i++)
    {
        aprox = (a + b) / 2; // a(n+1) = (a(n)+b(n))/2
        bprox = sqrt(a * b); // b(n+1) = sqrt(b(n)*a(n))
        aux = a - aprox;
        tprox = t - (p * pow(aux, 2)); // t(n+1) = t(n)-p(n)*(a(n)-a(n+1))²
        pprox = 2 * p;                 // p(n) = 2*p(n-1)

        // os valores de a,b,t e p são atualizados
        a = aprox;
        b = bprox;
        t = tprox;
        p = pprox;
    }
    pi = pow(a + b, 2) / (4 * t);

    return pi;
}

int main (){
    printf("pi: %f\n",pi(1000));
    return 0;    
}
