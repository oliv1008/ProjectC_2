#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "include/parser.h"

//FONCTION PARSER
//A FAIRE : instance->nbObjectCurrent ne sert actuellement à rien, à corriger
 
DataFile * Parser(FILE* file_to_parse)
{
	int data_to_ignore;
	char char_to_ignore;
	
	FILE * f = fopen("output.txt", "w+");
	
	//Initialisation de la datafile (nb d'instance totales)
	int TotalNbInstance;
	fscanf(file_to_parse, "%i", &TotalNbInstance);
	printf("TotalNbInstance = %i\n", TotalNbInstance);
	DataFile * datafile = DataFile_new(TotalNbInstance);
	
	//On itère sur chaque instance tout au long du fichier
	for (int instance_count = 0; instance_count < datafile->TotalNbInstance; instance_count++)
	{
		//Initialisation du timer
		clock_t debut;
		debut = clock();
		
		//Initialisation de l'instance
		int nbObjectTotal;
		int nbDimension;
		fscanf(file_to_parse, "%i", &nbObjectTotal);
		fscanf(file_to_parse, "%i", &nbDimension);
		fprintf(f, "Numéro de l'instance = %i\n", instance_count);
		fprintf(f, "Nombre d'objet = %i\n", nbObjectTotal);
		fprintf(f, "Nombre de dimension = %i\n", nbDimension);
		Instance * instance = Instance_new(nbObjectTotal, nbDimension);
		DataFile_addInstance(datafile, instance);
		
		//Ignorer les données à ignorer
			//Les valeur d'une solution et une autre solution
		fscanf(file_to_parse, "%i", &data_to_ignore);
		fscanf(file_to_parse, "%i", &data_to_ignore);
			//Retour à la ligne
		char_to_ignore = fgetc(file_to_parse);
			//Valeur des variables xj d'une solution réalisable
		do
		{
			char_to_ignore = fgetc(file_to_parse);
		} while (char_to_ignore != '\n');
		//Fin des valeurs à ignorer
		
		//Remplissage des objets contenus dans l'instance
		int value;
		for (int i = 0; i < nbDimension + 1; i++)
		{
			for (int j = 0; j < nbObjectTotal; j++)
			{
				fscanf(file_to_parse, "%i", &value);
				if (i == 0)
				{
					instance->object[j]->value = value;
				}
				else
				{
					instance->object[j]->weight[i - 1] = value;
				}
			}
		}
		//Fin du remplissage des objets
		
		//Récupération des limites
		for (int i = 0; i < instance->nbDimension; i++)
		{
			fscanf(file_to_parse, "%i", &value);
			instance->limit[i] = value;
		}
		//Fin de la récupération des limites
		
		double time_elapsed = (((double) clock() - debut) / CLOCKS_PER_SEC);
		fprintf(f, "Temps écoulé pour l'instance %i = %f\n\n", instance_count, time_elapsed);
	}

	fclose(f);
	return datafile;
}


//FONCTIONS OBJECT

int Object_init(Object* object, int nbDimension)
{
	//Dimension + 1 car une colone pour la valeur et nbDimension pour le nombre de dimension
	object->weight = (int*) malloc(sizeof(int) * nbDimension);
	if (object->weight)
	{
		return 0;
	}
	
	return 1;}

Object * Object_new(int nbDimension)
{
	Object * my_object = (Object*) malloc(sizeof(Object));
	if (my_object)
	{
		if(Object_init(my_object, nbDimension))
		{
			free(my_object);
			my_object = NULL;
		}
	}
	
	return my_object;
}

void Object_finalize(Object * object)
{
	free(object->weight);
}

void Object_delete(Object * object)
{
	Object_finalize(object);
	free(object);
}

//FONCTIONS INSTANCE

int Instance_init(Instance * instance, int nbObjectTotal, int nbDimension)
{
	instance->nbObjectTotal = nbObjectTotal;
	instance->nbDimension = nbDimension;
	instance->object = (Object**) malloc(sizeof(Object*) * instance->nbObjectTotal);
	if (instance->object == NULL)
	{
		return 1;
	}
	else
	{
		for (int i = 0; i < nbObjectTotal; i++)
		{
			instance->object[i] = Object_new(nbDimension);
		}
	}
	instance->limit = (int *) malloc (sizeof(int) * instance->nbDimension);
	if (instance->limit == NULL)
	{
		return 1;
	}
	
	return 0;
}

Instance * Instance_new(int nbObjectTotal, int nbDimension)
{
	Instance * my_instance = (Instance*) malloc(sizeof(Instance));
	if (my_instance)
	{
		if (Instance_init(my_instance, nbObjectTotal, nbDimension))
		{
			free(my_instance);
			my_instance = NULL;
		}
	}
	
	return my_instance;
}

void Instance_finalize(Instance * instance)
{
	for (int i = 0; i < instance->nbObjectTotal; i++)
	{
		Object_delete(instance->object[i]);
	}
	free(instance->object);
	free(instance->limit);
}

void Instance_delete(Instance * instance)
{
	Instance_finalize(instance);
	free(instance);
}

//FONCTIONS DATAFILE

int DataFile_init(DataFile * datafile, int TotalNbInstance)
{
	datafile->CurrentNbInstance = 0;
	datafile->TotalNbInstance = TotalNbInstance;
	datafile->instance = (Instance**) malloc(sizeof(Instance*) * datafile->TotalNbInstance);
	
	if (datafile->instance)
	{
		return 0;
	}
	
	return 1;
} 

DataFile * DataFile_new(int TotalNbInstance)
{
	DataFile * my_datafile = (DataFile*) malloc(sizeof(DataFile));
	if (my_datafile)
	{
		if (DataFile_init(my_datafile, TotalNbInstance))
		{
			free(my_datafile);
			my_datafile = NULL;
		}
	}
	
	return my_datafile;
}

void DataFile_finalize(DataFile * datafile)
{
	for (int i = 0; i < datafile->CurrentNbInstance; i++)
	{
		Instance_delete(datafile->instance[i]);
	}
	free(datafile->instance);
}

void DataFile_delete(DataFile * datafile)
{
	DataFile_finalize(datafile);
	free(datafile);
}

int DataFile_addInstance(DataFile * datafile, Instance * instance)
{
		//Si la datafile n'est pas déjà pleine, on ajoute l'instance
	if (datafile->CurrentNbInstance < datafile->TotalNbInstance)
	{
		datafile->instance[datafile->CurrentNbInstance] = instance;
		datafile->CurrentNbInstance++;
		
		return 0;
	}
	
	//Sinon on renvoie une erreur
	return 1;
}