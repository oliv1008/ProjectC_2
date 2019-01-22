#ifndef PARSER_H
#define PARSER_H

#include "stdio.h"

typedef struct __Object
{
	int value;
	int * weight;
}Object;

typedef struct __Instance
{
	int nbObjectTotal;
	int nbDimension;
	Object ** object;
	int * limit;
}Instance;

typedef struct __DataFile
{
	Instance ** instance;
	int CurrentNbInstance;
	int TotalNbInstance;
}DataFile;

DataFile * Parser(FILE* file_to_parse);

//FONCTIONS OBJECT

int Object_init(Object* object, int nbdimension);
Object * Object_new(int nbDimension);
void Object_finalize(Object * object);
void Object_delete(Object * object);

//FONCTIONS INSTANCE

int Instance_init(Instance * instance, int nbObject, int nbDimension);
Instance * Instance_new(int nbObjectTotal, int nbDimension);
void Instance_finalize(Instance * instance);
void Instance_delete(Instance * instance);
int Instance_addObject(Instance * instance, Object * object);

//FONCTIONS DATAFILE

int DataFile_init(DataFile * datafile, int TotalNbInstance);
DataFile * DataFile_new(int TotalNbInstance);
void DataFile_finalize(DataFile * datafile);
void DataFile_delete(DataFile * datafile);
int DataFile_addInstance(DataFile * datafile, Instance * instance);

#endif