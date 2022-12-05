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


image construitBlanc();
image construitNoir ();
image construitComposee( image i0, image i1, image i2, image i3);
void afficheNoir(); 
void afficheBlanc(); 
void afficheInt(int i);
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
bool filsNoir(image im);
bool filsBlanc(image im);
image diagonale(int p) ;
image quartDeTour( image im) ;
void SimplifieProfP(image *img,int p);
bool sontToutesBlanches(image im) ;
bool sontToutesNoire(image im) ;
void detruire(image* im);
bool incluse(image im1, image im2);
bool incluseComposee( image im1, image im2);
int hautMaxBlanc( image im) ;
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

image construitComposee( image i0, image i1, image i2, image i3){
    image img =  (image) malloc(sizeof(bloc_image));
    if (((i0)==NULL)&&((i1)==NULL)&&((i3)==NULL)&&((i3)==NULL)) return construitBlanc();
    // else 
    if (((i0)->toutnoir)&&(estNoireBF(i1))&&(estNoireBF(i3))&&(estNoireBF(i3))) return construitNoir();
    // else 
    image res = malloc (sizeof(bloc_image)); 
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

void afficheNormalRL(image im){
    afficheNormal(im);
    printf("\n");
}

void afficheNormal( image im){
    if ((im)==NULL) { afficheBlanc() ; return; } 
    if ((im)->toutnoir) { afficheNoir(); return ; }  
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
    if ((im)==NULL) { afficheBlanc(); afficheInt(prof)  ; return; } 
    if ((im)->toutnoir) { afficheNoir(); afficheInt(prof) ; return ; }  
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
    *cur+=1 ; // get char : 
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

// Bien Forme :  estBlancheBienForme: supposant que BBBB ce simplifie en B et NNNN en N et que le bool fonctionne bien 
bool estBlancheBF(image im){
    return im==NULL; 
}
bool estNoireBF(image im){
    if((im)==NULL) return FALSE; 
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
	if((im)==NULL || im->toutnoir ) return im ; 
	// else 
	return construitComposee(quartDeTour(im->fils[2]),quartDeTour(im->fils[0]),quartDeTour(im->fils[3]),quartDeTour(im->fils[1])); 
}



void Negatif(image *img){
    if ((*img) == NULL){
        (*img) = construitNoir();
    }
    else if ((*img)->toutnoir )
        (*img) = construitBlanc();
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
/*     if (img == NULL){
        return TRUE; 
    }
    else if (img->toutnoir){
        return FALSE;
    }
    else {
        return estBlanche(img->fils[0]) && estBlanche(img->fils[1]) 
        && estBlanche(img->fils[2]) && estBlanche(img->fils[3]) ;
    } */
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
    else  {
        p--;
        if ( !((*img) == NULL || (*img)->toutnoir)){
            SimplifieProfP(&((*img)->fils[0]),p);
            SimplifieProfP(&((*img)->fils[1]),p);
            SimplifieProfP(&((*img)->fils[2]),p);
            SimplifieProfP(&((*img)->fils[3]),p);
        }

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
    if (estBlanche(im2)) return estBlanche(im1);
    if (estNoire(im2)) return estNoire(im1); 
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
    if(estBlanche(im)) return (max(hmb0, hmb1, hmb2, hmb3) +1);
    else return (max(hmb0, hmb1, hmb2, hmb3)); 
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
        detruire( &((*im)->fils[fils]));
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
    if (estBlanche(im)) return im; 
    return construitComposee(construitBlanc(), construitBlanc(), unionNoir(chute(im->fils[0]),chute(im->fils[3])),  unionNoir(chute(im->fils[2]),chute(im->fils[4]))) ; 
}

image unionNoir(image im1, image im2){
    if(estBlanche(im1)) return im2;
    if (estNoire(im1)) return im1; 
    // else composee 
    if (estBlanche(im2)) return im1; 
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

int main(int argc, char const *argv[])
{
    image img = construitComposee(construitBlanc(),construitNoir(),construitNoir(),construitBlanc());
    image img2 = construitComposee(construitNoir(),construitBlanc(),img,construitNoir());
    image img3 = construitComposee(construitNoir(),construitBlanc(),construitBlanc(),img2);
    afficheProfondeur(img3); 
     image img  = construitComposee(construitNoir(),construitNoir(),construitNoir(),
        construitComposee(construitNoir(),construitNoir(),
        construitComposee(construitNoir(),construitNoir(),construitNoir(),construitNoir()), construitNoir()));
    printBool(estNoire(img)); 

     image img = diagonale(0);
    afficheNormal(img); 
     Negatif(&img3);
    afficheNormal(img3);
    printf("\n"); 
     char *str = "(N(BBNN)(BBNN)N)";
    printf("%s\n",str);  
    //image img = construitNoir();
     image img = construitComposee(construitComposee(construitBlanc(),construitNoir(),construitNoir(),construitNoir()),
                        construitBlanc(),construitComposee(construitNoir(),construitNoir(),construitBlanc(),construitBlanc()),construitNoir());
    quartDeTour(&img);
    afficheNormal(img); 
     image img2 = construitComposee(construitNoir(),
    construitComposee(construitBlanc(),construitNoir(),construitNoir(),construitNoir()),
    construitComposee(construitBlanc(),construitBlanc(),construitNoir(),construitNoir()),construitNoir());
    image img = Lecture();
    affichage_Profondeur(img2);
    affichage_Profondeur(img);
 
     image i1 = construitComposee(construitNoir(),construitBlanc(),construitComposee(construitNoir(),construitNoir(),
    construitComposee(construitNoir(),construitNoir(),construitNoir(),construitNoir())
    ,construitNoir())
    ,construitBlanc());

    image i2 = construitComposee(construitNoir(),construitBlanc(),construitNoir(),
    construitComposee(construitNoir(),construitBlanc(),construitNoir(),
    construitComposee(construitBlanc(),construitBlanc(),construitBlanc(),construitBlanc())));

    image i3 = construitComposee(construitBlanc(),construitBlanc(),
    construitComposee(construitBlanc(),construitBlanc(),construitBlanc(),construitBlanc()),construitBlanc());
    image img  = construitComposee(construitNoir(),i1,i2,i3);
    //SimplifieProfP(&img,2);
    afficheNormal(img); 
 
    
    image img = Lecture();
     SimplifieProfP(&img,2);
    afficheNormal(img); 
    blanchitProfP(&img,2,1,3);
    afficheNormal(img);

    return 0;
}
