#!/bin/bash

rm -f HTML-CSS/*.html
rm -f textes/*.html

docker container run -ti -v "$(pwd)":/work bigpapoo/sae103-php php PHP/extraction_data.php

for fichier in textes/*.txt; do
    fichier_sans_ext=$(basename "$fichier" .txt)
    fichier_sortie=$(echo $fichier_sans_ext | tr ' ' '-')
    docker container run -ti -v "$(pwd)":/work bigpapoo/sae103-php php PHP/fusion_data.php "$fichier_sans_ext" > "HTML-CSS/$fichier_sortie.html"
done