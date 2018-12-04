#include <stdio.h>
#include "stdlib.h"
#include "time.h"
#include "include/parser.h"
#include "include/codage.h"

int main(int argc, char **argv)
{
	char c;
	FILE * f;
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
	
	Randomize_solution(100, 5);
	/*Pour chaque instance : 
	 * 		Créer aléatoirement une solution
	 * 		Remplir cette solution avec les valeurs de l'instance
	 * 		Evaluer la solution
	 * 		Tester la faisabilité
	 * 		Ecrire la solution dans un fichier
	
	//Solution temp pour empêcher le terminal de se fermer
	scanf("%c", &c);
	return 0;
}

/*void codageDirect(parser, solution)
{
	// on lit chaque objet et sa solution associée
	// si solution = 1, on met l'objet dans le sac
	// si solution = 0, ON LE TEJ (comme Felix)
}*/