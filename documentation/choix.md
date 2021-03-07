# Justification des choix faits au long du projet

## Le polymorphisme

Le polymorphisme, c'est-à-dire notamment les surcharges d'opérateur et l'héritages ont été des clées de notre projet.

Nous avons surchargé un certain nombre d'opérateurs notamment pour l'affichage des informations des différentes classes.

L'héritage est lui au centre de toutes nos classes. Les 2 moteurs de Ray tracing héritent d'un moteur générique, tous les objects héritent de Physical Object puis de basis object, les lumières héritent de Light, les textures comme les images héritent de Texture, etc...

Les templates ne nous ont pas été directement très importants. Toutefois, nous les avons utilisés par l'intermédiaire des shared pointers notamment.

Ce polymorphisme permet de ne pas avoir à recopier du code et redéfinir des fonctions à chaque fois que l'on souhaite créer une classe comme un objet par exemple.

Le polymorphisme était donc absolument nécessaire pour notre projet.

## L'encapsulation

L'encapsulation a pris de l'importance au fur et à mesure du projet. Tout d'abord, l'utilisation très intensive des attributs des objets nous a plutôt restreint dans l'utilisation de l'encapsulation. Les classes implémentées plus tard mettent beaucoup plus à profit la notion d'encapsulation.

## Pourquoi GLM ?

GLM permet une gestion facile des différents types de vecteurs : les glm::vec2, glm::vec3, ou glm::vec4. Les opérations habituelles sont définies pour ces objets, comme le produit scalaire, le produit vectoriel, etc. Nous avons uniquement dû coder quelques opératuers supplémentaires ainsi que la mutliplication élément par élément pour la gestion des couleurs.

## La gestion des couleurs sous la forme de glm::vec3

Le fait d'utiliser les glm::vec3 pour gérer les couleurs permet une uniformisation des données qui rend le développement plus facile. La chaîne n°4 des PNG a obligé le passage à des glm::vec4 pour la gestion des textures.

## Purger OpenCV ? -> LodePNG

Notre premier choix était d'utiliser OpenCV pour la gestion des images. Son utilisation est très facile. Toutefois, celui-ci prenait plus de 2h30 à compiler dans la pipeline github. De plus, il possède un très grand nombre de fonctionnalités totalement inutiles pour ce projet (comme de réseaux de neurones, etc). Nous avons donc décidé d'utiliser une librairie beaucoup plus légère : lodepng. Nous avions commencé par nous intéresser à libpng, toutefois, l'absence de wrapper pour C++, et le côté abrupte de libpng nous a poussé à chercher autre chose.

## Quelle documentation ?

Nous avons décidé de créer une documentation en deux parties. La documentation plus générale est disponible dans ce dossier, et s'accompagne du README à la racine. Elle contient les informations plus générales sur le projet. La documentation des fichiers, des classes et du code est elle effectuée avec Doxygen, ce qui permet de la créer facilement. Notons qu'elle se lie directement avec notre environnement de développement.

## Cmake

Cmake permet une gestion très facile des dépendances et permet plus de souplesse qu'un Makefile fait main. Le Makefile ou cmake étaient absolument nécessaires pour le projet. La compilation aurait sinon été trop complexe. De plus, il est possible de compiler sur les différents processeurs et ainsi gagner beaucoup de temps.

## Arguments de compilation

Nous avons décidé d'utiliser -O3 pour améliorer la compilation du code. La différence entre -O3 -O2 et -O1 semble assez faible sur notre problème.

## Architecture du projet

Posez-nous des questions ! :)
