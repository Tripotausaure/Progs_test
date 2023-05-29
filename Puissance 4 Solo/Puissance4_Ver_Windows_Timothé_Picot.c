#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#define NBLIG 6
#define NBCOL 7

typedef char tab[NBLIG][NBCOL];
typedef char Tableau[];

const char PION_A = 'x';
const char PION_B = 'o';
const char VIDE = ' ';
const char INCONNU = ' ';
const int COLONNE_DEBUT = NBCOL/2;

void initGrille(tab);
void afficher(tab,char,int);
void jouer(tab,char,int*,int*);
void finDePartie(char);
void afficheCurs(char, int);
int choisirColonne(tab,char,int);
int trouverLigne(tab,int);
int colonnePleine(tab, int);
int gagneLigne(tab, int, int);
int gagneColonne(tab, int, int);
int gagneDiagonaleHB(tab, int, int);
int gagneDiagonaleBH(tab, int, int);
int recupPosition(int,int);
bool grillePleine(tab);
bool estVainqueur(tab, int, int);



int main()
{
    char vainqueur;
    int ligne,colonne=COLONNE_DEBUT;
    tab g;

    initGrille(g);
    vainqueur = INCONNU;
    afficher(g,PION_A,COLONNE_DEBUT);

    while (vainqueur == INCONNU && !grillePleine(g))
    {
        jouer(g,PION_A,&colonne,&ligne);
        afficher(g,PION_A,COLONNE_DEBUT);
        if (estVainqueur(g, ligne, colonne))
        {
            vainqueur = PION_A;
        }
        else if ((!grillePleine(g)))
        {
            jouer(g,PION_B,&colonne,&ligne);
            afficher(g,PION_B,COLONNE_DEBUT);
            if (estVainqueur(g, ligne, colonne))
            {
                vainqueur = PION_B;
            }
        }
    }
    finDePartie(vainqueur);
    return 0;
}



void initGrille(tab g)
//Cette procédure remplit entièrement le tableau de cases "VIDE"
{
    int i,j;
    for (i = 0; i < NBLIG; i++)
    {
        for (j = 0; j < NBCOL; j++)
        {
            g[i][j] = VIDE;
        }
        
    }
    
}

void afficher(tab g, char pion, int colonne)
//Cette procédure appelle la fonction afficheCurs et affiche ensuite l'intégralité du tableau ainsi que les consignes de base pour jouer
{
    int i,j;
    system("cls");
    afficheCurs(pion, colonne);
    printf("-----------------------------\n");
    for (i = 0; i < NBLIG; i++)
    {
        printf("|");
        for (j = 0; j < NBCOL; j++)
        {   
            if (g[i][j] == PION_A){
                printf("\033[31;1m %c \033[m|", g[i][j]);
            }
            else if (g[i][j] == PION_B){
                printf("\033[33;1m %c \033[m|", g[i][j]);
            }
            else{
                printf(" %c |", g[i][j]);
            }
        }
        if (i!=5){
            printf("\n-----------------------------\n");
        }
    }
    printf("\n_____________________________\n");
    printf("  1   2   3   4   5   6   7  \n");
    printf("\n Ceci est un jeu de Puissance 4\n");
    printf("Deplacez vous avec les touches Q et D\n");
    printf("Appuyez sur la touche [entree] pour deposer votre pion\n");
}

void afficheCurs(char pion, int colonne)
//Cette procédure affiche le curseur du joueur au dessus de la grille
{
    int i;
    for (i = 0; i < 7; i++)
    {
        if (i == colonne)
        {
            if (pion == PION_A)
            {
                printf(" \033[31;1m %c \033[m\n", pion);
            }
            else
            {
                printf(" \033[33;1m %c \033[m\n", pion);
            }
            
        }
        else
        {
            printf("    ");
        }
    }
    printf("\n");
}

bool grillePleine(tab g)
//Cette procédure verifie si la grille est pleine
{
    int i,j;
    for (i = 0; i < NBLIG; i++)
    {
        for (j = 0; j < NBCOL; j++)
        {
            if (g[i][j] == VIDE)
            {
                return false;
            }
            
        }
        
    }
    return true;
}

void jouer(tab g,char pion,int *colonne, int *ligne)
//Cette procédure appelle la fonction choisirColonne et la fonction trouverLigne afin de savoir ou le joueur placera-t'il son pion dans le tableau
{
    *colonne = choisirColonne(g,pion,*colonne);
    while (colonnePleine(g,*colonne))
    {
        *colonne = choisirColonne(g,pion,*colonne);
    }
    *ligne = trouverLigne(g,*colonne);
    g[*ligne][*colonne] = pion;
}

int trouverLigne(tab g, int colonne)
//Cette fonction parcours une colonne donnée en partant du bas et renvoie l'id de la ligne vide la plus basse (pour simuler entre autre la gravité)
{
    int i;
    if (colonnePleine(g,colonne)!=1){
        for (i = NBLIG-1; i >= 0; i--)
        {
            if (g[i][colonne] == VIDE)
            {
                return i;
            }
            
        }
    }
    return 1;
}
int choisirColonne(tab g,char pion,int colonne){
/*Cette fonction permet de choisir la colonne dans laquelle le joueur veut placer son pion 
en utilisant les touches Q et D pour se déplacer et la touche [entree] pour choisir la colonne shouaitée*/
    char touche='E';
    while (touche!=' '){
        printf("choisirColonne\n");
        afficher(g,pion,colonne);
        touche = getch();
        if (touche!=' '){
            if (touche=='q'){
                colonne--;
            }
            else if (touche=='d'){
                colonne++;
            }
            if (colonne<0){
                colonne=0;
            }
            else if (colonne>6){
                colonne=6;
            }
        }
    } 
    return colonne;
    
}

int colonnePleine(tab g, int colonne)
//Cette fonction permet de vérifier si une colomne est pleine pour éviter d'écraser le dernier pion d'une colonne encore et encore
{
    if (g[0][colonne] != VIDE)
    {
        return 1;
    }
    return 0;
}
bool estVainqueur(tab g, int ligne, int colomne)
//Cette fonction appelle les Quatres fonctions nessesaires pour vérifier si le joueur a gagné
{
    return gagneLigne(g, ligne, colomne) || gagneColonne(g, ligne, colomne) || gagneDiagonaleHB(g, ligne, colomne) || gagneDiagonaleBH(g, ligne, colomne);
}

int gagneLigne(tab g, int ligne, int colomne)
//Cette fonction cherche 4 pions allignées à la verticale
{
    int i;
    int compteur = 0;
    for (i = 0; i < NBCOL; i++)
    {
        if (g[ligne][i] == g[ligne][colomne])
        {
            compteur++;
        }
        else
        {
            compteur = 0;
        }
        if (compteur == 4)
        {
            return 1;
        }
    }
    return 0;
}

int gagneColonne(tab g, int ligne, int colomne)
//Cette fonction cherche 4 pions allignées à l'horisontale
{
    int i;
    int compteur = 0;
    for (i = 0; i < NBLIG; i++)
    {
        if (g[i][colomne] == g[ligne][colomne])
        {
            compteur++;
        }
        else
        {
            compteur = 0;
        }
        if (compteur == 4)
        {
            return 1;
        }
    }
    return 0;
}

int gagneDiagonaleHB(tab g, int ligne, int colomne)
//Cette fonction cherche 4 pions allignées en diagonale de "en haut à gauche" à "en bas à droite" (le sens d'un \)
{
    char pion;
    int compteur = 0;
    int ligne2,colomne2;
    compteur=1;
    ligne2=ligne+1;
    colomne2=colomne+1;
    pion=g[ligne][colomne];

    while (compteur<4 && g[ligne2][colomne2]==pion && ligne2<NBLIG && colomne2<NBCOL){
        compteur++;
        ligne2++;
        colomne2++;
    }
    
    ligne2=ligne-1;
    colomne2=colomne-1;

    while (compteur<4 && g[ligne2][colomne2]==pion && ligne2>=0 && colomne2>=0){
        compteur++;
        ligne2--;
        colomne2--;
    }
    if (compteur>=4){
        return 1;
    }
    return 0;
}

int gagneDiagonaleBH(tab g, int ligne, int colomne)
//Cette fonction cherche 4 pions allignées en diagonale de "en bas à gauche" à "en haut à droite" (le sens d'un /)
{
    char pion;
    int compteur = 0;
    int ligne2,colomne2;
    compteur=1;
    ligne2=ligne-1;
    colomne2=colomne+1;
    pion=g[ligne][colomne];

    while (compteur<4 && g[ligne2][colomne2]==pion && ligne2>=0 && colomne2<NBCOL){
        compteur++;
        ligne2--;
        colomne2++;
    }
    
    ligne2=ligne+1;
    colomne2=colomne-1;

    while (compteur<4 && g[ligne2][colomne2]==pion && ligne2<NBLIG && colomne2>=0){
        compteur++;
        ligne2++;
        colomne2--;
    }
    if (compteur>=4){
        return 1;
    }
    return 0;
}

void finDePartie(char vainqueur)
//Cette fonction permet d'afficher le vainqueur de la partie
{
    if (vainqueur == PION_A)
    {
        printf("Le joueur Rouge a Win");
    }
    else if (vainqueur == PION_B)
    {
        printf("Le joueur Jaune a Win");
    }
    else
    {
        printf("Match nul");
    }
}
