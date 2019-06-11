#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gmp.h>
#include <string.h>
#include <time.h>

void main ()) {

    // Inicialização das variáveis
    int i;
    int n=1000000; 

    mpf_t pi;
    mpf_t aux;
    mpf_t a;
    mpf_t b;
    mpf_t c;
    mpf_t d;
    mpf_t e;
    
   for (i = 0; i < n; i++){

       // a = 8*i + 1;
       mpf_mul_ui(a,a,i);
       mpf_add_ui(a,a,1);
       // b = 8*i + 4;
       mpf_mul_ui(b,b,i);
       mpf_add_ui(b,b,4);
       // c = 8*i + 5;
       mpf_mul_ui(c,c,i);
       mpf_add_ui(c,c,5);
       // d = 8*i + 6;
       mpf_mul_ui(d,d,i);
       mpf_add_ui(d,d,1);
       // e = pow(16,i);
       
       
       aux = (1/e)*((4/a) - (2/b) - (1/c) - (1/d));
       pi = pi + aux;
   }
    gmp_printf("pi: %.6Ff\n",pi); // Printa o valor de pi
}