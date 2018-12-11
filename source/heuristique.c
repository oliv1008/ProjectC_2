#include "stdlib.h"
#include "include/parser.h"

//FONCTIONS D'ORDONNANCEMENTS

Object ** Ordonnancement_aleatoire(Instance * instance)
{
	//On créer un tableau de pointeur d'Object
	// /!\ ATTENTION NE PAS FREE LES OBJECTS (le tableau agrège les objets de l'instance passée en paramètre)
	Object ** objectTab = (Object **) malloc(sizeof(Object *) * instance->nbObjectTotal);
	int * tab = (int *) malloc(sizeof(int) * instance->nbObjectTotal);
	
	for (int i = 0; i < instance->nbObjectTotal; i++)
	{
		tab[i] = i;
	}
	
	int alea;
	int taille = instance->nbObjectTotal;
	
	for (int i = 0; i < instance->nbObjectTotal; i++)
	{
		alea = rand() % taille;
		objectTab[i] = instance->object[tab[alea]];
		--taille;
		
		for(int j = alea; j < taille; j++)
		{
			tab[j] = tab[j + 1];
		}
	}
	
	free(tab);
	return objectTab;
}