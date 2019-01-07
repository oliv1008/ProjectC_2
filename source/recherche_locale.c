#include "stdlib.h"
#include "include/parser.h"
#include "include/codage.h"
#include "include/heuristique.h"

// FONCTIONS D'OPERATEURS DE VOISINAGE
// CODAGE DIRECT
// (1)

Solution ** ajoutObject_indirect(Instance * Instance)
{
	
	Solution * Algorithme_solutions (Instance * instance, Object ** (*ordo_fct)(Instance *), int codage)
	// on prend une solution qui existe
	// on remplace un 0 par un 1
	// si c'est réalisable, on garde dans une liste
	// sinon on tej
	
	int i = 0;
	int boolC = 0;
	
	while (i != solution->nbObject-1 || boolC != 1)
	{
		// on parcourt la liste tant que l'on a pas trouvé un objet qui n'est pas dans le sac
		if (solution->objectTab[i] == 1)
		{
			i++;
		}
		else
		{
			solution->objectTab[i] = 1;
			boolC = 1;
		}
	}
	
	// on vérifie si cette solution est réalisable
	
	for (int j = 0; j < solution->nbDimension; j++)
	{
		if (solution->weightDimension[j] > i)
	}
	for (int i = 0; i < instance->nbDimension; i++)
	{
		if (solution->weightDimension[i] > instance->limit[i])
		{
			return 0;
		}
	}

	return 1;
	
	
	
	
}



// (2) on échange un objet (0 devient 1 et 1 devient 0), solutions voisines sont contituées des solutions réalisables résultantes de tous les échanges possibles.


// POUR LE CODAGE INDIRECT
// échange entre deux objets de la liste, qui donne une solution voisine. L'ensemble des solutions du voisinage est donné par tous les échanges possibles (N(N-1) / 2) possibilités.



