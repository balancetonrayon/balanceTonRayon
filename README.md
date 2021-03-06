# balanceTonRayon

## Description of the project

###

## Dependencies

## How to Build the project

First, you need to build the binaries. To do so,

```shell
mkdir build
cd build
cmake ../src
cmake --build .
```

on peut ensuite utiliser `make -j`

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
