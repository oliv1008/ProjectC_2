#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "include/parser.h"

//FONCTION PARSER

/*
 * ALGO PARSER
 * 
 * Pour chaque instance
 * 	Récupérer nbObject
 * 	Récupérer nbDimension
 * 	Récupérer matrice nbObject x nbDimensions
 * 	->Obtention d'une matrice "à l'envers" par rapport au fichier.txt, une ligne comporte
 * 	->la valeur(matrice[0]) puis le poids(matrice[1+]
 * 	Récupérer limit
 * 	init(instance)
 * 	Pour chaque object
 * 		Init(Object)
 * 		Ajouter object à instance
 * */


//FONCTIONS OBJECT

int Object_init(Object* object, int value, int * weight)
{
	object->value = value;
	object->weight = weight;
	
	return 0;}

Object * Object_new(int value, int * weight)
{
	Object * my_object = (Object*) malloc(sizeof(Object));
	if (my_object)
	{
		if(Object_init(my_object, value, weight))
		{
			free(my_object);
			my_object = NULL;
		}
	}
	
	return my_object;
}

void Object_finalize(Object * object)
{
	(void) object;
}

void Object_delete(Object * object)
{
	Object_finalize(object);
	free(object);
}

//FONCTIONS INSTANCE

int Instance_init(Instance * instance, int nbObjectTotal, int nbDimension, int * limit)
{
	instance->nbObjectTotal = nbObjectTotal;
	instance->nbObjectCurrent = 0;
	instance->nbDimension = nbDimension;
	instance->object = (Object**) malloc(sizeof(Object*) * instance->nbObjectTotal);
	if (instance->object == NULL) return 1;
	instance->limit = limit;
	
	return 0;
}

Instance * Instance_new(int nbObject, int nbDimension, int * limit)
{
	Instance * my_instance = (Instance*) malloc(sizeof(Instance));
	if (my_instance)
	{
		if (Instance_init(my_instance, nbObject, nbDimension, limit))
		{
			free(my_instance);
			my_instance = NULL;
		}
	}
	
	return my_instance;
}

void Instance_finalize(Instance * instance)
{
	for (int i = 0; i < instance->nbObjectCurrent; i++)
	{
		Object_delete(instance->object[i]);
	}
	free(instance->object);
}

void Instance_delete(Instance * instance)
{
	Instance_finalize(instance);
	free(instance);
}

int Instance_addObject(Instance * instance, Object * object)
{
	//Si l'instance n'est pas déjà pleine, on ajoute l'object
	if (instance->nbObjectCurrent < instance->nbObjectTotal)
	{
		instance->object[instance->nbObjectCurrent] = object;
		instance->nbObjectCurrent++;
		
		return 0;
	}
	
	//Sinon on renvoie une erreur
	return 1;
}