/************************************************
 *   SAÉ1.04 - Création d'une base de données   *
 *               Équipe sae104_e25              *
 *                 Timothé Picot                *
 *                 Ryan Troadec                 *
 *                 Maxime Perrot                *
 ************************************************/

--------------------------------
-- Réinitialisation du schéma --
--------------------------------

DROP SCHEMA IF EXISTS transmusicales CASCADE;
CREATE SCHEMA transmusicales;
SET SCHEMA 'transmusicales';


-------------------------
-- Création des tables --
-------------------------

-- Pays
CREATE TABLE Pays (
    nom_p VARCHAR(255) PRIMARY KEY
);

-- Ville
CREATE TABLE Ville (
    nom_v VARCHAR(255) PRIMARY KEY, 
    nom_p VARCHAR(255) NOT NULL,
	
	-- Contraintes
    CONSTRAINT Ville_fk
      FOREIGN KEY(nom_p)
        REFERENCES Pays(nom_p)
);

-- Lieu
CREATE TABLE Lieu (
    id_lieu VARCHAR(255) PRIMARY KEY,
    nom_lieu VARCHAR(255) NOT NULL,
    accessPMR BOOLEAN NOT NULL,
    capacite_max INT NOT NULL,
    type_lieu VARCHAR(255) NOT NULL,
    nom_v VARCHAR(255) NOT NULL,
	
	-- Contraintes
    CONSTRAINT Lieu_fk
      FOREIGN KEY(nom_lieu)
        REFERENCES Ville(nom_v)
);

-- Type_musique
CREATE TABLE Type_musique (
    type_m VARCHAR(255) PRIMARY KEY
);

-- Concert
CREATE TABLE Concert (
    no_concert VARCHAR(255) PRIMARY KEY,
    titre VARCHAR(255) NOT NULL,
    resume VARCHAR(255) NOT NULL,
    duree INT NOT NULL,
    tarif NUMERIC(5) NOT NULL,
    type_m VARCHAR(255) NOT NULL,
    nom_edition VARCHAR(255)NOT NULL,
	
	-- Contraintes
    CONSTRAINT Concert_fk1
      FOREIGN KEY(type_m)
        REFERENCES Type_musique(type_m),
		
    CONSTRAINT Concert_fk2
      FOREIGN KEY(nom_edition)
        REFERENCES Edition(nom_edition)
);

-- Annee
CREATE TABLE Annee (
    an INT PRIMARY KEY
);

-- Edition
CREATE TABLE Edition (
    nom_edition VARCHAR(255) PRIMARY KEY,
    no_concert VARCHAR(255) NOT NULL,
    an INT NOT NULL,
	
	-- Contraintes
    CONSTRAINT Edition_fk1
      FOREIGN KEY(no_concert)
        REFERENCES Concert(no_concert),
		
    CONSTRAINT Edition_fk2
      FOREIGN KEY(an)
        REFERENCES Annee(an)
);

-- Formation
CREATE TABLE Formation (
    libelle_formation VARCHAR (255) PRIMARY KEY
);

-- Groupe_artiste
CREATE TABLE Groupe_artiste (
    id_groupe_artiste VARCHAR(255) PRIMARY KEY,
    nom_groupe_artiste VARCHAR(255) NOT NULL,
    site_web VARCHAR(255) NOT NULL,
    nom_p VARCHAR(255) NOT NULL,
    an_sortie_discographie INT NOT NULL,
    an_debut INT NOT NULL,
    libelle_formation VARCHAR(255) NOT NULL,
    type_m_principal VARCHAR(255) NOT NULL ,
    type_m_ponctuel VARCHAR(255) NOT NULL,
	
	-- Contraintes
    CONSTRAINT Groupe_artiste_fk1
		FOREIGN KEY (nom_p)
			REFERENCES Pays(nom_p),
			
    CONSTRAINT Groupe_artiste_fk2
		FOREIGN KEY (an_sortie_discographie)
			REFERENCES Annee(an),
			
    CONSTRAINT Groupe_artiste_fk3
		FOREIGN KEY (an_debut)
			REFERENCES Annee(an),
			
    CONSTRAINT Groupe_artiste_fk4
		FOREIGN KEY (libelle_formation)
			REFERENCES Formation(libelle_formation),
			
    CONSTRAINT Groupe_artiste_fk5
		FOREIGN KEY (type_m_principal)
			REFERENCES Type_musique(type_m),
			
    CONSTRAINT Groupe_artiste_fk6
		FOREIGN KEY (type_m_ponctuel)
			REFERENCES Type_musique(type_m)
);

CREATE TABLE Representation (
    numero_representant VARCHAR(255) PRIMARY KEY,
    heure VARCHAR(255) NOT NULL,
    date_representation VARCHAR(255) NOT NULL,
    id_lieu VARCHAR(255) NOT NULL,
    no_concert VARCHAR(255) NOT NULL,
    id_groupe_artiste VARCHAR(250) NOT NULL,
	
	-- Contraintes
    CONSTRAINT Representation_fk1
		FOREIGN KEY (id_lieu)
			REFERENCES Lieu(id_lieu),
			
    CONSTRAINT Representation_fk2
		FOREIGN KEY (no_concert)
			REFERENCES Concert(no_concert),
			
    CONSTRAINT Representation_fk3
		FOREIGN KEY (id_groupe_artiste)
			REFERENCES Groupe_artiste(id_groupe_artiste)
);




































--     _________________
--    |                 |
--    | J'adore le SQL !|
--    |___  ____________|
--        |/
--   \o/
--    |
--   / \
