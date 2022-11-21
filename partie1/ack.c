#include <stdlib.h>
#include <stdio.h>


#define ISNOT !=
#define NOT !
#define AND &&
#define OR ||
#define then
typedef enum { false, true } bool;

long ackermanIR(int m, long n);
long ackerman(int m, long n);

int main(){
    int m = 2;  // pour 6 ca tourne sans resultat
    long n = 0;
    
    printf ("ack(%d,%ld)=%ld\n", m,n,ackerman(m,n));
    return EXIT_SUCCESS; 
}




long ackerman(int m, long n){
    if (m==0) return (n+1); 
    if (n==0) return ackerman(m-1,1);
    return ackerman(m-1,ackerman(m,n-1));
}




long ackermanIR(int m, long n){
    if (m==0) return (n+1);
    int r = 1;
    int i; 
    for (i=1; i<=n+1; i++){
        r = ackermanIR(m-1,r);
    }
    return r;
}

