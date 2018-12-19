Object ** Ordonnancement_aleatoire(Instance * instance);
Object ** Ordonnancement_decroissant(Instance * instance);
Object ** Ordonnancement_ratio(Instance * instance);
Object ** Ordonnancement_critique(Instance * instance);
Solution * Algorithme_solutions (Instance * instance, Object ** (*ordo_fct)(Instance *));
