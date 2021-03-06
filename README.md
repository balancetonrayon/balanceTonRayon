# balanceTonRayon

## Description of the project

This project, developed by Atoli Huppé and Olivier Laurent, is a small RayTracer engine. The user can define a 3D scene, with several objects, lights and a camera and the algorithm will render this scene in 2D.

## Dependencies

The developers have tried to reduce the amount of third parties/dependencies.

You will need at least glm and tinyxml2. Lodepng is already included in the code.

## How to Build the project

First, you need to build the binaries. To do so clone the repository. Then type the following commands inside the new folder.

```shell
mkdir build
cd build
cmake ../src
cmake --build .
```

On peut utiliser `make -j` pour accélerer la compilation.

Building Xcode Project

```shell
cd build
cmake -G Xcode ../src
```

Lint

```shell
cpplint --recursive src
```

## How to use the project

### Simple use

To use the project, just type

```shell
./RayTracing
```

### Advanced use

Look at the \*.xml files. Create your own, let's say file.xml. Put it in /data. Then type :

```shell
./RayTracing file.xml n
```

with n being the power of anti-aliasing that your wish. The complexity of the algorithm increases with the square of this number. n is not necessary.

## Enrich the engine

If you want to enrich the engine, please refer to the developmentNotes in the documentation folder.
