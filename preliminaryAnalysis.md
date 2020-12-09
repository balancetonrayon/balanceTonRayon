# Analyse Préliminaire

## A Une analyse d'usage du logiciel

### 1 - Contexte d'utilisation

Contexte d'utilisation : ray_tracing pour l'affichage et la modélisation d'une scène simple. Base d'une librairie qui vocation à être enrichie.

### 2 - Fonctions souhaitées par les utilisateurs de la bibliothèque à la fois pour la description des composantes de la scène que pour les moteurs d'exécution

- faire du ray_tracing
- pouvoir définir la scène de façon simple
- pouvoir faire le rendu du plus d'objet possible
- pouvoir utiliser plusieurs moteurs graphiques
- (pouvoir utiliser plusieurs algos de ray tracing)
- le calcul doit être aussi rapide que possible
- avoir un code bien documenté
- avoir un code facile à compléter

### 3 - Définition des interactions

#### Interaction directe avec l'utilisateur

- affichage de la scène après rendu
- entrée des données pour définir la scène (manuel, XML)

#### Interaction avec la mémoire de l'ordinateur

- sauvegarde des images
- importation d'objets définis de façon externe
- importation de textures

#### Interaction avec le développeur 

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
  - texture ou couleur
  - indice de réfraction
  - intersect() qui renvoie les nouveaux rayons si intersection

- Classe Source lumineuse : Objet physique

  - couleur
  - cône

- Classe Camera : Objet Physique

  - taille et resolution de l'écran

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

Exemples d'algorithmes de ray-tracing :

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
