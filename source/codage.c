#include "stdlib.h"
#include "include/codage.h"
#include "include/parser.h"

//FONCTIONS SOLUTIONS

void Randomize_solution_direct(Solution * solution)
{	
	for (int i = 0; i < solution->nbObject; i++)
	{
		solution->objectTab[i] = rand() % 2;
	}
}

void Randomize_solution_indirect(Solution * solution)
{
	int * tableau = (int *) malloc (sizeof(int) * solution->nbObject);
	
	for (int i = 0; i < solution->nbObject; i++)
	{
		tableau[i] = i;
	}
	
	int alea;
	int taille = solution->nbObject;
	
	for (int i = 0; i < solution->nbObject; i++)
	{
		alea = rand() % taille;
		solution->objectTab[i] = tableau[alea];
		--taille;
		
		for(int j = alea; j < taille; j++)
		{
			tableau[j] = tableau[j + 1];
		}
	}
	
	free(tableau);
}

//Remplit les valeurs "value" et "weightDimension" en fonction de la valeur
//et du poids des dimensions des objets dans le sac
//POUR CODAGE DIRECT
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

//Remplit les valeurs "value" et "weightDimension" en fonction de la valeur
//et du poids des dimensions des objets dans le sac
//POUR CODAGE INDIRECT
void Load_Solution_indirect(Solution * solution, Instance * instance)
{
	int valid = 1;
	
	for (int i = 0; i < solution->nbObject; i++)
	{
		for (int j = 0; j < solution->nbDimension && valid; j++)
		{
			if (instance->object[solution->objectTab[i]]->weight[j] + solution->weightDimension[j] > instance->limit[j])
			{
				valid = 0;
			}
		}
		
		if (valid)
		{
			solution->value += instance->object[solution->objectTab[i]]->value;
			for (int j = 0; j < solution->nbDimension; j++)
			{
				solution->weightDimension[j] += instance->object[solution->objectTab[i]]->weight[j];
			}
		}
		
		valid = 1;
	}
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

//FONCTIONS D'INITIALISATION DE SOLUTION

int Solution_init(Solution * solution, int nbObject, int nbDimension)
{
	solution->nbObject = nbObject;
	
	solution->objectTab = (int *) malloc(sizeof(int) * solution->nbObject);
	if (solution->objectTab == NULL)
	{
		return 1;
	}
	
	solution->value = 0;
	
	solution->nbDimension = nbDimension;
	solution->weightDimension = (int*) malloc (sizeof(int) * solution->nbDimension);
	if (solution->weightDimension == NULL)
	{
		return 1;
	}
	else
	{
		for (int i = 0; i < solution->nbDimension; i++)
		{
			solution->weightDimension[i] = 0;
		}
	}
	
	return 0;
}

Solution * Solution_new(int nbObject, int nbDimension)
{
	Solution * my_solution = (Solution*) malloc(sizeof(Solution));
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
	SolutionArray * my_solution_array = (SolutionArray*) malloc(sizeof(SolutionArray));
	
	if (my_solution_array != NULL)
	{
		if (SolutionArray_init(my_solution_array, totalNbSolutions, nbObject, nbDimension))
		{
			free(my_solution_array);
			my_solution_array = NULL;
		}
	}
	
	return my_solution_array;
}

int SolutionArray_init(SolutionArray * solutions, int totalNbSolutions, int nbObject, int nbDimension)
{
	solutions->currentNbSolution = 0;
	solutions->totalNbSolutions = totalNbSolutions;
	solutions->solutions = (Solution **) malloc(sizeof(Solution*) * solutions->totalNbSolutions);
	if (solutions->solutions != NULL)
	{
		for (int i = 0; i < solutions->totalNbSolutions; i++)
		{
			solutions->solutions[i] = Solution_new(nbObject, nbDimension);
			if (solutions->solutions[i] == NULL)
			{
				return 1;
			}
		}
	}
	else
	{
		return 1;
	}
	
	return 0;
}

void SolutionArray_finalize(SolutionArray * solutions)
{
	for (int i = 0; i < solutions->currentNbSolution; i++)
	{
		 Solution_delete(solutions->solutions[i]);
	}
	free(solutions->solutions);
}

void SolutionArray_delete(SolutionArray * solutions)
{
	SolutionArray_finalize(solutions);
	free(solutions);
}