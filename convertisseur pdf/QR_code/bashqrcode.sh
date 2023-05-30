#!/bin/bash

docker container run -ti -v "$(pwd)/QR_code":/work bigpapoo/sae103-qrcode qrencode -o "$1.png" "https://bigbrain.biz/$1"
