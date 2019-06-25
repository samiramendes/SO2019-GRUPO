// Compilar usando gcc GaussLegendrePthreads.c -o GaussLegendrePthreads -lm -lgmp -lpthread

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gmp.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

void *calc(void *n)
{
    int it = 200; // número de iterações

    // Declaração das variáveis do tipo mpf_t
    mpf_t a, b, t, p;
    mpf_t aux;
    mpf_t aprox, bprox, tprox, pprox;
    mpf_t *pi;

    pi = (mpf_t *)malloc(sizeof(mpf_t)); // pi é alocado na heap

    // Inicialização das variáveis do tipo mpf_t
    mpf_init_set_ui(a, 1);
    mpf_init_set_d(b, 1 / sqrt(2));
    mpf_init_set_d(t, 0.25);
    mpf_init_set_ui(p, 1);

    mpf_init(aux);
    mpf_init(aprox);
    mpf_init(bprox);
    mpf_init(tprox);
    mpf_init(pprox);
    mpf_init(*pi);

    for (int i = 0; i < it; i++)
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
    mpf_add(*pi, a, b);
    mpf_pow_ui(*pi, *pi, 2);

    mpf_mul_ui(aux, t, 4);

    mpf_div(*pi, *pi, aux);

    // gmp_printf("pi: %.6Ff\n", *pi); // Printa o valor de pi

    // Liberação da memória alocada p/ as varáveis do tipo mpf_t
    mpf_clear(a);
    mpf_clear(b);
    mpf_clear(t);
    mpf_clear(p);
    mpf_clear(aux);
    mpf_clear(aprox);
    mpf_clear(bprox);
    mpf_clear(tprox);
    mpf_clear(pprox);

    return pi;
}

pthread_t CallThread(char *name) // Função que cria a thread e retorna o seu id
{
    // Um id e um status são atribuídos a nova thread
    pthread_t thread_id;
    int rstatus;

    printf("Call thread name: %c\n", *name);

    // Criação da thread que chamará a função calc e mandará (void*)name como parâmetro da mesma
    rstatus = pthread_create(&thread_id, NULL, calc, (void *)name);

    if (rstatus != 0)
    {
        // Se status não valer 0, houve um erro na criação da thread
        printf("Erro ao criar o thread %c\n", *name);
        exit(EXIT_FAILURE);
    }
    else
    {
        // Se status valer 0, a thread foi criada com sucesso
        printf("Thread %c iniciada com sucesso!\n", *name);
    }

    return thread_id;
}

void *WaitThread(pthread_t id, char name) // Função que aguarda o resultado calculado pela função que a thread está rodando, o atribui a out e o retorna
{
    printf("Chama o join %c\n", name);
    void *out; // ponteiro auxiliar que recebe o resultado calculado na função que a thread está rodando

    int jstatus = pthread_join(id, &out); // o resultado calculado na thread identificada pelo id é atribuído a out
    printf("Fez o join %c\n", name);

    if (jstatus != 0)
    {
        // Se status não valer 0, houve um erro ao atribuir o resultado da thread a join
        printf("Erro ao dar join %c\n", name);
        exit(EXIT_FAILURE);
    }
    else
    {
        // Se status valer 0, houve um erro ao atribuir o resultado da thread a join
        printf("Thread %c finalizada com sucesso!\n", name);
    }

    return out;
}

int main()
{
    mpf_t pi;

    mpf_init(pi);

    // Nomeação das threads que serão criadas
    char typeA = 'A';
    char typeB = 'B';
    char typeC = 'C';
    char typeD = 'D';

    // Criação das threads juntamente com seus respectivos ids
    pthread_t thread_idA = CallThread(&typeA);
    pthread_t thread_idB = CallThread(&typeB);
    pthread_t thread_idC = CallThread(&typeC);
    pthread_t thread_idD = CallThread(&typeD);

    // O resultado calculado pela função que cada thread está chamando é atribuido a variáveis out
    void *outA = WaitThread(thread_idA, 'A');
    void *outB = WaitThread(thread_idB, 'B');
    void *outC = WaitThread(thread_idC, 'C');
    void *outD = WaitThread(thread_idD, 'D');

    // Como as threads retornam void, é feito um cast em cada saída
    mpf_t *calc_valueA = (mpf_t *)outA;
    mpf_t *calc_valueB = (mpf_t *)outB;
    mpf_t *calc_valueC = (mpf_t *)outC;
    mpf_t *calc_valueD = (mpf_t *)outD;

    // gmp_printf("A: %6Ff\n", *calc_valueA);
    // gmp_printf("B: %6Ff\n", *calc_valueB);
    // gmp_printf("C: %6Ff\n", *calc_valueC);
    // gmp_printf("D: %6Ff\n", *calc_valueD);

    // É feita uma média dos resultados de pi calculados em cada thread
    mpf_add(pi, *calc_valueA, *calc_valueB);
    mpf_add(pi, pi, *calc_valueC);
    mpf_add(pi, pi, *calc_valueD);

    mpf_div_ui(pi, pi, 4);

    gmp_printf("pi: %6Ff\n", pi);

    // Liberação do espaço de memória antes alocado
    mpf_clear(pi);

    free(calc_valueA);
    free(calc_valueB);
    free(calc_valueC);
    free(calc_valueD);
}
