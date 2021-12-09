#!/bin/bash
mkdir -p build

LLVM_INSTALL_DIR="${HOME}/prog/mongodb/llvm-project/build/install"
LLVM_CONFIG_EXECUTABLE="${LLVM_INSTALL_DIR}/bin/llvm-config"

cmd=(
        cmake
        --log-level=VERBOSE
        -S .
        -B build
        -D boost_optional_migration_Clang_INSTALL_DIR="${LLVM_INSTALL_DIR}/lib/cmake/clang"
        -D boost_optional_migration_LLVM_INSTALL_DIR="${LLVM_INSTALL_DIR}/lib/cmake/llvm"
        #-D LLVM_CONFIG_EXECUTABLE="${LLVM_CONFIG_EXECUTABLE}"
)
"${cmd[@]}"
