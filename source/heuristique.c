#include "stdlib.h"
#include "include/parser.h"
#include "include/codage.h"

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

Object ** Ordonnancement_critique(Instance * instance)
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
	
	//On recherche la dimension critique
	float ratioMaxActuel = 0;
	float sommePoids = 0;
	int indiceDimCritique = 0;
	for (int i = 0; i < instance->nbDimension; i++)
	{
		for (int j = 0; j < instance->nbObjectTotal; j++)
		{
			sommePoids += instance->object[j]->weight[i];
		}
		
		if (sommePoids / ((float)instance->limit[i]) > ratioMaxActuel)
		{
			ratioMaxActuel = sommePoids / ((float)instance->limit[i]);
			indiceDimCritique = i;
		}
		
		sommePoids = 0;
	}
	
	//On créer le tableau de ratio valeur/sommePoids en prenant uniquement en compte la dimension critique
	for (int i = 0; i < instance->nbObjectTotal; i++)
	{
		tabRatio[i] = ((float) instance->object[i]->value) / ((float) instance->object[i]->weight[indiceDimCritique]);
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

Object ** Ordonnancement_dynamique(Instance * instance)
{
	//On créer un tableau de pointeur d'Object
	// /!\ ATTENTION NE PAS FREE LES OBJECTS (le tableau agrège les objets de l'instance passée en paramètre)
	Object ** objectTab = (Object **) malloc(sizeof(Object *) * instance->nbObjectTotal);
	int * tab = (int *) malloc(sizeof(int) * instance->nbObjectTotal);
	float * tabRatio = (float *) malloc(sizeof(float) * instance->nbObjectTotal);
	int * tabLimit = (int *) malloc(sizeof(int) * instance->nbDimension);
	
	//On créer le tableau d'indice (utilisé pour garder trace des objets que l'on a déjà ajouté)
	for (int i = 0; i < instance->nbObjectTotal; i++)
	{
		tab[i] = i;
	}
	
	//On recherche la dimension critique
	float ratioMaxActuel = 0;
	float sommePoids = 0;
	int indiceDimCritique = 0;
	for (int i = 0; i < instance->nbDimension; i++)
	{
		for (int j = 0; j < instance->nbObjectTotal; j++)
		{
			sommePoids += instance->object[j]->weight[i];
		}
		
		if (sommePoids / ((float)instance->limit[i]) > ratioMaxActuel)
		{
			ratioMaxActuel = sommePoids / ((float)instance->limit[i]);
			indiceDimCritique = i;
		}
		
		sommePoids = 0;
	}
	
	//On créé le tableau de ratio valeur/sommePoids en prenant uniquement en compte la dimension critique
	for (int i = 0; i < instance->nbObjectTotal; i++)
	{
		tabRatio[i] = ((float) instance->object[i]->value) / ((float) instance->object[i]->weight[indiceDimCritique]);
	}
	
	//On copie les limites de poids dans un tableau alloué sur le tas
	for (int i = 0; i < instance->nbDimension; i++)
	{
		tabLimit[i] = instance->limit[i];
	}
	
	//A chaque itération on recherche l'objet avec la plus grande valeur
	float valMax = tabRatio[tab[0]];
	int indiceValMax = tab[0];
	int indiceAEnlever = 0;
	int taille = instance->nbObjectTotal;
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
		//Et on met à jour le tableau de limites
		for (int j = 0; j < instance->nbDimension; j++)
		{
			tabLimit[j] -= objectTab[i]->weight[j];
		}
		
		//Et on l'enlève du tableau d'indice pour ne pas réitérer dessus par la suite
		for (int j = indiceAEnlever; j < taille - 1; j++)
		{
			tab[j] = tab[j + 1];
		}
		taille--;
		
		//On recherche la nouvelle dimension critique
		ratioMaxActuel = 0;
		sommePoids = 0;
		indiceDimCritique = 0;
		for (int w = 0; w < instance->nbDimension; w++)
		{
			for (int j = 0; j < taille; j++)
			{
				sommePoids += instance->object[tab[j]]->weight[w];
			}
			
			if (sommePoids / ((float)tabLimit[w]) > ratioMaxActuel)
			{
				ratioMaxActuel = sommePoids / ((float)tabLimit[w]);
				indiceDimCritique = w;
			}
			
			sommePoids = 0;
		}
		
		//On met à jours le tableau de ratio valeur/sommePoids en prenant uniquement en compte la nouvelle dimension critique
		printf("dimension critique = %i\n", indiceDimCritique);
		for (int w = 0; w < instance->nbObjectTotal; w++)
		{
			tabRatio[w] = ((float) instance->object[w]->value) / ((float) instance->object[w]->weight[indiceDimCritique]);
		}
	}
	
	free(tab);
	free(tabRatio);
	free(tabLimit);
	return objectTab;
}

// ALGORITHME HEURISTIQUE
Solution * Algorithme_solutions (Instance * instance, Object ** (*ordo_fct)(Instance *), int codage)
{
	Object * element;
	Object ** tabObject = ordo_fct(instance);
	Solution * sol = Solution_new(instance->nbObjectTotal, instance->nbDimension);
	int priority = 1;
	
	for (int i = 0; i < instance->nbObjectTotal; i++)
	{
		// on initialise notre solution direct à 0
		sol->objectTab[i] = 0;
	}
	
	int valid = 1;
	for (int j = 0; j < instance->nbObjectTotal; j++)
	{
		element = tabObject[j];
		for (int k = 0; (k < instance->nbDimension) && valid; k++)
		{
			if (element->weight[k] + sol->weightDimension[k] > instance->limit[k])
			{
				valid = 0;
			}
		}
		if (valid)
		{
			sol->value += element->value;
			//Si nous travaillons avec une solution direct
			if (codage == 0)
			{
				sol->objectTab[j] = 1;
			}
			//Sinon si on travaille avec une solution indirect
			else if (codage == 1)
			{
				sol->objectTab[j] = priority;
				priority++;
			}
			for (int k = 0; k < sol->nbDimension; k++)
			{
				sol->weightDimension[k] += element->weight[k];
			}
		}
		valid = 1;
	}
	
	return sol;
}
