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
	int boolC = 0;
	
	// on créé un tableau de solutions
	SolutionArray * solVoisine = SolutionArray_new(solution->nbObject, solution->nbObject, solution->nbDimension);
	
	while (i != solution->nbObject)
	{
		// on parcourt tous les objets de la solution courante
		// on copie la solution courante pour l'utiliser et la modifier temporairement
		Solution * solutiontmp = Solution_new(solution->nbObject, solution->nbDimension);
		copySolution(solution, solutiontmp);
		while (boolC == 0 && i != solution->nbObject)
		{
			// on parcourt la liste d'objets tant que l'on a pas trouvé un objet qui n'est pas dans le sac
			if (solutiontmp->objectTab[i] == 1)
			{
				i++;
			}
			else
			{
				// si un objet n'est pas dans le sac, on le rajoute
				solutiontmp->objectTab[i] = 1;
				solutiontmp->value += instance->object[i]->value;
				for (int j = 0; j < solutiontmp->nbDimension; j++)
				{
					solutiontmp->weightDimension[j] += instance->object[i]->weight[j];
				}
				
				boolC = 1;
			}
		}
		
		// on vérifie si cette solution est réalisable
		if (Is_Solution_Feasible(solutiontmp, instance) == 1)
		{
			copySolution(solutiontmp, solVoisine->solutions[solVoisine->currentNbSolution]);
			solVoisine->currentNbSolution++;
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
	
	printf("solVoisine->currentNbSolution : %i\n", solVoisine->currentNbSolution);
	return solVoisine;
}

// ECHANGE D'UN OBJET

SolutionArray * echangeObject_direct(Solution * solution, Instance * instance)
{
	int i = 0;
	int j = 0;
	int itmp = 0;
	int indiceSolVoisine = 0;
	int boolE = 0; // marqueur pour savoir s'il on a trouvé une possible solution
	
	// on créé un tableau de solutions
	SolutionArray * solVoisine = SolutionArray_new(solution->nbObject, solution->nbObject, solution->nbDimension);
	Solution * solutiontmp;
	
	for (i = 0; i < solution->nbObject-1; i++)
	{
		// on parcourt tous les objets de la solution courante
		itmp = i;
		if (solution->objectTab[i] == 0)
		{
			// si un objet n'est pas dans le sac
			// on copie la solution courante pour l'utiliser et la modifier temporairement
			solutiontmp = Solution_new(solution->nbObject, solution->nbDimension);
			copySolution(solution, solutiontmp);
			
			while (boolE == 0)
			{
				// tant que l'on a pas échangé deux objets
				for (j = itmp; j < solutiontmp->nbObject && boolE == 0; j++)
				{
					// on parcourt la suite des objets pour l'échanger avec un objet du sac
					if (solutiontmp->objectTab[j] == 1)
					{
						// si on trouve un objet du sac, on échange les deux objets
						// on commence par ajouter l'objet i
						solutiontmp->objectTab[i] = 1;
						solutiontmp->value += instance->object[i]->value;
						for (int w = 0; w < solutiontmp->nbDimension; w++)
						{
							solutiontmp->weightDimension[w] += instance->object[i]->weight[w];
						}
						
						//et on enleve ensuite l'objet j
						solutiontmp->objectTab[j] = 0;
						solutiontmp->value -= instance->object[j]->value;
						for (int w = 0; w < solutiontmp->nbDimension; w++)
						{
							solutiontmp->weightDimension[w] -= instance->object[j]->weight[w];
						}
						boolE = 1; // on notifie que l'on a trouvé une solution
					}
					itmp++;
				}
			}
				
			// on vérifie si cette solution est réalisable
			if (Is_Solution_Feasible(solutiontmp, instance) == 1)
			{
				copySolution(solutiontmp, solVoisine->solutions[indiceSolVoisine]);
				indiceSolVoisine++;
			}
			boolE = 0;
			free(solutiontmp);
		}
		else
		{
			// si un objet est dans le sac
			// on copie la solution courante pour l'utiliser et la modifier temporairement
			solutiontmp = Solution_new(solution->nbObject, solution->nbDimension);
			copySolution(solution, solutiontmp);
			
			while (boolE == 0)
			{
				// tant que l'on a pas échangé deux objets
				for (j = itmp; j < solutiontmp->nbObject && boolE == 0; j++)
				{
					// on parcourt la suite des objets pour l'échanger avec un objet hors du sac
					if (solutiontmp->objectTab[j] == 0)
					{
						// si on trouve un objet qui n'est pas dans le sac, on échange les deux objets
						//on commence par enlever l'objet i
						solutiontmp->objectTab[i] = 0;
						solutiontmp->value -= instance->object[i]->value;
						for (int w = 0; w < solutiontmp->nbDimension; w++)
						{
							solutiontmp->weightDimension[w] -= instance->object[i]->weight[w];
						}
						
						//puis on rajoute l'objet j
						solutiontmp->objectTab[j] = 1;
						solutiontmp->value += instance->object[j]->value;
						for (int w = 0; w < solutiontmp->nbDimension; w++)
						{
							solutiontmp->weightDimension[w] += instance->object[j]->weight[w];
						}
						
						boolE = 1; // on notifie que l'on a trouvé une solution
					}
					itmp++;
				}
			}
				
			// on vérifie si cette solution est réalisable
			if (Is_Solution_Feasible(solutiontmp, instance) == 1)
			{
				copySolution(solutiontmp, solVoisine->solutions[indiceSolVoisine]);
				indiceSolVoisine++;
			}
			boolE = 0;
			free(solutiontmp);
		}
	}
	
	return solVoisine;
}

// POUR LE CODAGE INDIRECT
// échange entre deux objets de la liste, qui donne une solution voisine. L'ensemble des solutions du voisinage est donné par tous les échanges possibles (N(N-1) / 2) possibilités.

/*
 * Pour chaque objet du sac sauf le dernier
	Pour i = indiceObjet + 1 jusqu'a nbObjectTotal
		nouvelleSol = newSol()
		nouvelleSol = copySol(solution_courante)
		nouvelleSol = Echange sac[objet] avec sac[i]
		Si solution réalisable
			solVoisine[indiceSolVoisine] = nouvelleSol
			indiceSolVoisine++
		Sinon
			free(nouvelleSol)
*/

SolutionArray * voisinage_indirect(Solution * solution, Instance * instance)
{
	// on créé un tableau de solutions qui comporte (N(N-1))/2 solutions (avec N le nombre d'objet)
	int nbMaxSolution = ((solution->nbObject * solution->nbObject - 1)/2);
	SolutionArray * solVoisine = SolutionArray_new(nbMaxSolution, solution->nbObject, solution->nbDimension);
	Solution * solutiontmp;
	//On va parcourir chaque objet du sac jusqu'a l'avant dernier
	for (int indiceObjetAEchanger = 0; indiceObjetAEchanger < solution->nbObject - 1; indiceObjetAEchanger++)
	{
		//Et on va l'échanger avec chaque objet venant après lui
		for (int indiceObjetParcouru = indiceObjetAEchanger + 1; indiceObjetParcouru < solution->nbObject; indiceObjetParcouru++)
		{
			//On fait une copie de la solution courante
			solutiontmp = Solution_new(instance->nbObjectTotal, instance->nbDimension);
			copySolution(solution, solutiontmp);
			//On échange la priorite de l'objet d'indice indiceObjetAEchanger avec celle de l'ojbjet indiceObjetParcouru
			int priorityTmp = solutiontmp->objectTab[indiceObjetAEchanger];
			solutiontmp->objectTab[indiceObjetAEchanger] = solutiontmp->objectTab[indiceObjetParcouru];
			solutiontmp->objectTab[indiceObjetParcouru] = priorityTmp;
			//On ajoute la nouvelle solution à l'array de solutions
			copySolution(solutiontmp, solVoisine->solutions[solVoisine->currentNbSolution]);
			solVoisine->currentNbSolution++;
			Solution_delete(solutiontmp);
		}
	}
	
	return solVoisine;
}