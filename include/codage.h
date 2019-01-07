#ifndef CODAGE_H
#define CODAGE_H

#include "include/parser.h"

typedef struct __Solution
{
	int nbObject;
	int * objectTab;
	int value;
	int nbDimension;
	int * weightDimension;
}Solution;

typedef struct __SolutionArray
{
	int currentNbSolution;
	int totalNbSolutions;
	Solution ** solutions;
} SolutionArray;

void Randomize_solution_direct(Solution * solution);
void Randomize_solution_indirect(Solution * solution);
void Load_Solution_direct(Solution * solution, Instance * instance);
void Load_Solution_indirect(Solution * solution, Instance * instance);
int Is_Solution_Feasible(Solution* solution, Instance * instance);
void copySolution(Solution * solutionFrom, Solution * solutionTo);

//FONCTIONS D'INITIALISATION DE SOLUTION

int Solution_init(Solution * solution, int nbObject, int nbDimension);
Solution * Solution_new(int nbObject, int nbDimension);
void Solution_finalize(Solution * solution);
void Solution_delete(Solution * solution);

//FONCTIONS D'INITIALISATION DE SOLUTION_ARRAY

SolutionArray * SolutionArray_new(int totalNbSolutions, int nbObject, int nbDimension);
int SolutionArray_init(SolutionArray * solutions, int totalNbSolutions, int nbObject, int nbDimension);
void SolutionArray_finalize(SolutionArray * solutions);
void SolutionArray_delete(SolutionArray * solutions);

#endif