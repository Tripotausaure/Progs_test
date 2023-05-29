#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NBLIG 6
#define NBCOL 7

typedef char tab[NBLIG][NBCOL];
typedef char Tableau[];

const char PION_A = 'x';
const char PION_B = 'o';
const char VIDE = ' ';
const char INCONNU = ' ';
const int COLONNE_DEBUT = NBCOL/2;
const Tableau SEPARE = "│";
const Tableau MILLEU = "├───┼───┼───┼───┼───┼───┼───┤";
const Tableau HAUT = "┌───┬───┬───┬───┬───┬───┬───┐";
const Tableau BAS = "└───┴───┴───┴───┴───┴───┴───┘";

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
    tab grilleDebut;
    char vainqueur = INCONNU;
    int ligne,colonne=COLONNE_DEBUT;
    initGrille(grilleDebut);
    afficher(grilleDebut,PION_A,COLONNE_DEBUT);
    while (vainqueur == INCONNU && !grillePleine(grilleDebut))
    {
        jouer(grilleDebut,PION_A,&colonne,&ligne);
        afficher(grilleDebut,PION_A,COLONNE_DEBUT);
        if (estVainqueur(grilleDebut, ligne, colonne))
        {
            vainqueur = PION_A;
        }
        else if ((!grillePleine(grilleDebut)))
        {
            jouer(grilleDebut,PION_B,&colonne,&ligne);
            afficher(grilleDebut,PION_B,COLONNE_DEBUT);
            if (estVainqueur(grilleDebut, ligne, colonne))
            {
                vainqueur = PION_B;
            }
        }
    }
    finDePartie(vainqueur);
    return 0;
}



void initGrille(tab grilleDebut)
{
    int i,j;
    for (i = 0; i < NBLIG; i++)
    {
        for (j = 0; j < NBCOL; j++)
        {
            grilleDebut[i][j] = VIDE;
        }
        
    }
    
}

void afficher(tab grilleDebut, char pion, int colonne)
{
    int i,j;
    system("clear");
    afficheCurs(pion, colonne);
    printf("%s\n",HAUT);
    for (i = 0; i < NBLIG; i++)
    {
        printf("|");
        for (j = 0; j < NBCOL; j++)
        {   
            if (grilleDebut[i][j] == PION_A){
                printf("\033[31;1m %c \033[m%s", grilleDebut[i][j], SEPARE);
            }
            else if (grilleDebut[i][j] == PION_B){
                printf("\033[33;1m %c \033[m%s", grilleDebut[i][j], SEPARE);
            }
            else{
                printf(" %c |", grilleDebut[i][j]);
            }
        }
        if (i!=5){
            printf("\n%s\n",MILLEU);
        }
    }
    printf("\n%s\n",BAS);
    printf("  1   2   3   4   5   6   7  \n");
    printf("\n Ceci est un jeu de Puissance 4\n");
    printf("Deplacez vous avec les touches Q et D\n");
    printf("Appuyez sur la touche [entree] pour deposer votre pion\n");
}

void afficheCurs(char pion, int colonne)
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

bool grillePleine(tab grilleDebut)
{
    int i,j;
    for (i = 0; i < NBLIG; i++)
    {
        for (j = 0; j < NBCOL; j++)
        {
            if (grilleDebut[i][j] == VIDE)
            {
                return false;
            }
            
        }
        
    }
    return true;
}

void jouer(tab grilleDebut,char pion,int *colonne, int *ligne)
{
    *colonne = choisirColonne(grilleDebut,pion,*colonne);
    while (colonnePleine(grilleDebut,*colonne))
    {
        *colonne = choisirColonne(grilleDebut,pion,*colonne);
    }
    *ligne = trouverLigne(grilleDebut,*colonne);
    grilleDebut[*ligne][*colonne] = pion;
}

int trouverLigne(tab grilleDebut, int colonne)
{
    int i;
    if (colonnePleine(grilleDebut,colonne)!=1){
        for (i = NBLIG-1; i >= 0; i--)
        {
            if (grilleDebut[i][colonne] == VIDE)
            {
                return i;
            }
            
        }
    }
    return 1;
}
int choisirColonne(tab grilleDebut,char pion,int colonne){
    char touche='E';
    while (touche!=' '){
        printf("choisirColonne\n");
        afficher(grilleDebut,pion,colonne);
        scanf("%c", &touche);
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

int colonnePleine(tab grilleDebut, int colonne)
{
    if (grilleDebut[0][colonne] != VIDE)
    {
        return 1;
    }
    return 0;
}
bool estVainqueur(tab grilleDebut, int ligne, int colomne)
{
    return gagneLigne(grilleDebut, ligne, colomne) || gagneColonne(grilleDebut, ligne, colomne) || gagneDiagonaleHB(grilleDebut, ligne, colomne) || gagneDiagonaleBH(grilleDebut, ligne, colomne);
}

int gagneLigne(tab grilleDebut, int ligne, int colomne)
{
    int i;
    int compteur = 0;
    for (i = 0; i < NBCOL; i++)
    {
        if (grilleDebut[ligne][i] == grilleDebut[ligne][colomne])
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

int gagneColonne(tab grilleDebut, int ligne, int colomne)
{
    int i;
    int compteur = 0;
    for (i = 0; i < NBLIG; i++)
    {
        if (grilleDebut[i][colomne] == grilleDebut[ligne][colomne])
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
int gagneDiagonaleHB(tab grilleDebut, int ligne, int colomne)
{
    char pion;
    int compteur = 0;
    int ligne2,colomne2;
    compteur=1;
    ligne2=ligne+1;
    colomne2=colomne+1;
    pion=grilleDebut[ligne][colomne];

    while (compteur<4 && grilleDebut[ligne2][colomne2]==pion && ligne2<NBLIG && colomne2<NBCOL){
        compteur++;
        ligne2++;
        colomne2++;
    }
    
    ligne2=ligne-1;
    colomne2=colomne-1;

    while (compteur<4 && grilleDebut[ligne2][colomne2]==pion && ligne2>=0 && colomne2>=0){
        compteur++;
        ligne2--;
        colomne2--;
    }
    if (compteur>=4){
        return 1;
    }
    return 0;
}

int gagneDiagonaleBH(tab grilleDebut, int ligne, int colomne)
{
    char pion;
    int compteur = 0;
    int ligne2,colomne2;
    compteur=1;
    ligne2=ligne-1;
    colomne2=colomne+1;
    pion=grilleDebut[ligne][colomne];

    while (compteur<4 && grilleDebut[ligne2][colomne2]==pion && ligne2>=0 && colomne2<NBCOL){
        compteur++;
        ligne2--;
        colomne2++;
    }
    
    ligne2=ligne+1;
    colomne2=colomne-1;

    while (compteur<4 && grilleDebut[ligne2][colomne2]==pion && ligne2<NBLIG && colomne2>=0){
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
{
    if (vainqueur == PION_A)
    {
        printf("Le joueur Rouge a Win\n");
    }
    else if (vainqueur == PION_B)
    {
        printf("Le joueur Jaune a Win\n");
    }
    else
    {
        printf("Match nul\n");
    }
}

// function that takes directly char input without enter

