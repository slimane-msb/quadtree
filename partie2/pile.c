// todo: recopier les signature avant toutes les fonctions 
#include <stdio.h>
#include <stdlib.h>

/*************************************************/
/*                                               */
/*                sucre syntaxique               */
/*                                               */
/*************************************************/

#define AND &&
#define OR ||
#define ISNOT !=
#define NOT !
#define then

typedef enum { FALSE, TRUE} bool;

/*************************************************/
/*                                               */
/*          definition type liste                */
/*                                               */
/*************************************************/

typedef struct Bloc
{
    int nombre;
    struct Bloc *suivant;
    struct Bloc *pred; // a utiliser que pour la dernier question 
} Bloc;

typedef Bloc *Liste ;


typedef struct BlocListe
{
    Liste list;
    struct BlocListe *suivant;
} BlocListe;

typedef BlocListe *ListeListe ;

/*************************************************/
/*                                               */
/*                predeclarations                */
/*                                               */
/*************************************************/

/* initialise une Liste vide */
void initVide(Liste *L);

/* renvoie 1 si la Liste en parametre est vide, 0 sinon */
bool estVide(Liste l);

/* renvoie le premier element de la Liste en parametre */
int premier(Liste l);

/* renvoie une nouvelle Liste correspondant a celle en parametre, avec l'element x ajoute en haut de la pile */
Liste ajoute(int x, Liste l);

/* modifie la Liste en parametre: x est ajoute comme premier element */
void empile(int x, Liste* L);

/* renvoie une nouvelle Liste correspondant a celle en parametre sans son premier element */
Liste suite(Liste l);

/* modifie la Liste en parametre: le premier element est retire */
void depile(Liste* l);

/* affichage simple en recursif et en iteratif */
void affiche_rec(Liste l);
void affiche_iter(Liste l);

/* longueur en recursif et en iteratif */
int longueur_rec (Liste l);
int longueur_iter (Liste l);

/*  Elimination du dernier element en recursif et en iteratif  */
/*  VD est la sousprocedure utilitaire de la version recursive */
void VD (Liste *L);
void VireDernier_rec (Liste *L);
void VireDernier_iter (Liste *L);


/*************************************************/
/*                                               */
/*                briques de base                */
/*                                               */
/*************************************************/


void initVide( Liste *L)
{
    *L = NULL ;
}

bool estVide(Liste l)
{
    return l == NULL ;
}

int premier(Liste l)
{
    return l->nombre ; 
}

Liste ajoute(int x, Liste l)
{
    Liste tmp = (Liste) malloc(sizeof(Bloc)) ;
    tmp->nombre = x ;
    tmp->suivant = l ;
    return tmp ;
}

ListeListe ajoutell(Liste x, ListeListe l)
{
    ListeListe tmp = (ListeListe) malloc(sizeof(BlocListe)) ;
    tmp->list = x ;
    tmp->suivant = l ;
    return tmp ;
}

void empile(int x, Liste *L)
{
      *L = ajoute(x,*L) ; 
}

Liste suite(Liste l)
{
    return l->suivant ;
}


void depile(Liste *L)
{
    Liste tmp = *L ;
    *L = suite(*L) ;
    free(tmp) ;
}

/*************************************************/
/*                                               */
/*     Affiche, avec les briques de base         */
/*                                               */
/*************************************************/

void affiche_rec(Liste l)
{
    if(estVide(l))
        printf("\n");
    else
    {
        printf("%d ", premier(l));
        affiche_rec(suite(l));
    }
}


void affiche_iter(Liste l)
{
    Liste L2 = l;
    while(!estVide(L2))
    {
        printf("%d ", premier(L2));
        L2 = suite(L2);
    }
    printf("\n");
}

/*************************************************/
/*                                               */
/*     Longueur, sans les briques de base        */
/*                                               */
/*************************************************/

int longueur_rec (Liste l)
{
    if (l == NULL)
         return 0 ;
    else return (1 + longueur_rec(l->suivant)) ;
}


int longueur_iter (Liste l)
{
    Liste P = l;
    int cpt = 0 ;
    while (P ISNOT NULL)
    {   P = P->suivant ;
        cpt++ ;
    }
    return cpt ;
}

/*************************************************/
/*                                               */
/*       VireDernier,                            */
/*               sans les briques de base,       */
/*               ni le "->"                      */
/*                                               */
/*************************************************/

void VD (Liste *L)
          // *L non NULL ie liste non vide
{
     if ( ((**L).suivant) == NULL )
            depile(L) ;   // moralement : depile(& (*L)) ;
     else VD (& ( (**L).suivant )) ;
}

void VireDernier_rec (Liste *L)
{
     if ( (*L) ISNOT NULL )
          VD(L);        // moralement : VD(& (*L)) ;
}

void VireDernier_iter (Liste *L)
{
    if ( (*L) ISNOT NULL)
    {
        while ( ((**L).suivant) ISNOT NULL )
                 L = & ( (**L).suivant ) ;
        free(*L) ;
        *L = NULL ;
     }
}


/*************************************************/
/*                                               */
/*       Libere la memoire                       */
/*                                               */
/*************************************************/

void VideListe(Liste *L)
{
    if(NOT(estVide(*L)))
    {
        depile(L);
        VideListe(L);
    }
      
}

// todo: signature cop

/*************************************************/
/*                                               */
/*       zeroen123                               */
/*                                               */
/*************************************************/

/*compilation paresseuse */
bool ZeroEnPositionUnOuDeuxOuTrois(Liste l){
    return (l ISNOT NULL)AND(premier(l)==0 OR 
                (suite(l) ISNOT NULL AND (premier(suite(l)==0) OR 
                    (suite(suite(l) ISNOT NULL AND premier(suite(suite(l)==0)))))));
}

/*************************************************/
/*                                               */
/*       Pluscourte                              */
/*                                               */
/*************************************************/

bool Pluscourte(Liste l1, Liste l2){
    if (estVide(l2)) return FALSE;
    if (estVide(l1)) return TRUE;
    return Pluscourte(suite(l1),suite(l2));
}



/*************************************************/
/*                                               */
/*       NombreDe0AvantPositionK                 */
/*                                               */
/*************************************************/
/*rec non terminal*/
int NombreDe0AvantPositionKnt(Liste l, int k){
    if (estVide(l) OR k==0) return 0;
    if (premier(l)==0) return 1+NombreDe0AvantPositionKnt(suite(l),k-1);
    return NombreDe0AvantPositionKnt(suite(l),k-1);
}

/*rec sous fonction terminal */
int NombreDe0AvantPositionKsf(Liste l, int k){
    return sfNDAPK(l,k,0);
}

int sfNDAPK(Liste l, int k, int r){
    if (estVide(l) OR k==0) return r;
    if (premier(l)==0) return sfNDAPK(suite(l),k-1,r+1);
    return sfNDAPK(suite(l),k-1,r);
}


/*rec sous procedure terminal */
int NombreDe0AvantPositionKsp(Liste l, int k){
    int r=0;
    spNDAPK(l,k,&r);
    return r;
}

void spNDAPK(Liste l, int k, int* r){
    if (estVide(l) OR k==0) return;
    if (premier(l)==0) {
        *r = *r+1;
        spNDAPK(suite(l),k-1,r);
    } else spNDAPK(suite(l),k-1,r);
}

/* iteratif*/
int NombreDe0AvantPositionKi(Liste l, int k){
    int r=0;
    while (l ISNOT NULL AND k!=0)
    {
        if (premier(l)==0) r++;
        k--;
        l = suite(l); 
    }
    return r;
}




/*************************************************/
/*                                               */
/*           NombreDe0ApresRetroPositionK        */
/*                                               */
/*************************************************/

/*rec sous fonction non terminal - une seul passe */
int NombreDe0ApresRetroPositionK(Liste l, int k){
    if (k==0) return 0; // car si k=0 on fera pas le parcours de l'annaire de paris pour just renvoyer 0
    int posInv;
    return sfNDARPK(l,k,&posInv);
}

int sfNDARPK(Liste l, int k, int* posInv){
    if (estVide(l)) {
        *posInv=k; 
        return 0;
    }
    // sinon
    int r = sfNDARPK(suite(l),k,posInv);
    *posInv=*posInv-1;
    if (*posInv==0) return r;
    if (premier(l)==0) return r++;
}




/*************************************************/
/*                                               */
/*           FctBegaye                           */
/*                                               */
/*************************************************/


/* rec sans sous fonction*/

Liste FctBegayessf(Liste l){
    if (estVide(l)) return l;
    // sinon
    if (premier(l)<0) return  FctBegayessf(suite(l));
    return ajoute(premier(l),ajoute(premier(l),FctBegayessf(suite(l))));
}

/* rec terminal */


/*
    lf : pointeur vers le dernier bloc 
    l  : pointeur vers le premier bloc 
*/
Liste FctBegayeT(Liste l){
    Liste r;
    Liste lf; 
    return FctBegayeTbis(l, r,  lf);

}
Liste FctBegayeTbis(Liste l, Liste r, Liste pfin){
    if (estVide(l)) return r;
    // sinon
    if (premier(l)<0) return  FctBegayeTbis(suite(l),r,pfin);
    else {
        ajouteFin(premier(l),pfin);
        ajouteFin(premier(l),pfin); // car deux fois
        return FctBegayeTbis(suite(l),r,pfin);
    }
}

/*ajouter un element a la fin, avec fl : pointeur vers le dernier bloc */
Liste ajouteFin(int x, Liste fl)
{
    Liste tmp = (Liste) malloc(sizeof(Bloc)) ;
    tmp->nombre = x ;
    tmp->suivant = NULL;
    fl->suivant = tmp;
    return tmp ;
}


/* iteratif: */


Liste FctBegayeI (Liste l){
    Liste r;
    Liste lf; // pointeur vers la fin de r
    while (NOT estVide(l)){
        if (premier(l)>=0) {
            ajouteFin(premier(l), lf);
            ajouteFin(premier(l), lf);
        }
        l = suite(l);
    }
    return r;
}





/*************************************************/
/*                                               */
/*           ProcBegaye                          */
/*                                               */
/*************************************************/

Liste ProcBegayeT(Liste l){
    Bloc* d = l; // pointeur vers le bloc avant le bloc pointe' par l;
    ProcBegayeTbis(l, d);
    return (Liste)d;

}
// just peut etre il faut faire quelque cast List() mais gcc 
void ProcBegayeTbis(Liste l, Bloc* d){
    if (estVide(l)) return;
    // sinon
    if (premier(l)<0) { // virer p(l)        
        d->suivant = l->suivant;
        free(l); // free bloc qui contient p(l)<0
        ProcBegayeTbis(d->suivant,d);
    }else {
        Bloc* dup = malloc(sizeof(Bloc)) ;
        dup->nombre = premier(l) ;
        dup->suivant = l->suivant;
        l->suivant = dup;
        ProcBegayeTbis(dup->suivant,dup);
    }
}




/*************************************************/
/*                                               */
/*           Permutations                        */
/*                                               */
/*************************************************/

ListeListe permutation (int n){
    if (n==0){
        ListeListe ll;
        return ll;
    }else{
        return ATLTP(n, permutation(n-1));
    }
}


Liste ATLTP(int n, ListeListe ll){
    if (ll == NULL){
        Liste l;
        return l; // peut-on faire return (Liste)NULL; ? 
    }else{
        return concat(ATP(n, ll->list), ATLTP(n, ll->suivant));
    }
}

Liste concat(Liste l1, Liste l2){
    if (estVide(l1)) return l2;
    else return ajoute(premier(l1),concat(suite(l1),l2));
}

ListeListe ATP (int n, Liste l){
    if (estVide(l)) {
        ajoute(n,l);
        ListeListe ll;
        return ajoutell(l,ll);
    } else return ajoutell(ajoute(n,l),AETTL(premier(l),ATP(n,suite(l))));
}

ListeListe AETTL (int n, ListeListe ll){
    if (ll==NULL) return ll;
    else return ajoutell(ajoute(n,ll->list),AETTL(n,ll->suivant));
}



/*************************************************/
/*                                               */
/*           retire                              */
/*                                               */
/*************************************************/

void retir (Liste l, Bloc* p){
    if (estVide(l)) return;
    else {
        if (l->pred==p){
            l->suivant->pred = l->pred;
            l->pred->suivant = l->suivant;
            free(l);
            return;
        }else{
            retir(suite(l),p);
        }
    }
}








/*************************************************/
/*                                               */
/*           Main                                */
/*                                               */
/*************************************************/

void poup (Liste l)
{
        printf("Double Affichage \n") ;
        affiche_rec(l) ;
        affiche_iter(l) ;

        printf("Longueur en double %d %d \n\n", 
                           longueur_rec(l), 
                           longueur_iter(l) 
               ) ;
}

int main(int argc, char** argv)
{
    Liste l ;

        initVide (&l) ;

          poup(l) ;

             empile(4, &l) ;

          poup(l) ;

             empile(5, &l) ;
             empile(6, &l) ;
             empile(7, &l) ;
             empile(8, &l) ;
             empile(9, &l) ;

          poup(l) ;

        VireDernier_rec  (&l) ;
        VireDernier_iter (&l) ;
        depile(& l) ;

          poup(l) ;

    VideListe(&l);
    return 0;
}





