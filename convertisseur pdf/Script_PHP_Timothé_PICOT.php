<?php
$directory = "textes/";
$files = glob($directory . '*.txt');
foreach ($files as $filename) {
    $file = fopen($filename, "r");
    $texte = fopen($filename . ".html", "w");
    $tab = fopen($filename . "_tab.html", "w");
    $comm = fopen($filename . "_comm.html", "w");
    while(!feof($file)){
        $line = fgets($file);
        if (preg_match("/Sous_titre=|SOUS_TITRE=/", $line)){
            fwrite($texte, "<h3>\n" . $line . "</h3>\n");
        }
        else if (preg_match("/Titre=|TITRE=/", $line)){
            fwrite($texte, "<h1>\n" . $line . "</h1>\n");
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
                fwrite($tab, "<p style='color: ");
                if((($cells[2] - $cells[4])/$cells[4])*100 > 0) {
                    fwrite($tab, "limegreen'><strong>+");
                }
                else {
                fwrite($tab, "red'><strong>");
                }
                fwrite($tab, number_format((($cells[2] - $cells[4])/$cells[4])*100, 2, '.', '') . "% <br>" . number_format(abs($cells[2] - $cells[4]), 2, '.', '') . "€</strong></p>\n");
                fwrite($tab, "</td>\n</tr>\n");
            }
        } 
        else if (preg_match("/Meilleurs:|MEILLEURS:/", $line)) {
            $line = preg_replace("/Meilleurs:|MEILLEURS:/", "", $line);
            $commercials = explode(",", $line);
            fwrite($comm, "<div id='page2'>\n<div>\n<h1>Nos meilleurs vendeurs du trimestre</h1>\n</div>\n<div class='commercials-container'>\n");
            foreach($commercials as $commercial) {
                $commercial_info = explode("=", $commercial);
                $code_nom = explode("/", $commercial_info[0]);
                fwrite($comm, "<div class='commercial'>\n<img src='Ressources/" .$code_nom[0]. ".svg' alt='Avatar commercial' class='photo'>\n<p>" . $commercial_info[0] . "</p>\n<p>CA : " . $commercial_info[1] . "</p>\n</div>\n");
            }
            fwrite($comm, "</div>\n</div>\n");
            }
    }
}
?>