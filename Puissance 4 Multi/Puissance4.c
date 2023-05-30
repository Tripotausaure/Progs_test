#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// les constantes
#define LIGNE 6
#define COLONNE 7
#define JOUEUR 'X'
#define ADVERSAIRE 'O'
#define VIDE ' '
#define INCONNU ' '

// les types
typedef int Grille[LIGNE][COLONNE];

// prototypes des fonctions
void initGrille(Grille laGrille);
void afficher(Grille laGrille, char pion);
bool grillePleine(Grille laGrille);
void jouer(Grille laGrille, char pion, int *ligne, int *colonne);
int choisirColonne(Grille laGrille, char pion);
int chercherLigne(Grille laGrille, int col);
bool estVainqueur(Grille laGrille, int lig, int col);
void finDePartie(char vainqueur);
bool bloquerGagnant(Grille laGrille, char pion, int *ligne, int *colonne);
int maStrategie(Grille laGrille);
bool aligne2(Grille laGrille, int *ligne, int *colonne);
void cloneGrille(Grille laGrille, Grille clone);
void comparerGrille(Grille laGrille, Grille laGrille2, int *lig, int *col);
void rangerGrille3(Grille laGrille3, int lig, int col);
void chercherGrille3(Grille laGrille3);

// Programme principal. C'est le pion A qui commence Ã  jouer
int main()
{
    Grille laGrille;
    char vainqueur = INCONNU;
    int ligne, colonne;
    initGrille(laGrille);
    afficher(laGrille, JOUEUR);
    while (vainqueur == INCONNU && !grillePleine(laGrille))
    {
        jouer(laGrille, JOUEUR, &ligne, &colonne);
        afficher(laGrille, ADVERSAIRE);
        if (estVainqueur(laGrille, ligne, colonne))
        {
            vainqueur = JOUEUR;
        }
        else if (!grillePleine(laGrille))
        {
            jouer(laGrille, ADVERSAIRE, &ligne, &colonne);
            afficher(laGrille, JOUEUR);
            if (estVainqueur(laGrille, ligne, colonne))
            {
                vainqueur = ADVERSAIRE;
            }
        }
    }
    finDePartie(vainqueur);
    system(EXIT_SUCCESS);
}

void initGrille(Grille laGrille)
{
    int l, c;
    for (l = 0; l < LIGNE; l++)
    {
        for (c = 0; c < COLONNE; c++)
        {
            laGrille[l][c] = VIDE;
        }
    }
}

void afficher(Grille laGrille, char pion)
{
    int l, c;
    system("cls");
    printf("\t");
    printf("  %c\n", pion);
    printf("\t");
    for (c = 0; c < COLONNE; c++)
    {
        printf("----");
    }
    printf("-\n");
    for (l = 0; l < LIGNE; l++)
    {
        printf("\t");
        for (c = 0; c < COLONNE; c++)
        {
            printf("| %c ", laGrille[l][c]);
        }
        printf("|\n");
        printf("\t");
        for (c = 0; c < COLONNE; c++)
        {
            printf("----");
        }
        printf("-\n");
    }
    printf("\t");
    for (c = 0; c < COLONNE; c++)
    {
        printf("  %d ", c);
    }
    printf("\n\n");
}

bool grillePleine(Grille laGrille)
{
    bool pleine = true;
    int c = 0;
    while (pleine && c < COLONNE)
    {
        if (laGrille[0][c] == VIDE)
        {
            pleine = false;
        }
        c++;
    }
    return pleine;
}

void jouer(Grille laGrille, char pion, int *ligne, int *colonne)
{
    if (pion == ADVERSAIRE)
    {
        int c;
        c = maStrategie(laGrille);
        *colonne = c;
    }
    else
    {
        *colonne = choisirColonne(laGrille, pion);
    }
    *ligne = chercherLigne(laGrille, *colonne);
    if (*ligne >= 0)
    {
        laGrille[*ligne][*colonne] = pion;
    }
}

void finDePartie(char vainqueur)
{
    if (vainqueur != INCONNU)
    {
        printf("Joueur %c vainqueur\n", vainqueur);
    }
    else
    {
        printf("MATCH NUL");
    }
}

int choisirColonne(Grille laGrille, char pion)
{
    int col;

    do
    {
        printf("Numero de colonne ? ");
        scanf("%d", &col);
    } while (col < 0 || col > 6);
    return col;
}

int chercherLigne(Grille laGrille, int col)
{
    int ligne = -1;

    while (ligne < LIGNE - 1 && laGrille[ligne + 1][col] == VIDE)
    {
        ligne++;
    }
    return ligne;
}

bool estVainqueur(Grille laGrille, int lig, int col)
{
    // consiste Ã  regarder si une ligne de 4 pions s'est formÃ©e autour du pion qui vient de tomber en (lig, col)
    char lePion = laGrille[lig][col];
    int cpt, i, j;

    // regarder la verticale, en comptant le nombre de pions au Sud (inutile de regarder au Nord du pion qui vient de tomber)
    i = lig;
    cpt = 0;
    while (i < LIGNE && laGrille[i][col] == lePion)
    {
        cpt++;
        i++;
    }
    if (cpt >= 4)
    {
        return true;
    }
    // regarder l'horizontale, en comptant le nombre de pions Ã  l'Est et Ã  l'Ouest
    j = col;
    cpt = 0;
    // on regarde Ã  l'est
    while (j >= 0 && laGrille[lig][j] == lePion)
    {
        cpt++;
        j--;
    }
    j = col + 1;
    // on regarde Ã  l'ouest
    while (j < COLONNE && laGrille[lig][j] == lePion)
    {
        cpt++;
        j++;
    }
    if (cpt >= 4)
    {
        return true;
    }
    // regarder la diagonale descendante, en comptant le nombre de pions au Nord Ouest et au Sud Est
    i = lig;
    j = col;
    cpt = 0;
    // on regarde au Nord Ouest
    while (j >= 0 && i >= 0 && laGrille[i][j] == lePion)
    {
        cpt++;
        i--;
        j--;
    }
    i = lig + 1;
    j = col + 1;
    // on regarde au Sud Est
    while (i < LIGNE && j < COLONNE && laGrille[i][j] == lePion)
    {
        cpt++;
        i++;
        j++;
    }
    if (cpt >= 4)
    {
        return true;
    }
    // regarder la diagonale descendante, en comptant le nombre de pions au Nord Est et au Sud Ouest
    i = lig;
    j = col;
    cpt = 0;
    // on regarde au Nord Est
    while (j < COLONNE && i >= 0 && laGrille[i][j] == lePion)
    {
        cpt++;
        i--;
        j++;
    }
    i = lig + 1;
    j = col - 1;
    // on regarde au Sud Ouest
    while (i < LIGNE && j >= 0 && laGrille[i][j] == lePion)
    {
        cpt++;
        i++;
        j--;
    }
    if (cpt >= 4)
    {
        return true;
    }
    return false;
}

bool bloquerGagnant(Grille laGrille, char pion, int *ligne, int *colonne)
{
    for (int c = 0; c < COLONNE; c++)
    {
        int l = chercherLigne(laGrille, c);
        if (l != -1)
        // si la colonne n'est pas pleine
        {
            laGrille[l][c] = pion;
            // on place le pion temporairement
            if (estVainqueur(laGrille, l, c))
            // si le pion placé permet de gagner
            {
                *ligne = l;
                *colonne = c;
                // on enregistre la position du pion
                laGrille[l][c] = VIDE;
                // on remet la case vide
                return true;
            }
            laGrille[l][c] = VIDE;
            // on remet la case vide
        }
    }
    return false;
}

bool aligne2(Grille laGrille, int *lig, int *col)
{
    // consiste à regarder si une ligne de 2 pions s'est formée autour du pion qui vient de tomber en (lig, col)
    char lePion = laGrille[*lig][*col];
    int cpt, i, j;

    // regarder la verticale, en comptant le nombre de pions au Sud (inutile de regarder au Nord du pion qui vient de tomber)
    i = *lig;
    cpt = 0;
    while (i < LIGNE && laGrille[i][*col] == lePion)
    {
        cpt++;
        i++;
    }
    i = *lig;
    if (cpt >= 2)
    {
        if (i < LIGNE - 1 && laGrille[i - 1][*col] == VIDE)
        {
            *lig = i - 1;
        }
        return true;
    }
    // regarder l'horizontale, en comptant le nombre de pions à l'Est et à l'Ouest
    j = *col;
    cpt = 0;
    // on regarde à l'est
    while (j >= 0 && laGrille[*lig][j] == lePion)
    {
        cpt++;
        j--;
    }
    j = *col + 1;
    // on regarde à l'ouest
    while (j < COLONNE && laGrille[*lig][j] == lePion)
    {
        cpt++;
        j++;
    }
    j = *col;
    if (cpt >= 2)
    {
        if (j > 0 && j < COLONNE - 1)
        {
            if (laGrille[*lig][j - 1] == VIDE && *lig == chercherLigne(laGrille, j - 1))
            // on regarde si le pion peut tomber à gauche
            {
                *col = j - 1;
            }
            else if (laGrille[*lig][j + 1] == VIDE && *lig == chercherLigne(laGrille, j + 1))
            // on regarde si le pion peut tomber à droite
            {
                *col = j + 1;
            }
        }
        else if (j == 0)
        {
            if (laGrille[*lig][j + 1] == VIDE && *lig == chercherLigne(laGrille, j + 1))
            // on regarde si le pion peut tomber à droite
            {
                *col = j + 1;
            }
        }
        else if (j == COLONNE - 1)
        {
            if (laGrille[*lig][j - 1] == VIDE && *lig == chercherLigne(laGrille, j - 1))
            // on regarde si le pion peut tomber à gauche
            {
                *col = j - 1;
            }
        }
        return true;
    }
    // regarder la diagonale descendante, en comptant le nombre de pions au Nord Ouest et au Sud Est
    i = *lig;
    j = *col;
    cpt = 0;
    // on regarde au Nord Ouest
    while (j >= 0 && i >= 0 && laGrille[i][j] == lePion)
    {
        cpt++;
        i--;
        j--;
    }
    i = *lig + 1;
    j = *col + 1;
    // on regarde au Sud Est
    while (i < LIGNE && j < COLONNE && laGrille[i][j] == lePion)
    {
        cpt++;
        i++;
        j++;
    }
    i = *lig;
    j = *col;
    if (cpt >= 2)
    {
        if (i < LIGNE - 1 && j > 0 && j < COLONNE - 1)
        {
            if (laGrille[i + 1][j + 1] == VIDE && i + 1 == chercherLigne(laGrille, j + 1))
            // on regarde si la case en dessous à droite est vide et si on peut placer a cet endroit
            {
                *lig = i + 1;
                *col = j + 1;
            }
        }
        else if (i == LIGNE - 1 && j > 0 && j < COLONNE - 1)
        {
            if (laGrille[i - 1][j - 1] == VIDE && i - 1 == chercherLigne(laGrille, j - 1))
            // on regarde si la case au dessus a gauche est vide et si on peut placer a cet endroit
            {
                *lig = i - 1;
                *col = j - 1;
            }
        }
        else if (i < LIGNE - 1 && j == 0)
        {
            if (laGrille[i + 1][j + 1] == VIDE && i + 1 == chercherLigne(laGrille, j + 1))
            // on regarde si la case en dessous a droite est vide et si on peut placer a cet endroit
            {
                *lig = i + 1;
                *col = j + 1;
            }
        }
        else if (i < LIGNE - 1 && j == COLONNE - 1)
        {
            if (laGrille[i - 1][j - 1] == VIDE && i - 1 == chercherLigne(laGrille, j - 1))
            // on regarde si la case au dessus a gauche est vide et si on peut placer a cet endroit
            {
                *lig = i - 1;
                *col = j - 1;
            }
        }
        return true;
    }
    // regarder la diagonale descendante, en comptant le nombre de pions au Nord Est et au Sud Ouest
    i = *lig;
    j = *col;
    cpt = 0;
    // on regarde au Nord Est
    while (j < COLONNE && i >= 0 && laGrille[i][j] == lePion)
    {
        cpt++;
        i--;
        j++;
    }
    i = *lig + 1;
    j = *col - 1;
    // on regarde au Sud Ouest
    while (i < LIGNE && j >= 0 && laGrille[i][j] == lePion)
    {
        cpt++;
        i++;
        j--;
    }
    i = *lig;
    j = *col;
    if (cpt >= 2)
    {
        if (i < LIGNE - 1 && j > 0 && j < COLONNE - 1)
        {
            if (laGrille[i + 1][j - 1] == VIDE && i + 1 == chercherLigne(laGrille, j - 1))
            // on regarde si la case en dessous a gauche est vide et si on peut placer a cet endroit
            {
                *lig = i + 1;
                *col = j - 1;
            }
        }
        else if (i == LIGNE - 1 && j > 0 && j < COLONNE - 1)
        {
            if (laGrille[i - 1][j + 1] == VIDE && i - 1 == chercherLigne(laGrille, j + 1))
            // on regarde si la case au dessus a droite est vide et si on peut placer a cet endroit
            {
                *lig = i - 1;
                *col = j + 1;
            }
        }
        else if (i < LIGNE - 1 && j == 0)
        {
            if (laGrille[i - 1][j + 1] == VIDE && i - 1 == chercherLigne(laGrille, j + 1))
            // on regarde si la case au dessus a droite est vide et si on peut placer a cet endroit
            {
                *lig = i - 1;
                *col = j + 1;
            }
        }
        else if (i < LIGNE - 1 && j == COLONNE - 1)
        {
            if (laGrille[i + 1][j - 1] == VIDE && i + 1 == chercherLigne(laGrille, j - 1))
            // on regarde si la case en dessous a gauche est vide et si on peut placer a cet endroit
            {
                *lig = i + 1;
                *col = j - 1;
            }
        }
        return true;
    }
    return false;
}

// fonction qui clone la grille actuelle et qui renvoie un clone
void cloneGrille(Grille laGrille, Grille clone)
{
    int i, j;
    for (i = 0; i < LIGNE; i++)
    {
        for (j = 0; j < COLONNE; j++)
        {
            clone[i][j] = laGrille[i][j];
        }
    }
}

// fonction qui compare deux grille et qui renvoie l'endroit ou elles sont différents
void comparerGrille(Grille laGrille, Grille laGrille2, int *lig, int *col)
{
    int i, j;
    for (i = 0; i < LIGNE; i++)
    {
        for (j = 0; j < COLONNE; j++)
        {
            if (laGrille[i][j] != laGrille2[i][j])
            {
                *lig = i;
                *col = j;
            }
        }
    }
}

void rangerGrille3(Grille laGrille3, int lig, int col)
{
    laGrille3[lig][col] = ADVERSAIRE;
    FILE *fp;
    fp = fopen("laGrille3.txt", "w");
    for (int l = 0; l < LIGNE; l++)
    {
        for (int c = 0; c < COLONNE; c++)
        {
            fprintf(fp, "%c", laGrille3[l][c]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

void chercherGrille3(Grille laGrille3)
{
    FILE *fp;
    fp = fopen("laGrille3.txt", "r");
    for (int l = 0; l < LIGNE; l++)
    {
        for (int c = 0; c < COLONNE; c++)
        {
            fscanf(fp, "%c", &laGrille3[l][c]);
        }
    }
    fclose(fp);
}

int maStrategie(Grille grille)
{
    int l, c;
    Grille laGrille2, laGrille3;
    FILE *file;
    file = fopen("laGrille3.txt", "r");
    if (file != NULL)
    {
        cloneGrille(grille, laGrille2);
        chercherGrille3(laGrille3);
        comparerGrille(laGrille2, laGrille3, &l, &c);
        if (bloquerGagnant(grille, ADVERSAIRE, &l, &c))
        // si le bot peut gagner au prochain coup , alors il place son pion pour gagner
        {
            cloneGrille(grille, laGrille3);
            rangerGrille3(laGrille3, l, c);
            return c;
        }
        else if (bloquerGagnant(grille, JOUEUR, &l, &c))
        // si l'adversaire peut gagner au prochain coup , alors le bot bloque
        {
            cloneGrille(grille, laGrille3);
            rangerGrille3(laGrille3, l, c);
            return c;
        }
        else if (aligne2(grille, &l, &c))
        // si le bot peut faire une ligne de 2 pions , alors il place son pion pour faire une ligne de 3
        // si l'adversaire peut faire une ligne de 2 pions , alors le bot bloque
        {
            cloneGrille(grille, laGrille3);
            rangerGrille3(laGrille3, l, c);
            return c;
        }
        else
        // sinon le bot place son pion au hasard
        {
            srand(time(NULL));
            c = rand() % 6;
            cloneGrille(grille, laGrille3);
            rangerGrille3(laGrille3, l, c);
            return c;
        }
    }
    else
    {
        srand(time(NULL));
        c = rand() % 6;
        l = chercherLigne(grille, c);
        cloneGrille(grille, laGrille3);
        rangerGrille3(laGrille3, l, c);
        return c;
    }
}