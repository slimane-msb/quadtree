#include <stdlib.h>
#include <stdio.h>


#define ISNOT !=
#define NOT !
#define AND &&
#define OR ||
#define then
typedef enum { false, true } bool;

double xr(int n);
double xi(int n);
double xsf(int n);
double xsp(int n);

int main(){
    int n=5;
    printf ("xr(%d)=%lf\n",n, xr(n));
    printf ("xi(%d)=%lf\n",n, xi(n));
    printf ("xsf(%d)=%lf\n",n, xsf(n));
    printf ("xsp(%d)=%lf\n",n, xsp(n));
    return EXIT_SUCCESS; 
}

// recursif ssf ssp 
double xr(int n){
    if (n==0) return 1;
    else{
        double y = xr(n-1);
        return y+2/y;
    }
}


// iteratif: 
double xi(int n){
    double x = 1; 
    int i;
    for (i=1; i<n+1; i++){
        x = x+2/x;
    }
    return x;
}


// avec sous fonction
double sfx(int n, double x){
    if (n==0) return x;
    return sfx(n-1,x+2/x);
} 
double xsf(int n){
    return sfx(n,1);
}


// avec sous procedure 
void spx(int n, double* x){
    if (n==0) *x;
    else{
        *x = *x+2/(*x);
        spx(n-1, x);
    }
}
double xsp(int n){
    double x=1;
    spx(n,&x);
    return x;
} 