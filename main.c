#include <stdio.h>
#include "stdlib.h"
#include "time.h"
#include "include/parser.h"
#include "include/codage.h"
#include "include/heuristique.h"
#include "include/recherche_locale.h"

int main(int argc, char **argv)
{
	int codage = 0;
	int ordonnancement = 0;
	FILE * f;
	DataFile * datafile;
	srand( time(NULL));
	
	if (argc != 2)
	{
		printf("Erreur, utilisation : [Chemin vers un fichier]\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		f = fopen(argv[1], "r");
		if (f == NULL)
		{
			printf("Chemin d'accès incorrect, veuillez spécifier un chemin d'accès correct\n");
			exit(EXIT_FAILURE);
		}
		else
		{
			datafile = Parser(f);
		}
	}
	
	do
	{
		// choix du codage par l'utilisateur
		printf("Quel codage ? (0 = direct, 1 = direct) ");
		scanf("%i", &codage);
	}while (codage < 0 || codage > 1);
	printf("\n");
	
	do
	{
		// choix de l'ordonnancement par l'utilisateur
		printf("Quel ordonnancement ?\n");
		printf("1 : decroissant\n");
		printf("2 : ratio\n");
		printf("3 : critique\n");
		printf("4 : dynamique\n");
		printf("5 : leger\n");
		scanf("%i", &ordonnancement);
	}while(ordonnancement < 1 || ordonnancement > 5);
	printf("\n\n\n");
	
	//Codage direct
	if(codage == 0)
	{
		void * pFonction = 0;
		
		switch(ordonnancement)
		{
			case 1: 
				pFonction = Ordonnancement_decroissant;
				break;
			case 2:
				pFonction = Ordonnancement_ratio;
				break;
			case 3:
				pFonction = Ordonnancement_critique;
				break;
			case 4:
				pFonction = Ordonnancement_dynamique;
				break;
			case 5:
				pFonction = Ordonnancement_leger;
				break;
			default:
				break;
		}
		
		Solution * startSol;
		Solution * endSol;
		for (unsigned int uiIndiceInstance = 0; uiIndiceInstance < datafile->TotalNbInstance; uiIndiceInstance++)
		{
			startSol = Algorithme_solutions(datafile->instance[uiIndiceInstance], pFonction, 0);
			endSol = algorithme_recherche_locale_direct(startSol, datafile->instance[uiIndiceInstance]);
			printf("Solution pour l'instance %i :\n\n", uiIndiceInstance + 1);
			printSolutionToConsole(endSol);
			Solution_delete(startSol);
			Solution_delete(endSol);
		}
	}
	
	else if (codage == 1)
	{
		
		void * pFonction = 0;
		
		switch(ordonnancement)
		{
			case 1: 
				pFonction = Ordonnancement_decroissant;
				break;
			case 2:
				pFonction = Ordonnancement_ratio;
				break;
			case 3:
				pFonction = Ordonnancement_critique;
				break;
			case 4:
				pFonction = Ordonnancement_dynamique;
				break;
			case 5:
				pFonction = Ordonnancement_leger;
				break;
			default:
				break;
		}
		
		Solution * startSol;
		Solution * endSol;
		for (unsigned int uiIndiceInstance = 0; uiIndiceInstance < datafile->TotalNbInstance; uiIndiceInstance++)
		{
			startSol = Algorithme_solutions(datafile->instance[uiIndiceInstance], pFonction, 1);
			endSol = algorithme_recherche_locale_indirect(startSol, datafile->instance[uiIndiceInstance]);
			printf("Solution pour l'instance %i :\n\n", uiIndiceInstance + 1);
			printSolutionToConsole(endSol);
			Solution_delete(startSol);
			Solution_delete(endSol);
		}
	}
	
	DataFile_delete(datafile);
	fclose(f);
	return 0;
}