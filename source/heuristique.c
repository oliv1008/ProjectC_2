#include "stdlib.h"
#include "include/parser.h"
#include "include/codage.h"

//FONCTIONS D'ORDONNANCEMENTS

int * Ordonnancement_aleatoire(Instance * instance)
{
	//On créé un tableau de pointeurs d'Object
	// /!\ (le tableau agrège les objets de l'instance passée en paramètre)
	int * objectTab = (int *) malloc(sizeof(int) * instance->nbObjectTotal);
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
		objectTab[i] = tab[alea];
		--taille;
		
		for(int j = alea; j < taille; j++)
		{
			tab[j] = tab[j + 1];
		}
	}
	
	free(tab);
	return objectTab;
}

//Renvoie l'indice des objets de l'instance passée en parametre, trie selon leur valeur (decroissant)
int * Ordonnancement_decroissant(Instance * instance)
{
	//On créé un tableau de pointeur d'Object
	int * objectTab = (int *) malloc(sizeof(int) * instance->nbObjectTotal);
	int * tab = (int *) malloc(sizeof(int) * instance->nbObjectTotal);
	
	//On créé le tableau d'indices (utilisé pour garder trace des objets que l'on a déjà ajouté)
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
		objectTab[i] = indiceMax;
		
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

//Renvoie l'indice des objets de l'instance passée en parametre, trie selon leur ratio valeur/sommePoids de leurs dimensions
//(decroissant)
int * Ordonnancement_ratio(Instance * instance)
{
	//On créé un tableau de pointeur d'Object
	int * objectTab = (int *) malloc(sizeof(int) * instance->nbObjectTotal);
	int * tab = (int *) malloc(sizeof(int) * instance->nbObjectTotal);
	float * tabRatio = (float *) malloc(sizeof(float) * instance->nbObjectTotal);
	
	//On créé le tableau d'indice (utilisé pour garder trace des objets que l'on a déjà ajouté)
	for (int i = 0; i < instance->nbObjectTotal; i++)
	{
		tab[i] = i;
	}
	
	//On créé le tableau de ratio valeur/sommePoids
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
		//On repart du début du tableau des objets restants
		valMax = tabRatio[tab[0]];
		indiceValMax = tab[0];
		indiceAEnlever = 0;
		//On parcourt uniquement les objets que l'on n'a pas encore ajouté au tableau d'objet
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
		objectTab[i] = indiceValMax;
		
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

//Renvoie l'indice des objets de l'instance passée en parametre, trie selon leur ration valeur/sommePoids des poids de
// la dimension critique (dimension ayant le ratio sommePoids/limite le plus élevé) (decroissant)
int * Ordonnancement_critique(Instance * instance)
{
	//On créé un tableau de pointeur d'Object
	int * objectTab = (int *) malloc(sizeof(int) * instance->nbObjectTotal);
	int * tab = (int *) malloc(sizeof(int) * instance->nbObjectTotal);
	float * tabRatio = (float *) malloc(sizeof(float) * instance->nbObjectTotal);
	
	//On créé le tableau d'indice (utilisé pour garder trace des objets que l'on a déjà ajouté)
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
	
	float valMax = tabRatio[tab[0]];
	int indiceValMax = tab[0];
	int indiceAEnlever = 0;
	int taille = instance->nbObjectTotal;
	//A chaque itération on recherche l'objet avec la plus grande valeur
	for (int i = 0; i < instance->nbObjectTotal; i++)
	{
		//On repart du début du tableau des objets restants
		valMax = tabRatio[tab[0]];
		indiceValMax = tab[0];
		indiceAEnlever = 0;
		//On parcourt uniquement les objets que l'on n'a pas encore ajouté au tableau d'objet
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
		objectTab[i] = indiceValMax;
		
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

//Renvoie l'indice des objets de l'instance passée en parametre, trie selon leur ratio valeur/sommePoids des poids de 
//la dimension critique (dimension ayant le ratio sommePoids/limite le plus élevé) (decroissant)
//Cette dimension critique est recalculée a chaque ajout dans le sac
int * Ordonnancement_dynamique(Instance * instance)
{
	//On créé un tableau de pointeur d'Object
	int * objectTab = (int *) malloc(sizeof(int) * instance->nbObjectTotal);
	int * tab = (int *) malloc(sizeof(int) * instance->nbObjectTotal);
	float * tabRatio = (float *) malloc(sizeof(float) * instance->nbObjectTotal);
	int * tabLimit = (int *) malloc(sizeof(int) * instance->nbDimension);
	
	//INITIALISATION DES VARIABLES ET TABLEAUX
	//On créé le tableau d'indice (utilisé pour garder trace des objets que l'on a déjà ajouté)
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
	//FIN INITIALISATION
	
	//A chaque itération on recherche l'objet avec la plus grande valeur
	float valMax = tabRatio[tab[0]];
	int indiceValMax = tab[0];
	int indiceAEnlever = 0;
	int taille = instance->nbObjectTotal;
	for (int i = 0; i < instance->nbObjectTotal; i++)
	{
		//On repart du début du tableau des objets restants
		valMax = tabRatio[tab[0]];
		indiceValMax = tab[0];
		indiceAEnlever = 0;
		//On parcourt uniquement les objets que l'on n'a pas encore ajouté au tableau d'objet
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
		objectTab[i] = indiceValMax;
		
		//Et on l'enlève du tableau d'indice pour ne pas réitérer dessus par la suite
		for (int j = indiceAEnlever; j < taille - 1; j++)
		{
			tab[j] = tab[j + 1];
		}
		taille--;
		
		//Et on met à jour le tableau de limites
		for (int j = 0; j < instance->nbDimension; j++)
		{
			tabLimit[j] -= instance->object[objectTab[i]]->weight[j];
		}
		
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
		
		//On met à jour le tableau de ratio valeur/sommePoids en prenant uniquement en compte la nouvelle dimension critique
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

//Renvoie l'indice des objets de l'instance passée en parametre, trie selon la somme de leur poids (croissant)
int * Ordonnancement_leger(Instance * instance)
{
	//On créé un tableau de pointeur d'Object
	int * objectTab = (int *)malloc(sizeof(int) * instance->nbObjectTotal);
	int * tab = (int *) malloc(sizeof(int) * instance->nbObjectTotal);
	
	//On créé le tableau d'indice (utilisé pour garder trace des objets que l'on a déjà ajouté)
	for (int i = 0; i < instance->nbObjectTotal; i++)
	{
		tab[i] = i;
	}
	
	int poidsMin = 0;
	int poidsObject = 0;
	int indiceMin;
	int indiceAEnlever;
	int taille = instance->nbObjectTotal;
	//A chaque itération on recherche l'objet avec le poids le plus léger
	for (int i = 0; i < instance->nbObjectTotal; i++)
	{
		// On repart du début du tableau des objets restants
		// On calcule le poids min en sommant le poids de chaque dimensions
		for (int j = 0; j < instance->nbDimension; j++)
		{
			poidsMin += instance->object[tab[0]]->weight[j];
		}
		indiceMin = tab[0];
		indiceAEnlever = 0;
		
		//On parcourt uniquement les objets que l'on n'a pas encore ajouté au tableau d'objet
		for (int j = 0; j < taille; j++)
		{
			for (int k = 0; k < instance->nbDimension; k++)
			{
				poidsObject += instance->object[tab[j]]->weight[k];
			}
			// Lorsqu'on a trouvé un objet avec un poids plus léger, on remplace le poidsMin actuel
			// et on garde en mémoire sa position de manière à l'enlever plus tard
			if (poidsMin > poidsObject)
			{
				poidsMin = poidsObject;
				indiceMin = tab[j];
				indiceAEnlever = j;
			}
			poidsObject = 0; // on réinitialise à 0
		}		
		
		//On ajoute l'objet trouvé au tableau d'objet
		objectTab[i] = indiceMin;
		
		//Et on l'enlève du tableau d'indice pour ne pas réitérer dessus par la suite
		for (int j = indiceAEnlever; j < taille - 1; j++)
		{
			tab[j] = tab[j + 1];
		}
		
		taille--;
		poidsMin = 0; // on réinitialise à 0
	}
	
	free(tab);
	return objectTab;
}

// ALGORITHME HEURISTIQUE
//Renvoie une solution direct ou indirect, ordonnee selon un algorithme passé en paramètre
Solution * Algorithme_solutions (Instance * instance, int * (*ordo_fct)(Instance *), int codage)
{
	int element;
	//On trie les objets de l'instance selon une fonction donnée
	int * tabObject = ordo_fct(instance);
	Solution * sol = Solution_new(instance->nbObjectTotal, instance->nbDimension);
	int priority = 1;
	int valid = 1;
	
	//Pour autant d'objet qu'il y a dans l'instance
	for (int i = 0; i < instance->nbObjectTotal; i++)
	{
		element = tabObject[i];
		//Si on est en codage direct
		if (codage == 0)
		{
			//On regarde si on peut ajouter le prochain objet du tableau d'objets trié
			for (int j = 0; (j < instance->nbDimension) && valid; j++)
			{
				//cad est ce que son poids dans chaque dimension ne fait pas "deborder" la somme des poids actuelle
				// de chaque dimension en dehors de la limite ?
				if (instance->object[element]->weight[j] + sol->weightDimension[j] > instance->limit[j])
				{
					valid = 0;
				}
			}
			//Si oui, on l'ajoute a la solution
			if (valid)
			{
				sol->objectTab[element] = 1;
				sol->value += instance->object[element]->value;
				for (int k = 0; k < sol->nbDimension; k++)
				{
					sol->weightDimension[k] += instance->object[element]->weight[k];
				}
			}
			valid = 1;
		}
		//Si on est en codage indirect
		else if (codage == 1)
		{
			sol->objectTab[element] = priority;
			priority++;
		}
	}
	
	if (codage == 1)
	{
		Load_Solution_indirect(sol, instance);
	}
	
	free(tabObject);
	return sol;
}