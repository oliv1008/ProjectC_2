#include <stdio.h>
#include "stdlib.h"
#include "time.h"
#include "include/parser.h"
#include "include/codage.h"
#include "include/heuristique.h"
#include "include/recherche_locale.h"

int main(int argc, char **argv)
{
	FILE * f;
	FILE * solutions_output;
	DataFile * datafile;
	srand( time(NULL));
	
	if (argc != 3)
	{
		printf("Erreur, utilisation : [Chemin vers un fichier] [0 (Codage direct) || 1 (Codage indirect)]\n");
	}
	else
	{
		f = fopen(argv[1], "r");
		if (f == NULL)
		{
			printf("Chemin d'accès incorrect, veuillez spécifier un chemin d'accès correct\n");
			exit(EXIT_FAILURE);
		}
		else if (atoi(argv[2]) < 0 || atoi(argv[2]) > 1)
		{
			printf("Type de codage incorrect, veuillez choisir entre 0 (codage direct) ou 1 (codage indirect)");
			exit(EXIT_FAILURE);
		}
		else
		{
			datafile = Parser(f);
		}
	}
	
	//Codage direct
	if(atoi(argv[2]) == 0)
	{
		solutions_output = fopen("solutions_output.txt", "w+");
		/*
		SolutionArray * solutions_direct = SolutionArray_new(datafile->TotalNbInstance, \
													datafile->instance[0]->nbObjectTotal, \
													datafile->instance[0]->nbDimension);
		for (int i = 0; i < datafile->TotalNbInstance; i++)
		{
			Randomize_solution_direct(solutions_direct->solutions[i]);
			Load_Solution_direct(solutions_direct->solutions[i], datafile->instance[i]);
			fprintf(solutions_output, "Solution pour l'instance : %i \n\n", i);
			for (int j = 0; j < solutions_direct->solutions[i]->nbObject; j++)
			{
				fprintf(solutions_output, "%i ", solutions_direct->solutions[i]->objectTab[j]);
			}
			fprintf(solutions_output, "\nValeur totale : %i\n", solutions_direct->solutions[i]->value);
			for (int j = 0; j < solutions_direct->solutions[i]->nbDimension; j++)
			{
				fprintf(solutions_output, "Poids total pour la dimension %i : %i\n", j, \
											solutions_direct->solutions[i]->weightDimension[j]);
			}
			if (Is_Solution_Feasible(solutions_direct->solutions[i], datafile->instance[i]))
			{
				fprintf(solutions_output, "La solution est réalisable \n");
			}
			else
			{
				fprintf(solutions_output, "La solution n'est pas réalisable \n");
			}
			fprintf(solutions_output, "\n\n\n");
		}
		
		SolutionArray_delete(solutions_direct);
		*/
		fprintf(solutions_output, "Ordo_ratio\n");
		Solution * sol = Algorithme_solutions (datafile->instance[0], Ordonnancement_ratio, 1);
		Load_Solution_indirect(sol, datafile->instance[0]);
		printSolutionToFile(sol, solutions_output);
		
		fprintf(solutions_output, "\nSol array\n");
		SolutionArray * solArray = voisinage_indirect(sol, datafile->instance[0]);
		printSolutionArrayToFile(solArray, solutions_output);

		Solution_delete(sol);
		SolutionArray_delete(solArray);
	}
	
	else if (atoi(argv[2]) == 1)
	{
		printf("cc\n\n");
		solutions_output = fopen("solutions_output.txt", "w+");
		
		Solution * solin = Algorithme_solutions(datafile->instance[0], Ordonnancement_leger, 1);
		printf("yo\n");
		Solution * newsol = algorithme_recherche_locale_direct(solin, datafile->instance[0]);
		printSolutionToFile(newsol, solutions_output);
		
		
	}
	
	DataFile_delete(datafile);
	fclose(solutions_output);
	return 0;
}