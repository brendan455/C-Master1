//***********************************************************
//  DENIAUD Brendan E109500X Master de bioinformatique

//  Voir le fichier README pour les consignes et des informations
//  sur la compilation et l'exécution du programme.

// Ce fichier contient les fonctions relatives au traitement du ficher d'entree

//  Voir le fichier main.c pour des exemples d'utilisation.
//***********************************************************


#include <stdio.h>    // Pour printf, scanf
#include <stdlib.h>   // Pour abs
#include <string.h>   // Pour memset

#include "fichier.h"
#include "constantes.h"


void caracterisationGene(int *piEtatInitial, int *iValMin, int *iValMax, int *iArc1, int *iArc2, int *iArc3)
{
    FILE *pGene;
    char sBuffer[200];
    int iIndiceGene = 0;
    int iIndiceBuffer = 0;

    pGene = fopen(FICHIER_GENE, "r");
    if (pGene == NULL)
    {
        printf("Impossible d'ouvrir le fichier \"%s\"\n", FICHIER_GENE);
    }
    else
    {
        //***********************************************************
        // On lit les 2 première lignes en commentaire sans ne faire aucun traitement.
        //***********************************************************
        while (/*ftell(pGene) != EOF &&*/ iIndiceGene < NBR_GENES_MAX)
        {
            iIndiceBuffer = 0;
            fgets(sBuffer, 200, pGene);
            if (sBuffer[0] != '#')
            {
                piEtatInitial[iIndiceGene] = fichierVersTableau(sBuffer, &iIndiceBuffer);

                iValMin[iIndiceGene] = fichierVersTableau(sBuffer, &iIndiceBuffer);

                iValMax[iIndiceGene] = fichierVersTableau(sBuffer, &iIndiceBuffer);

                iArc1[iIndiceGene] = fichierVersTableau(sBuffer, &iIndiceBuffer);

                iArc2[iIndiceGene] = fichierVersTableau(sBuffer, &iIndiceBuffer);

                iArc3[iIndiceGene] = fichierVersTableau(sBuffer, &iIndiceBuffer);

                iIndiceGene++;
            }
        }
    }

    //***********************************************************
    // Fermeture du fichier à la fin de la fonction
    //***********************************************************
    if (pGene)
    {
        fclose(pGene);
    }
}

int fichierVersTableau(char *sBuffer, int *iIndiceBuffer)
{
    char sValue[40] = "";
    int iTailleBuffer = sizeof(sBuffer);
    int iIndex = 0;
    int iRetour = 0;

    //***********************************************************
    // Initialiser le tableau de char avec que des 0 == '\0'
    //***********************************************************
    memset(sValue, 0, 40);

    for( ; iIndex < iTailleBuffer; iIndex++)
    {
        if (sBuffer[*iIndiceBuffer] == ',')
        {
            *iIndiceBuffer = *iIndiceBuffer + 1;
            break;
        }
        sValue[iIndex] = sBuffer[*iIndiceBuffer];
        *iIndiceBuffer = *iIndiceBuffer + 1;
    }

    //***********************************************************
    // Transforme la char en int
    //***********************************************************
    iRetour = atoi(sValue);
    return iRetour;
}
