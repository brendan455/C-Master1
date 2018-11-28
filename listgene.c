//***********************************************************
//  DENIAUD Brendan E109500X Master de bioinformatique

//  Voir le fichier README pour les consignes et des informations
//  sur la compilation et l'exécution du programme.

// Ce fichier contient les fonctions relatives au traitement de la liste chainee

//  Voir le fichier main.c pour des exemples d'utilisation.
//***********************************************************

#include <stdlib.h>
#include <stdio.h>

#include "constantes.h"
#include "listgene.h"

void libererListe(etat_gene *pListEtatGene)
{
    if (pListEtatGene != NULL)
    {
        if (pListEtatGene->pSuivant != NULL)
        {
            libererListe(pListEtatGene->pSuivant);
        }
        free(pListEtatGene);
    }
}
void ajoutElemListe(etat_gene *pListEtatGene, int *etat_courant)
{
    int i;
    etat_gene *pNouveau;
    etat_gene *pCourant;

    if (pListEtatGene != NULL)
    {
        pCourant = pListEtatGene;
        while (pCourant->pSuivant != NULL)
        {
            pCourant = pCourant->pSuivant;
        }

        pNouveau = (etat_gene*)malloc(sizeof(struct etat_gene));
        for (i = 0; i < NBR_GENES_MAX; i++)
        {
            pNouveau->etat_courant[i] = etat_courant[i];
        }
        pCourant->pSuivant = pNouveau;

        pNouveau->pSuivant = NULL;
    }
}

//***********************************************************
//  afficherListe
//      Cette fonction sert a afficher tous les elements de
//      la liste chainée.
//  entree
//      p   pointeur sur la liste chainee
//***********************************************************
void afficherListe(etat_gene *p)
{
    if (p != NULL)
    {
        printf("%-5d %-5d %-5d\n",p->etat_courant[0], p->etat_courant[1], p->etat_courant[2]);
        if (p->pSuivant != NULL)
        {
            afficherListe(p->pSuivant);
        }
    }
}
