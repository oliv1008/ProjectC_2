#include "stdlib.h"
#include "include/codage.h"

Solution * Randomize_solution(int nbObject, int nbDimension)
{
	Solution * my_solution = Solution_new(nbObject, nbDimension);
	
	for (int i = 0; i < nbObject; i++)
	{
		my_solution->objectBoolean[i] = rand() % 2;
	}
	
	return my_solution;
}

//FONCTIONS D'INITIALISATION DE SOLUTION

int Solution_init(Solution * solution, int nbObject, int nbDimension)
{
	solution->nbObject = nbObject;
	solution->objectBoolean = (int *) malloc(sizeof(int) * solution->nbObject);
	if (solution->objectBoolean == NULL)
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
	free(solution->objectBoolean);
	free(solution->weightDimension);
}

void Solution_delete(Solution * solution)
{
	Solution_finalize(solution);
	free(solution);
}