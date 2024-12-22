cmake_minimum_required(VERSION 3.30)
project(llvm_test)

find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

set(CMAKE_CXX_STANDARD 23)

include_directories(SYSTEM ${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

set(NO_RTTI "-fno-rtti")
add_definitions(${NO_RTTI})

add_executable(llvm_test
        calc/Lexer.cpp
        calc/Lexer.h
        calc/Parser.cpp
        calc/Parser.h
        calc/AST.cpp
        calc/AST.h
        calc/Semantics.cpp
        calc/Semantics.h
        calc/CodeGen.cpp
        calc/CodeGen.h
        calc/Calc.cpp
        calc/rtcalc.c)

llvm_map_components_to_libnames(llvm_libs support core irreader)
target_link_libraries(llvm_test PRIVATE ${llvm_libs})
