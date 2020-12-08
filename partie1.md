# Partie 1

## A Une analyse d'usage du logiciel

### 1 -

Contexte d'utilisation : ray_tracing pour l'affichage et la modélisation d'une scène simple. Base d'une librairie qui vocation à être enrichie.

### 2 -

- faire du ray_tracing
- pouvoir définir la scène de façon simple
- rendre les objets que l'on veut de la façon la plus riche possible
- pouvoir utiliser plusieurs moteurs graphiques
- (pouvoir utiliser plusieurs algos de ray tracing)
- le calcul doit être aussi rapide que possible
- avoir un code bien documenté

### 3 - Définition des interactions

- affichage de la scène après rendu
- entrée des données pour définir la scène (manuel, XML)
- importation d'objets définis de façon externe
- importation de textures
- sauvegarde des images

#### 4 - Fonctions de base

- Qu'est-ce que ça veut dire exactement ?

## B Une analyse fonctionnelle du logiciel

### 1 - Les différents blocs fonctionnels du programme

- le rendu des images (Ray tracing, affichage, sauvegarde)
- la navigation (Interface graphique, prise en compte clavier souris)
- le décodage et l'encodage des fichiers de scènes (conversion XML C++, C++->XML)

### 2 -Les interactions avec l'environnement au niveau fonctionnel (interactions entre formes géométriques ??)

- fenêtre et contexte openGL

## C - Une architecture gros grains du logiciel

### 1 - Les différentes classes principales

- ObjectBase

### 2 - Les concepts de modularité et d'extensibilité

### 3 - Les interactions entre ces éléments
