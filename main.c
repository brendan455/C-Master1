//***********************************************************
// DENIAUD Brendan E109500X Master de bioinformatique

// Ce fichier contient les déclarations des données du modèle
//  d'interactions génétiques de la Figure 1,
//  ainsi que plusieurs tests montrant l'utilisation de ces données
//  et des fonctions développées.

//  Voir le fichier README pour les consignes et des informations
//  sur la compilation et l'exécution du programme.
//***********************************************************

#include <stdio.h>    // Pour printf, scanf
#include <string.h>   // Pour strcmp

#include "constantes.h"
#include "util.h"
#include "dynamique.h"
#include "fichier.h"
#include "listgene.h"

int menuSementic();
int menuExport();

//***********************************************************
// Fonction principale : déclaration des données du modèle et tests
//***********************************************************
int main()
{
//***********************************************************
//  Déclaration des variables
//***********************************************************
    int iValMin[NBR_GENES_MAX];
    int iValMax[NBR_GENES_MAX];
    int iArc1[NBR_GENES_MAX];
    int iArc2[NBR_GENES_MAX];
    int iArc3[NBR_GENES_MAX];

    etat_gene *pListEtatGene = NULL;
    etat_gene *pNouveau;

    int piEtatInitial[NBR_GENES_MAX];   // Tableau des etats initiaux des genes
    int plafonds[NBR_GENES_MAX];    // Tableau des niveaux maximums des gènes
    int arcs[NBR_GENES_MAX][NBR_GENES_MAX];   // Matrice des arcs et labels

    char* genes[NBR_GENES_MAX];   // Tableau des noms des gènes
    int nbr_genes = NBR_GENES_MAX;
    int testgenea;
    int testgeneb;
    int testgenec;

    int iChoix;

    //***********************************************************
    // Variable pour sementique synchrone ou asynchrone
    //***********************************************************
    int iIndex;
    int nbr_etapes;
    int etat_courant[NBR_GENES_MAX];
    int etat_suivant[NBR_GENES_MAX];

    //***********************************************************
    // Variable pour sementique asynchrone
    //***********************************************************
    int gene_prioritaire = 0;

    //***********************************************************
    // Lecture du fichier d'entree
    // Appel de la fonction du fichier.c
    //***********************************************************
    caracterisationGene(&piEtatInitial, &iValMin, &iValMax, &iArc1, &iArc2, &iArc3);

    pNouveau = (etat_gene*)malloc(sizeof(struct etat_gene));
    pNouveau->pSuivant = pListEtatGene;
    pListEtatGene = pNouveau;
    for (iIndex = 0; iIndex < NBR_GENES_MAX; iIndex++)
    {
        pNouveau->etat_courant[iIndex] = piEtatInitial[iIndex];
    }

    //***********************************************************
    // Incrémentation des valeurs du fichier dans les tableaux correspondants
    //***********************************************************
    plafonds[0] = iValMax[0];
    plafonds[1] = iValMax[1];
    plafonds[2] = iValMax[2];

    arcs[0][0] = iArc1[0];
    arcs[0][1] = iArc2[0];
    arcs[0][2] = iArc3[0];
    arcs[1][0] = iArc1[1];
    arcs[1][1] = iArc2[1];
    arcs[1][2] = iArc3[1];
    arcs[2][0] = iArc1[2];
    arcs[2][1] = iArc2[2];
    arcs[2][2] = iArc3[2];

    genes[0] = "a"; genes[1] = "b";  genes[2] = "c";
    testgenea = index_gene("a", nbr_genes, genes);
    testgeneb = index_gene("b", nbr_genes, genes);
    testgenec = index_gene("c", nbr_genes, genes);

    //***********************************************************
    // Menu d'introduction du programme et rappel des variables de base
    //***********************************************************
    printf("\t\t\tBienvenue ^_^\n\n");

    printf("\n--------------------------------------------------------\n");
    printf("|  Index de %s : %d                                      |\n", genes[testgenea], testgenea);
    printf("|  Index de %s : %d                                      |\n", genes[testgeneb], testgeneb);
    printf("|  Index de %s : %d                                      |\n", genes[testgenec], testgenec);
    printf("|  Plafond de %s : %d                                    |\n", genes[testgenea], plafonds[testgenea]);
    printf("|  Nombre total d'etats : %d                           |\n", calcul_taille_totale(nbr_genes, plafonds));
    printf("|  Arc %s -> %s : %d                                      |\n", genes[testgeneb], genes[testgenea], arcs[testgeneb][testgenea]);
    printf("|  Evolution de %s depuis l'etat initial : %d -> %d       |\n", genes[testgenea], piEtatInitial[testgenea], evolution_variable(piEtatInitial, testgenea, nbr_genes, plafonds, arcs, gene_prioritaire));
    printf("--------------------------------------------------------\n\n");

    printf("Voici l'etat initial des genes : ");
    afficher_etat(piEtatInitial, nbr_genes, genes);

    //***********************************************************
    // Appel de la fonction du menu de choix des sémantiques
    //***********************************************************
    do
        {
            iChoix = menuSementic();
        }
    while (iChoix != 1 && iChoix != 2);

    //***********************************************************
    // Le programme envoi le cas choisi par l'utilisateur
    //***********************************************************
    switch(iChoix)
    {
        case 1:

           printf("\nEtat initial : ");
           afficher_etat(piEtatInitial, nbr_genes, genes);
           printf("\n*************** Semantique synchrone *******************\nCalculer combien d'etapes ? > ");
           scanf("%d", &nbr_etapes);
           recopie_etat(piEtatInitial, etat_courant, nbr_genes);
           for (iIndex = 0; iIndex < nbr_etapes; iIndex++)
           {
                evolution_etat_synchrone(etat_courant, etat_suivant, nbr_genes, plafonds, arcs);
                printf("Etape %d : ", iIndex + 1);
                afficher_etat(etat_suivant, nbr_genes, genes);
                recopie_etat(etat_suivant, etat_courant, nbr_genes);

                //***********************************************************
                // Ajouter l'element dans la isrte chainee
                //***********************************************************
                ajoutElemListe(pListEtatGene, etat_suivant);
            }

            break;
        case 2:

            printf("\nEtat initial : ");
            afficher_etat(piEtatInitial, nbr_genes, genes);
            printf("\n*************** Semantique asynchrone ******************\nQuel est le gene prioritaite ? > \nAide : Gene1 = 1 / Gene 2 = 2 / Gene 3 = 3\nVotre choix :\n");
            scanf("%d", &gene_prioritaire);
            while (gene_prioritaire <= 0 || gene_prioritaire > NBR_GENES_MAX)
            {
                printf("\n\t\t\a!!! Ce gene n'existe pas !!! \nEntrer un nouveau gene prioritaire : ");
                scanf("%d", &gene_prioritaire);
            }
            printf("\nCalculer combien d'etapes ? > ");
            scanf("%d", &nbr_etapes);

            recopie_etat(piEtatInitial, etat_courant, nbr_genes);
            recopie_etat(piEtatInitial, etat_suivant, nbr_genes);
            for (iIndex = 0; iIndex < nbr_etapes; iIndex++)
            {
                evolution_etat_asynchrone(etat_courant, etat_suivant, nbr_genes, plafonds, arcs, gene_prioritaire);
                afficher_etat(etat_suivant, nbr_genes, genes);
                recopie_etat(etat_suivant, etat_courant, nbr_genes);

                //***********************************************************
                // Ajouter l'element dans la liste chainee
                //***********************************************************
                ajoutElemListe(pListEtatGene, etat_suivant);
            }
            break;

        default:
            break;
    }

    //***********************************************************
    // Appel de la fonction de menu de choix de présentation des résultats
    //***********************************************************
    do
    {
        iChoix = (int)menuExport();
    }
    while (iChoix != 0 && iChoix != 1);
    switch(iChoix)
    {
        case 1:

            //***********************************************************
            // exporter dans un fichier
            //***********************************************************
            printf("Gene1 Gene2 Gene3\n");
            afficherListe(pListEtatGene);
            break;

        default:
            break;
    }

    libererListe(pListEtatGene);
}

//***********************************************************
// Fonction de menu de choix des sémantiques
//***********************************************************
int menuSementic()
{
    int iChoix;
    printf("\nQuel semantique desirez vous tester ? : 1 -> synchrone    2 -> asynchrone\n");
    scanf("%d", &iChoix);

    return iChoix;
}

//***********************************************************
// Fonction de menu de choix d'affichage des résultats ou de sortie du programme
//***********************************************************
int menuExport()
{
    int iChoix;
    printf("\nTaper 0 pour quitter le programme\nTaper 1 pour exporter les resultats\nVotre choix : ");
    scanf("%d", &iChoix);

    return iChoix;
}
