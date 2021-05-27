#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED

struct point{
    int x;
    int y;
};

typedef struct point point;
typedef struct cellule cellule;
struct cellule {
    int in_T;
    point coord;
    cellule* gauche;
    cellule* droite;
    cellule* haut;
    cellule* bas;
};

typedef cellule** grid;

void fill_grid(grid grille,int lon , int lar);
void print(char ** W,int lon,int lar);
int inVois(grid grille, int x , int y);
void add_cell_modif(grid gri, int lon,int lar, char ** W);
void add_cell(grid gri, int lon,int lar, char ** W);
int test_complete (grid grille,int lon ,int lar);
void createGrid (grid grille,int lon,int lar, char ** W,int choix);
void createWall(char** W, int lon , int lar);

#endif // FONCTIONS_H_INCLUDED
