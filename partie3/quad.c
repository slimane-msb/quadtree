#include <stdio.h>
#include <stdlib.h>

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

typedef struct bloc_image { 
        bool toutnoir ;
        struct bloc_image * fils[4] ;
    } bloc_image ;
typedef bloc_image *image ;


image Construit_Blanc(){
    return NULL;
}

image Construit_Noir(){
    image img =  (image) malloc(sizeof(bloc_image));
    img->toutnoir = TRUE ;
    img->fils[0] = NULL;
    img->fils[1] = NULL;
    img->fils[2] = NULL;
    img->fils[3] = NULL;
    return img;
}


image Construit_Composee(image i0,image i1,image i2, image i3){
    image img =  (image) malloc(sizeof(bloc_image));
    img->toutnoir = FALSE ;
    img->fils[0] = i0;
    img->fils[1] = i1;
    img->fils[2] = i2;
    img->fils[3] = i3;
    return img;
}

void affichage_Normal(image img){
    if (img == NULL){
        printf("B");
    }
    else if (img->toutnoir){
        printf("N");
    }
    else  {
        printf("(");
        affichage_Normal(img->fils[0]);
        affichage_Normal(img->fils[1]);
        affichage_Normal(img->fils[2]);
        affichage_Normal(img->fils[3]);
        printf(")");
    }

}



void affichage_ProfondeurBis(image img,int count){
    if (img == NULL){
        printf("B%d ",count);
    }
    else if (img->toutnoir){
        printf("N%d ", count);
    }
    else  {
        count++;
        printf("( ");
        affichage_ProfondeurBis(img->fils[0],count);
        affichage_ProfondeurBis(img->fils[1],count);
        affichage_ProfondeurBis(img->fils[2],count);
        affichage_ProfondeurBis(img->fils[3],count);
        printf(") ");
    }

}

void affichage_Profondeur(image img){
    affichage_ProfondeurBis(img,0);
    printf("\n");
}

// avec lecture clavier ; 
image Lecture(){
    char c = getchar();
    if (c == 'B'){
        return Construit_Blanc();
    }
    else if (c == 'N')
    {
        return Construit_Noir();
    }
    else if (c == '('){
        image i1 = Lecture();
        image i2 = Lecture();
        image i3 = Lecture();
        image i4 = Lecture();
        return Construit_Composee(i1,i2,i3,i4);
    }
    else {
        return Lecture();
    }
} 


bool estNoire(image img){
    if (img == NULL){
        return FALSE; 
    }
    else if (img->toutnoir){
        return TRUE;
    }
    else {
        return estNoire(img->fils[0]) && estNoire(img->fils[1]) 
        && estNoire(img->fils[2]) && estNoire(img->fils[3]) ;
    }
}

bool estBlanche(image img){
     if (img == NULL){
        return TRUE; 
    }
    else if (img->toutnoir){
        return FALSE;
    }
    else {
        return estBlanche(img->fils[0]) && estBlanche(img->fils[1]) 
        && estBlanche(img->fils[2]) && estBlanche(img->fils[3]) ;
    }
}




// before done 

void DiagonaleBis(int p, image *img){
    if (p == 0){
        (*img) = Construit_Noir();
    }
    else if (p != 0){
        p--;
        image i1 ;
        image i4 ;
        DiagonaleBis(p, &i1);
        DiagonaleBis(p, &i4);
        (*img) = Construit_Composee(i1,Construit_Blanc(),Construit_Blanc(),i4);
    
    }

}

image Diagonale(int p){
    image img;
    DiagonaleBis(p,&img);
    return img;
    
}


void QuartDeTour(image* img){
    if (*img == NULL || (*img)->toutnoir){
            //ne rien faire
    }
    else {
    QuartDeTour(&(*img)->fils[0]);
    QuartDeTour(&(*img)->fils[1]);
    QuartDeTour(&(*img)->fils[2]);
    QuartDeTour(&(*img)->fils[3]);
    (*img) = Construit_Composee((*img)->fils[2],(*img)->fils[0],(*img)->fils[3],(*img)->fils[1]);
    }
    
    
}

void Negatif(image *img){
    if ((*img) == NULL){
        (*img) = Construit_Noir();
    }
    else if ((*img)->toutnoir )
        (*img) = Construit_Blanc();
    else
    {
        Negatif(&((*img)->fils[0]));
        Negatif(&((*img)->fils[1]));
        Negatif(&((*img)->fils[2]));
        Negatif(&((*img)->fils[3]));
    }
     
}

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
            *img = Construit_Blanc();
        }

        else if (estNoire(*img)){
            *img = Construit_Noir();
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

bool Incluse(image img1, image img2){
    
}
int max(int n, int m){
    return n > m ? n : m;
}

int max4(int a, int b ,int c, int d){
    return max(max(a,b),max(c,d));
}
//TODO : optimisable ? estBlanche en trop ?
int HautMaxBlanc(image img){
    if (img == NULL){
        return 0;
    }
    else if (img->toutnoir)
        return -1;
    else {
        if(estBlanche(img)){
            return 1 + max4(HautMaxBlanc(img->fils[0]),HautMaxBlanc(img->fils[1]),HautMaxBlanc(img->fils[2]),HautMaxBlanc(img->fils[3]));
        }
        else {
           return   max4(HautMaxBlanc(img->fils[0]),HautMaxBlanc(img->fils[1]),HautMaxBlanc(img->fils[2]),HautMaxBlanc(img->fils[3]));
        }
    }
}

void BlanchitProfP(image *img,int p,int x,int y){
    /* printf("Profondeur : %d ", p);
    affichage_Normal(*img);
    printf("\n"); */
    if (p > 0){
        if ((*img) == NULL){
        }
        else if ((*img)->toutnoir){
            --p;
            image i1 = Construit_Noir();
            image i2 = Construit_Noir();
            image i3 = Construit_Noir();
            image i4 = Construit_Noir();
            

            BlanchitProfP(&i1,p,x*2,y*2);
            BlanchitProfP(&i2,p,x*2,y*2);
            BlanchitProfP(&i3,p,x*2,y*2);
            BlanchitProfP(&i4,p,x*2,y*2);

            *img = Construit_Composee(i1,i2,i3,i4);
        }
        else{
            p--;
            if (x/2 > 0 && y/2 > 0){
                printf("NE %d %d\n",x/2,y/2);
                BlanchitProfP(&((*img)->fils[1]),p,x/2-1,y/2-1);
            }
            else if (x/2 == 0 && y/2 > 0){
                printf("NO %d %d\n",x/2,y/2);
                BlanchitProfP(&((*img)->fils[0]),p,x/2,y/2-1);
            }
            else if (x/2 == 0 && y/2 == 0){
                printf("SO %d %d\n",x/2,y/2);
                BlanchitProfP(&((*img)->fils[3]),p,x/2,y/2);
            }
            else if (x/2 > 0 && y/2 == 0){
                printf("SE %d %d\n",x/2,y/2);
                BlanchitProfP(&((*img)->fils[4]),p,x/2-1,y/2);
            }
            else{
                printf(" BIZZZZARE %d %d %d\n",p,x,y);
            }

        }
    }
   else if (p == 0){
        if((*img) == NULL){}
        else{
            printf("Blanchit : %d %d\n",x,y);
            *img = Construit_Blanc();
        }
    }    

}
