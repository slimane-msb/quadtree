#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	
// je vois pas trop c'est quoi transformer une image en image negative 

void simplifieProfP(image* im, int p ){
    if(p==0) simplifie(im);
    else {
        for (int i=0; i<4; i++){
            simplifieProfP(&((*im)->fils[i])), p-1) 
        }
    }
}




// im NF: 
void simplifie(image* im){
    if (*im == NULL) return ; 
    for (int i=0; i<4; i++) simplifie(&((*im)->fils[0]); 
    // a partir de la les fils sont bien formee: 
    if (filsNoir(*im)){
        for (int i=0; i<4; i++) detruire(&((*im)->fils[i])); 
        (*im)->toutNoire = true ; 
        return ; 
    }
    if ( (NOT (*im)->toutNoire)   && filsBlanc(*im)){
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


// elle fait quoi incluse : ? 


int hautMaxBlanc( image im) {
    if (im==NULL) return 0; 
    // else 
    if (NOT im->toutNoire)
    // else 
    if (im->toutNoire) return -1; 
    // else 
    hmb0 = hautMaxBlanc(im->fils[0]); 
    hmb1 = hautMaxBlanc(im->fils[1]); 
    hmb2 = hautMaxBlanc(im->fils[2]); 
    hmb3 = hautMaxBlanc(im->fils[3]); 
    return (max(hmb0, hmb1, hmb2, hmb3) +1); 
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