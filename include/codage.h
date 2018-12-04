typedef struct __Solution
{
	int nbObject;
	int * objectBoolean;
	int value;
	int nbDimension;
	int * weightDimension;
}Solution;

Solution * Randomize_solution(int nbObject, int nbDimension);

//FONCTIONS D'INITIALISATION DE SOLUTION

int Solution_init(Solution * solution, int nbObject, int nbDimension);
Solution * Solution_new(int nbObject, int nbDimension);
void Solution_finalize(Solution * solution);
void Solution_delete(Solution * solution);
