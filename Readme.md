# cpp-class-parser

Helper class to parse C++ class definitions for implementing code generators.

## Compiling

Make shure you have a llvm/clang installation with clang tools. Otherwise compile a llvm/clang version on your own.
The repository [rcl-llvm](https://github.com/ycollani/rcl-llvm.git) might help to comilpe a custom llvm version.

Set the environment variable `PREFIX` to the base path of the llvm installation. Use `-DCMAKE_INSTALL_PREFIX` for cmake to define install directory. 

```
cd cpp-class-parser
mkdir -p ./build -DCMAKE_INSTALL_PREFIX=<install path prefix>
cmake ../
make
make install
```

## Usefull Links

- https://eli.thegreenplace.net/2014/05/21/compilation-databases-for-clang-based-tools

