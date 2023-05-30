<?php
error_reporting(E_ERROR | E_PARSE);
chdir("PHP");

function comparer_commerciaux(array $tab1, array $tab2) {
    // Fonction permettant de comparer deux commerciaux sur le CA, puis
    // en cas de CA égal sur leur nom dans l'ordre alphabétique
    // -1 -> tab1 < tab2
    // 1 -> tab1 > tab2
    if ($tab1["ca"] < $tab2["ca"]) {
        return 1;
    }
    elseif ($tab1["ca"] > $tab2["ca"]) {
        return -1;
    }
    elseif ($tab1["nom"] < $tab2["nom"]) {
        return 1;
    }
    else {
        return -1;
    }
}

$directory = "../textes/";
$files = glob($directory . '*.txt');
foreach ($files as $filename) {
    // Traiter chaque fichier TXT pour le transformer en plusieurs morceaux HTML
    $file = fopen($filename, "r");
    $texte = fopen($filename . ".html", "w");       // Description globale de la région
    $tab = fopen($filename . "_tab.html", "w");     // Résultats trimestriels
    $comm = fopen($filename . "_comm.html", "w");   // Meilleurs commerciaux

    while(!feof($file)){
        // Extraction des informations globales
        $line = fgets($file);
        $match = [];
        if (preg_match("/(?>SOUS_TITRE=|Sous_titre=)(.+)/", $line, $match)){
            fwrite($texte, "<h3>\n" . $match[1] . "</h3>\n");
        }
        else if (preg_match("/(?>Titre=|TITRE=)(.+)/", $line, $match)){
            fwrite($texte, "<h1>\n" . $match[1] . "</h1>\n");
        }
        else if (preg_match("/DEBUT_TEXTE|Début_texte/", $line)) {
            fwrite($texte, "<p id = Texte_Presentation>\n");
            while(!feof($file)){
                $line = fgets($file);
                if (preg_match("/FIN_TEXTE|Fin_texte/", $line)) {
                    fwrite($texte, $line . "</p>\n");
                    break;
                }
                fwrite($texte, $line);
            }
        }

        // Extraction des résultats trimestriels
        else if (preg_match("/DEBUT_STATS|Début_stats/", $line)) {
            fwrite($tab, "<table>\n<tr>\n<th>Nom du produit</th>\n<th>Ventes du trimestre</th>\n<th>Chiffre d’affaires du trimestre</th>\n<th>Ventes du même trimestre année précédente</th>\n<th>CA du même trimestre année précédente</th>\n<th>Evolution du CA (% et €)</th>\n</tr>\n");
            while(!feof($file)){
                $line = fgets($file);
                if (preg_match("/FIN_STATS|Fin_stats/", $line)) {
                    fwrite($tab, "</table>\n");
                    break;
                }
                $cells = explode(",", $line);
                fwrite($tab, "<tr>\n");
                fwrite($tab, "<td>" . $cells[0] . "</td>\n");
                fwrite($tab, "<td>" . $cells[1] . "</td>\n");
                fwrite($tab, "<td>" . $cells[2] . "</td>\n");
                fwrite($tab, "<td>" . $cells[3] . "</td>\n");
                fwrite($tab, "<td>" . $cells[4] . "</td>\n");
                fwrite($tab, "<td>\n");
                fwrite($tab, "<span style='color: ");
                if((($cells[2] - $cells[4])/$cells[4])*100 > 0) {
                    fwrite($tab, "limegreen'><strong>+");
                }
                else {
                fwrite($tab, "red'><strong>");
                }
                fwrite($tab, number_format((($cells[2] - $cells[4])/$cells[4])*100, 2, '.', '') . "% <br>" . number_format(abs($cells[2] - $cells[4]), 2, '.', '') . "€</strong></span>\n");
                fwrite($tab, "</td>\n</tr>\n");
            }
        } 

        // Extraction des meilleurs commerciaux
        else if (preg_match("/Meilleurs:|MEILLEURS:/", $line)) {
            $line = preg_replace("/Meilleurs:|MEILLEURS:/", "", $line);
            $commercials = explode(",", $line);
            
            fwrite($comm, "<div id='page2'>\n<div>\n<h1>Nos meilleurs vendeurs du trimestre</h1>\n</div>\n<div class='commercials-container'>\n");
            $tab_commerciaux=[];
            foreach($commercials as $commercial) {
                $pattern_commercial = "/(?'photo'[A-Z]+)\/(?'nom'.+)=(?'ca'[0-9]+)K€/";
                $commercial_info = [];
                preg_match($pattern_commercial, $commercial, $commercial_info);
                $tab_commerciaux[]=$commercial_info;
            }

            // Trier à l'aide de la fonction de comparaison puis garder les 3 meilleurs 
            usort($tab_commerciaux, comparer_commerciaux);
            $tab_meilleurs=array_slice($tab_commerciaux, 0, 3);

            foreach ($tab_meilleurs as $best) {
                fwrite($comm, "<div class='commercial'>\n<img src='../Photos/" .$best["photo"]. ".png' alt='Avatar commercial' class='photo'>\n<p>" . $best["nom"] . "</p>\n<p>CA : " . $best["ca"] . "K€</p>\n</div>\n");
            }
            fwrite($comm, "</div>\n</div>\n");
        }
    }
}
?>
