#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double a(int n);
double b(int n);
double c(int n);
double d(int n);
double e(int n);
double pi(int n);

double a(int n){
    return 4/(8*n+1);
}

double b(int n){
    return 2/(8*n+4);
}

double c(int n){
    return 1/(8*n+5);
}

double d(int n){
    return 1/(8*n+6);
}

double e(int n){
    return (1/pow(16,n))*(a(n)-b(n)-c(n)-d(n));
}

/*double pi(int n) {
    if(n==0){
        return 3.3-1/6;
    }
    else{
        return e(n)+e(n-1);
    }
}
*/

double pi(int n) {
    double pi;
   for (int i=0;i++;i<n){
       pi= pi+((1/pow(16,i))*(a(i)-b(i)-c(i)-d(i)));
   }
   return pi;
}

int main(){
    printf("%f", pi(10));
    getchar();
}