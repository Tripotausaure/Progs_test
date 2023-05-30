function switchNavModal() {
    // get checkbox
    var checkBox = document.getElementById("navMenuCheckbox");
    // get modal of the nav menu
    var navModal = document.getElementById("navModal");
    
    // If the checkbox is checked, display the output text

    if (checkBox.checked == true){
    navModal.style.left = 0;
    scrolDisable();
    
    
    
  } else {
    
    navModal.style.left = "-900px";
    scrolEnable();
    
  }

}

// TO STOP SCROLLING

function scrolDisable() {
    // To get the scroll position of current webpage
    TopScroll = window.pageYOffset || document.documentElement.scrollTop;
    LeftScroll = window.pageXOffset || document.documentElement.scrollLeft,
    
    // if scroll happens, set it to the previous value
    window.onscroll = function() {
    window.scrollTo(LeftScroll, TopScroll);
            };
    }
    
function scrolEnable() {
    window.onscroll = function() {};
}

// Tableau des images de la galerie
var images = [
    "../ressources/HeberLoca/Img_inte_bunga1.jpeg",
    "../ressources/HeberLoca/Img_inte_bunga2.jpeg",
    "../ressources/HeberLoca/Img_inte_bunga3.jpeg",
    "../ressources/HeberLoca/Img_inte_bunga4.jpeg",
    "../ressources/HeberLoca/Img_inte_bunga5.jpeg"
];

// Initialisation de la variable pour suivre l'image courante
var currentImage = 0;

// Fonction pour afficher l'image courante
function displayImage() {
    document.getElementById("galerie").src = images[currentImage];
}

// Fonction pour passer à l'image suivante
function nextImage() {
    currentImage++;
    if (currentImage >= images.length) {
        currentImage = 0;
    }
    displayImage();
}

// Fonction pour passer à l'image précédente
function prevImage() {
    currentImage--;
    if (currentImage < 0) {
        currentImage = images.length - 1;
    }
    displayImage();
}

// Fonction pour afficher les points de navigation
function displayNav() {
    var nav = "";
    for (var i = 0; i < images.length; i++) {
        if (i == currentImage) {
            nav += "<span class='active'></span>";
        } else {
            nav += "<span onclick='currentImage = " + i + "; displayImage();'></span>";
        }
    }
    document.getElementById("nav").innerHTML = nav;
}

// Appel de la fonction pour afficher l'image courante au chargement de la page
window.onload = function() {
    displayImage();
    displayNav();
    setInterval(nextImage, 10000);
}
