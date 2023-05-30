<?php
chdir("PHP");
$date = date("d/m/Y H:i",time());
$mois = date("m", time());
$annee = date("Y");
$trimestre = floor(($mois - 1) / 3) + 1;

$file = fopen("regions.conf", "r");
while (!feof($file)) {
   $line = fgets($file);
   $columns = explode(";", $line);
   // var_dump([$argv[1], $columns[2]]);
   if ($columns[2] == $argv[1]) {
      $region_code = $columns[1];
      $region_name = $columns[2];
      $population = $columns[3];
      $superficie = $columns[4];
      $departments = $columns[5];
      echo "<!DOCTYPE html>
      <html lang=\"en\">
      <head>
         <meta charset=\"UTF-8\">
         <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">
         <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">
         <title>$region_name</title>
         <link rel=\"stylesheet\" href=\"style.css\">
      </head>
      <body>
         <section>
            <div id=\"couverture\">
               <h1 id=\"nom_region\"> $region_name</h1>
               <img src=\"../Logos/$region_code.png\"  id=\"logoRegion\">
               <div class=\"infoCouverture\">
                  <p>Population : $population</p>
                  <p>Superficie : $superficie</p>
                  <p>Nombre de départements :  $departments</p>
               </div>
            </div>
            <div class=\"bottom\">$date</div>
         </section>

         <section>
            <div id=\"page1\">";
            include("../textes/$argv[1].txt.html");
            echo "<h1>Résultats trimestriels T$trimestre-$annee</h1>";
            include("../textes/$argv[1].txt_tab.html");
      echo "  
            </div>
            <div class=\"bottom\">$date</div>
         </section>

         <section>
            <div id=\"page2\">";
            include("../textes/$argv[1].txt_comm.html");
            echo "
         </div>
            
            </div>
            <div class=\"bottom\">$date</div>
         </section>

         <section>
            <div id=\"page3\">
               <div>
                  <a href=\"https://bigbrain.biz/%3C$region_code\" style=\"text-decoration: none;\">bigbrain.biz/$region_code</a>
                  <img src=\"../QR_code/$region_code.png\" alt=\"QRcode\" id=\"QR\">
               </div>
            </div>
            <div class=\"bottom\">$date</div>
         </section>
      </body>
      </html>";
      }
}
?>
