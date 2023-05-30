#!/usr/bin/bash

####################
# CONVERTIR IMAGES #
####################

# Clear png
rm -f Photos/*.png

# Traite images
for photo in Photos/*.svg; do
	bash Photos/bashphoto.sh $(basename "$photo" .svg)
done

####################
#  CREER QR CODES  #
####################
rm -f QR_code/*.png
for codeIso in Logos/*.png; do
	QR_code/bashqrcode.sh $(basename "$codeIso" .png)
done

####################
#    LANCER PHP    #
####################

PHP/bashphp.sh

####################
#  CONVERTIR PDFs  #
####################

HTML-CSS/bashpdf.sh

####################
#    COMPRESSER    #
####################
tar -cf resul_trim.tar.gz Resultats_Trimestriels/*.pdf
