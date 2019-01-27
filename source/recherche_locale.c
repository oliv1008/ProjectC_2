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
	Solution * solutiontmp;
	
	// on parcourt tous les objets de la solution courante
	while (i < solution->nbObject)
	{
		// on copie la solution courante pour l'utiliser et la modifier temporairement
		solutiontmp = Solution_new(solution->nbObject, solution->nbDimension);
		copySolution(solution, solutiontmp);
		// on parcourt la liste d'objets tant que l'on a pas trouvé un objet qui n'est pas dans le sac
		while (boolC == 0 && i != solution->nbObject)
		{
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
		// si oui on la rajoute au tableau de solutions de voisinage
		if (Is_Solution_Feasible(solutiontmp, instance) == 1)
		{
			copySolution(solutiontmp, solVoisine->solutions[solVoisine->currentNbSolution]);
			solVoisine->currentNbSolution++;
			boolC = 0;
			i++;
			Solution_delete(solutiontmp);
		}
		else
		{
			Solution_delete(solutiontmp);
			boolC = 0;
			i++;
		}	
	}
	
	return solVoisine;
}

// ECHANGE D'UN OBJET

SolutionArray * echangeObject_direct(Solution * solution, Instance * instance)
{
	int nbMaxSolutions = ((solution->nbObject * solution->nbObject-1)/2);
	
	// on créé un tableau de solutions
	SolutionArray * solVoisine = SolutionArray_new(nbMaxSolutions, solution->nbObject, solution->nbDimension);
	Solution * solutiontmp;
	
	// on parcourt tous les objets de l'instance
	for (int indiceObjetAEchanger = 0; indiceObjetAEchanger < solution->nbObject-1; indiceObjetAEchanger++)
	{
		// on parcourt les objets à la suite de l'objet à échanger pour effectuer les échanges
		for (int indiceObjetParcouru = indiceObjetAEchanger+1; indiceObjetParcouru < solution->nbObject; indiceObjetParcouru++)
		{
			// si on trouve un objet dans le sac à échanger avec un objet hors du sac
			if (solution->objectTab[indiceObjetAEchanger] != solution->objectTab[indiceObjetParcouru])
			{
				// on créé une copie de la solution pour pouvoir la modifier temporairement
				solutiontmp = Solution_new(instance->nbObjectTotal, instance->nbDimension);
				copySolution(solution, solutiontmp);
				
				// on échange les deux objets
				int indicetmp = solutiontmp->objectTab[indiceObjetAEchanger];
				solutiontmp->objectTab[indiceObjetAEchanger] = solutiontmp->objectTab[indiceObjetParcouru];
				solutiontmp->objectTab[indiceObjetParcouru] = indicetmp;
				
				// on ajoute la valeur et les poids de l'objet ajouté au sac
				// on retire la valeur et les poids de l'objet enlevé du sac
				if (solutiontmp->objectTab[indiceObjetAEchanger] == 1)
				{
					solutiontmp->value += instance->object[indiceObjetAEchanger]->value;
					solutiontmp->value -= instance->object[indiceObjetParcouru]->value;
					
					for (int i = 0; i < solutiontmp->nbDimension; i++)
					{
						solutiontmp->weightDimension[i] += instance->object[indiceObjetAEchanger]->weight[i];
						solutiontmp->weightDimension[i] -= instance->object[indiceObjetParcouru]->weight[i];
						
					}
				}
				else
				{
					solutiontmp->value -= instance->object[indiceObjetAEchanger]->value;
					solutiontmp->value += instance->object[indiceObjetParcouru]->value;
					
					for (int i = 0; i < solutiontmp->nbDimension; i++)
					{
						solutiontmp->weightDimension[i] -= instance->object[indiceObjetAEchanger]->weight[i];
						solutiontmp->weightDimension[i] += instance->object[indiceObjetParcouru]->weight[i];
						
					}
				}
				
				// on vérifie si cette solution est réalisable
				if (Is_Solution_Feasible(solutiontmp, instance) == 1)
				{
					copySolution(solutiontmp, solVoisine->solutions[solVoisine->currentNbSolution]);
					solVoisine->currentNbSolution++;
				}
				Solution_delete(solutiontmp);
			}
		}
	}
	
	return solVoisine;
}

SolutionArray * voisinage_direct(Solution * solution, Instance * instance)
{
	SolutionArray * solArrayAjout = ajoutObject_direct(solution, instance);
	SolutionArray * solArrayEchange = echangeObject_direct(solution, instance);
	
	SolutionArray * solArray = fuseSolutionArrays(solArrayAjout, solArrayEchange, instance);
	
	SolutionArray_delete(solArrayAjout);
	SolutionArray_delete(solArrayEchange);
	
	return solArray;
}

//CODAGE INDIRECT
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
			Load_Solution_indirect(solVoisine->solutions[solVoisine->currentNbSolution], instance);
			solVoisine->currentNbSolution++;
			Solution_delete(solutiontmp);
		}
	}
	
	return solVoisine;
}

// ALGORITHME RECHERCHE LOCALE INDIRECT
Solution * algorithme_recherche_locale_indirect(Solution * solution, Instance * instance)
{
	int boolC = 1;
	
	Solution * solCourante = Solution_new(instance->nbObjectTotal, instance->nbDimension);
	Solution * solBest = Solution_new(instance->nbObjectTotal, instance->nbDimension);
	Solution * solPrec = Solution_new(instance->nbObjectTotal, instance->nbDimension);
	Solution * solBestVoisine = Solution_new(instance->nbObjectTotal, instance->nbDimension);
	Solution * solVoisine = Solution_new(instance->nbObjectTotal, instance->nbDimension);
	
	copySolution(solution, solCourante);
	copySolution(solCourante, solBest);
	copySolution(solCourante, solPrec);
	
	SolutionArray * solTableau;
	while (boolC)
	{
		// on récupère le tableau de solutions de voisinage
		solTableau = voisinage_indirect(solCourante, instance);
		for (int i = 0; i < solTableau->currentNbSolution; i++)
		{
			copySolution(solTableau->solutions[i], solVoisine);
			// on vérifie si la solution est meilleure que la meilleure des solutions voisines
			if (solVoisine->value > solBestVoisine->value)
			{
				copySolution(solVoisine, solBestVoisine);
			}
		}
		copySolution(solBestVoisine, solCourante);
		
		// on vérifie si la solution est meilleure que la meilleure des solutions
		if (solCourante->value > solBest->value)
		{
			copySolution(solCourante, solBest);
		}
		else
		{
			if (solCourante->value == solPrec->value)
			{
				boolC = 0;
			}
		}
		copySolution(solCourante, solPrec);
		SolutionArray_delete(solTableau);
	}
	Solution_delete(solCourante);
	Solution_delete(solPrec);
	Solution_delete(solBestVoisine);
	Solution_delete(solVoisine);
	return solBest;
}

// ALGORITHME RECHERCHE LOCALE DIRECT
Solution * algorithme_recherche_locale_direct(Solution * solution, Instance * instance)
{
	int boolC = 1;
	
	Solution * solCourante = Solution_new(instance->nbObjectTotal, instance->nbDimension);
	Solution * solBest = Solution_new(instance->nbObjectTotal, instance->nbDimension);
	Solution * solPrec = Solution_new(instance->nbObjectTotal, instance->nbDimension);
	Solution * solBestVoisine = Solution_new(instance->nbObjectTotal, instance->nbDimension);
	Solution * solVoisine = Solution_new(instance->nbObjectTotal, instance->nbDimension);
	
	copySolution(solution, solCourante);
	copySolution(solCourante, solBest);
	copySolution(solCourante, solPrec);
	
	SolutionArray * solTableau;
	while (boolC)
	{
		// on récupère le tableau de solutions de voisinage
		solTableau = voisinage_direct(solCourante, instance);
		for (int i = 0; i < solTableau->currentNbSolution; i++)
		{
			copySolution(solTableau->solutions[i], solVoisine);
			// on vérifie si la solution est meilleure que la meilleure des solutions voisines
			if (solVoisine->value > solBestVoisine->value)
			{
				copySolution(solVoisine, solBestVoisine);
			}
		}
		copySolution(solBestVoisine, solCourante);
		
		// on vérifie si la solution est meilleure que la meilleure des solutions
		if (solCourante->value > solBest->value)
		{
			copySolution(solCourante, solBest);
		}
		else
		{
			if (solCourante->value == solPrec->value)
			{
				boolC = 0;
			}
		}
		copySolution(solCourante, solPrec);
		SolutionArray_delete(solTableau);
	}
	Solution_delete(solCourante);
	Solution_delete(solPrec);
	Solution_delete(solBestVoisine);
	Solution_delete(solVoisine);
	return solBest;
}
