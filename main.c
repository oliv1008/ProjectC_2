#include <stdio.h>
#include "stdlib.h"
#include "time.h"
#include "include/parser.h"
#include "include/codage.h"

int main(int argc, char **argv)
{
	char c;
	FILE * f;
	FILE * solutions_output;
	DataFile * datafile;
	srand( time(NULL));
	
	if (argc != 2)
	{
		printf("Erreur, veuillez spécifier un chemin vers un fichier .txt\n");
	}
	else
	{
		f = fopen(argv[1], "r");
		if (f == NULL)
		{
			printf("Chemin d'accès incorrect, veuillez spécifier un chemin d'accès correct\n");
		}
		else
		{
			datafile = Parser(f);
		}
	}
	
	solutions_output = fopen("solutions_output.txt", "w+");
	SolutionArray * solutions = SolutionArray_new(datafile->TotalNbInstance, \
												datafile->instance[0]->nbObjectTotal, \
												datafile->instance[0]->nbDimension);
	for (int i = 0; i < datafile->TotalNbInstance; i++)
	{
		Randomize_solution(solutions->solutions[i]);
		Load_Solution(solutions->solutions[i], datafile->instance[i]);
		fprintf(solutions_output, "Solution pour l'instance : %i \n\n", i);
		for (int j = 0; j < solutions->solutions[i]->nbObject; j++)
		{
			fprintf(solutions_output, "%i ", solutions->solutions[i]->objectBoolean[j]);
		}
		fprintf(solutions_output, "\nValeur totale : %i\n", solutions->solutions[i]->value);
		for (int j = 0; j < solutions->solutions[i]->nbDimension; j++)
		{
			fprintf(solutions_output, "Poids total pour la dimension %i : %i\n", j, \
																			solutions->solutions[i]->weightDimension[j]);
		}
		if (Is_Solution_Feasible(solutions->solutions[i], datafile->instance[i]))
		{
			fprintf(solutions_output, "La solution est réalisable \n");
		}
		else
		{
			fprintf(solutions_output, "La solution n'est pas réalisable \n");
		}
		fprintf(solutions_output, "\n\n\n");
		
	}
	
	/*Pour le codage indirect : même principe mais au lieu de génèrer des 0 et 1 aléatoirement
	 * on génère des priorités (forcèment pas 2 fois la même priorité)
	 * On remplit ensuite les objets en fonctions de leur priorité
	 * */
	
	//Solution temp pour empêcher le terminal de se fermer
	DataFile_delete(datafile);
	scanf("%c", &c);
	return 0;
}

/*void codageDirect(parser, solution)
{
	// on lit chaque objet et sa solution associée
	// si solution = 1, on met l'objet dans le sac
	// si solution = 0, ON LE TEJ (comme Felix)
}*/