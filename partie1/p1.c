#include <stdlib.h>
#include <stdio.h>


#define ISNOT !=
#define NOT !
#define AND &&
#define OR ||
#define then
typedef enum { false, true } bool;


double formuleE();
void afficheSuiteEn();
double power1bis(int x, int n);
double power2abis(int x, int n);
double power1bisc(int x, int n);
int power1(int x, int n);
int power2a(int x, int n);
double power2abis (int x, int n);
int power2b(int x, int n);
int pow3(int x, int n, int* r);
int power3(int x, int n);
int pow4 (int x, int n, int r);
int power4(int x, int n);
int power5(int x, int n);
int power6(int x, int n);
int power7(int x, int n);
int pow8 (int x, int n, int r);
int power8(int x, int n);
int pow9 (int x, int n, int* r);
int power9(int x, int n);
int power10(int x, int n);

int main(){
    // printf("formule e = %lf\n", formuleE());
    // afficheSuiteEn();

    // test simple : 
    int 
    x = 3; 
    int n = 4;
    printf( "\n\ntest pow : %d^%d\n\n",x,n);
    printf (" power1bis(%d, %d)=%f \n", x,n,power1bis(x, n));

    printf (" power2abis(%d, %d)=%f \n", x,n,power2abis(x, n));

    printf (" power1bisc(%d, %d)=%f \n", x,n,power1bisc(x, n));
    printf (" power1(%d, %d)=%d \n", x,n,power1(x, n));
    printf (" power2a(%d, %d)=%d \n", x,n,power2a(x, n)  );
    printf (" power2abis (%d, %d)=%f \n", x,n,power2abis (x, n)  );
    printf (" power2b(%d, %d)=%d \n", x,n,power2b(x, n)  );
    printf (" power3(%d, %d)=%d \n", x,n,power3(x, n));
    printf (" power4(%d, %d)=%d \n", x,n,power4(x, n));
    printf (" power5(%d, %d)=%d \n", x,n,power5(x, n));
    printf (" power6(%d, %d)=%d \n", x,n,power6(x, n));
    printf (" power7(%d, %d)=%d \n", x,n,power7(x, n));
    printf (" power8(%d, %d)=%d \n", x,n,power8(x, n));
    printf (" power9(%d, %d)=%d \n", x,n,power9(x, n));
    printf (" power10(%d, %d)=%d \n", x,n,power10(x, n)  );

    
    x = 0; 
    n = 4;
    printf( "\n\ntest pow : %d^%d\n\n",x,n);
    printf (" power1bis(%d, %d)=%f \n", x,n,power1bis(x, n));

    printf (" power2abis(%d, %d)=%f \n", x,n,power2abis(x, n));

    printf (" power1bisc(%d, %d)=%f \n", x,n,power1bisc(x, n));
    printf (" power1(%d, %d)=%d \n", x,n,power1(x, n));
    printf (" power2a(%d, %d)=%d \n", x,n,power2a(x, n)  );
    printf (" power2abis (%d, %d)=%f \n", x,n,power2abis (x, n)  );
    printf (" power2b(%d, %d)=%d \n", x,n,power2b(x, n)  );
    printf (" power3(%d, %d)=%d \n", x,n,power3(x, n));
    printf (" power4(%d, %d)=%d \n", x,n,power4(x, n));
    printf (" power5(%d, %d)=%d \n", x,n,power5(x, n));
    printf (" power6(%d, %d)=%d \n", x,n,power6(x, n));
    printf (" power7(%d, %d)=%d \n", x,n,power7(x, n));
    printf (" power8(%d, %d)=%d \n", x,n,power8(x, n));
    printf (" power9(%d, %d)=%d \n", x,n,power9(x, n));
    printf (" power10(%d, %d)=%d \n", x,n,power10(x, n)  );

    
    x = 3; 
    n = 0;
    printf( "\n\ntest pow : %d^%d\n\n",x,n);
    printf (" power1bis(%d, %d)=%f \n", x,n,power1bis(x, n));

    printf (" power2abis(%d, %d)=%f \n", x,n,power2abis(x, n));

    printf (" power1bisc(%d, %d)=%f \n", x,n,power1bisc(x, n));
    printf (" power1(%d, %d)=%d \n", x,n,power1(x, n));
    printf (" power2a(%d, %d)=%d \n", x,n,power2a(x, n)  );
    printf (" power2abis (%d, %d)=%f \n", x,n,power2abis (x, n)  );
    printf (" power2b(%d, %d)=%d \n", x,n,power2b(x, n)  );
    printf (" power3(%d, %d)=%d \n", x,n,power3(x, n));
    printf (" power4(%d, %d)=%d \n", x,n,power4(x, n));
    printf (" power5(%d, %d)=%d \n", x,n,power5(x, n));
    printf (" power6(%d, %d)=%d \n", x,n,power6(x, n));
    printf (" power7(%d, %d)=%d \n", x,n,power7(x, n));
    printf (" power8(%d, %d)=%d \n", x,n,power8(x, n));
    printf (" power9(%d, %d)=%d \n", x,n,power9(x, n));
    printf (" power10(%d, %d)=%d \n", x,n,power10(x, n)  );


    // test neg : 
    
    x = -3; 
    n = -4;
    printf( "\n\ntest pow : %d^%d\n\n",x,n);
    printf (" power1bis(%d, %d)=%f \n", x,n,power1bis(x, n));

    printf (" power2abis(%d, %d)=%f \n", x,n,power2abis(x, n));

    printf (" power1bisc(%d, %d)=%f \n", x,n,power1bisc(x, n));
    printf (" power2abis (%d, %d)=%f \n", x,n,power2abis (x, n)  );

    
    x = -3 ; 
    n = 0;
    printf( "\n\ntest pow : %d^%d\n\n",x,n);
    printf (" power1bis(%d, %d)=%f \n", x,n,power1bis(x, n));

    printf (" power2abis(%d, %d)=%f \n", x,n,power2abis(x, n));

    printf (" power1bisc(%d, %d)=%f \n", x,n,power1bisc(x, n));
    printf (" power2abis (%d, %d)=%f \n", x,n,power2abis (x, n)  );

    
    x = -3 ; 
    n = 5;
    printf( "\n\ntest pow : %d^%d\n\n",x,n);
    printf (" power1bis(%d, %d)=%f \n", x,n,power1bis(x, n));

    printf (" power2abis(%d, %d)=%f \n", x,n,power2abis(x, n));

    printf (" power1bisc(%d, %d)=%f \n", x,n,power1bisc(x, n));
    printf (" power2abis (%d, %d)=%f \n", x,n,power2abis (x, n)  );

    
    x = 0 ; 
    n = -4;
    printf( "\n\ntest pow : %d^%d\n\n",x,n);
    printf (" power1bis(%d, %d)=%f \n", x,n,power1bis(x, n));

    printf (" power2abis(%d, %d)=%f \n", x,n,power2abis(x, n));

    printf (" power1bisc(%d, %d)=%f \n", x,n,power1bisc(x, n));
    printf (" power2abis (%d, %d)=%f \n", x,n,power2abis (x, n)  );

    
    x = 2 ; 
    n = -4;
    printf( "\n\ntest pow : %d^%d\n\n",x,n);
    printf (" power1bis(%d, %d)=%f \n", x,n,power1bis(x, n));

    printf (" power2abis(%d, %d)=%f \n", x,n,power2abis(x, n));

    printf (" power1bisc(%d, %d)=%f \n", x,n,power1bisc(x, n));
    printf (" power2abis (%d, %d)=%f \n", x,n,power2abis (x, n)  );



    // test plus long 
    int N = 100; 
    double pN = (1.0+1.0/N); 

    printf ("\n\nplus de testes\n\n");

    // test Np 
    printf ("power1bis(%f,%d)=%f\n", pN,N,power1bis(pN,N));
    printf ("power2abis(%f,%d)=%f\n", pN,N,power2abis(pN,N));
    printf ("power1bis(%f,%d)=%lf\n", pN,N,power1bis(pN,N));

    printf ("power2abis(%f,%d)=%f\n", pN,N,power2abis(pN,N));
    printf ("power1(%f,%d)=%d\n", pN,N,power1(pN,N));
    printf ("power2a(%f,%d)=%d\n", pN,N,power2a(pN,N));
    printf ("power2b(%f,%d)=%d\n", pN,N,power2b(pN,N));
    printf ("power3(%f,%d)=%d\n", pN,N,power3(pN,N));
    printf ("power4(%f,%d)=%d\n", pN,N,power4(pN,N));
    printf ("power5(%f,%d)=%d\n", pN,N,power5(pN,N));
    printf ("power6(%f,%d)=%d\n", pN,N,power6(pN,N));
    printf ("power7(%f,%d)=%d\n", pN,N,power7(pN,N));
    printf ("power8(%f,%d)=%d\n", pN,N,power8(pN,N));
    printf ("power9(%f,%d)=%d\n", pN,N,power9(pN,N));
    printf ("power10(%f,%d)=%d\n", pN,N,power10(pN,N));
    /*
        le calcul termine imm ́ediatement, il rame, il tourne sans donner de
        r ́esultat, il stoppe avec un out of memory ? -> il stoppe avec un out of memory
        Votre compilateur semble-t-il effectuer l’optimisation du r ́ecursif terminal ? : oui
    */

    return EXIT_SUCCESS; 
}


/**********************************************************************************************/
/*                                         q1                                                 */
/**********************************************************************************************/

// doit-on faire plusieur version ( deja c'st pas note donc je pense pas)
double formuleE(){
    double res=0;
    int factI = 1 ;
    int i; 
    for(i=1; i<11;i++){ // faut il faire une version while(last!=current) then do this else stop 
        res+=(1.0/factI);
        // printf ("termi_i = %lf  |  ",  res) ;
        factI*=i;
        
    }
    return res;
}

/**********************************************************************************************/
/*                                         q2                                                 */
/**********************************************************************************************/



void afficheSuiteEn(){
    double prec = formuleE()-1;
    int n;
    for (n=1; n<51; n++){
        printf("e_%d = %f\n", (n-1),prec); // afficher e_n-1
        prec = n*prec-1; // prec <- e_n
    }
}

/* e_49 = -184239971244948377316113616974237414151667483811675897856.000000 */


/**********************************************************************************************/
/*                                         q3                                                 */
/**********************************************************************************************/
// 10 version de power : 

// version 1 :

int power1(int x, int n){
    if (n==0) return 1; 
    else return (power1(x,n-1)*x); 
}

// version 1 bis : 

// avec n pos || neg (version pourrie)
double power1bis(int x, int n){
    if (n==0) return 1.0; 
    else {
        if (n<0) return (power1bis(x,n+1)*(1.0/x));
        return (power1bis(x,n-1)*x);  
    }
}


// pour ne pas faire test n<0 pleusieur fois 

double power1bisc(int x, int n){
    if (n>=0) return (double)power1(x,n);
    return (double)1/power1(x,-n);
} 

// version n>=0
int power2a (int x, int n){
    int r = 1; 
    int i; 
    for (i=1; i<n+1; i++) r=r*x; 
    return r;
} 

// version aussi pour n<0
double power2abis (int x, int n){
    if (n>=0) return (double)power2a(x,n);
    else return (double)1.0/power2a(x,-n);
} 


// version aussi pour n<0 et 0^0

// double power2abisbis (int x, int n){
//     assert(x==0 && n==0);
//     if (n>=0) return (double)power2a(x,n);
//     else return (double)1.0/power2a(x,-n);
// } 



int power2b (int x, int n){
    int r = 1; 
    while(n>0){
        r = r*x; 
        n--;
    }
    return r;
} 


int pow3(int x, int n, int* r){
    if (n!=0){
        *r = *r*x;
        pow3(x,n-1,r);
    } 
}

int power3 (int x, int n){
    int r = 1; 
    pow3(x,n, &r);
    return r;
}


int pow4 (int x, int n, int r){
    if (n==0) return r;
    else return pow4(x,n-1,r*x);
}

int power4 (int x, int n){
    return pow4(x,n,1);
}



int power5 (int x, int n){
    if (n==0) return 1; 
    else{
        if (n%2==0) return power5(x,n/2)*power5(x,n/2);
        else return power5(x,n/2)*power5(x,n/2)*x;
    }
}


int power6 (int x, int n){
    if (n==0) return 1; 
    else {
        int y = power6 (x,n/2);
        if (n%2==0) return y*y;
        else return y*y*x;
    }
}


int power7 (int x, int n){
    if (n==0) return 1; 
    else {
        if (n%2==0) return power7(x*x, n/2);
        else return power7(x*x, n/2)*x;
    }
}

int pow8 (int x, int n, int r){
    if (n==0) return r;
    else{
        if (n%2==0) return pow8(x*x,n/2,r);
        else return pow8(x*x,n/2,r*x);
    }
}

int power8 (int x, int n){
    return pow8(x,n,1);
}


int pow9 (int x, int n, int* r){
    if (n!=0){
        if (n%2!=0) *r = *r*x;
        pow9(x*x, n/2, r);
    } 
}

int power9 (int x, int n){
    int r = 1;
    pow9(x,n,&r);
    return r;
}



int power10( int x, int n){
    int r=1; 
    while(n!=0){
        if (n%2!=0) r=r*x;
        n=n/2;
        x=x*x;
    }
    return r;
}