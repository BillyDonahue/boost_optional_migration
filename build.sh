#!/bin/bash
mkdir -p build

LLVM_INSTALL_DIR="${HOME}/prog/mongodb/llvm-project/build/install"
LLVM_CONFIG_EXECUTABLE="${LLVM_INSTALL_DIR}/bin/llvm-config"
# -D LLVM_CONFIG_EXECUTABLE="${LLVM_CONFIG_EXECUTABLE}"

cmd=(
        cmake
        -G "Unix Makefiles"
        -S .
        -C build
        -D LLVM_DIR="${LLVM_INSTALL_DIR}/lib/cmake/llvm"
        -D Clang_DIR="${LLVM_INSTALL_DIR}/lib/cmake/clang"
)
"${cmd[@]}"
