#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gmp.h>

int main()
{
    int n = 200; // número de iterações

    // Declaração das variáveis do tipo mpf_t
    mpf_t a, b, t, p;
    mpf_t pi, aux;
    mpf_t aprox, bprox, tprox, pprox;

    // Inicialização das variáveis do tipo mpf_t
    mpf_init_set_ui(a, 1);
    mpf_init_set_d(b, 1 / sqrt(2));
    mpf_init_set_d(t, 0.25);
    mpf_init_set_ui(p, 1);

    mpf_init(pi);
    mpf_init(aux);
    mpf_init(aprox);
    mpf_init(bprox);
    mpf_init(tprox);
    mpf_init(pprox);

    for (int i = 0; i < n; i++)
    {
        // a(n+1) = (a(n)+b(n))/2
        mpf_add(aprox, a, b);
        mpf_div_ui(aprox, aprox, 2);

        // b(n+1) = sqrt(b(n)*a(n))
        mpf_mul(bprox, b, a);
        mpf_sqrt(bprox, bprox);

        // t(n+1) = t(n)-p(n)*(a(n)-a(n+1))²
        mpf_sub(tprox, a, aprox);    // a(n)-a(n+1)
        mpf_pow_ui(tprox, tprox, 2); // (a(n)-a(n+1))²
        mpf_mul(tprox, p, tprox);    // p(n)*(a(n)-a(n+1))²
        mpf_sub(tprox, t, tprox);    // t(n)-p(n)*(a(n)-a(n+1))²

        // p(n) = 2*p(n-1)
        mpf_mul_ui(pprox, p, 2);

        // os valores de a,b,t e p são atualizados
        mpf_add_ui(a, aprox, 0);
        mpf_add_ui(b, bprox, 0);
        mpf_add_ui(t, tprox, 0);
        mpf_add_ui(p, pprox, 0);
    }

    // pi = (a(n-1)+b(n-1))²/4*t(n-1)
    mpf_add(pi, a, b);
    mpf_pow_ui(pi, pi, 2);

    mpf_mul_ui(aux, t, 4);

    mpf_div(pi, pi, aux);

    gmp_printf("pi: %.6Ff\n", pi); // Printa o valor de pi

    // Liberação da memória alocada p/ as varáveis do tipo mpf_t
    mpf_clear(a);
    mpf_clear(a);
    mpf_clear(b);
    mpf_clear(t);
    mpf_clear(p);
    mpf_clear(pi);
    mpf_clear(aux);
    mpf_clear(aprox);
    mpf_clear(bprox);
    mpf_clear(tprox);
    mpf_clear(pprox);

    return 0;
}
