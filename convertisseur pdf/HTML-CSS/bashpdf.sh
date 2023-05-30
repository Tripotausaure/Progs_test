#!/bin/bash

rm -f Resultats_Trimestriels/*.pdf

for file in HTML-CSS/*.html; do
    fichier_sans_ext=$(basename "$file" .html)
    docker run --rm -ti -v "$(pwd)":/work bigpapoo/sae103-html2pdf "html2pdf \"$file\" \"Resultats_Trimestriels/$fichier_sans_ext.pdf\""
    # docker run --rm -ti -v $(pwd)/HTML-CSS:/work sae103-html2pdf "html2pdf $1.html $2.pdf"
done
