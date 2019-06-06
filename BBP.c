#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double pi(int n) {
    int i;
    double pi;
    double aux;
    double a,b,c,d,e;
   for (int i=0;i<n;i++){
       a = 8*i + 1;
       b = 8*i + 4;
       c = 8*i + 5;
       d = 8*i + 6;
       e = pow(16,i);
       aux = (1/e)*((4/a) - (2/b) - (1/c) - (1/d));
       pi = pi + aux;
   }
   return pi;
}

int main(){
    printf("%f", pi(10));
    getchar();
}