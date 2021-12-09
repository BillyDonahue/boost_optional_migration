cmake_minimum_required(VERSION 3.5)

#list(APPEND CMAKE_PREFIX_PATH "${boost_optional_migration_Clang_INSTALL_DIR}/lib/cmake/clang/")

#find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)

include_directories(SYSTEM "${LLVM_INCLUDE_DIRS};${CLANG_INCLUDE_DIRS}")

# Use the std that llvm uses internally
set(CMAKE_CXX_STANDARD 14 CACHE STRING "")

# LLVM is normally built without RTTI. Be consistent with that.
if(NOT LLVM_ENABLE_RTTI)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
endif()

message(STATUS "LLVM_INCLUDE_DIRS='${LLVM_INCLUDE_DIRS}'")
message(STATUS "CLANG_INCLUDE_DIRS='${CLANG_INCLUDE_DIRS}'")
message(STATUS "CLANG_LIBS='${CLANG_LIBS}'")
message(STATUS "LLVM_LIBS_CORE='${LLVM_LIBS_CORE}'")
message(STATUS "LLVM_LDFLAGS='${LLVM_LDFLAGS}'")

add_library(
        boost-optional-migration-lib
        SHARED
        utils/utils.cc
        actions/frontendaction.cc
        consumer/consumer.cc
        transformer/transformer.cc
        transformer/functioncalltransformer.cc
        finder/finder.cc
        finder/integervariablefinder.cc
)
target_link_libraries(
        boost-optional-migration-lib
        clangTooling
        ${CLANG_LIBS}
        ${LLVM_LIBS_CORE}
        ${LLVM_LDFLAGS}
)

# Allow undefined symbols in shared objects on Darwin (this is the default
# behaviour on Linux)
#target_link_libraries(boost-optional-migration-lib "$<$<PLATFORM_ID:Darwin>:-undefined dynamic_lookup>")


add_executable(boost-optional-migration main.cc)
target_link_libraries(boost-optional-migration boost-optional-migration-lib)
