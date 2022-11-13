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


void affiche_recLL(ListeListe ll)
{
    if(ll=NULL)
        printf("\n");
    else
    {
        affiche_rec(ll->list);
        affiche_recLL(ll->suivant);
    }
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
    return (l ISNOT NULL)AND(
        (premier(l)==0) OR (
            (suite(l) ISNOT NULL) AND (
                (premier(suite(l))==0) OR (
                    (suite(suite(l) ISNOT NULL) AND (premier(suite(suite(l)==0))))
                )
            )
        )
    );
}

/*************************************************/
/*                                               */
/*       Pluscourte                              */
/*                                               */
/*************************************************/

bool Pluscourte(Liste l1, Liste l2){
    if (estVide(l2)) return FALSE;
    if (estVide(l1)) return TRUE;
    else return Pluscourte(suite(l1),suite(l2));
}


/*************************************************/
/*                                               */
/*       NombreDe0AvantPositionK                 */
/*                                               */
/*************************************************/
/*rec non terminal*/
int NombreDe0AvantPositionKRec(Liste L, int K){
    if (estVide(L) || K <= 0) return 0;
    if (premier(L) == 0) return 1 + NombreDe0AvantPositionKRec(suite(L), K-1);
    else return NombreDe0AvantPositionKRec(suite(L), K-1);
}

/*rec sous fonction terminal */
int NombreDe0AvantPositionKRecTermBis(Liste L, int K, int res){
    if (estVide(L) || K <= 0) return res;
    else if (premier(L) == 0) return NombreDe0AvantPositionKRecTermBis(suite(L), K-1, (res+1));
    else return NombreDe0AvantPositionKRecTermBis(suite(L), K-1, res);
}
int NombreDe0AvantPositionKRecTerm(Liste L, int K){
    return NombreDe0AvantPositionKRecTermBis(L, K, 0);
}


/*rec sous procedure terminal */
void NombreDe0AvantPositionKRecTermProcBis(Liste L, int K, int *res){
    if (!(estVide(L) || K <= 0)){
        if (premier(L) == 0){
            *res+=1;
            NombreDe0AvantPositionKRecTermBis(suite(L), K-1, res);
        }
        else NombreDe0AvantPositionKRecTermBis(suite(L), K-1, res);
    }
}
int NombreDe0AvantPositionKRecTermProc(Liste L, int K){
    int res = 0;
    NombreDe0AvantPositionKRecTermProcBis(L, K, &res);
    return res; 
}


/* iteratif*/
int NombreDe0AvantPositionKIter(Liste L, int K){
    int res = 0;
    while (!(estVide(L) || K <= 0))
    {
        if (premier(L) == 0)
            res ++;
        L = suite(L);
        K--;
    }
    return res;;
} 




/*************************************************/
/*                                               */
/*           NombreDe0ApresRetroPositionK        */
/*                                               */
/*************************************************/

/*rec sous fonction non terminal - une seul passe */
void NombreDe0ApresRetroPositionKBis(Liste L,int* K,int* res){
    
    if (L != NULL) {
        NombreDe0ApresRetroPositionKBis(suite(L), K ,res);
        if (*K > 0  && premier(L) == 0 )
            ++*res;
        --*K;
    }

    
} 


int NombreDe0ApresRetroPositionK(Liste L,int K){
    int res = 0;
    NombreDe0ApresRetroPositionKBis(L,&K, &res);
    return res;
}




/*************************************************/
/*                                               */
/*           FctBegaye                           */
/*                                               */
/*************************************************/


/* rec sans sous fonction*/

Liste FctBegayeSimple(Liste l){
    if (l == NULL)
        return l;
    else{
        if (premier(l) > 0 ){
            return ajoute(premier(l),ajoute(premier(l), FctBegayeSimple(suite(l))));
        }
        else
            return FctBegayeSimple(suite(l));
    }
}

/* rec terminal */

void FctBegayeTermBis(Liste l, Liste* res){
    if (l != NULL){
        if (premier(l) > 0){
            empile(premier(l), res);
            res = &((**res).suivant);
            empile(premier(l), res);
            res = &((**res).suivant);
        }
        FctBegayeTermBis(suite(l),res);
    }

}

// version avec suite(l)
// TODO 

Liste FctBegayeTerm(Liste l){
    Liste res;
    initVide(&res);
    FctBegayeTermBis(l, &res);
    return res;
}



/* iteratif: */

Liste FctBegayeIter(Liste l){
    Liste res ;
    initVide(&res);
    Liste *tmp = &res;
    Liste p = l;
    while(p != NULL){
        if (premier(p) > 0 ){
            empile(premier(p), tmp);
            tmp = &((**tmp).suivant);
            empile(premier(p), tmp);
            tmp = &((**tmp).suivant);
            
        }
        p = suite(p);    
    }
    free(*tmp);
    free(p);
    return res;
}


/*************************************************/
/*                                               */
/*           ProcBegaye                          */
/*                                               */
/*************************************************/

void ProcBegaye(Liste *L){
    if (*L != NULL){
        if (premier(*L) <= 0 ){
            depile(L);
        } 
        else if (premier(*L) > 0){
            empile(premier(*L),L);
            L = &((**L).suivant);
            L = &((**L).suivant);    
        } 
        ProcBegaye(L);;
    }
}



/*************************************************/
/*                                               */
/*           Permutations                        */
/*                                               */
/*************************************************/
ListeListe permutation (int n);
ListeListe concatll(ListeListe l1, ListeListe l2);
ListeListe ATLTP(int n, ListeListe ll);
ListeListe ATP (int n, Liste l);
ListeListe AETTL (int n, ListeListe ll);


// Ajouter En Tete Toutes Listes : (3,[[1,2],[4]]) -> [[3,1,2],[3,4]]
ListeListe AETTL (int n, ListeListe ll){
    if (ll==NULL) return ll;
    else return ajoutell(ajoute(n,ll->list),AETTL(n,ll->suivant));
}

// ajouter n a Toutes les Positions de l
ListeListe ATP (int n, Liste l){
    if (estVide(l)) {
        ajoute(n,l);
        ListeListe ll = NULL;
        return ajoutell(l,ll);
    } else return ajoutell(ajoute(n,l),AETTL(premier(l),ATP(n,suite(l))));
}

// Ajouter a Toutes les Listes a Toutes les Position 
ListeListe ATLTP(int n, ListeListe ll){
    if (ll == NULL) return ll;
    else return concatll(ATP(n, ll->list), ATLTP(n, ll->suivant));
}

// [a,b,c]^[d,e] => [a,b,c,d,e]
ListeListe concatll(ListeListe l1, ListeListe l2){
    if (l1 == NULL) return l2;
    else return ajoutell(l1->list,concatll(l1->suivant,l2));
}

// 2 -> [[1,2],[2,1]]
ListeListe permutation (int n){
    if (n==0) return NULL;
    else return ATLTP(n, permutation(n-1));
}




/*************************************************/
/*                                               */
/*           retire                              */
/*                                               */
/*************************************************/


void retire (Liste l, Bloc* p){
    if (estVide(l)) return;
    else {
        if (l->pred==p){
            l->suivant->pred = l->pred;
            l->pred->suivant = l->suivant;
            free(l);
            return;
        }else{
            retire(suite(l),p);
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



    affiche_recLL(permutation(3));

    return 0;
}





