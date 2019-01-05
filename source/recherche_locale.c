#include "stdlib.h"
#include "include/parser.h"
#include "include/codage.h"
#include "include/heuristique.h"

// POUR LE CODAGE DIRECT
// (1) on ajoute un objet (0 devient 1), tester les N possibilités et garder que celles réalisables.
// (2) on échange un objet (0 devient 1 et 1 devient 0), solutions voisines sont contituées des solutions réalisables résultantes de tous les échanges possibles.


// POUR LE CODAGE INDIRECT
// échange entre deux objets de la liste, qui donne une solution voisine. L'ensemble des solutions du voisinage est donné par tous les échanges possibles (N(N-1) / 2) possibilités.



