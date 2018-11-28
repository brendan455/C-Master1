// Prototypes
int est_ressource(int arc_courant, int niveau_courant);
int evolution_variable(int etat[NBR_GENES_MAX], int index, int nbr_genes, int plafonds[NBR_GENES_MAX], int arcs[NBR_GENES_MAX][NBR_GENES_MAX], int gene_prioritaire);
void evolution_etat_synchrone(int etat[NBR_GENES_MAX], int newetat[NBR_GENES_MAX], int nbr_genes, int plafonds[NBR_GENES_MAX], int arcs[NBR_GENES_MAX][NBR_GENES_MAX]);
void evolution_etat_asynchrone(int etat[NBR_GENES_MAX], int newetat[NBR_GENES_MAX], int nbr_genes, int plafonds[NBR_GENES_MAX], int arcs[NBR_GENES_MAX][NBR_GENES_MAX], int gene_prioritaire);
