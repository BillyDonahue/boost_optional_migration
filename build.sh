#!/bin/bash
mkdir build

cmake -C build -G Ninja -D LLVM_CONFIG_EXECUTABLE=${HOME}/prog/mongodb/llvm-project/build/install/bin/llvm-config
ninja -C build
