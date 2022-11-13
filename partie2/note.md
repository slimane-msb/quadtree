
E   

Yn

POW  // dans le désordre, P1 après P2ab après P1b qui appel P1 ... ( %done : reorganisation) 
P1 version 1 ; RNR gestion n<0 recursif : Malhabile : ne pas refaire le test n<0 à chaque appel (%done : power1bisc)

P1 version 2 : on peut se passer de coder P1neg ( %done : power1bisc)

P2a, n<0 ne va pas marcher (% done: power2abis)

Ack

Xn : Avec sous-proc : n'est pas RT (%done )

ZPUDT

PC LD0 : test lourd (si L1, si L2)

NZAVPK rec : il manque un else ... FOnctions : vérifiez que vous avez bien autant de else que de if. Si un else manque, vous devez savoir pourquoi.
NZAVPK it
NZAVPK SF ldB++  rec(in j++) j++ c'est l'instruction j=j+1. Utilisez j+1 ici

plus structuré avec un "else"

NZAVPK SP    BUG D : Depile au lieu de Suite, ce qui détruit la liste.
    Pour accéder à la deuxième page d'un livre,
    vous arrachez et jetez la page 1 (depile(&l)) au lieu de la tourner (l=suite(l))


NZAPRK

FBeg rec
FBeg RT   yep... c'est la première version correcte que je vois, et j'ai presque fini. Ce sera peut-être la seule

Notes : au lieu de deux res = &((**res).suivant);, vous pouvez faire un seul res\suite\suite, ou bien appeler sur ptsuite/suite, itou pour les suivantes, mais ce que vous faites marche aussi.

Liste res;    initVide(&res); peut devenir liste res = NULL ;

FBeg It : c'est presque ça (là encore; première fois)

mais free non compris, free(p) rend à la mémoire la variable pointée par p

free(*tmp), c'est free(res), ie que vous rendez à la mémoire le premier bloc de votre rendu de fonction . NON

free(p) rend à la mémoire le premier bloc de l . NON


PBeg