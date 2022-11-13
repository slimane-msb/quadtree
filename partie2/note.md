
# E  
        (? il veut dire on a pas fait E ?) 

# Yn 

# POW   (done)
        // dans le désordre, P1 après P2ab après P1b qui appel P1 ... ( %done : reorganisation) 
# P1 version 1 ;  (done)
        RNR gestion n<0 recursif : Malhabile : ne pas refaire le test n<0 à chaque appel (%done : power1bisc)

# P1 version 2 : (done)
        on peut se passer de coder P1neg ( %done : power1bisc)

# P2a, (done)
        n<0 ne va pas marcher (% done: power2abis)

# Ack 

# Xn : (done)
        Avec sous-proc : n'est pas RT (%done )

# ZPUDT

# PC LD0 : (done)
        test lourd (si L1, si L2)  (% done)

# NZAVPK rec : (done)
        il manque un else ... FOnctions : vérifiez que vous avez bien autant de else que de if. Si un else manque, vous devez savoir pourquoi. (% done )

# NZAVPK it


# NZAVPK SF (done)
        ldB++  rec(in j++) j++ c'est l'instruction j=j+1. Utilisez j+1 ici (%done)
        plus structuré avec un "else" (%done)

# NZAVPK SP    (done)
        BUG D : Depile au lieu de Suite, ce qui détruit la liste. (% done)
        Pour accéder à la deuxième page d'un livre,
        vous arrachez et jetez la page 1 (depile(&l)) au lieu de la tourner (l=suite(l))


# NZAPRK

# FBeg rec


# FBeg RT   (%todo mazino)
        yep... c'est la première version correcte que je vois, et j'ai presque fini. Ce sera peut-être la seule (%yep done)

        Notes : au lieu de deux res = &((**res).suivant);, vous pouvez faire un seul res\suite\suite, ou bien appeler sur ptsuite/suite, itou pour les suivantes, mais ce que vous faites marche aussi. (% TODO mazino )

        Liste res;    initVide(&res); peut devenir liste res = NULL ; (? pour quel fonctionne)

# FBeg It :  (%todo mazino)
        c'est presque ça (là encore; première fois) (% TODO mazino  | bien joue pour ces deux)

        mais free non compris, free(p) rend à la mémoire la variable pointée par p

        free(*tmp), c'est free(res), ie que vous rendez à la mémoire le premier bloc de votre rendu de fonction . NON

        free(p) rend à la mémoire le premier bloc de l . NON


# PBeg