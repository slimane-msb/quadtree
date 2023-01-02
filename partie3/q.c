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
/*                definition                     */
/*                                               */
/*************************************************/
/*
    bienForme: B ou N ou BNNB ..
    MalForme ou NonSimplifie as (NS) : BBBB ou (BB(NNNN)B) ou (false,BBBB)                          
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
image construitComposeeNS( image i0, image i1, image i2, image i3);
void afficheNormalRL(image im);
void afficheNormal( image im);
void afficheProfondeurAux( image im, int prof);
image Lecture();
image lecture(char*s);
image lecture_aux(char* s, int* cur);
bool estBlanche(image im);
bool estNoire(image im);
bool estBlancheBF(image im);
bool estNoireBF(image im);
// tq im est bien forme  
bool filsNoir(image im);
// tq im est bien forme
bool filsBlanc(image im);
image diagonale(int p) ;
image quartDeTour( image im) ;
void Negatif(image *img);
void SimplifieProfP(image *img,int p);
void detruire(image im);

bool incluse(image im1, image im2);
bool incluseComposee( image im1, image im2);

int hautMaxBlanc( image im) ;
int hautMaxBlancAux( image im, bool* blanche );
int max ( int a, int b, int c, int d);
int max2(int n, int m);

void blanchitProfPCase(image* im, int p, int x, int y, int taille );
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



image construitComposeeNS( image i0, image i1, image i2, image i3){
    image img =  (image) malloc(sizeof(bloc_image));
    img->toutnoir = FALSE ;
    img->fils[0] = i0;
    img->fils[1] = i1;
    img->fils[2] = i2;
    img->fils[3] = i3;
    return img;
}

image construitComposee( image i0, image i1, image i2, image i3){ // %%% maybe put in comment on work on the right principle and have one function for everything 
    if (((i0)==NULL)&&((i1)==NULL)&&((i2)==NULL)&&((i3)==NULL)) 
        return construitBlanc();
    // else 
    if ((estNoireBF(i0))&&(estNoireBF(i1))&&(estNoireBF(i2))&&(estNoireBF(i3))) 
        return construitNoir();
    // else 
    image img =  (image) malloc(sizeof(bloc_image));
    img->toutnoir = FALSE; 
    (img->fils)[0] = i0 ; 
    (img->fils)[1] = i1 ; 
    (img->fils)[2] = i2 ; 
    (img->fils)[3] = i3 ; 
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
    if (im==NULL) { printf("B %d",prof) ; return; } 
    if (im->toutnoir) { printf("N %d",prof);  return ; }  
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
    *cur+=1 ; // get char : //%%% start with 0 and increase cursor at the end of lecture aux code 
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

// Bien Forme :  estBlancheBienForme: supposant que BBBB ce simplifie en B et NNNN en N et que le 
// bool fonctionne bien 
bool estBlancheBF(image im){
    return im==NULL; 
}
bool estNoireBF(image im){
    if(im==NULL) return FALSE; 
    // else (soit noire soit composee )
    return im->toutnoir; 
}


bool filsNoir(image im){
    return estNoireBF(im->fils[0]) && estNoireBF(im->fils[1]) && 
           estNoireBF(im->fils[2]) && estNoireBF(im->fils[3]) ; 
}

bool filsBlanc(image im){
    return estBlancheBF(im->fils[0]) && estBlancheBF(im->fils[1]) && 
           estBlancheBF(im->fils[2]) && estBlancheBF(im->fils[3]) ; 
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
        // detruire(*img);  // %%% to fix 
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
            detruire(*img);
            *img = construitBlanc();
        }

        else if (estNoire(*img)){
            // detruire(*img); // %%% make work without sig fault  
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



void detruire(bloc_image* im){
    if((im) !=NULL){
        for (int i=0 ; i<4; i++) 
            detruire((im->fils[i])); 
        free(im); 
        im = NULL; 
    }
}

/*

traitement de cas : 
    im1    N    B      4
    im2 
    N      t    f      4=N
    B      f    t       4=B 
    4      4=N  4=B     im1, img2[0] || ...3|| in moitite 

in moitie = 
    todo 
*/
bool incluse(image im1, image im2){  // %% a refaire entierement 
    if (estBlanche(im2)) return estBlanche(im1);
    if (estNoire(im2)) return estNoire(im1); 
    // else im2 construite: 
    return incluse(im1, im2->fils[0]) || incluse(im1, im2->fils[1]) || incluse(im1, im2->fils[2]) ||
           incluse(im1, im2->fils[3]) || incluseComposee(im1,im2); 
}


bool incluseComposee( image im1, image im2){
    return FALSE; // todo 
}

int hautMaxBlanc( image im) {
    bool blanche = TRUE; 
    hautMaxBlancAux(im, &blanche);
}

int hautMaxBlancAux( image im, bool* blanche ){  //%%% optimise 
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





/*

c correspond a fils[c ]


*/

void blanchitProfPCase(image* im, int p, int x, int y, int taille ){
    if(*im == NULL) return; // deja bon
    if (p==0) { // il faut blanchir la fils[c] 
        // cas blanche deja teste 
        // else 
        int fils ; 
        if ((x==1) && (y==1 || y==0)) fils = y;
        else if ((x==0) && (y==1 || y==0)) fils = y+3; 
        else return; 
        detruire( (*im)->fils[fils]);
        // (*im)->fils[c] = NULL; // blanchir le fils c  :: ==NULL deja fait dans detruire 
    }
    if (p>0) {
        // cas blanche deja teste 
        int c; 
        int l; 
        int newTaille = taille/2; 
        if (x<newTaille) c = 0 ; 
        else c=1; 
        if (y<newTaille) l = 0 ; 
        else {
            l=1;
            y = y-newTaille; 
        }
        int fils ; 
        if (l==1) fils = c; 
        else fils = 3+c;  
        blanchitProfPCase(&((*im)->fils[fils]), p-1, x, y, newTaille); 
    }
}


void blanchitProfP(image* im, int p, int x, int y){
    // int taille = (int)pow((double)2,(double)p); 
    blanchitProfPCase(im, p, x, y, 0); // 0-> taille 
}


image chute(image im) {
    if (estBlanche(im)) 
        return im;
    if(estNoire(im)) 
        return construitComposeeNS(construitBlanc(),construitBlanc(),im->fils[2], im->fils[3]) ; 
    image bg, bd; 
    bg = unionNoir(chute(im->fils[0]),chute(im->fils[3])); 
    bd = unionNoir(chute(im->fils[2]),chute(im->fils[4])); 
    return construitComposeeNS(construitBlanc(), construitBlanc(), bg,  bd) ; 
}

image unionNoir(image im1, image im2){
    if((im1)==NULL) return im2;
    if (estNoire(im1)) return im1; 
    // else composee 
    if (estBlanche(im2)) return im1; 
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
image cn(image i1, image i2, image i3, image i4){
    return construitComposeeNS(i1,i2,i3,i4); 
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
    image NBNN = construitComposeeNS(N, B, N, N); 
    image NBNB = construitComposeeNS(N, B, N, B); 
    image NBBN = construitComposeeNS(N, B, B, N); 
    image NBBB = construitComposeeNS(N, B, B, B); 
    image NNNN = construitComposeeNS(N, N, N, N); 
    image NNNB = construitComposeeNS(N, N, N, B); 
    image NNBN = construitComposeeNS(N, N, B, N); 
    image NNBB = construitComposeeNS(N, N, B, B); 
    image BBNN = construitComposeeNS(B, B, N, N); 
    image BBNB = construitComposeeNS(B, B, N, B); 
    image BBBN = construitComposeeNS(B, B, B, N); 
    image BBBB = construitComposeeNS(B, B, B, B); 
    image BNNN = construitComposeeNS(B, N, N, N); 
    image BNNB = construitComposeeNS(B, N, N, B); 
    image BNBN = construitComposeeNS(B, N, B, N); 
    image BNBB = construitComposeeNS(B, N, B, B); 

    image imgB = construitComposee(B, B, B, B);
    image imc1 = construitComposee(NNBN,BBNB,BBBN,NBNB);
    image imc2 = construitComposee(BNBN,NNBN,BBNB,BNBN);
    image im = construitComposee(construitComposee(imc1,imc2,NBNN,imgB),imc1,BNNN,N);

    // image NON simplifies : 
    image imgBNS = construitComposeeNS(B, B, B, B); 
    image imgNNS = construitComposeeNS(N, N, N, N); 
    image imgBN2NS = construitComposeeNS(imgBNS,imgBNS,imgBNS,imgBNS);
    image imgNN2NS = construitComposeeNS(imgNNS,imgNNS,imgNNS,imgNNS);
    
    

    
    
            // void afficheNormalRL(image im);
    printf("\n\n//Test:  void afficheNormalRL(image im);-\n");
    printBool(estNoireBF(B));
    printnl();
    afficheNormalRL(NBNN);
    afficheNormalRL(im);

    // image construitComposee( image i0, image i1, image i2, image i3);
    printf("\n\n//Test:  image construitComposee( image i0, image i1, image i2, image i3); est composeNonSimplifie-\n");
    printf("construiteBienForme: construire(BBBB) doit etre construite en B :: simplification est faite en construction\n");
    afficheNormalRL(imgB);
    printf("construiteNonForme: construire(BBBB) doit etre construite en BBBB :: simplification est faite en construction\n");
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
    printBool(estBlanche(imgBN2NS));printnl();
    printBool(estBlanche(im));printnl();
    printBool(estBlanche(B));printnl();
   
    
    
            // bool estNoire(image im);
    printf("\n\n//Test:  bool estNoire(image im);-\n");
    printBool(estNoire(imgNN2NS));printnl();
    printBool(estNoire(im));printnl();
    printBool(estNoire(N));printnl();
    
    
            // bool estBlancheBF(image im);
    printf("\n\n//Test:  bool estBlancheBF(image im);-\n");
    printBool(estBlancheBF(imgBN2NS));printnl(); // ca marche pour les bien formee 
    printBool(estBlancheBF(im));printnl();
    printBool(estBlancheBF(B));printnl();
    
    
            // bool estNoireBF(image im);
    printf("\n\n//Test:  bool estNoireBF(image im);-\n");
    printBool(estNoireBF(imgNN2NS));printnl(); // ca marche pour les bien formee 
    printBool(estNoireBF(im));printnl();
    printBool(estNoireBF(N));printnl();
    
    
            // bool filsNoir(image im);
    printf("\n\n//Test:  bool filsNoir(image im);-\n");
    printBool(filsNoir(imgNNS));printnl();
    printBool(filsNoir(imgNN2NS));printnl();
    
    
            // bool filsBlanc(image im);
    printf("\n\n//Test:  bool filsBlanc(image im);-\n");
    printBool(filsBlanc(imgBNS));printnl();
    printBool(filsNoir(imgBN2NS));printnl();
    
    
            // image diagonale(int p) ;
    printf("\n\n//Test:  image diagonale(int p) ;-\n");
    afficheNormalRL(diagonale(3));
    
    
            // image quartDeTour( image im) ;
    printf("\n\n//Test:  image quartDeTour( image im) ;-\n");
    image imqd = construitComposee(BNNN,B,NNBB,N);
    afficheNormalRL(quartDeTour(imqd));

                //  void Negatif(image *img);
    printf("\n\n//Test:   void Negatif(image *img);-\n");
    afficheNormalRL(imqd);
    Negatif(&imqd);
    afficheNormalRL((imqd));

    void Negatif(image *img);
    
    
            // void SimplifieProfP(image *img,int p);
    printf("\n\n//Test:  void SimplifieProfP(image *img,int p);-\n");
    image imspp = cn(N,
                     cn(N,B,cn(N,N,cn(N,N,N,N),N),B),
                     cn(N,B,N,cn(N,B,N,cn(B,B,B,B))),
                     cn(B,B,cn(B,B,B,B),B));
    afficheNormalRL(imspp);
    SimplifieProfP(&imspp, 2);
    afficheNormalRL(imspp);


    
    
            // void detruire(image* im); 
    printf("\n\n//Test:  void detruire(image* im);-\n");
    image nnnn = cn(N,N,N,N);
    image bbbb = cn(B,B,B,B);  
    afficheNormalRL(bbbb);
    detruire(bbbb);
    printBool(bbbb==NULL);
    
    
            // bool incluse(image im1, image im2);
    printf("\n\n//Test:  bool incluse(image im1, image im2);-\n");
    printf("exemple: \n");
    image inc1 = B; 
    image inc2 = N; 
    printBool(incluse(inc1, inc2));

        printf("exemple: \n");
    inc1 = B; 
    inc2 = B; 
    printBool(incluse(inc1, inc2));

        printf("exemple: \n");
    inc1 = N; 
    inc2 = N; 
    printBool(incluse(inc1, inc2));

        printf("exemple: \n");
    inc1 = N; 
    inc2 = B; 
    printBool(incluse(inc1, inc2));

        printf("exemple: \n");
    inc1 = B; 
    inc2 = BBBB; 
    printBool(incluse(inc1, inc2));

        printf("exemple: \n");
    inc1 = N; 
    inc2 = NNNN; 
    printBool(incluse(inc1, inc2));

            printf("exemple: \n");
    inc1 = N; 
    inc2 = BBNB; 
    printBool(incluse(inc1, inc2));

    
            // int hautMaxBlanc( image im) ;
    printf("\n\n//Test:  int hautMaxBlanc( image im) ;-\n");

    printf("%d \n",hautMaxBlanc( B));
    printf("%d \n",hautMaxBlanc(BBBB));
    printf("%d \n",hautMaxBlanc(cn(B,B,B,BBBB)));
    printf("%d \n",hautMaxBlanc(cn(B,B,BBBB,cn(B,B,B,BBBB))));
    printf("%d \n",hautMaxBlanc( N));
    printf("%d \n",hautMaxBlanc( NNNN));
    image imhmb = cn(cn(B,B,B,B),
                     N,
                     cn(B,N,B,N),
                     cn(N,B,N,cn(N,B,cn(B,B,cn(B,B,B,B),cn(B,B,B,cn(B,B,B,B))),N)));
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
    image bpp = cn(cn(N,cn(N,B,N,N),N,N),B,N,B); 
    blanchitProfP(&bpp,2,1,3); 
    afficheNormalRL(bpp); 
    bpp = cn(cn(N,B,N,N),B,N,B); 
    blanchitProfP(&bpp,2,1,3); 
    afficheNormalRL(bpp); 
    
    
            // image chute(image im) ; // todo:: avec imch 
    printf("\n\n//Test:  image chute(image im) ;-\n");
    image imch = cn(N,cn((NBNN),N,B,(BNBN)),cn(N,(NBBN),(BNNN),NBNB),cn(N,N,NBBB,BNBN));
    afficheNormalRL(imch);
    printf("chute\n");
    // afficheNormalRL(chute(imch));

    printf("autre exemple\n");
    imch = BBBB;
    afficheNormalRL(imch);
    printf("chute\n");
    afficheNormalRL(chute(imch)); 

    printf("autre exemple\n");
    imch = cn(B,BBBB,BBBB,cn(BBBB,B,B,B));
    afficheNormalRL(imch);
    printf("chute\n");
    afficheNormalRL(chute(imch));
    
    printf("autre exemple\n");
    imch = NNNN;
    afficheNormalRL(imch);
    printf("chute\n");
    afficheNormalRL(chute(imch));

    printf("autre exemple\n");
    imch = cn(N,NNNN,NNNN,cn(NNNN,N,N,N));
    afficheNormalRL(imch);
    printf("chute\n");
    afficheNormalRL(chute(imch));
    
    
            // image unionNoir(image im1, image im2); // toFix: keep same prof 
    printf("\n\n//Test:  image unionNoir(image im1, image im2);-\n");
    afficheNormalRL(unionNoir(cn(N,B,BBNN,BBNN),cn(N,B,NBNB,BBNN)));
    afficheNormalRL(NNNN);
    afficheNormalRL(unionNoir(N,NNNN));
    afficheNormalRL(unionNoir(N,N));

    
    
                // image Lecture();
    printf("\n\n//Test:  image Lecture(); // uncommet to test -\n");
    // image iml = Lecture(); 
    // afficheNormalRL(iml);





    return EXIT_SUCCESS;
}
