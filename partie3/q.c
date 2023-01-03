#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


/*************************************************/
/*                                               */
/*                NOM-PRENOM                     */
/*                                               */
/*************************************************/

/*

Nassim ARIFETTE 
Slimane MESBAH 

*/



/*************************************************/
/*                                               */
/*                sucre syntaxique               */
/*                                               */
/*************************************************/

#define AND &&
#define OR ||
// #define ISNOT !=
#define NOT !
#define then

typedef enum { FALSE, TRUE} bool;

void printBool( bool b){
    switch (b)
    {
    case FALSE:
        printf("false");
        break;
    case TRUE:
        printf("true");
        break;
    
    default:
        break;
    }
}






/*************************************************/
/*                                               */
/*          definition type liste                */
/*                                               */
/*************************************************/

typedef struct  bloc_image
{
    bool toutnoir;
    struct bloc_image* fils[4];  // [hg hd bg bd]
}bloc_image;

typedef bloc_image* image; 




/*************************************************/
/*                                               */
/*                predeclarations                */
/*                                               */
/*************************************************/


image construitBlanc();
image construitNoir ();
image construitComposee( image i0, image i1, image i2, image i3);

void afficheNormalRL(image im);
void afficheNormal( image im);
void afficheProfondeurAux( image im, int prof);

image Lecture();
image lecture(char*s);
image lecture_aux(char* s, int* cur);

bool estBlanche(image im);
bool estNoire(image im);
bool filsNoir(image im);
bool filsBlanc(image im);

image diagonale(int p) ;
image quartDeTour( image im) ;
void Negatif(image *img);
void SimplifieProfP(image *img,int p);
void detruire(image* im);

bool incluse(image im1, image im2);
bool incluseComposee( image im1, image im2);

int hautMaxBlanc( image im) ;
int hautMaxBlancAux( image im, bool* blanche );
int max ( int a, int b, int c, int d);
int max2(int n, int m);

void blanchitProfPCase(image* im, int p, int x, int y, double taille );
void blanchitProfP(image* im, int p, int x, int y);

image chute(image im) ;
image unionNoir(image im1, image im2);


/*************************************************/
/*                                               */
/*                fonctionnes                    */
/*                                               */
/*************************************************/
image construitBlanc(){
    return NULL ; 
}


image construitNoir (){
    image res = (image) malloc(sizeof(bloc_image)); 
    res->toutnoir = TRUE; 
    for (int i=0 ; i<4; i++){
        (res->fils)[i] = NULL; 
    }
    return res ; 
}



image construitComposee( image i0, image i1, image i2, image i3){
    image img =  (image) malloc(sizeof(bloc_image));
    img->toutnoir = FALSE ;
    img->fils[0] = i0;
    img->fils[1] = i1;
    img->fils[2] = i2;
    img->fils[3] = i3;
    return img;
}









void afficheNormalRL(image im){
    afficheNormal(im);
    printf("\n");
}

void afficheNormal( image im){
    if (im==NULL) { printf("B") ; return; } 
    if (im->toutnoir) { printf("N"); return ; }  
    // else 
    printf("("); 
    afficheNormal(im->fils[0]); 
    afficheNormal(im->fils[1]); 
    afficheNormal(im->fils[2]); 
    afficheNormal(im->fils[3]);
    printf(")");  
}


void afficheProfondeur(image im){
    afficheProfondeurAux(im, 0 ); 
}

void afficheProfondeurAux( image im, int prof){
    if (im==NULL) { printf("B%d",prof) ; return; } 
    if (im->toutnoir) { printf("N%d",prof);  return ; }  
    // else 
    printf("("); 
    afficheProfondeurAux(im->fils[0], prof+1); 
    afficheProfondeurAux(im->fils[1], prof+1); 
    afficheProfondeurAux(im->fils[2], prof+1); 
    afficheProfondeurAux(im->fils[3], prof+1);
    printf(")");  
}

// avec lecture clavier ; 
image Lecture(){
    char c = getchar();
    if (c == 'B'){
        return construitBlanc();
    }
    else if (c == 'N')
    {
        return construitNoir();
    }
    else if (c == '('){
        image i1 = Lecture();
        image i2 = Lecture();
        image i3 = Lecture();
        image i4 = Lecture();
        return construitComposee(i1,i2,i3,i4);
    }
    else {
        return Lecture();
    }
} 


// a partir de char* :: string  ; 
image lecture(char*s){
    int cur=-1; 
    return lecture_aux(s, &cur); 
}


// specification: chaine bien formee : 
image lecture_aux(char* s, int* cur){
    *cur+=1 ; 
    if (s[*cur] == 'B'){
        return construitBlanc();
    }
    else if (s[*cur] == 'N')
    {
        return construitNoir();
    }
    else if (s[*cur] == '('){
        image i1 = lecture_aux(s, cur);
        image i2 = lecture_aux(s, cur);
        image i3 = lecture_aux(s, cur);
        image i4 = lecture_aux(s, cur);
        return construitComposee(i1,i2,i3,i4);
    }
    else {
        return lecture_aux(s, cur);
    }
} 











// Non Formee : 
bool estBlanche(image im){
    if(im==NULL) return TRUE; 
    else if (im->toutnoir) return FALSE; 
    return estBlanche(im->fils[0]) && estBlanche(im->fils[1]) &&
           estBlanche(im->fils[2]) && estBlanche(im->fils[3]) ; 
}

bool estNoire(image im){
    if(im==NULL) return FALSE; 
    else if (im->toutnoir) return TRUE; 
    return estNoire(im->fils[0]) && estNoire(im->fils[1]) && 
           estNoire(im->fils[2]) && estNoire(im->fils[3]) ; 
}


// prend une image composee est rend vrai si tout les fils sont noirs 
bool filsNoir(image im){
    return estNoire(im->fils[0]) && estNoire(im->fils[1]) && 
           estNoire(im->fils[2]) && estNoire(im->fils[3]) ; 
}

// prend une image composee est rend vrai si tout les fils sont blancs  
bool filsBlanc(image im){
    return estBlanche(im->fils[0]) && estBlanche(im->fils[1]) && 
           estBlanche(im->fils[2]) && estBlanche(im->fils[3]) ; 
}







image diagonale(int p) {
    if (p==0) return construitNoir(); 
    // else 
    return construitComposee(diagonale(p-1),construitBlanc(),construitBlanc(), diagonale(p-1));  
}



image quartDeTour( image im) {
	if(im==NULL) return construitBlanc();
    if (im->toutnoir ) return construitNoir() ; 
	// else 
	return construitComposee( quartDeTour(im->fils[2]),
                              quartDeTour(im->fils[0]),
                              quartDeTour(im->fils[3]),
                              quartDeTour(im->fils[1])); 
}



void Negatif(image *img){
    if ((*img) == NULL){
        (*img) = construitNoir();
    }
    else if ((*img)->toutnoir ){
        detruire(img);  
        (*img) = construitBlanc();
    }
    else
    {
        Negatif(&((*img)->fils[0]));
        Negatif(&((*img)->fils[1]));
        Negatif(&((*img)->fils[2]));
        Negatif(&((*img)->fils[3]));
    }    
}


// im NF: 



void SimplifieProfP(image *img,int p){
    if (p == 0){
        if (estBlanche(*img)){
            detruire(img);
            *img = construitBlanc();
        }

        else if (estNoire(*img)){
            detruire(img); 
            *img = construitNoir();
        }
    }
    else if(p>0) {
        p--;
        if ( !((*img) == NULL || (*img)->toutnoir)){
            SimplifieProfP(&((*img)->fils[0]),p);
            SimplifieProfP(&((*img)->fils[1]),p);
            SimplifieProfP(&((*img)->fils[2]),p);
            SimplifieProfP(&((*img)->fils[3]),p);
        }

    }    
}



void detruire(image* im){
    if((*im) !=NULL){
        for (int i=0 ; i<4; i++) 
            detruire(&((*im)->fils[i])); 
        free(*im); 
        *im = NULL; 
    }
}

/*

traitement de cas : 
 
    B       N               C
B   1       0               estBlanche(C)         
N   1       1               1
C   1       estNoire(C)     C

*/
bool incluse(image im1, image im2){
    if (im1==NULL) return TRUE; 
    // cas im1 != NULL
    if (im2==NULL) return estBlanche(im1) ;   
    // cas im1 != NULL && im2 != NULL
    if (im2->toutnoir) return TRUE; 
    // cas im2 composee 
    if (im1->toutnoir) return estNoire(im2);
    // cas im1 et im2 composee: 
    return  incluse(im1->fils[0], im2->fils[0]) &&
            incluse(im1->fils[1], im2->fils[1]) &&
            incluse(im1->fils[2], im2->fils[2]) &&
            incluse(im1->fils[3], im2->fils[3]) ; 
}




int hautMaxBlanc( image im) {
    bool blanche = TRUE; 
    hautMaxBlancAux(im, &blanche);
}

int hautMaxBlancAux( image im, bool* blanche ){  
    if (im==NULL) return 0; 
    // else soit noir ou composee 
    if (estNoire(im)) {
        *blanche = FALSE; 
        return -1;
    } 
    // else composee : 
    bool blanche0 = TRUE; 
    bool blanche1 = TRUE; 
    bool blanche2 = TRUE; 
    bool blanche3 = TRUE; 
    int hmb0 = hautMaxBlancAux(im->fils[0], & blanche0); 
    int hmb1 = hautMaxBlancAux(im->fils[1], & blanche1); 
    int hmb2 = hautMaxBlancAux(im->fils[2], & blanche2); 
    int hmb3 = hautMaxBlancAux(im->fils[3], & blanche3); 
    *blanche = *blanche && blanche0 && blanche1 && blanche2 && blanche3;
    if (*blanche) 
        return (max(hmb0, hmb1, hmb2, hmb3) +1); 
    else 
        return (max(hmb0, hmb1, hmb2, hmb3) );
}


int max ( int a, int b, int c, int d){
    return max2(max2(a,b),max2(c,d)); 
}

int max2(int n, int m){
    return n > m ? n : m;
}





void blanchitProfPCase(image* im, int p, int x, int y, double taille ){
    if(*im == NULL) return; // deja bonne ( car image blanche ) 
    if (p==0) { 
        detruire( im);
        *im = NULL; 
    }
    else if (p>0) {
        if ((*im)->toutnoir){
             detruire(im); 
            *im = construitComposee(construitNoir(),construitNoir(),construitNoir(),construitNoir());
        }
        // cas blanche deja teste'
        int xc; 
        int yc; 
        double newTaille = taille/2; 
        if (x<newTaille) xc = 0 ; 
        else {
            xc=1;
            x = x-newTaille;  
        }
        if (y<newTaille) yc = 0 ; 
        else {
            yc=1;
            y = y-newTaille; 
        }
        int fils ; 
        if (yc==1) fils = xc; 
        else fils = 2+xc;  
        blanchitProfPCase(&((*im)->fils[fils]), p-1, x, y, newTaille); 
    }
}




void blanchitProfP(image* im, int p, int x, int y){
    double taille = pow((double)2,(double)p); // %%% gcc q.c -lm 
    printf("%f\n",taille);
    blanchitProfPCase(im, p, x, y, taille); 
}


image chute(image im) {
    if (estBlanche(im) || im->toutnoir)
        return im; 
    image bg = unionNoir((im->fils[0]),(im->fils[2])); 
    image bd = unionNoir((im->fils[1]),(im->fils[3])); 
    return construitComposee(construitBlanc(), construitBlanc(), chute(bg),  chute(bd)) ; 
}

/*

traitement des cas : 
    B   N   C
B   B   N   C         
N   N   N   N
C   C   N   C

*/
image unionNoir(image im1, image im2){
    if((im1)==NULL) return im2;
    if (im2==NULL) return im1; 
    // cas im1!=NULL et im2 != NULL: 
    if (im1->toutnoir ) return im1; 
    if (im2->toutnoir) return im2 ; 
    return construitComposee(unionNoir(im1->fils[0], im2->fils[0]), 
                             unionNoir(im1->fils[1], im2->fils[1]), 
                             unionNoir(im1->fils[2], im2->fils[2]), 
                             unionNoir(im1->fils[3], im2->fils[3])   ); 
}







/*************************************************/
/*                                               */
/*           test gen                            */
/*                                               */
/*************************************************/

// a la fin 
void printnl(){
    printf("\n");
}

image cc(image i1, image i2, image i3, image i4){
    return construitComposee(i1,i2,i3,i4); 
}

image b(){
    return construitBlanc(); 
}

image n(){
    return construitNoir(); 
}




/*************************************************/
/*                                               */
/*           Main                                */
/*                                               */
/*************************************************/

// a la fin 

int main(int argc, char const *argv[])
{
    // image de base 
    image B = construitBlanc();
    image N = construitNoir();
    // LES 16 PERMUTATION POSSIBLE 
    image NBNN = construitComposee(N, B, N, N); 
    image NBNB = construitComposee(N, B, N, B); 
    image NBBN = construitComposee(N, B, B, N); 
    image NBBB = construitComposee(N, B, B, B); 
    image NNNN = construitComposee(N, N, N, N); 
    image NNNB = construitComposee(N, N, N, B); 
    image NNBN = construitComposee(N, N, B, N); 
    image NNBB = construitComposee(N, N, B, B); 
    image BBNN = construitComposee(B, B, N, N); 
    image BBNB = construitComposee(B, B, N, B); 
    image BBBN = construitComposee(B, B, B, N); 
    image BBBB = construitComposee(B, B, B, B); 
    image BNNN = construitComposee(B, N, N, N); 
    image BNNB = construitComposee(B, N, N, B); 
    image BNBN = construitComposee(B, N, B, N); 
    image BNBB = construitComposee(B, N, B, B); 

    image imgB = construitComposee(B, B, B, B);
    image imc1 = construitComposee(NNBN,BBNB,BBBN,NBNB);
    image imc2 = construitComposee(BNBN,NNBN,BBNB,BNBN);
    image im = construitComposee(construitComposee(imc1,imc2,NBNN,imgB),imc1,BNNN,N);

    // image NON simplifies : 
    image imgBNS = construitComposee(B, B, B, B); 
    image imgNNS = construitComposee(N, N, N, N); 
    image imgBN2NS = construitComposee(imgBNS,imgBNS,imgBNS,imgBNS);
    image imgNN2NS = construitComposee(imgNNS,imgNNS,imgNNS,imgNNS);
    
    

    
    
            // void afficheNormalRL(image im);
    printf("\n\n//Test:  void afficheNormalRL(image im);-\n");
    printBool(estNoire(B));
    printnl();
    afficheNormalRL(NBNN);
    afficheNormalRL(im);

    // image construitComposee( image i0, image i1, image i2, image i3);
    printf("\n\n//Test:  image construitComposee( image i0, image i1, image i2, image i3); -\n");
    afficheNormalRL(imgBNS);
    afficheNormalRL(imgNN2NS);

    
            // void afficheProfondeurAux( image im, int prof);
    printf("\n\n//Test:  void afficheProfondeurAux( image im, int prof);-\n");
    afficheProfondeur(im);
    printnl();
    
    
            // image lecture(char*s);
    printf("\n\n//Test:  image lecture(char*s);-\n");
    image imt = lecture("((((NNBN)(NNNB)(NBBN)(NBNB))((NBBN)(NNBN)(NBNB)(NNNB))(NNNB)B)((NNBN)(NNNB)(NBBN)(NBNB))(NNBN)N)");
    afficheNormalRL(imt);
    
    
            // bool estBlanche(image im);
    printf("\n\n//Test:  bool estBlanche(image im);-\n");
    afficheNormalRL(imgBN2NS);
    printBool(estBlanche(imgBN2NS));printnl();
    afficheNormalRL(im);
    printBool(estBlanche(im));printnl();
    afficheNormalRL(B);
    printBool(estBlanche(B));printnl();
   
    
    
            // bool estNoire(image im);
    printf("\n\n//Test:  bool estNoire(image im);-\n");
    afficheNormalRL(imgNN2NS);
    printBool(estNoire(imgNN2NS));printnl();
    afficheNormalRL(im);
    printBool(estNoire(im));printnl();
    afficheNormalRL(N);
    printBool(estNoire(N));printnl();
    
    
    
    
            // bool filsNoir(image im);
    printf("\n\n//Test:  bool filsNoir(image im);-\n");
    afficheNormalRL(imgNNS);
    printBool(filsNoir(imgNNS));printnl();
    afficheNormalRL(imgNN2NS);
    printBool(filsNoir(imgNN2NS));printnl();
    afficheNormalRL(cc(B,B,B,B));
    printBool(filsNoir(cc(B,B,B,B)));printnl();
    afficheNormalRL(cc(N,N,N,N));
    printBool(filsNoir(cc(N,N,N,N)));printnl();
    afficheNormalRL(cc(B,B,N,B));
    printBool(filsNoir(cc(B,B,N,B)));printnl();
    
    
            // bool filsBlanc(image im);
    printf("\n\n//Test:  bool filsBlanc(image im);-\n");
    afficheNormalRL(imgBNS);
    printBool(filsBlanc(imgBNS));printnl();
    afficheNormalRL(imgBN2NS);
    printBool(filsBlanc(imgBN2NS));printnl();
    afficheNormalRL(cc(B,B,B,B));
    printBool(filsBlanc(cc(B,B,B,B)));printnl();
    afficheNormalRL(cc(N,N,N,N));
    printBool(filsBlanc(cc(N,N,N,N)));printnl();
    afficheNormalRL(cc(B,B,N,B));
    printBool(filsBlanc(cc(B,B,N,B)));printnl();
    
    
            // image diagonale(int p) ;
    printf("\n\n//Test:  image diagonale(int p) ;-\n");
    afficheNormalRL(diagonale(3));
    
    
            // image quartDeTour( image im) ;
    printf("\n\n//Test:  image quartDeTour( image im) ;-\n");
    image imqd = construitComposee(BNNN,B,NNBB,N);
    afficheNormalRL(quartDeTour(imqd));

                //  void Negatif(image *img);


    printf("\n\n//Test:   void Negatif(image *img);-\n");

    image negB = b();
    afficheNormalRL(negB);
    Negatif(&negB);
    afficheNormalRL((negB));

    image negN = n();
    afficheNormalRL(negN);
    Negatif(&negN);
    afficheNormalRL((negN));

    image negcc = cc(cc(b(),n(),n(),n()),b(),cc(n(),n(),b(),b()),n());
    afficheNormalRL(negcc);
    Negatif(&negcc);
    afficheNormalRL((negcc));
   
    
            // void SimplifieProfP(image *img,int p);
    printf("\n\n//Test:  void SimplifieProfP(image *img,int p);-\n");
    image imspp = cc(n(),
                     cc(n(),b(),cc(n(),n(),cc(n(),n(),n(),n()),n()),b()),
                     cc(n(),b(),n(),cc(n(),b(),n(),cc(b(),b(),b(),b()))),
                     cc(b(),b(),cc(b(),b(),b(),b()),b()));
    afficheNormalRL(imspp);
    SimplifieProfP(&imspp, 2);
    afficheNormalRL(imspp);


    
    
            // void detruire(image* im); 
    printf("\n\n//Test:  void detruire(image* im);-\n");
    image nnnn5 = cc(n(),n(),n(),n());
    image bbbb5 = cc(b(),b(),b(),b());  
    afficheNormalRL(bbbb5);
    detruire(&bbbb5);
    printBool(bbbb5==NULL);

    afficheNormalRL(nnnn5);
    detruire(&nnnn5);
    printBool(nnnn5==NULL);

    image db = b();
    afficheNormalRL(db);
    detruire(&db);
    printBool(db==NULL);

    image dn =n();
    afficheNormalRL(dn);
    detruire(&dn);
    printBool(dn==NULL);

    image dbnnb =cc(b(),n(),n(),b());
    afficheNormalRL(dbnnb);
    detruire(&dbnnb);
    printBool(dbnnb==NULL);
    
    
            // bool incluse(image im1, image im2);
    printf("\n\n//Test:  bool incluse(image im1, image im2);-\n");
    printf("\n\n -- \n");
    printf(" assert true = ");
    printBool(incluse(b(), b()));

    printf("\n\n -- \n");
    printf(" assert true = ");
    printBool(incluse(b(), n()));

    printf("\n\n -- \n");
    printf(" assert true = ");
    printBool(incluse(b(), cc(n(),b(),b(),n())));

    // c2: 
    printf("\n\n -- \n");
    printf(" assert false = ");
    printBool(incluse(n(), b()));

    printf("\n\n -- \n");
    printf(" assert true = ");
    printBool(incluse(n(), n()));

    printf("\n\n -- \n");
    printf(" assert true = ");
    printBool(incluse(n(), cc(n(),n(),n(),cc(n(),n(),n(),n()))));

    printf("\n\n -- \n");
    printf(" assert false = ");
    printBool(incluse(n(), cc(n(),n(),n(),cc(n(),n(),n(),b()))));

    // c3: 

    printf("\n\n -- \n");
    printf(" assert false = ");
    printBool(incluse(cc(b(),b(),b(),cc(b(),b(),n(),b())), b()));

    printf(" assert true = ");
    printBool(incluse(cc(b(),b(),b(),cc(b(),b(),b(),b())), b()));

    printf("\n\n -- \n");
    printf(" assert true = ");
    printBool(incluse(cc(b(),b(),b(),cc(b(),b(),n(),b())), n()));

    printf("\n\n -- \n");
    printf(" assert false = ");
    image incImg1 = (cc(   cc(cc(b(),b(),b(),b()),n(),b(),n()),
                            b(),
                            n(),
                            cc(cc(b(),b(),n(),n()),b(),b(),cc(n(),b(),b(),n()))    )); 

    image incImg2 = (cc(    cc(b(),n(),n(),n()),
                            cc(b(),b(),n(),b()),
                            cc(n(),n(),n(),n()),
                            cc(n(),b(),n(),cc(n(),n(),n(),b()))    )); 
                            
    printBool(incluse(incImg1, incImg2));

    printf("\n\n -- \n");
    printf(" assert true = ");
    image incImg11 = (cc(   cc(cc(b(),b(),b(),b()),n(),b(),n()),
                            b(),
                            n(),
                            cc(cc(b(),b(),n(),n()),b(),b(),cc(n(),b(),b(),n()))    )); 

    image incImg22 = (cc(    cc(b(),n(),n(),n()),
                            cc(b(),b(),n(),b()),
                            cc(n(),n(),n(),n()),
                            cc(n(),b(),n(),cc(n(),n(),n(),n()))    ));  
                            
    printBool(incluse(incImg11, incImg22));




    
            // int hautMaxBlanc( image im) ;
    printf("\n\n//Test:  int hautMaxBlanc( image im) ;-\n");

    printf("%d \n",hautMaxBlanc( B));
    printf("%d \n",hautMaxBlanc(BBBB));
    printf("%d \n",hautMaxBlanc(cc(B,B,B,BBBB)));
    printf("%d \n",hautMaxBlanc(cc(B,B,BBBB,cc(B,B,B,BBBB))));
    printf("%d \n",hautMaxBlanc( N));
    printf("%d \n",hautMaxBlanc( NNNN));
    image imhmb = cc(cc(B,B,B,B),
                     N,
                     cc(B,N,B,N),
                     cc(N,B,N,cc(N,B,cc(B,B,cc(B,B,B,B),cc(B,B,B,cc(B,B,B,B))),N)));
    afficheNormal(imhmb);printnl();
    printf("%d \n",hautMaxBlanc(imhmb));printnl();
    printBool(estNoire(BBBB));
    
            // int max ( int a, int b, int c, int d);
    printf("\n\n//Test:  int max ( int a, int b, int c, int d);-\n");
    printf("%d \n",max(3,0,4,-1)); 
    
    
            // void blanchitProfPCase(image* im, int p, int x, int y, int taille );
    printf("\n\n//Test:  void blanchitProfPCase(image* im, int p, int x, int y, int taille );-\n");
    
    
            // void blanchitProfP(image* im, int p, int x, int y); // todo : cas1 
    printf("\n\n//Test:  void blanchitProfP(image* im, int p, int x, int y);-\n");
    
    image nbnb = cc(n(),b(),n(),b());
    
    afficheNormalRL(nbnb);
    blanchitProfP(&nbnb,2,1,3); 
    afficheNormalRL(nbnb); 

    printf("\n -- \n");

    image  nnbnnnnBNB = cc(cc(n(),cc(n(),b(),n(),n()),n(),n()),b(),n(),b());
    
    afficheNormalRL(nnbnnnnBNB);
    blanchitProfP(&nnbnnnnBNB,2,1,3); 
    afficheNormalRL(nnbnnnnBNB); 


    
    printf("\n -- \n");
    image bl = construitBlanc();

    afficheNormalRL(bl);
    blanchitProfP(&bl,0,0,0); 
    afficheNormalRL(bl); 

    
    bl = construitBlanc();
    blanchitProfP(&bl,1,0,1); 
    afficheNormalRL(bl); 

    
    bl = construitBlanc();
    blanchitProfP(&bl,2,1,3); 
    afficheNormalRL(bl); 

    
    printf("\n -- \n");    
    image noir = construitNoir();

    afficheNormalRL(noir);
    blanchitProfP(&noir,0,0,0); 
    afficheNormalRL(noir); 

    
    noir = construitNoir();
    blanchitProfP(&noir,1,0,1); 
    afficheNormalRL(noir); 

    
    noir = construitNoir();
    blanchitProfP(&noir,2,1,3); 
    afficheNormalRL(noir); 

    printf("\n -- \n");
    image bbbb2 = cc(b(),b(),b(),b());

    afficheNormalRL(bbbb2);
    blanchitProfP(&bbbb2,0,0,0); 
    afficheNormalRL(bbbb2); 

    
    bbbb2 = cc(b(),b(),b(),b());
    blanchitProfP(&bbbb2,1,0,1); 
    afficheNormalRL(bbbb2); 

    
    bbbb2 = cc(b(),b(),b(),b());
    blanchitProfP(&bbbb2,2,1,3); 
    afficheNormalRL(bbbb2); 

    printf("\n -- \n");
    image nnnn2 = cc(n(),n(),n(),n());

    afficheNormalRL(nnnn2);
    blanchitProfP(&nnnn2,0,0,0); 
    afficheNormalRL(nnnn2); 

    
    nnnn2 = cc(n(),n(),n(),n());
    blanchitProfP(&nnnn2,1,0,1); 
    afficheNormalRL(nnnn2); 

    
    nnnn2 = cc(n(),n(),n(),n());
    blanchitProfP(&nnnn2,2,1,3); 
    afficheNormalRL(nnnn2); 

    printf("\n -- \n");
    image bnnn = cc(b(),n(),n(),n());

    afficheNormalRL(bnnn);
    blanchitProfP(&bnnn,0,0,0); 
    afficheNormalRL(bnnn); 

    
    bnnn = cc(b(),n(),n(),n());
    blanchitProfP(&bnnn,1,0,1); 
    afficheNormalRL(bnnn); 

    
    bnnn = cc(b(),n(),n(),n());
    blanchitProfP(&bnnn,2,1,3); 
    afficheNormalRL(bnnn); 

    printf("\n -- \n");
    image NbnbnBN = cc(n(),cc(b(),n(),b(),n()),b(),n());

    afficheNormalRL(NbnbnBN);
    blanchitProfP(&NbnbnBN,0,0,0); 
    afficheNormalRL(NbnbnBN); 

    
    NbnbnBN = cc(n(),cc(b(),n(),b(),n()),b(),n());
    blanchitProfP(&NbnbnBN,1,0,1); 
    afficheNormalRL(NbnbnBN); 

    
    NbnbnBN = cc(n(),cc(b(),n(),b(),n()),b(),n());
    blanchitProfP(&NbnbnBN,2,1,3); 
    afficheNormalRL(NbnbnBN); 

    
    
            // image chute(image im) ;  
    printf("\n\n//Test:  image chute(image im) ;-\n");

    printf("\n -- \n");
    afficheNormalRL(n());
    afficheNormalRL(chute(n()));
    
    printf("\n -- \n");
    afficheNormalRL(b());
    afficheNormalRL(chute(b()));

    printf("\n -- \n");
    afficheNormalRL(cc(n(),b(),b(),b()));
    afficheNormalRL(chute(cc(n(),b(),b(),b())));

    printf("\n -- \n");
    afficheNormalRL(cc(n(),b(),n(),b()));
    afficheNormalRL(chute(cc(n(),b(),n(),b())));

    printf("\n -- \n");
    afficheNormalRL(cc(n(),b(),cc(b(),n(),b(),b()),b()));
    afficheNormalRL(chute(cc(n(),b(),cc(b(),n(),b(),b()),b())));

    printf("\n -- \n");
    afficheNormalRL(cc(n(),n(),n(),n()));
    afficheNormalRL(chute(cc(n(),n(),n(),n())));

    printf("\n -- \n");
    afficheNormalRL(cc(cc(n(),n(),n(),n()),n(),n(),n()));
    afficheNormalRL(chute(cc(cc(n(),n(),n(),n()),n(),n(),n())));

    printf("\n -- \n");
    afficheNormalRL(cc(cc(n(),n(),n(),n()),n(),cc(n(),n(),n(),n()),n()));
    afficheNormalRL(chute(cc(cc(n(),n(),n(),n()),n(),cc(n(),n(),n(),n()),n())));

    printf("\n -- \n");
    afficheNormalRL(cc(n(),n(),cc(n(),n(),n(),n()),n()));
    afficheNormalRL(chute(cc(n(),n(),cc(n(),n(),n(),n()),n())));

    printf("\n -- \n");
    afficheNormalRL(cc(n(),b(),n(),n()));
    afficheNormalRL(chute(cc(n(),b(),n(),n())));

    
   
    
                // image Lecture();
    // printf("\n\n//Test:  image Lecture(); -\n");
    // image iml = Lecture(); 
    // afficheNormalRL(iml);


    printf("\ntest success\n");





    return EXIT_SUCCESS;
}
