# définition de la taille de l'échiquier
N = 6

# définition des mouvements autorisés du cavalier
deplacements = [
    (-2, -1), (-2, 1), (-1, -2), (-1, 2),
    (1, -2), (1, 2), (2, -1), (2, 1)
]

# fonction qui génère le graphe représentant les cases accessibles depuis chaque case de l'échiquier
def generer_graphe():
    graphe = {}

    for i in range(N):
        for j in range(N):
            case_depart = (i, j)
            voisins = []
            for deplacement in deplacements:
                i_suivant, j_suivant = i + deplacement[0], j + deplacement[1]
                if 0 <= i_suivant < N and 0 <= j_suivant < N:
                    voisins.append((i_suivant, j_suivant))
            graphe[case_depart] = voisins

    return graphe


def parcours_cavalier(graphe, case_depart, visites, chemin_courant):
    # on marque la case de départ comme visitée
    visites.add(case_depart)

    # on ajoute la case de départ au chemin courant
    chemin_courant.append(case_depart)

    # si le chemin courant contient toutes les cases, on a trouvé une solution
    if len(chemin_courant) == N*N:
        return chemin_courant

    # on explore les cases voisines non visitées
    for voisin in graphe[case_depart]:
        if voisin not in visites:
            chemin = parcours_cavalier(graphe, voisin, set(visites), list(chemin_courant))
            if chemin:
                return chemin

    # si aucune solution n'a été trouvée, on retourne None
    return None


# génération du graphe
graphe = generer_graphe()
case_depart = (0, 0)
data = parcours_cavalier(graphe, case_depart, set(), [])




def initEchi():
    """La fonction initEchi() initialise un échiquier de taille N*N.

    Returns:
        Une liste de listes de taille N*N.
        Un échiquier vide.
    """
    return [[0 for j in range(N)] for i in range(N)]

newData = initEchi()

data[0]



for i in range(len(data)):
    newData[data[i][0]][data[i][1]] = i



def afficher_echiquier(tab,N,num):
    """
    La fonction afficher_echiquier() affiche l'échiquier sur l'écran Pygame.

    Args:
        tab (list): La liste de listes représentant l'échiquier à afficher.
        N (int): La taille de l'échiquier.
        num (int): Le numéro de l'échiquier à afficher.

    Returns:
        None
    """
    print("")
    barre = "-"*(N*2-4)
    print(barre," ",num+1," ",barre) # On affiche le numéro de l'échiquier
    for i in range(N):
        
        for j in range(N):
            if len(str(tab[i][j])) == 1:
                print(tab[i][j],"  ",end='')
            else:
                print(tab[i][j]," ",end='')
        print("")
    print("")

afficher_echiquier(newData,N,0)
# affichage du résultat
"""
if data:
    print("Un chemin hamiltonien a été trouvé :")
    print(data)
else:
    print("Aucun chemin hamiltonien n'a été trouvé.")"""