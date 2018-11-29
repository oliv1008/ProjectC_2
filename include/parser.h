typedef struct __Object
{
	int value;
	int * weight;
}Object;

typedef struct __Instance
{
	int nbObjectCurrent;
	int nbObjectTotal;
	int nbDimension;
	Object ** object;
	int * limit;
}Instance;

//FONCTIONS OBJECT

int Object_init(Object* object, int value, int * weight);
Object * Object_new(int value, int * weight);
void Object_finalize(Object * object);
void Object_delete(Object * object);

//FONCTIONS INSTANCE

int Instance_init(Instance * instance, int nbObject, int nbDimension, int * limit);
Instance * Instance_new(int nbObject, int nbDimension, int * limit);
void Instance_finalize(Instance * instance);
void Instance_delete(Instance * instance);
int Instance_addObject(Instance * instance, Object * object);