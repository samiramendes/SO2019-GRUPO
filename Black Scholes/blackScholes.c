#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <gmp.h>
#include <time.h>
#define myrand ((float)(random())/(float)(RAND_MAX))


int main (){
    /* Cálculo através de Black Scholes pela simulação Monte Carlo*/
    /* Serão determinadas as variáveis do problema, em seguida será lido um arquivo entrada_blackscholes.txt onde contém todos esses dados das variáveis,
    tendo os dados serao feitos os cálculos e a saída será escrita no arquivo saida_blackscholes.txt */

    /*variáveis de entrada 
    S - valor da ação 
    E - preço de exercício da opçao
    r - taxa de juros livre de risco (SELIC)
    sigma - volatilidade da ação
    T - tempo de validade da opçao
    M - número de iterações */

    srand(time(NULL)); //garantia de aleatoriedade

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
    scanf("%lf %lf %lf %lf %lf %d", &S, &E, &r, &sigma, &T, &M );

    /* Calculo iterado */
    double trials[M];
    double t; //variável temporária

    for (int i = 0; i < M; i++){

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
