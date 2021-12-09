#!/bin/bash
mkdir -p build

LLVM_INSTALL_DIR="${HOME}/prog/mongodb/llvm-project/build/install"
LLVM_CONFIG_EXECUTABLE="${LLVM_INSTALL_DIR}/bin/llvm-config"

cmd=(
        cmake
        -S .
        -B build
        -D LLVM_DIR="${LLVM_INSTALL_DIR}/lib/cmake/llvm"
        -D Clang_DIR="${LLVM_INSTALL_DIR}/lib/cmake/clang"
        -D LLVM_CONFIG_EXECUTABLE="${LLVM_CONFIG_EXECUTABLE}"
)
"${cmd[@]}"
