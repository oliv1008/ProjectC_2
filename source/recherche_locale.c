#include "stdlib.h"
#include "include/parser.h"
#include "include/codage.h"
#include "include/heuristique.h"

// FONCTIONS D'OPERATEURS DE VOISINAGE
// CODAGE DIRECT
// AJOUT D'UN OBJET

SolutionArray * ajoutObject_direct(Solution * solution, Instance * instance)
{
	int i = 0;
	int indiceSolVoisine = 0;
	int boolC = 0;
	
	// on créé un tableau de solutions
	SolutionArray * solVoisine = SolutionArray_new(solution->nbObject, solution->nbObject, solution->nbDimension);
	//Solution * newSolution = Solution_new(instan))
	
	while (i != solution->nbObject)
	{
		Solution * solutiontmp = Solution_new(solution->nbObject, solution->nbDimension);
		copySolution(solution, solutiontmp);
		// on parcourt toute la solution courante
		while (boolC == 0)
		{
			// on parcourt la liste tant que l'on a pas trouvé un objet qui n'est pas dans le sac
			if (solutiontmp->objectTab[i] == 1)
			{
				i++;
			}
			else
			{
				// si un objet n'est pas dans le sac, on le rajoute
				solutiontmp->objectTab[i] = 1;
				boolC = 1;
			}
		}
		
		// on vérifie si cette solution est réalisable
		if (Is_Solution_Feasible(solutiontmp, instance) == 1)
		{
			copySolution(solutiontmp, solVoisine->solutions[indiceSolVoisine]);
			indiceSolVoisine++;
			boolC = 0;
			i++;
			free(solutiontmp);
		}
		else
		{
			free(solutiontmp);
			boolC = 0;
			i++;
		}	
	}
	
	return solVoisine;
}

// ECHANGE D'UN OBJET

/*Solution ** echangeObject_direct(Solution * solution, Instance * instance)
{
	
}*/



// (2) on échange un objet (0 devient 1 et 1 devient 0), solutions voisines sont contituées des solutions réalisables résultantes de tous les échanges possibles.


// POUR LE CODAGE INDIRECT
// échange entre deux objets de la liste, qui donne une solution voisine. L'ensemble des solutions du voisinage est donné par tous les échanges possibles (N(N-1) / 2) possibilités.



