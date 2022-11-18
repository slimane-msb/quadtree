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

// rendre une liste vide 
Liste listeVide();
ListeListe listelisteVide();

// renvoyer une liste a un elem
Liste initElem(int n);
ListeListe initElemll(Liste l);

/* initialise une Liste vide */
void initVide(Liste *L);
void initVidell( ListeListe *L);

/* renvoie 1 si la Liste en parametre est vide, 0 sinon */
bool estVide(Liste l);
bool estVidell(ListeListe l);

/* renvoie le premier element de la Liste en parametre */
int premier(Liste l);
Liste premierll(ListeListe l);

/* renvoie une nouvelle Liste correspondant a celle en parametre, avec l'element x ajoute en haut de la pile */
Liste ajoute(int x, Liste l);
ListeListe ajoutell(Liste x, ListeListe l);

/* modifie la Liste en parametre: x est ajoute comme premier element */
void empile(int x, Liste* L);
void empilell(Liste l, ListeListe *L);

/* renvoie une nouvelle Liste correspondant a celle en parametre sans son premier element */
Liste suite(Liste l);
ListeListe suitell(ListeListe ll);

/* modifie la Liste en parametre: le premier element est retire */
void depile(Liste* l);
void depilell(ListeListe *L);

/* affichage simple en recursif et en iteratif */
void affiche_rec(Liste l);
void affiche_recLL(ListeListe ll);
void affiche_iter(Liste l);
void affiche_recSansRALL(Liste l);

/* longueur en recursif et en iteratif */
int longueur_rec (Liste l);
int longueur_recll (ListeListe ll);
int longueur_iter (Liste l);

/*  Elimination du dernier element en recursif et en iteratif  */
/*  VD est la sousprocedure utilitaire de la version recursive */
void VD (Liste *L);
void VireDernier_rec (Liste *L);
void VireDernier_iter (Liste *L);


void VD (Liste *L);
void VireDernier_rec (Liste *L);
void VireDernier_iter (Liste *L);
void VideListe(Liste *L);


bool ZeroEnPositionUnOuDeuxOuTrois(Liste l);
bool Pluscourte(Liste l1, Liste l2);
int NombreDe0AvantPositionKRec(Liste L, int K);
int NombreDe0AvantPositionKRecTermBis(Liste L, int K, int res);
int NombreDe0AvantPositionKRecTerm(Liste L, int K);
void NombreDe0AvantPositionKRecTermProcBis(Liste L, int K, int *res);
int NombreDe0AvantPositionKRecTermProc(Liste L, int K);
int NombreDe0AvantPositionKIter(Liste L, int K);
void NombreDe0ApresRetroPositionKBis(Liste L,int* K,int* res);
int NombreDe0ApresRetroPositionK(Liste L,int K);
Liste FctBegayeSimple(Liste l);
void FctBegayeTermBis(Liste l, Liste* res);
Liste FctBegayeTerm(Liste l);
Liste FctBegayeIter(Liste l);
void ProcBegaye(Liste *L);

ListeListe permutation (int n);
ListeListe concatll(ListeListe ll1, ListeListe ll2);
ListeListe ATLTP(int n, ListeListe ll);
ListeListe ATP (int n, Liste l);
ListeListe AETTL (int n, ListeListe ll);

void retire (Liste l, Bloc* p);
void poup (Liste l);

Liste testBefore(int a, int b, int c, int d, int e);
ListeListe testBeforell();
void affichageTest (Liste l);
void affichageTestll (ListeListe l);

/*************************************************/
/*                                               */
/*                briques de base                */
/*                                               */
/*************************************************/

Liste listeVide(){
    Liste l = NULL;
    return l;
}

ListeListe listelisteVide(){
    ListeListe ll = NULL;
    return ll;
}

Liste initElem(int n){
    Liste l = NULL;
    empile(n, &l);
    return l;
}

ListeListe initElemll(Liste l){
    ListeListe ll = NULL;
    empilell(l, &ll);
    return ll;
}


void initVide( Liste *L)
{
    *L = NULL ;
}

void initVidell( ListeListe *L)
{
    *L = NULL ;
}

bool estVide(Liste l)
{
    return l == NULL ;
}

bool estVidell(ListeListe l)
{
    return l == NULL ;
}

int premier(Liste l)
{
    return l->nombre ; 
}

Liste premierll(ListeListe l)
{
    return l->list ; 
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

void empilell(Liste l, ListeListe *L)
{
      *L = ajoutell(l,*L) ; 
}

Liste suite(Liste l)
{
    return l->suivant ;
}

ListeListe suitell(ListeListe ll)
{
    return ll->suivant ;
}


void depile(Liste *L)
{
    Liste tmp = *L ;
    *L = suite(*L) ;
    free(tmp) ;
}

void depilell(ListeListe *L)
{
    ListeListe tmp = *L ;
    *L = suitell(*L) ;
    VideListe(&(tmp->list));
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

void affiche_recSansRALL(Liste l)
{
    if(! estVide(l))
    {
        printf("%d ", premier(l));
        affiche_recSansRALL(suite(l));
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
    if(estVidell(ll))
        printf("\n");
    else
    {
        printf("[");
        affiche_recSansRALL(ll->list);
        printf("]\n");
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

int longueur_recll (ListeListe ll)
{
    if (estVidell(ll))
         return 0 ;
    else return (1 + longueur_recll(suitell(ll))) ;
}


int longueur_iter (Liste l)
{
    Liste P = l;
    int cpt = 0 ;
    while (P != NULL)
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
     if ( (*L) != NULL )
          VD(L);        // moralement : VD(& (*L)) ;
}

void VireDernier_iter (Liste *L)
{
    if ( (*L) != NULL)
    {
        while ( ((**L).suivant) != NULL )
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

/*************************************************/
/*                                               */
/*       zeroen123                               */
/*                                               */
/*************************************************/

/*compilation paresseuse */
bool ZeroEnPositionUnOuDeuxOuTrois(Liste l){
    return (l != NULL)AND(
        (premier(l)==0) OR (
            (suite(l) != NULL) AND (
                (premier(suite(l))==0) OR (
                    (NULL != (suite(suite(l)) ) AND (premier(suite(suite(l)))==0))
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
            NombreDe0AvantPositionKRecTermProcBis(suite(L), K-1, res);
        }
        else NombreDe0AvantPositionKRecTermProcBis(suite(L), K-1, res);
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





// [a,b,c]^[d,e] => [a,b,c,d,e]
ListeListe concatll(ListeListe ll1, ListeListe ll2){
    if (estVidell(ll1)) return ll2;
    else return ajoutell(premierll(ll1),concatll(suitell(ll1),ll2));
}

// Ajouter En Tete Toutes Listes : (3,[[1,2],[4]]) -> [[3,1,2],[3,4]]
ListeListe AETTL (int n, ListeListe ll){
    if (estVidell(ll)) return ll;
    else return (ajoutell(ajoute(n,premierll(ll)),AETTL(n,suitell(ll))));
}


// ajouter n a Toutes les Positions de l
ListeListe ATP (int n, Liste l){
    if (estVide(l)) {
        return ajoutell(ajoute(n,l),NULL);
    } else return ajoutell(ajoute(n,l),AETTL(premier(l),ATP(n,suite(l))));
}


// Ajouter a Toutes les Listes a Toutes les Position 
ListeListe ATLTP(int n, ListeListe ll){
    if (estVidell(ll)) return ll;
    else return concatll(ATP(n, premierll(ll)), ATLTP(n, suitell(ll)));
}

// 2 -> [[1,2],[2,1]]
ListeListe permutation (int n){
    if (n==0) return listelisteVide();
    if (n==1)  return initElemll(initElem(n)); // return [[1]]
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
/*           test gen                            */
/*                                               */
/*************************************************/

Liste testBefore(int a, int b, int c, int d, int e){
    Liste l ;
    initVide (&l) ;
    empile(e, &l) ;
    empile(d, &l) ;
    empile(c, &l) ;
    empile(b, &l) ;
    empile(a, &l) ;
    return l;
}

ListeListe testBeforell(){
    ListeListe ll = initElemll(initElem(3));
    empilell(initElem(2), &ll);
    empile(1,&(ll->list));
    empile(2,&(ll->suivant->list));
    return ll;
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

void affichageTest (Liste l)
{
    printf("Affichage liste \n") ;
    printf("Longueur  %d \n", longueur_rec(l)) ;
    affiche_rec(l) ;
}

void affichageTestll (ListeListe ll)
{
    printf("Affichage liste de liste \n") ;
    printf("Longueur %d \n", longueur_recll(ll)) ;
    affiche_recLL(ll) ;
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

    // tests : 

    // permutation : 
    printf ("afficher permutation de 3\n");
    affiche_recLL(permutation(3));

    printf ("afficher permutation de 4\n");
    affiche_recLL(permutation(4));

    // depilell 
    printf ("tester depile liste de lsite : \n");
    ListeListe ll = testBeforell();
    affichageTestll(ll);

    printf("afficher depile(ll)\n");
    depilell(&ll);
    affichageTestll(ll);


    // zeroen123
    printf("ZeroEnPositionUnOuDeuxOuTrois\n");
    Liste l1 = testBefore(1,2,3,4,5);
    affichageTest(l1);
    printf("ZeroEnPositionUnOuDeuxOuTrois de l = " ); printBool(ZeroEnPositionUnOuDeuxOuTrois(l1));printf("\n\n");

    Liste l2 = testBefore(1,0,3,4,5);
    affichageTest(l2);
    printf("ZeroEnPositionUnOuDeuxOuTrois de l = " ); printBool(ZeroEnPositionUnOuDeuxOuTrois(l2));printf("\n");




    return 0;
}





