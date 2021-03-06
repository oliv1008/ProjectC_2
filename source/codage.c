#include "stdlib.h"
#include "include/codage.h"
#include "include/parser.h"

//FONCTIONS SOLUTIONS
//POUR CODAGE DIRECT

// Initialise "value" et "weightDimension" en fonction de la valeur et du poids des dimensions des objets dans le sac
void Load_Solution_direct(Solution * solution, Instance * instance)
{
	for (int i = 0; i < solution->nbObject; i++)
	{
		if (solution->objectTab[i] == 1)
		{
			solution->value += instance->object[i]->value;
			for (int j = 0; j < instance->nbDimension; j++)
			{
				solution->weightDimension[j] += instance->object[i]->weight[j];
			}
		}
	}
}

//POUR CODAGE INDIRECT

// Initialise "value" et "weightDimension" en fonction de la valeur et du poids des dimensions des objets dans le sac
void Load_Solution_indirect(Solution * solution, Instance * instance)
{
	int value = 0;
	int * weightDimension = (int*)calloc(instance->nbDimension, sizeof(int));
	int indiceObjet = 0;
	int priority = 1;
	int boolFindIndice = 1;
	int boolValid = 1;
	
	//Pour autant d'objet qu'il y a dans la solution
	for (int i = 0; i < solution->nbObject; i++)
	{
		//On commence par chercher l'indice de l'objet de la priorite suivante
		for (int j = 0; j < solution->nbObject && boolFindIndice; j++)
		{
			if (solution->objectTab[j] == priority)
			{
				indiceObjet = j;
				boolFindIndice = 0;
				priority++;
			}
		}
		boolFindIndice = 1;
		
		//On regarde ensuite si l'ajout de l'objet ne rend pas la solution infaisable
		for (int j = 0; j < instance->nbDimension && boolValid; j++)
		{
			if (weightDimension[j] + instance->object[indiceObjet]->weight[j] > instance->limit[j])
			{
				boolValid = 0;
			}
		} 
		
		//Si non, on l'ajoute bien au sac
		if (boolValid)
		{
			value += instance->object[indiceObjet]->value;
			for (int j = 0; j < instance->nbDimension; j++)
			{
				weightDimension[j] += instance->object[indiceObjet]->weight[j];
			}
		}
		boolValid = 1;
	}
	
	solution->value = value;
	for (int i = 0; i < instance->nbDimension; i++)
	{
		solution->weightDimension[i] = weightDimension[i];
	}
	free(weightDimension);
}

int Is_Solution_Feasible(Solution * solution, Instance * instance)
{
	for (int i = 0; i < instance->nbDimension; i++)
	{
		if (solution->weightDimension[i] > instance->limit[i])
		{
			return 0;
		}
	}

	return 1;
}

// FONCTIONS DE MANIPULATION DES SOLUTIONS
void copySolution(Solution * solutionFrom, Solution * solutionTo)
{
	for (int i = 0; i < solutionFrom->nbObject; i++)
	{
		solutionTo->objectTab[i] = solutionFrom->objectTab[i];
	}
	
	solutionTo->nbObject = solutionFrom->nbObject;
	solutionTo->nbDimension = solutionFrom->nbDimension;
	solutionTo->value = solutionFrom->value;
	
	for (int j = 0; j < solutionFrom->nbDimension; j++)
	{
		solutionTo->weightDimension[j] = solutionFrom->weightDimension[j];
	}
}

void printSolutionToConsole(Solution * solution)
{
	for (int i = 0; i < solution->nbObject; i++)
	{
		{
			printf("%i:%i ", i, solution->objectTab[i]);
		}
	}
	
	printf("\nScore solution : %i\n\n", solution->value);
}

SolutionArray * fuseSolutionArrays(SolutionArray * solArray1, SolutionArray * solArray2, Instance * instance)
{
	SolutionArray * newSolArray = SolutionArray_new(solArray1->totalNbSolutions + solArray2->totalNbSolutions,
													instance->nbObjectTotal,
													instance->nbDimension);
													
	for (int indiceArray1 = 0; indiceArray1 < solArray1->currentNbSolution; indiceArray1++)
	{
		copySolution(solArray1->solutions[indiceArray1], newSolArray->solutions[indiceArray1]);
	}
	
	for (int indiceArray2 = 0; indiceArray2 < solArray2->currentNbSolution; indiceArray2++)
	{
		copySolution(solArray2->solutions[indiceArray2], newSolArray->solutions[indiceArray2 + solArray1->currentNbSolution]);
	}
	
	newSolArray->currentNbSolution = solArray1->currentNbSolution + solArray2->currentNbSolution;
	
	return newSolArray;
}

//FONCTIONS D'INITIALISATION DE SOLUTION

int Solution_init(Solution * solution, int nbObject, int nbDimension)
{
	solution->nbObject = nbObject;
	solution->value = 0;
	solution->nbDimension = nbDimension;
	
	//Initialisation a 0 de tout les objets du sac
	solution->objectTab = (int*)calloc(solution->nbObject, sizeof(int));
	if (solution->objectTab == NULL)
	{
		return 1;
	}
	
	//Initialisation a 0 du poids dans toute les dimensions
	solution->weightDimension = (int*)calloc(solution->nbDimension, sizeof(int));
	if (solution->weightDimension == NULL)
	{
		return 1;
	}
	
	return 0;
}

Solution * Solution_new(int nbObject, int nbDimension)
{
	Solution * my_solution = (Solution *)malloc(sizeof(Solution));
	if (my_solution)
	{
		if (Solution_init(my_solution, nbObject, nbDimension))
		{
			free(my_solution);
			my_solution = NULL;
		}
	}
	
	return my_solution;
}

void Solution_finalize(Solution * solution)
{
	free(solution->objectTab);
	free(solution->weightDimension);
}

void Solution_delete(Solution * solution)
{
	Solution_finalize(solution);
	free(solution);
}

//FONCTIONS D'INITIALISATION DE SOLUTION_ARRAY

SolutionArray * SolutionArray_new(int totalNbSolutions, int nbObject, int nbDimension)
{
	SolutionArray * my_solution_array = (SolutionArray*)malloc(sizeof(SolutionArray));
	
	if (my_solution_array)
	{
		if (SolutionArray_init(my_solution_array, totalNbSolutions, nbObject, nbDimension))
		{
			free(my_solution_array);
			my_solution_array = NULL;
		}
	}
	
	return my_solution_array;
}

int SolutionArray_init(SolutionArray * solutionArray, int totalNbSolutions, int nbObject, int nbDimension)
{
	solutionArray->currentNbSolution = 0;
	solutionArray->totalNbSolutions = totalNbSolutions;
	solutionArray->solutions = (Solution**)malloc(sizeof(Solution*) * solutionArray->totalNbSolutions);
	if (solutionArray->solutions == NULL)
	{
		return 1;
	}
	else
	{
		for (int i = 0; i < totalNbSolutions; i++)
		{
			solutionArray->solutions[i] = Solution_new(nbObject, nbDimension);
		}
	}
	
	return 0;
}

void SolutionArray_finalize(SolutionArray * solutionArray)
{
	for (int i = 0; i < solutionArray->totalNbSolutions; i++)
	{
		 Solution_delete(solutionArray->solutions[i]);
	}
	free(solutionArray->solutions);
}

void SolutionArray_delete(SolutionArray * solutionArray)
{
	SolutionArray_finalize(solutionArray);
	free(solutionArray);
}