int * Ordonnancement_aleatoire(Instance * instance);
int * Ordonnancement_decroissant(Instance * instance);
int * Ordonnancement_ratio(Instance * instance);
int * Ordonnancement_critique(Instance * instance);
int * Ordonnancement_dynamique(Instance * instance);
int * Ordonnancement_leger(Instance * instance);
Solution * Algorithme_solutions (Instance * instance, int * (*ordo_fct)(Instance *), int codage);
