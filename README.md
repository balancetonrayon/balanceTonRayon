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

### Enrich the engine

If you want to enrich the engine, please refer to the developmentNotes in the documentation folder.
