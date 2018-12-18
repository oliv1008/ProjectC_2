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

Object ** Ordonnancement_decroissant(Instance * instance)
{
	//On créer un tableau de pointeur d'Object
	// /!\ ATTENTION NE PAS FREE LES OBJECTS (le tableau agrège les objets de l'instance passée en paramètre)
	Object ** objectTab = (Object **) malloc(sizeof(Object *) * instance->nbObjectTotal);
	int * tab = (int *) malloc(sizeof(int) * instance->nbObjectTotal);
	
	for (int i = 0; i < instance->nbObjectTotal; i++)
	{
		tab[i] = i;
	}
	
	int valMax = instance->object[0]->value;
	int indiceMax = 0;
	int indiceAEnlever;
	int taille = instance->nbObjectTotal;
	
	for (int i = 0; i < instance->nbObjectTotal; i++)
	{
		valMax = instance->object[tab[0]]->value;
		indiceMax = 0;
		for (int j = 0; j < taille; j++)
		{
			if (valMax < instance->object[tab[j]]->value)
			{
				valMax = instance->object[tab[j]]->value;
				indiceMax = tab[j];
				indiceAEnlever = j;
			}
		}
		
		objectTab[i] = instance->object[indiceMax];
		
		for (int j = indiceAEnlever; j < taille; j++)
		{
			tab[j] = tab[j + 1];
		}
		taille--;
	}
	
	return objectTab;
}

Object ** Ordonnancement_ratio(Instance * instance)
{
	//On créer un tableau de pointeur d'Object
	// /!\ ATTENTION NE PAS FREE LES OBJECTS (le tableau agrège les objets de l'instance passée en paramètre)
	Object ** objectTab = (Object **) malloc(sizeof(Object *) * instance->nbObjectTotal);
	int * tab = (int *) malloc(sizeof(int) * instance->nbObjectTotal);
	
	for (int i = 0; i < instance->nbObjectTotal; i++)
	{
		tab[i] = i;
	}
	
}