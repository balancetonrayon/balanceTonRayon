# Analyse Préliminaire

## A Une analyse d'usage du logiciel

### 1 - Contexte d'utilisation

Contexte d'utilisation : ray_tracing pour l'affichage et la modélisation d'une scène simple. Base d'une librairie qui vocation à être enrichie.

### 2 - Fonctions souhaitées par les utilisateurs de la bibliothèque à la fois pour la description des composantes de la scène que pour les moteurs d'exécution

- Faire du ray tracing : rendu d'une scene avec tracé de rayons
- Pouvoir définir la scène de façon simple (langage approprié facile à mettre en oeuvre)
- Pouvoir faire le rendu du plus d'objets possible (spheres, plans, parallélépipèdes rectangles, etc)
- Pouvoir utiliser plusieurs moteurs graphiques
- Pouvoir utiliser plusieurs algorithmes de ray tracing et les paramétrer
- Le calcul doit être aussi rapide que possible : proposer une parallélisation, ou plusieurs types de parallélisations
- Avoir un code bien documenté : documentation du code en lui même mais aussi de la librairie (instruction pour ajouter des formes, algorithmes et types de caméras ?)
- Avoir un code facile à compléter : structure nécessaire facile à trouver et quantité de code minimisées

### 3 - Définition des interactions

#### Interaction directe avec l'utilisateur

- affichage de la scène après rendu
- entrée des données pour définir la scène (manuel, XML), pour définir les modalités du rendu (profondeur de récursion, type d'algorithme) et de calcul du rendu (antialialiasing)

#### Interaction avec la mémoire de l'ordinateur

- sauvegarde des images sous plusieurs formats
- importation d'objets définis de façon externe
- importation de textures

#### Interaction avec le développeur

- affichage des objets sous forme de texte pour faciliter le débug

#### 4 - Fonctions de base

-

## B Une analyse fonctionnelle du logiciel

### 1 - Les différents blocs fonctionnels du programme

- le rendu des images (Ray tracing, affichage, sauvegarde)
- la navigation (Interface graphique, prise en compte clavier souris)
- le décodage et l'encodage des fichiers de scènes (conversion XML C++, C++->XML)

### 2 -Les interactions avec l'environnement au niveau fonctionnel (interactions entre formes géométriques ??)

- fenêtre et contexte openGL

## C - Une architecture gros grains du logiciel

### 1 - Les différentes classes principales

- Classe Scene

  - objets
  - camera

- Classe Objet physique

  - point (x, y, z)

- Classe Ray

  - point de départ (x, y, z)
  - direction (x, y, z)

- Classe Forme

  - pourcentage de transparence
  - pourcentage de réflexion et de transmission
  - texture ou couleur
  - indice de réfraction
  - intersect() qui renvoie les nouveaux rayons si intersection

- Classe Source lumineuse : Objet physique

  - couleur
  - cône
  - méthode pour calculer le shadowRay

- Classe Camera : Objet Physique

  - taille et resolution de l'écran
  - genRay() qui génère un rayon correspondant à un pixel de la caméra

### 2 - Les concepts de modularité et d'extensibilité

- utiliser un maximum l'héritage de classes
- maximiser le polymorphisme. On va éviter de créer chaque fonction pour chaque objet. Cela compliquerait nettement l'ajout de futures formes.
- éventuellement utiliser des templates pour gérer la précision des calculs.

### 3 - Les interactions entre ces éléments

- l'objet Ray va interagir avec tous les objets formes
- l'objet Camera va générer des objets Ray
- l'objet Scene va contenir des objets Camera et Forme
- l'objet Forme va peut-être contenir d'autres objets forme (pour les intersections et les unions)

texture : affiché par openGL, calcul de la position de la texture; texture de base à choisir (couleur)

## Deuxième partie

### La méthode choisie pour la propagation

rayon : oeil -> objet -> ... -> source

Exemples d'algorithmes de ray-tracing : scratchapixels2.0

### Représentation d'une scène d'objets

transparence (à voir comment on sépare en deux parties)

formes mathématiques d'abord (sphère, cube, cylindre, cône, ...)

XML pour stocker les données et la scène.

Support d'un format OBJ, FDX avec facilité pour en rajouter

### Interaction avec l'utilisateur

interaction clavier souris écran.

utilisation de plusieurs moteurs graphiques: OPENGL, Vulcan, ...

Interaction possible sur tous les supports : privilégier le multi-plateforme (Supporté par windows)

GTK pour l'interface avec l'utilisateur semble donc un bon choix.
