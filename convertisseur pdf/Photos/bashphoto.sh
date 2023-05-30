#!/usr/bin/bash
upperName=${1^^}
dir="$(pwd)/Photos"
docker container run -ti -v "$(pwd)":/work bigpapoo/sae103-imagick "magick Photos/$1.svg Photos/$upperName.png"
docker container run -ti -v "$(pwd)":/work bigpapoo/sae103-imagick "magick convert -colorspace gray Photos/$1.svg Photos/$upperName.png"
docker container run -ti -v "$(pwd)":/work bigpapoo/sae103-imagick "convert Photos/$upperName.png -resize 200x200 Photos/$upperName.png"
