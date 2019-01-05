Object ** Ordonnancement_aleatoire(Instance * instance);
Object ** Ordonnancement_decroissant(Instance * instance);
Object ** Ordonnancement_ratio(Instance * instance);
Object ** Ordonnancement_critique(Instance * instance);
Object ** Ordonnancement_dynamique(Instance * instance);
Object ** Ordonnancement_leger(Instance * instance);
Solution * Algorithme_solutions (Instance * instance, Object ** (*ordo_fct)(Instance *), int codage);
