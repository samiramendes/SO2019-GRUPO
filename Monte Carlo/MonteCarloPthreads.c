// Compilar usando gcc MonteCarloPthreads.c -o MonteCarloPthreads -lm -lgmp -lpthread

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gmp.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

void *calc(void *n)
{
    mpf_set_default_prec(pow(10, 5)); // Definindo a precisão

    // Inicialização das variáveis
    double x, y;         // Coordenadas do dardo
    double d;            // Distância do dardo ao centro
    int i;               // Auxiliar usada para iteração no for
    int it = 100000000; // Número de iterações

    mpf_t dentro;                        // Número de dardos dentro do círculo
    mpf_t dardos;                        // Número total de dados lançados
    mpf_t *pi;                           // Número calculado de pi
    pi = (mpf_t *)malloc(sizeof(mpf_t)); // pi é alocado na heap

    // Inicialização das variáveis do tipo mpf_t
    mpf_init(dentro);
    mpf_init(dardos);
    mpf_init(*pi);

    srand(time(NULL)); // Inicialização do gerador de números aleatórios

    for (i = 0; i < it; i++) // Neste ponto é definido o número de iterações
    {
        // Calcula um ponto (x,y) com coordenadas entre 0 e 1
        x = drand48();
        y = drand48();

        d = sqrt(x * x + y * y); // Calcula a distância do ponto (x,y) até o centro (0,0)

        mpf_add_ui(dardos, dardos, 1);

        if (d <= 1)
        {                                  // Se a distância é menor que 1, o ponto (x,y) pertence ao círculo de raio 1
            mpf_add_ui(dentro, dentro, 1); // dentro++;
        }
    }

    // gmp_printf("dardos: %.6Ff\ndentro: %.6Ff\n", dardos, dentro);

    mpf_mul_ui(dentro, dentro, 4); // 4*dentro/dardos
    mpf_div(*pi, dentro, dardos);

    //Liberação do espaço de memória antes alocado
    mpf_clear(dentro);
    mpf_clear(dardos);

    return pi; // retorna o valor de pi
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

    gmp_printf("A: %6Ff\n", *calc_valueA);
    gmp_printf("B: %6Ff\n", *calc_valueB);
    gmp_printf("C: %6Ff\n", *calc_valueC);
    gmp_printf("D: %6Ff\n", *calc_valueD);

    // É feita uma média dos resultados de pi calculados em cada thread
    mpf_add(pi, *calc_valueA, *calc_valueB);
    mpf_add(pi, pi, *calc_valueC);
    mpf_add(pi, pi, *calc_valueD);

    mpf_div_ui(pi, pi, 4);

    gmp_printf("pi: %6Ff\n", pi);

    // Liberação do espaço de memória antes alocado
    mpf_clear(pi);
}
