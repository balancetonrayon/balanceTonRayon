# Fonctionnalités

La plupart des fonctionnalité auquelles nous avions pensé ont été implémentées. Toutefois, les idées les plus ambitieuses comme l'interface graphique pour définir les scènes et l'utilisation de CUDA ont été progressivement abandonnées par manque de temps. OpenGL a aussi été abandonné car jugé peu utile.

## Fonctionnalités implémentées

Reprenons le markdown d'analyse préliminaire.

### Fonctionnalités prévues et implémentées

#### Fonctionnalités générales

Nous pouvons faire le rendu d'une scène par lancé de rayons.

Nous pouvons définir une scène de façon simple avec du XML.

Nous pouvons rendre des plans, des sphères, des triangles, des ensembles de triangles.

Nous avons deux moteurs graphiques de ray tracing. Le second permet de faire de l'anticrénelage.

Nous avons proposé une parallélisation avec OMP.

Le code est documenté de façon extensive.

Le code est facile à compléter et les instructions pour le faire sont dans le fichier developmentNotes.md.

#### Les interactions

La scène est affichée, on peut entrer la scène manuellement ou avec du XML. On ne peut pas encore choisir via le XML le moteur de ray tracing (anti crénelage ou non).

Les images ne peuvent être sauvegardées sous forme de png uniquement pour l'instant.

On peut importer des objets sous la forme de .obj mais le fonctionnement n'est pas complètement assuré.

On ne peut importer que des images directe en temps que textures (mais aussi définir de fonctions comme CheckedPattern2D)

Les classes peuvent presque toutes se mettre sous forme de texte grâce à l'héritage.

L'intéraction avec l'utilisateur est limité à l'utilisation des lignes de commandes.

### Les fonctionnalités non prévues et implémentées

La possibilité de définir des fonctions comme textures pour n'importe quel objet.

La possibilité de convertir et de tracer des maillages faits de polygônes.

Les scènes par défaut pour l'utilisateur pressé.

L'utilisation de cmake.

La pipeline github. Nous avons aussi installé un windows serveur sur les serveurs de DaTA pour vérifier le fonctionnement sur cette plateforme, mais nous n'avons pas eu le temps de la configurer correctement.

### Pistes d'amélioration

Nous souhaiterions tout d'abord améliorer l'optimisation du code. Notre volonté d'implémenter un maximum d'outils pour donner toute sa liberté à l'utilisateur a retardé la réflexion sur l'optimisation.

Les maillages ne permettent pas encore l'utilisation de fichiers de texture.

Ajouter du FXAA (post-traitement).
