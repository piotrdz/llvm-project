# Building clang-tidy only

From within the git root directory:
```
$ mkdir build
$ cd build
$ install_path="/usr/local" # change to where you want to install
$ cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DLLVM_ENABLE_PROJECTS="clang;clang-tools-extra;" -DCMAKE_INSTALL_PREFIX="$install_path" ../llvm
$ make -j install-clang-tidy
```
