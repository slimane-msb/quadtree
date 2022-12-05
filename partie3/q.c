#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

// a la fin 



/*************************************************/
/*                                               */
/*                fonctionnes                    */
/*                                               */
/*************************************************/
image construitBlanc(){
    return NULL ; 
}


image construitNoir (){
    image res = malloc(sizeof(bloc_image)); 
    (res->fils) = malloc(4*sizeof(image)); // car fils est du type bloc_image** est donc just un pointeur, alors il faut malloc les case des 4 pointeur;  
    res->toutnoir = TRUE; 
    for (int i=0 ; i<4; i++){
        (res->fils)[i] = NULL; 
    }
    return res ; 
}

image construitComposee( image i0, image i1, image i2, image i3){
    if ((estBlanc(i0))&&(estBlanc(i1))&&(estBlanc(i3))&&(estBlanc(i3))) return construitBlanc();
    // else 
    if ((estNoir(i0))&&(estNoir(i1))&&(estNoir(i3))&&(estNoir(i3))) return construitNoir(); // peut etre ganger quelque comparaisons 
    // else 
    image res = malloc (sizeof(bloc_image)); 
    (res->fils) = malloc(4*sizeof(image)); 
    res->toutnoir = FALSE; 
    (res->fils)[0] = i0 ; (res->fils)[1] = i1 ; (res->fils)[2] = i2 ; (res->fils)[3] = i3 ; 
    return res; 
}

void afficheNoir(){ 
    printf("N");
}

void afficheBlanc(){ 
    printf("B");
}

void afficheInt(int i){
    printf("%d",i);
}

void afficheNormal( image im){
    if (estBlanc(im)) { afficheBlanc() ; return; } 
    if (estNoir(im)) { afficheNoir(); return ; }  
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
    if (estBlanc(im)) { afficheBlanc(); afficheInt(prof)  ; return; } 
    if (estNoir(im)) { afficheNoir(); afficheInt(prof) ; return ; }  
    // else 
    printf("("); 
    afficheProfondeurAux(im->fils[0], prof+1); 
    afficheProfondeurAux(im->fils[1], prof+1); 
    afficheProfondeurAux(im->fils[2], prof+1); 
    afficheProfondeurAux(im->fils[3], prof+1);
    printf(")");  
}

// clavier 
image lecture(){
    char * txt[1000];
    scanf("%s", txt); 
    return getImageTxt(txt, 0, strlen(txt)-1); 
}

 
// image de :  B ou N : 
image getImageSimpleTxt(char t){
    if (t == "N" ) return construitNoir();
    if (t == "B") return construitBlanc();
    return EXIT_FAILURE; 
}

//image de : t=  ( N (BBNB) (NBBN) N )   d=0 f=len(t)-1 
image getImageTxt(char* t, int d, int f){
    if (d==f) return getImageSimpleTxt(t[d]); 
    if ((t[d]!='(') || (t[f]!=')') ) return EXIT_FAILURE; 
    // else cas : // (NBBN)
    if ((d-f)==4) return construitComposee( 
                            getImageSimpleTxt(t[d+1]),
                            getImageSimpleTxt(t[d+2]),
                            getImageSimpleTxt(t[d+3]),
                            getImageSimpleTxt(t[d+4])); 
    // else  cas : ( N (BBNB) (NBBN) N ) 
    image* imgT[4]; 
    int imageIndex =0; 
    for (int i=d+1; i<f; i++){ // d=(  f=)
        if (t[i]!='('){ 
            imgT[imageIndex] = getImageSimpleTxt(t[i]); 
            imageIndex++;
        }else {
            int s = i ; 
            int e = i ; 
            int p = 1; 
            while (p!=0 && e<f)
            {
                if (t[i]=='(' ) p++;
                if (t[i]==')' ) p--; 
                e++; 
            }
            imgT[imageIndex] = getImageTxt(t, s, e);
        }
    }
    return construitComposee(imgT[0],imgT[1],imgT[2],imgT[3]); 
}







// Bien Forme :  estBlancheBienForme: supposant que BBBB ce simplifie en B et NNNN en N et que le bool fonctionne bien 
bool estBlancheBF(image im){
    return im==NULL; 
}
bool estNoireBF(image im){
    if(estBlancheBF(im)) return FALSE; 
    // else (soit noire soit composee )
    return im->toutNoire; 
}

// Non Formee : 
bool estBlancheNF(image im){
    if(im==NULL) return TRUE; 
    return estBlancheNF(im->fils[0]) && estBlancheNF(im->fils[1]) && estBlancheNF(im->fils[2]) && estBlancheNF(im->fils[3]) ; 
}

bool estNoireNF(image im){
    if(im==NULL) return FALSE; 
    return estNoireNF(im->fils[0]) && estNoireNF(im->fils[1]) && estNoireNF(im->fils[2]) && estNoireNF(im->fils[3]) ; 
}

bool filsNoir(image im){
    return estNoireBF(im->fils[0]) && estNoireBF(im->fils[1]) && estNoireBF(im->fils[2]) && estNoireBF(im->fils[3]) ; 
}

bool filsBlanc(image im){
    return estBlancheBF(im->fils[0]) && estBlancheBF(im->fils[1]) && estBlancheBF(im->fils[2]) && estBlancheBF(im->fils[3]) ; 
}




bool estBlanche(image im){
    if (estBlancSimple(im)) return TRUE;
    // si bien formee: return im->toutnoir == FALSE ;  
    return (im->toutnoir==FALSE) && estBlanche(im->fils[0])&& estBlanche(im->fils[1])&& estBlanche(im->fils[2])&& estBlanche(im->fils[3]); 

}


/*


if p = 0 then rendre imNoire
else p=1 then rendre construireimage(rec(p-1)bbrec(p-1))



*/


image diagonale(int p) {
    if (p==0) return construitNoir(); 
    // else 
    return construitComposee(diagonale(p-1),construitBlanc(),construitBlanc(), diagonale(p-1));  
}





image quartDeTour( image im) {
	if(estBlanche(im)) return im ; 
	if(estNoire(im)) return im ; 
	// else 
	return construitComposee(quartDeTour(im->fils[0]),quartDeTour(im->fils[1]),quartDeTour(im->fils[2]),quartDeTour(im->fils[3])); 
}



image negative(image im){
    if (estBlancheBF(im)) return construitNoir();
    // else soit noire ou construite 
    if (estNoireBF(im)) return construitBlanc();
    // else consutruite : 
    return construitComposee(negative(im->fils[0]), negative(im->fils[1]), negative(im->fils[2]), negative(im->fils[3])) ; 
    
}

void simplifieProfP(image* im, int p ){
    if(p==0) simplifie(im);
    else {
        for (int i=0; i<4; i++){
            simplifieProfP((&((*im)->fils[i])), p-1) ; 
        }
    }
}

// im NF: 
void simplifie(image* im){
    if (*im == NULL) return ; 
    for (int i=0; i<4; i++) simplifie(&((*im)->fils[0])); 
    // a partir de la les fils sont bien formee: 
    if (filsNoir(*im)){
        for (int i=0; i<4; i++) detruire(&((*im)->fils[i])); 
        (*im)->toutnoir = TRUE ; 
        return ; 
    }
    if ( (NOT (*im)->toutnoir)   && filsBlanc(*im)){
        detruire(im); 
        return ; 
    }
}

bool sontToutesBlanches(image im) {
    if (im==NULL) return TRUE; 
    // else 
    return sontToutesBlanches(im->fils[0]) &&  sontToutesBlanches(im->fils[1]) &&  sontToutesBlanches(im->fils[2]) &&  sontToutesBlanches(im->fils[3]) ; 
}

bool sontToutesNoire(image im) {
    if (im==NULL) return FALSE; 
    // else // return im->toutNoire; 
    return sontToutesNoire(im->fils[0]) &&  sontToutesNoire(im->fils[1]) &&  sontToutesNoire(im->fils[2]) &&  sontToutesNoire(im->fils[3]) ; 
}


void detruire(image* im){
    if(im != NULL && *im !=NULL){
        for (int i=0 ; i<4; i++) detruire(&((*im)->fils[i])); 
        free(im); 
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
bool incluse(image im1, image im2){
    if (estBlancheNF(im2)) return estBlancheNF(im1);
    if (estNoireNF(im2)) return estNoireNF(im1); 
    // else im2 construite: 
    return incluse(im1, im2->fils[0]) ||  incluse(im1, im2->fils[1]) ||  incluse(im1, im2->fils[2]) ||  incluse(im1, im2->fils[3]) || incluseComposee(im1,im2); 
}


bool incluseComposee( image im1, image im2){
    return FALSE; // todo 
}

int hautMaxBlanc( image im) {
    if (im==NULL) return 0; 
    // else soit noir ou composee 
    if (im->toutnoir) return -1; 
    // else composee : 
    int hmb0 = hautMaxBlanc(im->fils[0]); 
    int hmb1 = hautMaxBlanc(im->fils[1]); 
    int hmb2 = hautMaxBlanc(im->fils[2]); 
    int hmb3 = hautMaxBlanc(im->fils[3]); 
    return (max(hmb0, hmb1, hmb2, hmb3) +1); 
}


int max ( int a, int b, int c, int d){
    return max2(max2(a,b),max2(c,d)); 
}

int max2(int a, int b){
    if (a<b) return b;
    return a; 
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
        if (x<taille/2) c = 0 ; 
        else c=1; 
        if (y<taille/2) l = 0 ; 
        else {
            l=1;
            y = y-taille/2; 
        }
        int fils ; 
        if (l==1) fils = c; 
        else fils = 3+c;  
        blanchitProfPCase((*im)->fils[fils], p-1, x, y, newTaille); 
    }
}


void blanchitProfP(image* im, int p, int x, int y){
    int taille = pow(2,p); 
    blanchitProfPCase(im, p, x, y, taille);
}


image chute(image im) {
    if (estBlancheNF(im)) return im; 
    return construitComposee(construitBlanc(), construitBlanc(), unionNoir(chute(im->fils[0]),chute(im->fils[3])),  unionNoir(chute(im->fils[2]),chute(im->fils[4]))) ; 
}

image unionNoir(image im1, image im2){
    if(estBlancheNF(im1)) return im2;
    if (estNoireNF(im1)) return im1; 
    // else composee 
    if (estBlancheNF(im2)) return im1; 
    return construitComposee(unionNoir(im1->fils[0], im2->fils[0]), unionNoir(im1->fils[1], im2->fils[1]), unionNoir(im1->fils[2], im2->fils[2]), unionNoir(im1->fils[3], im2->fils[3])   ); 

}







/*************************************************/
/*                                               */
/*           test gen                            */
/*                                               */
/*************************************************/

// a la fin 





/*************************************************/
/*                                               */
/*           Main                                */
/*                                               */
/*************************************************/

// a la fin 