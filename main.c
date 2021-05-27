#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fonctions.h"

int main (){
    //determination de la methode
    int choix=0;
    while((choix!=2)&&(choix!=1)){
        printf("Tapez 1 pour utiliser add_cell et 2 pour add_cell_modif\n");
        scanf("%d",&choix);
    }

    srand(time(0));//Pour pouvoir utiliser rand()
    int lon,lar;//la longueur et la largeur de la grille
    clock_t t; //pour pouvoir determiner le temps d'execution
        //Controle de saisie
    printf("donner la longueur et la largeur de la grille\n");
    scanf("%d %d", &lon , &lar);
    while ((lon<1)||(lar<1)){
        printf("veuillez inserer des dimensions valides :\n");
        scanf("%d %d", &lon , &lar);
    }

    t = clock(); // debut de calcul de temps d execution
    char **Wall; // tableau 2D de caractéres pour afficher le labyrinthe
        //Allocation dynamique
    Wall = malloc( (2*lon+1) * sizeof(char*));
    for (int i = 0; i < (2*lon+1); i++)
    {
        Wall[i] = malloc( (2*lar+1) * sizeof(char));
    }

    createWall(Wall,lon,lar); // initialisation de la chaine d affichage
    cellule **grille; // creation de la grille
         //Allocation dynamique
    grille = malloc( lon * sizeof(cellule*));
    for ( int i = 0; i < (lon); i++)
    grille[i] = malloc( lar * sizeof(cellule));

    fill_grid(grille,lon,lar); //Determination des caractéristiques des cellules
    createGrid(grille,lon,lar,Wall,choix); //Implemenation de l'arbre T
    t = clock() - t; //arret du compteur
    print(Wall,lon,lar); // affichage du labyrinthe
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // calculer le temps d execution
    printf("Le programme a mis %f seconds en execution", time_taken); //affichage du temps d execution
        //liberation de Wall
    for (int i = 0; i < (2*lon+1); i++)
    free(Wall[i]);
    free(Wall);
        //liberation de grille
    for ( int i = 0; i < (lon); i++)
    free (grille[i]);
    free(grille);
    return 0;


}
