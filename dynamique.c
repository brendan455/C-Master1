//***********************************************************
//  DENIAUD Brendan E109500X Master de bioinformatique

//  Voir le fichier README pour les consignes et des informations
//  sur la compilation et l'exécution du programme.

//  Ce fichier contient les fonctions relatives au calcul de la dynamique
//  pour les sémantiques.

//  Voir le fichier main.c pour des exemples d'utilisation.
//***********************************************************

#include <stdio.h>    // Pour printf, scanf
#include <stdlib.h>   // Pour abs

#include "constantes.h"
#include "util.h"
#include "dynamique.h"

//***********************************************************
// Retourne 1 si, en fonction des arguments, le gène et ressource, et 0 sinon
//***********************************************************
int est_ressource(int arc_courant, int niveau_courant) {
  int res;
  if ((arc_courant > 0 && niveau_courant >= arc_courant) ||
      (arc_courant < 0 && niveau_courant < abs(arc_courant))) {
    res = 1;
  } else {
    res = 0;
  }
  return res;
}

//***********************************************************
// Retourne l'évolution d'une variable dans un état donné pour les règles simplifiées
// (Question 6)
//***********************************************************
int evolution_variable(int etat[NBR_GENES_MAX], int index, int nbr_genes, int plafonds[NBR_GENES_MAX], int arcs[NBR_GENES_MAX][NBR_GENES_MAX], int gene_prioritaire) {
  int augmentation_valeur = 0;
  int diminution_valeur = 0;
  int resultat = etat[index];
  int i;    // Compteur

  //***********************************************************
  // Parcourir tous les arcs
  //***********************************************************
  for (i = 0; i < nbr_genes; i++) {
    // S'il existe un arc... (c.-à-d. si la valeur n'est pas 0)
    if (abs(arcs[i][index]) != 0) {
      // On peut augmenter ou diminuer selon le signe de l'arc et l'état de i
      if (est_ressource(arcs[i][index], etat[i])) {
        augmentation_valeur = 1;
      } else {
        diminution_valeur = 1;
      }
    }
  }

  //***********************************************************
  // On applique l'augmentation ou la diminution
  //***********************************************************
  if (augmentation_valeur == 1) {
    resultat++;
  }
  if (diminution_valeur == 1) {
    resultat--;
  }

  //***********************************************************
  // On vérifie qu'on ne dépasse pas les bornes
  //***********************************************************
  if (resultat < 0) {
    resultat = 0;
  }
  if (resultat > plafonds[index]) {
    resultat = plafonds[index];
  }
  return resultat;
}

//***********************************************************
// Crée le successeur d'un état pour la sémantique synchrone (Question 7)
//***********************************************************
void evolution_etat_synchrone(int etat[NBR_GENES_MAX], int newetat[NBR_GENES_MAX], int nbr_genes, int plafonds[NBR_GENES_MAX], int arcs[NBR_GENES_MAX][NBR_GENES_MAX]) {
  int i;    // Compteur

  //***********************************************************
  // On met à jour chaque gène
  //***********************************************************
  for (i = 0; i < nbr_genes; i++) {
    newetat[i] = evolution_variable(etat, i, nbr_genes, plafonds, arcs, 0);
  }
  return;
}

//***********************************************************
// Crée le successeur d'un état pour la sémantique synchrone (Question 7)
//***********************************************************
void evolution_etat_asynchrone(int etat[NBR_GENES_MAX], int newetat[NBR_GENES_MAX], int nbr_genes, int plafonds[NBR_GENES_MAX], int arcs[NBR_GENES_MAX][NBR_GENES_MAX], int gene_prioritaire) {
  int i;    // Compteur

  //***********************************************************
  // On met à jour chaque gène
  //***********************************************************
  for (i = 0; i < nbr_genes; i++) {
    if (gene_prioritaire - 1 != i)  // -1 car le table commence a 0
    {
      newetat[i] = evolution_variable(etat, i, nbr_genes, plafonds, arcs, gene_prioritaire);
    }
  }
  return;
}
