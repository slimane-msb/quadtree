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

bool estBlanc(image i){
    return i==NULL; 
}

bool sontFilsNull( bloc_image** fils){
    return fils[0]==NULL && fils[1]==NULL &&fils[2]==NULL &&fils[3]==NULL ; // on suppose une compilation paresseuse
}

bool estNoir(image i){
    if(i!=NULL) return ( i->toutnoir == TRUE ) && sontFilsNull(i->fils); // si on a bien creer les images | toutnoi == true suffit, mais on verifier quand les fils, car c'est rapide pour tester si c'est null 
    return FALSE ; 
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