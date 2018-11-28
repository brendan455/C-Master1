// Prototypes

//***********************************************************
//Structure repr�santant un �l�ment de l'etat gene.
//***********************************************************
typedef struct etat_gene
{
    int etat_courant[NBR_GENES_MAX];
    struct etat_gene *pSuivant;

}etat_gene;

//***********************************************************
//Liberer la memoire
//***********************************************************
void libererListe(etat_gene *pListEtatGene);

//***********************************************************
//Ajouter un element dans le liste chainee
//***********************************************************
void ajoutElemListe(etat_gene *pListEtatGene, int *etat_courant);

//***********************************************************
//Affiche la totalit� de la etat_gene en commen�ant par le sommet.
//***********************************************************
void afficherListe(etat_gene *pListEtatGene);

