#include <stdio.h>
#include "include/parser.h"

int main(int argc, char **argv)
{
	char c;
	FILE * f;
	
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
			Parser(f);
		}
	}
	
	//Solution temp pour empêcher le terminal de se fermer
	scanf("%c", &c);
	return 0;
}
