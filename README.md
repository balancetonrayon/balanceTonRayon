# balanceTonRayon

## build

Build binary

```shell
mkdir build
cd build
cmake ../src
cmake --build .
```

Building Xcode Project

```shell
cd build
cmake -G Xcode ../src
```

Lint
```shell
cpplint --recursive src
```
