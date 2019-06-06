#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//funções usadas no algoritmo
double a(int n);
double b(int n);
double t(int n);
double p(int n);

double a(int n){
    if(n==0){
        return 1;
    }
    else{
        return(a(n-1)+b(n-1))/2;
    }
}

double b(int n){
    if(n==0){
        return 1/sqrt(2);
    }
    else{
        return sqrt(a(n-1)*b(n-1));
    }
}

double p(int n){
    if(n==0){
        return 1;
    }
    else {
        return 2*p(n-1);
    }
}

double t(int n){
    if(n==0){
        return 0.25;
    }
    else{
        return t(n-1)-p(n-1)*pow(a(n-1)-a(n),2);
    }
}

double pi(int n){
    return pow(a(n)+b(n),2)/(4*t(n));
}

int main(){
    printf("%f", pi(10));
    getchar();
}

