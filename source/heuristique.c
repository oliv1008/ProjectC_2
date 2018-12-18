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
	
	//On créer le tableau d'indice (utilisé pour garder trace des objets que l'on a déjà ajouté)
	for (int i = 0; i < instance->nbObjectTotal; i++)
	{
		tab[i] = i;
	}
	
	int valMax = instance->object[tab[0]]->value;
	int indiceMax = tab[0];
	int indiceAEnlever = 0;
	int taille = instance->nbObjectTotal;
	//A chaque itération on recherche l'objet avec la plus grande valeur
	for (int i = 0; i < instance->nbObjectTotal; i++)
	{
		//On repart du début du tableau des objets restant
		valMax = instance->object[tab[0]]->value;
		indiceMax = tab[0];
		indiceAEnlever = 0;
		//On parcourt uniquement les objets que l'on pas encore ajouté au tableau d'objet
		for (int j = 0; j < taille; j++)
		{
			//Lorsqu'on a trouvé un objet avec une plus grande valeur, on remplace la valMax actuelle
			//et on garde en mémoire sa position de manière à l'enlever plus tard
			if (valMax < instance->object[tab[j]]->value)
			{
				valMax = instance->object[tab[j]]->value;
				indiceMax = tab[j];
				indiceAEnlever = j;
			}
		}
		//On ajoute l'objet trouvé au tableau d'objet
		objectTab[i] = instance->object[indiceMax];
		
		//Et on l'enlève du tableau d'indice pour ne pas réitérer dessus par la suite
		for (int j = indiceAEnlever; j < taille - 1; j++)
		{
			tab[j] = tab[j + 1];
		}
		taille--;
	}
	
	free(tab);
	return objectTab;
}

Object ** Ordonnancement_ratio(Instance * instance)
{
	//On créer un tableau de pointeur d'Object
	// /!\ ATTENTION NE PAS FREE LES OBJECTS (le tableau agrège les objets de l'instance passée en paramètre)
	Object ** objectTab = (Object **) malloc(sizeof(Object *) * instance->nbObjectTotal);
	int * tab = (int *) malloc(sizeof(int) * instance->nbObjectTotal);
	float * tabRatio = (float *) malloc(sizeof(float) * instance->nbObjectTotal);
	
	//On créer le tableau d'indice (utilisé pour garder trace des objets que l'on a déjà ajouté)
	for (int i = 0; i < instance->nbObjectTotal; i++)
	{
		tab[i] = i;
	}
	
	//On créer le tableau de ratio valeur/sommePoids
	for (int i = 0; i < instance->nbObjectTotal; i++)
	{
		float sommePoids = 0;
		for (int j = 0; j < instance->nbDimension; j++)
		{
			sommePoids += instance->object[i]->weight[j];
		} 
		tabRatio[i] = ((float) instance->object[i]->value) / (sommePoids);
	}
	
	float valMax = tabRatio[tab[0]];
	int indiceValMax = tab[0];
	int indiceAEnlever = 0;
	int taille = instance->nbObjectTotal;
	//A chaque itération on recherche l'objet avec la plus grande valeur
	for (int i = 0; i < instance->nbObjectTotal; i++)
	{
		//On repart du début du tableau des objets restant
		valMax = tabRatio[tab[0]];
		indiceValMax = tab[0];
		indiceAEnlever = 0;
		//On parcourt uniquement les objets que l'on pas encore ajouté au tableau d'objet
		for (int j = 0; j < taille; j++)
		{
			//Lorsqu'on a trouvé un objet avec une plus grande valeur, on remplace la valMax actuelle
			//et on garde en mémoire sa position de manière à l'enlever plus tard
			if (valMax < tabRatio[tab[j]])
			{
				valMax = tabRatio[tab[j]];
				indiceValMax = tab[j];
				indiceAEnlever = j;
			}
		}
		//On ajoute l'objet trouvé au tableau d'objet
		objectTab[i] = instance->object[indiceValMax];
		
		//Et on l'enlève du tableau d'indice pour ne pas réitérer dessus par la suite
		for (int j = indiceAEnlever; j < taille - 1; j++)
		{
			tab[j] = tab[j + 1];
		}
		taille--;
	}
	
	free(tab);
	free(tabRatio);
	return objectTab;
}