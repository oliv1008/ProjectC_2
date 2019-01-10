#include <stdio.h>
#include "stdlib.h"
#include "time.h"
#include "include/parser.h"
#include "include/codage.h"
#include "include/heuristique.h"

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
		}
		else if (atoi(argv[2]) < 0 || atoi(argv[2]) > 1)
		{
			printf("Type de codage incorrect, veuillez choisir entre 0 (codage direct) ou 1 (codage indirect)");
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

		fprintf(solutions_output, "Ordo_critique\n");		
		Solution * sol = Algorithme_solutions (datafile->instance[0], Ordonnancement_critique, atoi(argv[2]));
		fprintf(solutions_output, "\n%i\n\n", sol->value);
		Solution_delete(sol);
		
		fprintf(solutions_output, "Ordo_dynamique\n");
		Solution * sol2 = Algorithme_solutions (datafile->instance[0], Ordonnancement_dynamique, atoi(argv[2]));
		fprintf(solutions_output, "\n%i\n\n", sol2->value);
		Solution_delete(sol2);
		
		fprintf(solutions_output, "Ordo_decroissant\n");
		Solution * sol3 = Algorithme_solutions (datafile->instance[0], Ordonnancement_decroissant, atoi(argv[2]));
		fprintf(solutions_output, "\n%i\n\n", sol3->value);
		Solution_delete(sol3);
		
		fprintf(solutions_output, "Ordo_ratio\n");
		Solution * sol4 = Algorithme_solutions (datafile->instance[0], Ordonnancement_ratio, atoi(argv[2]));
		fprintf(solutions_output, "\n%i\n\n", sol4->value);
		Solution_delete(sol4);
		
		fprintf(solutions_output, "Ordo_leger\n");
		Solution * sol5 = Algorithme_solutions (datafile->instance[0], Ordonnancement_leger, atoi(argv[2]));
		fprintf(solutions_output, "\n%i\n\n", sol5->value);
		Solution_delete(sol5);
		
	}
	
	else if (atoi(argv[2]) == 1)
	{
		solutions_output = fopen("solutions_output.txt", "w+");
		SolutionArray * solutions_indirect = SolutionArray_new(datafile->TotalNbInstance, \
													datafile->instance[0]->nbObjectTotal, \
													datafile->instance[0]->nbDimension);
		for (int i = 0; i < datafile->TotalNbInstance; i++)
		{
			Randomize_solution_indirect(solutions_indirect->solutions[i]);
			Load_Solution_indirect(solutions_indirect->solutions[i], datafile->instance[i]);
			fprintf(solutions_output, "Solution pour l'instance : %i \n\n", i);
			for (int j = 0; j < solutions_indirect->solutions[i]->nbObject; j++)
			{
				fprintf(solutions_output, "%i ", solutions_indirect->solutions[i]->objectTab[j]);
			}
			fprintf(solutions_output, "\nValeur totale : %i\n", solutions_indirect->solutions[i]->value);
			for (int j = 0; j < solutions_indirect->solutions[i]->nbDimension; j++)
			{
				fprintf(solutions_output, "Poids total pour la dimension %i : %i\n", j, \
											solutions_indirect->solutions[i]->weightDimension[j]);
			}
			if (Is_Solution_Feasible(solutions_indirect->solutions[i], datafile->instance[i]))
			{
				fprintf(solutions_output, "La solution est réalisable \n");
			}
			else
			{
				fprintf(solutions_output, "La solution n'est pas réalisable \n");
			}
			fprintf(solutions_output, "\n\n\n");
		}
		
		SolutionArray_delete(solutions_indirect);
	}
	
	DataFile_delete(datafile);
	return 0;
}