# balanceTonRayon

rayon : oeil -> objet -> ... -> source

récursif

transparence (à voir comment on sépare en deux parties)

formes mathématiques d'abord (sphère, cube, cylindre, cône, ...)

XML pour stocker les données et la scène.

Support d'un format OBJ, FDX avec facilité pour en rajouter

interaction clavier souris écran : OPENGL, Vulcan, ...

supporté par windows

GTK pour l'interface avec l'utilisateur ?

limite de champ de vision

## Les classes

Object Scene

Object base

- geometrie (x, y, z)

Object Ray

- longueur d'onde (phase 3)

Object Forme -> quelle forme ? (mesh)

- géométrie
- pourcentage de transparence (phase 2)
- texture ou couleur
- indice de réfraction (phase 2)
- intersect() qui renvoie les nouveaux rayons si intersection

Object Source lumineuse

- couleur
- cône

Object Camera

intersection et union : object qui contient plusieurs objets

texture : affiché par openGL, calcul de la position de la texture; texture de base à choisir (couleur)
