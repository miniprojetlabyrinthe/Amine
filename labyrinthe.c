#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fonctions.h"

void print(char ** W,int lon,int lar){
    int i,j;//compteurs
    for (i=0;i<2*lon+1;i++){
        for (j=0;j<2*lar+1;j++){
            printf("%c",W[i][j]);//affichage des caractéres dans un meme ligne
        }
        printf("\n"); // passage a la ligne suivante
    }
}
int inVois(grid grille, int x , int y){
    //on verifie le cas NULL pour ne pas depasser les limites de la grille
    if (grille[x][y].bas!=NULL){
            if ((grille[x][y].bas->in_T)==1){return 1;}//un seul voisin suffit pour quitter
    }
    if (grille[x][y].droite!=NULL){
            if ((grille[x][y].droite->in_T)==1){return 1;}
    }
    if (grille[x][y].haut!=NULL){
            if ((grille[x][y].haut->in_T)==1){ return 1;}
    }
    if (grille[x][y].gauche!=NULL){
            if ((grille[x][y].gauche->in_T)==1){ return 1;}
    }
    return 0;//aucun voisin n'est trouvé

}
void add_cell_modif(grid gri, int lon,int lar, char ** W){
    int x,y;//coordonnées du cellule à ajouter
    int z;// nombre aléatoire
    char Tab[4];//case pour contenir les symboles des voisins
    x=rand()%lon;//choix au hasard de l'abscisse
    y=rand()%lar;// choix au hasard de l'ordonnée
    int t = inVois(gri,x,y);//etat des voisins de la cellule
    int hm =gri[x][y].in_T;//etat de la cellule
    //on teste si la cellule verifie les critéres de ne pas etre dans T et d'avoir des voisins dans T
    while ((t==0)||(hm==1)){

        x=rand()%lon;
        y=rand()%lar;
        hm=gri[x][y].in_T;
        t=inVois(gri,x,y);
    }

    gri[x][y].in_T = 1;//on integre la cellule dans T
    int k=0;//entier pour determiner le nombre de voisins dans T
    //Calcul de nombre de voisins et arrangement de leurs symboles
    //on choisit arbitrairement un sens de remplissage qui n'a pas d effet sur l'aspect aléatoire du problème
    if (gri[x][y].bas!=NULL){
        if (((*(gri[x][y].bas)).in_T)==1){
            Tab[k]='B';
            k++;
        }
    }
    if (gri[x][y].haut!=NULL){
        if (((*(gri[x][y].haut)).in_T)==1){
            Tab[k]='H';
            k++;
        }
    }
    if (gri[x][y].droite!=NULL){
        if (((*(gri[x][y].droite)).in_T)==1){
            Tab[k]='D';
            k++;
        }
    }
    if (gri[x][y].gauche!=NULL){
        if (((*(gri[x][y].gauche)).in_T)==1){
            Tab[k]='G';
            k++;
        }
    }
    z=rand()%k; //choix aléatoire d'un des voisins dans T
    switch (Tab[z]){
            case 'B':
                W[2*(x+1)][2*y+1]=' ';//destruction du mur
                break;
            case 'D':
                W[2*x+1][2*y+2]=' ';//destruction du mur
                break;
            case 'H':
                W[2*x][2*y+1]=' ';//destruction du mur
                break;
            case 'G':
                W[2*x+1][2*y]=' ';//destruction du mur
                break;



    }

}
void add_cell(grid gri, int lon,int lar, char ** W){
    int x,y;//coordonnées du cellule à ajouter
    int z;//nombre alétoire
    int test;//pour tester qu'on a trouvé le voisin dans T
    x=rand()%lon;//choix au hasard de l'abscisse
    y=rand()%lar;// choix au hasard de l'ordonné;
    int t = inVois(gri,x,y);//etat des voisins de la cellule
    int hm =gri[x][y].in_T;//etat de la cellule
    while ((t==0)||(hm==1)){

        x=rand()%lon;
        y=rand()%lar;
        hm=gri[x][y].in_T;
        t=inVois(gri,x,y);
    }
    gri[x][y].in_T = 1;//on integre la cellule dans T
    test=0;// a priori on n'a pas trouvé la cellule voisine
    while (test==0){
        z=rand()%4;
        switch (z){
            case 0:
                if (gri[x][y].bas!=NULL){
                        if (((*(gri[x][y].bas)).in_T)==1){
                                test=1;
                                W[2*(x+1)][2*y+1]=' ';//destruction du mur
                                break;
                        }
                }

            case 1:
                if (gri[x][y].droite!=NULL){
                        if (((*(gri[x][y].droite)).in_T)==1){
                                test=1;
                                W[2*x+1][2*y+2]=' ';//destruction du mur
                                break;
                        }
                }
            case 2:
                if (gri[x][y].haut!=NULL){
                        if (((*(gri[x][y].haut)).in_T)==1){
                                test=1;
                                W[2*x][2*y+1]=' ';//destruction du mur
                                break;
                        }
                }
            case 3:
                if (gri[x][y].gauche!=NULL){
                        if (((*(gri[x][y].gauche)).in_T)==1){
                                test=1;
                                W[2*x+1][2*y]=' ';//destruction du mur
                                break;
                        }
                }
        }
    }
}
int test_complete (grid grille,int lon ,int lar){
    int i,j;//utilisation de compteurs
    for (i=0;i<lon;i++){
        for (j=0;j<lar;j++){
            if (grille[i][j].in_T==0){
                    return 0;//si on trouve une case manquante on quitte imediatement
            }
        }
    }
    return 1;
}
void createGrid (grid grille,int lon,int lar, char ** W,int choix){
    //tester si toutes les cellules sont dans T
    while(test_complete(grille,lon,lar)==0){
            //ajouter des cellules selon deux methodes
        if (choix==1){
            add_cell(grille,lon,lar,W);// si on choisit la methode 1
        }
        else {
            add_cell_modif(grille,lon,lar,W);// si on choisit la methode 2
        }
    }
}
void createWall(char** W, int lon , int lar){
    int i,j;
    for (i=0;i<(2*lon+1);i++){
        for (j=0;j<(2*lar+1);j++){
            if((i%2)==0){
                if ((j%2)==1){
                    W[i][j]='-';//pour les murs horizentaux
                }
                else {
                    W[i][j]='+';//pour les coins
                }
            }
            else {
                if ((j%2)==0){
                    W[i][j]='|';//pour les murs verticaux
                }
                else{
                    W[i][j]=' ';//le reste est vide
                }
            }
        }
    }
    W[1][0]='D';//designation du début
    W[2*lon-1][2*lar]='F';// designation de la fin
}
void fill_grid(grid grille,int lon , int lar){
    int i,j; //compteurs pour parcourir la grille
    for (i=0;i<lon;i++){
        for (j=0;j<lar;j++){
                //association des coordonnées et des relations par rapport à T
            grille[i][j].coord.x=i;
            grille[i][j].coord.y=j;
            grille[i][j].in_T=0;

            if (i==0){
                grille[i][j].haut=NULL; //absence de cellule en haut
                if (lon ==1){ //pour les cas extremes
                    grille[i][j].bas=NULL;
                }
                else{
                    grille[i][j].bas=&(grille[i+1][j]);
                }

            }
            else if (i==(lon-1)){
                grille[i][j].bas=NULL; //abscence de cellules en bas
                grille[i][j].haut=&(grille[i-1][j]);
            }
            else {
                grille[i][j].haut=&(grille[i-1][j]);
                grille[i][j].bas=&grille[i+1][j];
            }
            if (j==0){
                grille[i][j].gauche=NULL;//abscence de cellules a gauche
                if (lar==1){ // pour les cas extremes
                        grille[i][j].droite=NULL; // abscence de cellules a droite
                }
                else {
                        grille[i][j].droite=&grille[i][j+1];
                }

            }
            else if (j==(lar-1)){
                grille[i][j].droite=NULL;// abscence de cellules a droite
                grille[i][j].gauche=&grille[i][j-1];
            }
            else {
                grille[i][j].gauche=&grille[i][j-1];
                grille[i][j].droite=&grille[i][j+1];
            }
        }
    }
    grille[0][0].in_T = 1;//debut de T commence avec la case du coin droit supérieur

}
