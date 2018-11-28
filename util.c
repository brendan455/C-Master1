//***********************************************************
//  DENIAUD Brendan E109500X Master de bioinformatique

//  Voir le fichier README pour les consignes et des informations
//  sur la compilation et l'exécution du programme.

//  Ce fichier contient les fonctions utilitaires répondant au sujet.

//  Voir le fichier main.c pour des exemples d'utilisation.
//***********************************************************

#include <stdio.h>    // Pour printf, scanf
#include <string.h>   // Pour strcmp

#include "constantes.h"
#include "util.h"

//***********************************************************
// Retourne l'index d'un gène donné (Question 3)
//***********************************************************
int index_gene(char* recherche, int nbr_genes, char* genes[NBR_GENES_MAX]) {
  int i;    // Compteur
  for (i = 0; i < nbr_genes; i++) {
    if (strcmp(recherche, genes[i]) == 0) {
      return i;
    }
  }
  return -1;    // Si non trouvé
}

//***********************************************************
// Affiche un état à l'écran (Question 4)
//***********************************************************
void afficher_etat(int etat[NBR_GENES_MAX], int nbr_genes, char* genes[NBR_GENES_MAX]) {
  int i;    // Compteur
  printf("<");
  for (i = 0; i < nbr_genes; i++) {
    printf("%s=%d", genes[i], etat[i]);
    if (i < nbr_genes - 1) {
      printf(", ");
    }
  }
  printf(">\n");
  return;
}

//***********************************************************
// Calcul le nombre total d'états du système (Question 5)
//***********************************************************
int calcul_taille_totale(int nbr_genes, int plafonds[NBR_GENES_MAX]) {
  int g;
  int taillegt = 1;
  for (g = 0; g < nbr_genes; g++) {
    taillegt *= plafonds[g] + 1;
  }
  return taillegt;
}

//***********************************************************
// Recopie un état etat1 dans etat2 (Question 7)
//***********************************************************
void recopie_etat(int etat1[NBR_GENES_MAX], int etat2[NBR_GENES_MAX], int nbr_genes) {
  int i;    // Compteur
  for (i = 0; i < nbr_genes; i++) {
    etat2[i] = etat1[i];
  }
  return;
}
