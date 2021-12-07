#!/bin/bash
mkdir build
cd build
cmake -G Ninja -D LLVM_CONFIG_EXECUTABLE=/usr/local/opt/llvm/bin/llvm-config ..
ninja
