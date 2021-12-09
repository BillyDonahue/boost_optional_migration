cmake_minimum_required(VERSION 3.5)
project(boost-optional-migration)

list(
    APPEND
    CMAKE_MODULE_PATH
    "${boost_optional_migration_Clang_INSTALL_DIR}"
    "${boost_optional_migration_LLVM_INSTALL_DIR}"
)

add_subdirectory(src)