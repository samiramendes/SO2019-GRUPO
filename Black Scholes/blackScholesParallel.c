#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <gmp.h>
#include <unistd.h>
#define myrand ((float)(random())/(float)(RAND_MAX))
#define num_threads 4


    /*variáveis de entrada 
    S - valor da ação 
    E - preço de exercício da opçao
    r - taxa de juros livre de risco (SELIC)
    sigma - volatilidade da ação
    T - tempo de validade da opçao
    M - número de iterações */

    /* entradas globais */ 

    

    double trials[100000];
    
    int M;
    double S, E, r, sigma, T;

    /* entradas */
    /*
    S = 100;
    E = 110;
    r = 10;
    sigma = 1;
    T = 1;
    M = 100000;
    */


void *black_scholes (void *index);

void main (){
    /* Cálculo através de Black Scholes pela simulação Monte Carlo*/
    /* Serão determinadas as variáveis do problema, em seguida será lido um arquivo entrada_blackscholes.txt onde contém todos esses dados das variáveis,
    tendo os dados serao feitos os cálculos e a saída será escrita no arquivo saida_blackscholes.txt */


    //Declaração das threads
    pthread_t thread_name[num_threads];  // ID das threads

    scanf("%lf %lf %lf %lf %lf %d", &S, &E, &r, &sigma, &T, &M );

    int *id;
    for(int i = 0; i < num_threads; i++){
        id = (int *)malloc(sizeof(int));
        *id = i;

        pthread_create(&thread_name[i], NULL, black_scholes, id);
    }

    for (int i = 0; i< num_threads ; i++){
	    // espera que as threads terminem
	    pthread_join (thread_name[i], NULL);
    }	


     /* Cálculo do Intervalo de Confiança */
    double somatorio= 0;
    for(int i = 0; i < M; i++){
        somatorio += trials[i];
        // printf(" %lf \n", somatorio);
    }
    // printf("somat %lf \n", somatorio);
    double media = somatorio/(double)M;
    // printf("media = %lf \n", media);
    double desvio_padrao;
    for(int i = 0; i < M; i++){
        somatorio += pow((trials[i] - media), 2.0);
    }
    // printf("somatorio %lf \n", somatorio);
    desvio_padrao = sqrt(somatorio/(double)M);
    // printf("stddev %lf \n", desvio_padrao);

    double conf_width = 1.96*desvio_padrao*pow(sqrt(M),-1);
    // printf("conf_width %lf \n", conf_width);
    double conf_max = media + conf_width;
    double conf_min = media - conf_width;
    // printf("conf_min %lf -- conf_max %lf\n", conf_min, conf_max);


    /* saida */
    printf("S     %lf\n", S);
    printf("E     %lf\n", E);
    printf("r     %lf\n", r);
    printf("sigma %lf\n", sigma);
    printf("T     %lf\n", T);
    printf("M     %d\n", M);
    printf("Confidence interval: (%lf, %lf)\n", conf_min, conf_max);

    
}

void *black_scholes(void *index){

    srand(time(NULL)); //garantia de aleatoriedade
    int thread_index = *((int*) index);
    // printf("inicio %d indice\n", thread_index);

    int m_fraction = M/num_threads;
    // printf("m_fraction %d\n", m_fraction);

    double t;
    for(int i = ((thread_index)*m_fraction); i < ((thread_index+1)*m_fraction); i++){
        /*
        Imprecisao de 4% -- myrand - 0.04
        */
        double expoente = T*(r - (0.5)*pow(sigma,2.0)) + sigma*sqrt(T)*(myrand);
        // printf("expoente %lf \n", expoente);
        t = S*exp(expoente);
        // printf("%d  %lf  \n",i, t);
        trials[i] = exp((-1)*r*T)*fmax(t-E, 0);
        // printf(" %lf \n", trials[i]);
    }
    // printf("fim indice --  %d \n", thread_index);
    pthread_exit(0);
}